# 训练代码结构

本页介绍 `gear_sonic/` 下的 Python 训练代码库，包括目录结构、训练流程、配置系统、核心模块以及评估脚本。

---

# 目录结构

```text
gear_sonic/
├── train_agent_trl.py          # 主训练入口
├── eval_agent_trl.py           # 单个 checkpoint 的评估脚本
├── eval_exp.py                 # Checkpoint 监控（持续评估）
├── config/                     # Hydra 配置层级
│   ├── base.yaml               # 全局默认配置（seed、num_envs、路径等）
│   ├── base_eval.yaml          # 评估专用全局默认配置
│   ├── eval_exp.yaml           # Checkpoint 监控配置
│   ├── base/                   # Hydra 基础配置（输出目录、resolver）
│   ├── algo/                   # PPO 超参数
│   ├── actor_critic/           # Actor-Critic 网络结构配置
│   │   ├── encoders/           # 各编码器 MLP 配置（g1、smpl、teleop）
│   │   ├── decoders/           # 解码器 MLP 配置（g1_kin、g1_dyn）
│   │   ├── critics/            # Critic 主干网络配置
│   │   ├── quantizers/         # FSQ 量化器配置
│   │   └── universal_token/    # 编码器+解码器+量化器组合预设
│   ├── aux_losses/             # 辅助损失定义
│   ├── callbacks/              # 训练回调配置
│   ├── exp/                    # 实验预设（组合所有组件）
│   ├── manager_env/            # 环境 MDP 组件配置
│   ├── opt/                    # 日志配置（wandb）
│   └── trainer/                # Trainer 类选择
├── envs/                       # IsaacLab 环境封装
│   ├── manager_env/
│   │   ├── modular_tracking_env_cfg.py   # 场景、传感器、机器人 articulation 配置
│   │   ├── robots/             # 各机器人配置（g1.py、h2.py）
│   │   └── mdp/                # MDP 组件（见下文）
│   ├── wrapper/
│   │   └── manager_env_wrapper.py  # 面向 RL 的环境封装
│   └── env_utils/              # 关节顺序工具
├── trl/                        # 训练模块（PPO、Actor-Critic、Loss）
│   ├── trainer/
│   │   ├── ppo_trainer.py          # 基础 PPO Trainer
│   │   └── ppo_trainer_aux_loss.py # PPO + 辅助损失（SONIC）
│   ├── modules/
│   │   ├── actor_critic_modules.py     # Actor、Critic 类
│   │   ├── universal_token_modules.py  # UniversalTokenModule（SONIC ATM）
│   │   ├── base_module.py              # 公共 MLP 模块
│   │   └── data_utils.py               # Batch / 数据工具
│   ├── losses/
│   │   └── token_losses.py     # 重建与 latent 辅助损失
│   ├── callbacks/              # 运行时回调
│   │   ├── im_eval_callback.py     # 模仿评估指标
│   │   ├── im_resample_callback.py # 自适应动作重采样
│   │   ├── model_save_callback.py  # Checkpoint 保存
│   │   ├── wandb_callback.py       # W&B 日志
│   │   └── read_eval_callback.py   # 从磁盘读取评估结果
│   └── utils/                  # 数学、旋转、调度工具
├── utils/                      # 公共工具
│   ├── motion_lib/             # Motion library 加载（PKL 格式）
│   ├── mujoco_sim/             # MuJoCo sim-to-sim 桥接
│   └── teleop/                 # VR 遥操作工具
├── data/                       # 机器人模型、URDF/USD 资源
├── data_process/               # 动作数据转换脚本
└── scripts/                    # MuJoCo 仿真循环、杂项工具
```

---

# 训练流程

运行：

```bash
python gear_sonic/train_agent_trl.py +exp=manager/universal_token/all_modes/sonic_release
```

会执行以下步骤：

---

## 1. 配置加载

入口脚本使用：

```python
@hydra.main(config_path="config", config_name="base")
```

`+exp=...` 参数用于选择实验预设，该预设会组合多个子配置：

```text
base.yaml                          # 全局默认配置
  └── +exp=manager/universal_token/all_modes/sonic_release
        ├── /algo: ppo_im_phc      # PPO 超参数
        ├── /actor_critic: universal_token/all_mlp_v1
        │     ├── encoders/g1_mf_mlp, smpl_mlp, teleop_mlp
        │     ├── decoders/g1_kin_mf_mlp, g1_dyn_mlp
        │     ├── quantizers/fsq
        │     └── critics/mlp
        ├── /manager_env: base_env
        │     ├── observations/{tokenizer, policy, critic}
        │     ├── rewards/tracking/base_5point_local_feet_acc
        │     ├── terminations/tracking/base_adaptive_strict_ori_foot_xyz
        │     └── events/tracking/level0_4
        ├── /aux_losses: universal_token/g1_recon_and_all_latent
        ├── /trainer: trl_ppo_aux
        └── /callbacks: model_save, wandb, read_eval, im_resample
```

---

## 2. 仿真器与加速器初始化

配置解析后，脚本会：

1. 从配置字典解析 TRL 的 `PPOConfig` / `ScriptArguments` / `ModelConfig`
2. 创建 HuggingFace `Accelerator` 用于多 GPU 分布式训练（DDP）
3. 启动 IsaacLab 的 `AppLauncher`，初始化 Isaac Sim
4. 将 `config.yaml` 和 `meta.yaml` 保存到实验目录

---

## 3. 环境创建

`create_manager_env()` 会根据环境配置实例化 IsaacLab 的 `ManagerBasedRLEnv`，然后再使用 `ManagerEnvWrapper` 包装：

```text
ManagerBasedRLEnv (IsaacLab)
  └── ManagerEnvWrapper
        ├── 观测空间（policy、critic、tokenizer）
        ├── 动作命令管理器（motion_lib）
        ├── 动作变换模块（可选，用于预训练 ATM）
        └── 键盘与可视化接口
```

---

## 4. Policy 与 Value 网络创建

Actor 和 Critic 根据算法配置实例化。

对于 SONIC 训练，Actor 主干网络为：

```python
UniversalTokenModule
```

示例：

```python
policy = custom_instantiate(config.algo.config.actor, env_config=env.config, ...)
value_model = custom_instantiate(config.algo.config.critic, env_config=env.config, ...)
```

其中：

* `Actor` 使用 `UniversalTokenModule` 作为 backbone，并额外添加对角高斯分布用于探索
* `Critic` 使用独立 MLP backbone

---

## 5. PPO 训练循环

核心训练循环位于：

```python
TRLAuxLossPPOTrainer.train()
```

流程如下：

```text
for iteration in range(num_learning_iterations):

    # 1. Rollout：收集 num_steps_per_env 步 transition
    for step in range(num_steps_per_env):
        actions = policy.rollout(obs_dict)
        obs_dict, rewards, dones, infos = env.step(actions)
        store(obs, actions, rewards, values, log_probs)

    # 2. GAE：计算 advantage 与 return
    advantages = generalized_advantage_estimation(...)

    # 3. PPO 更新
    for epoch in range(num_ppo_epochs):
        for mini_batch in rollout_data:
            policy_loss = ...
            value_loss = ...
            aux_loss = ...

            total_loss = policy_loss \
                       + value_loss_coef * value_loss \
                       + aux_loss_scale * aux_loss

            optimizer.step(total_loss)

    # 4. 后处理
    update_scheduled_params(...)
    callbacks.on_step_end(...)
```

---

# 配置系统

配置系统基于 [Hydra 官方网站](https://hydra.cc?utm_source=chatgpt.com) 的 config group 与组合机制。

---

## 配置层级

| 层级           | 路径                            | 作用                                |
| ------------ | ----------------------------- | --------------------------------- |
| 全局           | `config/base.yaml`            | seed、num_envs、路径、wandb 开关         |
| 算法           | `config/algo/ppo_im_phc.yaml` | PPO 超参数                           |
| Actor-Critic | `config/actor_critic/`        | 网络结构                              |
| 环境           | `config/manager_env/`         | observations、rewards、terminations |
| 辅助损失         | `config/aux_losses/`          | reconstruction 与 latent loss      |
| Trainer      | `config/trainer/`             | Trainer 类型                        |
| Callbacks    | `config/callbacks/`           | checkpoint、评估、日志                  |
| Experiment   | `config/exp/`                 | 实验预设                              |

---

## 关键配置参数

| 参数                        | 默认值    | 含义              |
| ------------------------- | ------ | --------------- |
| `num_envs`                | 4096   | 并行环境数           |
| `num_learning_iterations` | 100000 | 总训练迭代数          |
| `num_steps_per_env`       | 32     | 每轮 rollout 长度   |
| `num_learning_epochs`     | 5      | PPO epoch 数     |
| `num_mini_batches`        | 4      | mini-batch 数    |
| `actor_learning_rate`     | 2e-5   | Actor 学习率       |
| `critic_learning_rate`    | 1e-3   | Critic 学习率      |
| `clip_param`              | 0.2    | PPO clip 参数     |
| `init_noise_std`          | 0.05   | 初始探索噪声          |
| `save_interval`           | 500    | checkpoint 保存间隔 |

---

# Universal Token Module

`UniversalTokenModule` 实现了 SONIC 的 ATM（Action Transform Module），是整个系统的核心结构。

---

## 网络结构

```text
                  ┌─────────────┐
  G1 obs    ───►  │  G1 Encoder │──┐
                  └─────────────┘  │
                  ┌─────────────┐  │    ┌─────────┐     ┌─────────────┐
  Teleop obs───►  │Teleop Encdr │──┼──► │   FSQ   │──►  │ G1 Dynamic  │──► joint actions
                  └─────────────┘  │    │Quantizer│     │   Decoder   │
                  ┌─────────────┐  │    └─────────┘     └─────────────┘
  SMPL obs  ───►  │ SMPL Encoder│──┘          │
                  └─────────────┘             │         ┌─────────────┐
                                              └───────► │G1 Kinematic │──►（仅辅助损失）
                                                        │   Decoder   │
                                                        └─────────────┘
```

---

## 编码器（Encoders）

不同模态输入通过不同编码器映射到统一 latent 空间：

* G1 encoder
* Teleop encoder
* SMPL encoder

每个 encoder 都是一个 MLP。

训练时会根据：

```python
encoder_sample_probs
```

随机采样 encoder。

---

## FSQ Quantizer

FSQ（Finite Scalar Quantization）会将连续 latent 离散化为 token。

特点：

* 每个 latent 维度独立量化
* 每维映射到 `fsq_level_list` 中的离散 level
* 得到紧凑离散 token 表示

---

## 解码器（Decoders）

### G1 Dynamic Decoder

输出：

```text
joint actions
```

部署时真正使用的 decoder。

---

### G1 Kinematic Decoder

重建未来动作帧：

```text
future motion frames
```

仅用于训练辅助损失。

---

## Latent Residual Mode

下游任务（例如 manipulation）可在 token 空间添加 residual：

| 模式                         | 行为                   |
| -------------------------- | -------------------- |
| `post_quantization`        | residual 加在量化后       |
| `pre_quantization`         | residual 加在量化前       |
| `pre_quantization_replace` | residual 完全替换 latent |

---

# 环境结构

环境基于 IsaacLab 的：

```python
ManagerBasedRLEnv
```

采用模块化 MDP 设计。

---

## MDP 组件

位于：

```text
gear_sonic/envs/manager_env/mdp/
```

| 模块              | 配置路径          | 作用                   |
| --------------- | ------------- | -------------------- |
| observations.py | observations/ | 观测项                  |
| actions.py      | actions/      | 动作空间                 |
| rewards.py      | rewards/      | reward               |
| terminations.py | terminations/ | episode 终止条件         |
| events.py       | events/       | domain randomization |
| commands.py     | commands/     | motion command       |
| curriculum.py   | curriculum/   | curriculum           |
| terrain.py      | inline        | 地形                   |
| recorders.py    | recorders/    | 视频录制                 |

---

## Observation Groups

| Group     | 用途                     | 示例                                |
| --------- | ---------------------- | --------------------------------- |
| policy    | policy 输入              | joint_pos、joint_vel               |
| critic    | privileged observation | base_lin_vel、body_pos             |
| tokenizer | tokenizer 输入           | future joint commands、SMPL joints |

---

## Reward Terms

关键 tracking reward：

| Reward                     | 含义                |
| -------------------------- | ----------------- |
| tracking_relative_body_pos | 跟踪身体位置            |
| tracking_relative_body_ori | 跟踪身体姿态            |
| tracking_anchor_pos        | 跟踪 root anchor 位置 |
| tracking_anchor_ori        | 跟踪 root anchor 姿态 |
| tracking_body_linvel       | 跟踪线速度             |
| tracking_body_angvel       | 跟踪角速度             |
| action_rate_l2             | 惩罚动作抖动            |
| feet_acc                   | 惩罚足端加速度           |

---

# Evaluation Scripts

---

## eval_agent_trl.py（单 checkpoint 评估）

用于加载单个 checkpoint 并在 Isaac Sim 中评估：

```bash
python gear_sonic/eval_agent_trl.py +checkpoint=path/to/model.pt +headless=False ++num_envs=1
```

无头渲染：

```bash
python gear_sonic/eval_agent_trl.py \
    +checkpoint=path/to/model.pt \
    +headless=True \
    ++num_envs=16 \
    +run_once=True
```

特点：

* 自动读取训练时的 `config.yaml`
* 自动移除 train-only event
* 支持 worst-case motion 渲染
* 支持 metrics 文件输入

---

## eval_exp.py（Checkpoint 监控）

持续监控实验目录：

```bash
python gear_sonic/eval_exp.py ++experiment_dir=path/to/experiment
```

对于每个新 checkpoint：

1. 运行指标评估
2. 渲染 hardest motions 视频
3. 上传结果到 W&B
4. 标记已评估 checkpoint

---

# 核心类说明

| 类                       | 模块                         | 作用               |
| ----------------------- | -------------------------- | ---------------- |
| `Actor`                 | actor_critic_modules.py    | Policy 网络        |
| `Critic`                | actor_critic_modules.py    | Value 网络         |
| `UniversalTokenModule`  | universal_token_modules.py | SONIC ATM 核心模块   |
| `TRLPPOTrainer`         | ppo_trainer.py             | PPO Trainer      |
| `TRLAuxLossPPOTrainer`  | ppo_trainer_aux_loss.py    | 带辅助损失 PPO        |
| `PolicyAndValueWrapper` | ppo_trainer.py             | DDP 封装           |
| `ManagerEnvWrapper`     | manager_env_wrapper.py     | IsaacLab 与 RL 桥接 |
| `CheckpointEvaluator`   | eval_exp.py                | 自动评估 checkpoint  |

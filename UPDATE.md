# 更新记录

这个文件作为项目后续的大版本改动记录。

## 维护约定

1. 每次较大的代码变动，都在这个文件中追加记录。
2. 每条记录尽量包含：改动目的、涉及文件、核心改动、当前现象或风险。
3. 更新代码时适当补充简短备注，优先解释设计意图，不写低信息量注释。
4. 尽量保持代码风格统一：
   - 延续现有命名方式与缩进风格
   - 相同逻辑采用相近写法
   - 注释语言尽量统一为简洁中文
   - 避免同一模块内同时出现多套明显不同的实现风格
5. 调试时需要source scripts/setup_env.sh
6. 运行mujoco仿真的代码为：
    - source .venv_sim/bin/activate
    - python gear_sonic/scripts/run_sim_loop.py
7. 开启仿真下的控制器代码为:
    - bash deploy.sh sim

## 2026-05-17 HOI 仿真与部署联动

- 改动目的：
  为仿真部署链路增加 `--hoi` 模式，在 carry-box 场景下支持物块/anchor 位姿输出，以及 `sonic_export_carrybox` 动作播放期间的 residual policy 动作叠加。
- 涉及文件：
  `gear_sonic/scripts/run_sim_loop.py`
  `gear_sonic/utils/mujoco_sim/configs.py`
  `gear_sonic/utils/mujoco_sim/base_sim.py`
  `gear_sonic/utils/mujoco_sim/unitree_sdk2py_bridge.py`
  `gear_sonic_deploy/deploy.sh`
  `gear_sonic_deploy/src/g1/g1_deploy_onnx_ref/include/control_policy.hpp`
  `gear_sonic_deploy/src/g1/g1_deploy_onnx_ref/src/g1_deploy_onnx_ref.cpp`
  `docs/source/getting_started/quickstart.md`
- 核心改动：
  `run_sim_loop.py --hoi` 会切换到 `scene_resmimic_carry_box.xml`，关闭手部自由度，并通过 DDS 额外发布 `rt/resmimic/object_pose` 与 `rt/resmimic/anchor_pose`。
  MuJoCo 仿真增加了 HOI 位姿调试输出，并支持在 viewer 中按 `R` 重置机器人与物块。
  `deploy.sh sim --hoi` 会把 `--hoi` 和 residual policy 路径传给部署程序。
  部署程序新增 HOI pose 订阅、163 维 residual 观测构造，以及仅在 `sonic_export_carrybox` 动作播放期间叠加 `residual_policy.onnx` 输出。
- 当前现象或风险：
  HOI residual 依赖仿真侧持续发布 `object_pose/anchor_pose`，如果位姿话题缺失或超时，会自动退回 base policy。
  当前 `--hoi` 仅面向 MuJoCo 仿真链路，未对真机链路做支持。

## 2026-05-17 HOI 场景内置与仿真修复

- 改动目的：
  修复 `python gear_sonic/scripts/run_sim_loop.py --hoi` 启动后 29 维/43 维力矩上限不匹配的问题，并把 carry-box 场景及依赖资产收进仓库，去掉对外部 `unitree_rl_lab` 路径的依赖。
- 涉及文件：
  `.gitignore`
  `gear_sonic/scripts/run_sim_loop.py`
  `gear_sonic/utils/mujoco_sim/base_sim.py`
  `gear_sonic/data/robot_model/model_data/g1/scene_resmimic_carry_box.xml`
  `gear_sonic/data/robot_model/model_data/g1/g1_29dof.xml`
  `gear_sonic/data/robot_model/model_data/objects/largebox/urdf/largebox.obj`
  `gear_sonic/data/robot_model/model_data/objects/largebox/urdf/largebox.xml`
  `gear_sonic/data/robot_model/model_data/objects/largebox/urdf/largebox.urdf`
  `docs/source/getting_started/quickstart.md`
- 核心改动：
  `--hoi` 模式下把 `motor_effort_limit_list` 同步裁到 `NUM_MOTORS=29`，避免仿真主循环在 `np.clip` 时出现 `(29,)` 对 `(43,)` 的广播错误。
  `--hoi` 模式额外把 `SIMULATE_DT` 固定为 `0.002s`，修复 carry-box 场景在默认 `0.005s` 步长下会在 `0.065s` 附近出现 `QACC` 爆炸的问题。
  仿真初始化阶段新增 `motor_effort_limit_list` 长度检查，后续如果再出现配置维度不一致，会直接给出明确报错。
  新增仓库内的 `scene_resmimic_carry_box.xml`、`g1_29dof.xml` 和 `largebox` 资产副本，并把 scene 中的物块 mesh 引用改成 repo 内相对路径。
  `.gitignore` 中为这批 HOI 资产增加了例外规则，避免文件被 `data/` 通配规则吞掉后无法纳入版本管理。
  `run_sim_loop.py --hoi` 现在默认加载仓库内的 HOI scene，不再依赖 `/home/wan/Documents/unitree_rl_lab/...`。
- 当前现象或风险：
  这次只修了 HOI 仿真场景下的力矩维度问题，DDS 初始化报出的网卡/Domain 警告仍取决于本机 CycloneDDS 网络配置。

## 2026-05-17 MuJoCo 关节调试导出

- 改动目的：
  为 `python gear_sonic/scripts/run_sim_loop.py` 和 `python gear_sonic/scripts/run_sim_loop.py --hoi` 增加按键调试入口，便于在 viewer 中抓取当前 29 个 body joints 的目标值、实测值和力矩裁剪情况。
- 涉及文件：
  `gear_sonic/utils/mujoco_sim/base_sim.py`
- 核心改动：
  在 MuJoCo viewer 中按 `2` 会触发一次 29 关节快照导出，按键重复事件会连续追加多组快照。
  调试 CSV 会写到 `outputs/sim_joint_debug/`，文件带表头，包含 `q_target`、`q_measured`、`tau_raw`、`tau_applied` 和 `clip_applied`。
  每次导出会打印 CSV 路径和 snapshot 编号，方便对照当前动作阶段。
- 当前现象或风险：
  当前依赖 GLFW 的按键重复事件来实现“按住 2 连续记录”；如果系统没有开启按键重复，单次按下 `2` 只会记录一组快照。

## 2026-05-17 HOI 右臂力矩上限映射修复

- 改动目的：
  修复 `python gear_sonic/scripts/run_sim_loop.py --hoi` 下 43 维 `motor_effort_limit_list` 被错误截成前 29 维，导致右臂 7 个关节误用左手手指力矩上限的问题。
- 涉及文件：
  `gear_sonic/scripts/run_sim_loop.py`
- 核心改动：
  HOI 模式下不再直接使用 `motor_effort_limit_list[:29]`，而是按原始配置中的顺序重组为：
  左侧 body 22 维 + 右侧 body 7 维。
  这样 `right_shoulder_pitch_joint` 到 `right_wrist_yaw_joint` 会重新使用 `25/25/25/25/25/5/5` 的正确上限，不再误用 `2.45/0.7/...` 的左手手指上限。
- 当前现象或风险：
  这次修复的是 HOI 仿真侧 body 力矩上限映射错误；如果右臂仍然动作受限，后续需要继续结合 `outputs/sim_joint_debug/*.csv` 检查接触约束和动作目标本身。

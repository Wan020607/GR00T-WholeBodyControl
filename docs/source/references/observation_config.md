# 观测配置（Observation Configuration）

本页面是部署系统中观测（observations）配置的完整参考，涵盖 YAML 配置格式、编码器系统、所有可用观测类型，以及如何创建自定义观测。

---

## 配置格式

观测通过 `--obs-config <path>` 指定的 YAML 文件进行配置。每个观测包含一个 `name`（必须匹配已注册的观测）和一个 `enabled` 开关。

---

### 基础结构

```yaml
observations:
  - name: "motion_joint_positions"
    enabled: true
  - name: "motion_joint_velocities"
    enabled: true
  - name: "motion_anchor_orientation"
    enabled: true
  - name: "base_angular_velocity"
    enabled: true
  - name: "body_joint_positions"
    enabled: true
  - name: "body_joint_velocities"
    enabled: true
  - name: "last_actions"
    enabled: true
```

**关键规则：**

* 观测会按 YAML 中的顺序拼接，形成 policy 输入向量。
* offset 自动计算，无需手动管理。
* 所有启用观测的总维度必须与 ONNX 模型输入匹配。
* `enabled: false` 的观测会被完全忽略。
* 调整顺序会改变输入张量布局（offset 重新分配）。

---

## 带编码器（Token-based Policy）

如果 policy 使用 encoder 将观测压缩为 token，需要添加 `encoder:` 配置段。

```yaml
observations:
  - name: "token_state"           # encoder 输出（维度见下）
    enabled: true
  - name: "base_angular_velocity"
    enabled: true
  - name: "body_joint_positions"
    enabled: true
  - name: "body_joint_velocities"
    enabled: true
  - name: "last_actions"
    enabled: true

encoder:
  dimension: 64       # token 输出维度
  use_fp16: false     # TensorRT 精度（可选）
  encoder_observations:
    - name: "motion_joint_positions_10frame_step5"
      enabled: true
    - name: "motion_joint_velocities_10frame_step5"
      enabled: true
    - name: "motion_anchor_orientation_10frame_step5"
      enabled: true
    - name: "motion_root_z_position_10frame_step5"
      enabled: true
  encoder_modes:
    - name: "g1"
      mode_id: 0
      required_observations:
        - motion_joint_positions_10frame_step5
        - motion_joint_velocities_10frame_step5
        - motion_anchor_orientation_10frame_step5
        - motion_root_z_position_10frame_step5
```

---

### encoder 字段说明

| 字段                     | 含义                                                   |
| ---------------------- | ---------------------------------------------------- |
| `dimension`            | token 输出维度，必须与 encoder ONNX 输出一致；为 0 或省略表示禁用 encoder |
| `use_fp16`             | encoder TensorRT 是否使用 FP16（默认 false）                 |
| `encoder_observations` | 输入 encoder 的观测集合（policy 观测的子集/超集）                    |
| `encoder_modes`        | （可选）不同模式的观测需求配置                                      |

---

运行时使用：

```bash
--encoder-file <path>
```

加载 encoder 模型。如果不提供，则 `token_state` 可以通过 ROS2/ZMQ 外部提供。

---

### 命名规则

多帧观测格式：

```
{base_name}_{N}frame_step{S}
```

* **N**：帧数（时间窗口长度）
* **S**：采样步长（控制 tick，50Hz → step5 = 0.1s）
* 无后缀 = 单帧当前值

例如：

`motion_joint_positions_10frame_step5`

表示：

* 10 帧
* 每 5 tick 采样一次（0.1s）
* 总覆盖约 0.9s 历史/未来窗口

如果超出 motion 长度，会重复最后一帧。

---

## Encoder & Token 观测

| 名称               | 维度     | 说明                                                |
| ---------------- | ------ | ------------------------------------------------- |
| `token_state`    | config | encoder 输出 token（维度由 YAML `encoder.dimension` 决定） |
| `encoder_mode`   | 3      | 当前 encoder mode ID + padding                      |
| `encoder_mode_4` | 4      | mode ID + padding                                 |

---

## Motion Reference 观测

来自当前 motion sequence（reference / planner / ZMQ stream）。所有 joint 使用 IsaacLab 的 29 关节顺序。

---

### 关节位置（Joint Positions）

| 名称                                               | 维度  | 帧数 | 步长 | 说明      |
| ------------------------------------------------ | --- | -- | -- | ------- |
| `motion_joint_positions`                         | 29  | 1  | -  | 当前关节位置  |
| `motion_joint_positions_3frame_step1`            | 87  | 3  | 1  | 连续 3 帧  |
| `motion_joint_positions_5frame_step5`            | 145 | 5  | 5  | 0.1s 间隔 |
| `motion_joint_positions_10frame_step1`           | 290 | 10 | 1  | 连续 10 帧 |
| `motion_joint_positions_10frame_step5`           | 290 | 10 | 5  | 0.1s 间隔 |
| `motion_joint_positions_lowerbody_10frame_step1` | 120 | 10 | 1  | 下半身关节   |
| `motion_joint_positions_wrists_10frame_step1`    | 60  | 10 | 1  | 手腕关节    |

```note
当开启上半身 teleoperation（ZMQ/ROS2）时，上半身关节会被外部输入覆盖。
```

---

### 关节速度（Joint Velocities）

| 名称                                      | 维度  | 帧数 | 步长 |
| --------------------------------------- | --- | -- | -- |
| `motion_joint_velocities`               | 29  | 1  | -  |
| `motion_joint_velocities_3frame_step1`  | 87  | 3  | 1  |
| `motion_joint_velocities_5frame_step5`  | 145 | 5  | 5  |
| `motion_joint_velocities_10frame_step1` | 290 | 10 | 1  |
| `motion_joint_velocities_10frame_step5` | 290 | 10 | 5  |

---

### Anchor 姿态

表示相对基座的旋转（6D rotation matrix 前两列）。

| 名称                                        | 维度 |
| ----------------------------------------- | -- |
| `motion_anchor_orientation`               | 6  |
| `motion_anchor_orientation_10frame_step1` | 60 |
| `motion_anchor_orientation_10frame_step5` | 60 |
| `motion_anchor_orientation_heading`       | 6  |
| `motion_anchor_orientation_refheading`    | 6  |

---

### Root Z 位置

| 名称                                     | 维度 |
| -------------------------------------- | -- |
| `motion_root_z_position`               | 1  |
| `motion_root_z_position_10frame_step5` | 10 |

---

## SMPL 观测

来源于 SMPL motion 数据（需要 smpl_pose / smpl_joint 文件）。

---

### SMPL 关节位置

| 名称                                | 维度  |
| --------------------------------- | --- |
| `smpl_joints`                     | 72  |
| `smpl_joints_10frame_step5`       | 720 |
| `smpl_joints_lower_10frame_step1` | 270 |

---

### SMPL Pose（轴角）

| 名称                        | 维度  |
| ------------------------- | --- |
| `smpl_pose`               | 63  |
| `smpl_pose_10frame_step5` | 630 |

---

### SMPL 别名

| 名称                                      | 维度 |
| --------------------------------------- | -- |
| `smpl_root_z_10frame_step1`             | 10 |
| `smpl_anchor_orientation_10frame_step1` | 60 |

---

## VR 观测

### 3点 VR

| 名称                           | 维度 |
| ---------------------------- | -- |
| `vr_3point_local_target`     | 9  |
| `vr_3point_local_orn_target` | 12 |
| `vr_3point_compliance`       | 3  |

---

### 5点 VR

| 名称                           | 维度 |
| ---------------------------- | -- |
| `vr_5point_local_target`     | 15 |
| `vr_5point_local_orn_target` | 20 |

---

## 机器人状态历史观测

来自 StateLogger 环形缓冲区。

---

### 当前状态

| 名称                      | 维度 |
| ----------------------- | -- |
| `base_angular_velocity` | 3  |
| `body_joint_positions`  | 29 |
| `body_joint_velocities` | 29 |
| `last_actions`          | 29 |
| `gravity_dir`           | 3  |

---

### 历史帧（4帧）

| 名称                                       | 维度  |
| ---------------------------------------- | --- |
| `his_body_joint_positions_4frame_step1`  | 116 |
| `his_base_angular_velocity_4frame_step1` | 12  |

---

### 历史帧（10帧）

| 名称                                       | 维度  |
| ---------------------------------------- | --- |
| `his_body_joint_positions_10frame_step1` | 290 |
| `his_last_actions_10frame_step1`         | 290 |

---

## 创建自定义观测

---

### Step 1：编写 gather 函数

```cpp
bool MyObservation(std::vector<double>& target_buffer, size_t offset) {
    target_buffer[offset + 0] = ...;
    target_buffer[offset + 1] = ...;
    return true;
}
```

---

### 可用数据源

* `state_logger_`（机器人历史状态）
* `current_motion_`
* `operator_state`
* VR buffer
* planner buffer

---

### Step 2：注册观测

```cpp
{"my_obs", 3,
 [this](std::vector<double>& buf, size_t offset) {
     return MyObservation(buf, offset);
 }},
```

---

### Step 3：YAML 使用

```yaml
observations:
  - name: "my_obs"
    enabled: true
```

---

### 注意事项

* 维度必须固定
* 不要在循环中动态分配内存
* 返回 false 会停止控制循环
* 50Hz 热路径不能做耗时操作
* 需要重编译：

```bash
just build
```

---

## 示例配置

### Minimal（154D）

```yaml
observations:
  - name: "motion_joint_positions"
  - name: "motion_joint_velocities"
  - name: "motion_anchor_orientation"
  - name: "base_angular_velocity"
  - name: "body_joint_positions"
  - name: "body_joint_velocities"
  - name: "last_actions"
```

---

### Token Policy

```yaml
observations:
  - name: "token_state"
  - name: "base_angular_velocity"
  - name: "body_joint_positions"
  - name: "body_joint_velocities"
  - name: "last_actions"

encoder:
  dimension: 64
  encoder_observations:
    - name: "motion_joint_positions_10frame_step5"
```

---

### VR Policy

```yaml
observations:
  - name: "token_state"
  - name: "vr_3point_local_target"
  - name: "vr_3point_local_orn_target"
  - name: "vr_3point_compliance"
```

---

如果你下一步想要，我可以帮你把这套 observation 系统**画成一张结构图（policy / encoder / motion / VR / robot state 全链路）**，会更直观。

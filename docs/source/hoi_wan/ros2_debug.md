# ROS2 Planner Debug

这个文档说明新的 ROS2 方案 B 调试接口。现在 ROS2 控制被拆成了两条独立 topic：

- `ControlPolicy/planner_command`
  - 直接控制 planner
  - 用于 `slow walk / walk / run / squat / kneel / idle`
- `ControlPolicy/action_command`
  - 触发一次性 reference motion 播放
  - 目前默认示例是 `sonic_export_carrybox`

旧的 `ControlPolicy/upper_body_pose` 仍然保留给兼容的 VR / teleop 输入，但新的 `ros2_motion_debugger` 默认不再使用它。

## 前提

必须先加载部署环境：

```bash
cd /home/wan/Documents/GR00T-WholeBodyControl/gear_sonic_deploy
source scripts/setup_env.sh
```

否则 `ros2` CLI 和调试器可能看不到部署程序里的 ROS2 节点。

## 构建

```bash
cd /home/wan/Documents/GR00T-WholeBodyControl/gear_sonic_deploy
source scripts/setup_env.sh
just build
```

可执行文件：

```bash
./target/release/ros2_motion_debugger
```

## 启动顺序

### 1. 启动仿真

```bash
cd /home/wan/Documents/GR00T-WholeBodyControl
source .venv_sim/bin/activate
python gear_sonic/scripts/run_sim_loop.py
```

### 2. 启动部署

```bash
cd /home/wan/Documents/GR00T-WholeBodyControl/gear_sonic_deploy
bash deploy.sh --input-type manager sim
```

部署起来后：

1. 按 `]` 启动控制系统
2. 按 `$` 切到 ROS2 接口

### 3. 启动调试器

```bash
cd /home/wan/Documents/GR00T-WholeBodyControl/gear_sonic_deploy
source scripts/setup_env.sh
just run ros2_motion_debugger
```

也可以直接运行：

```bash
./target/release/ros2_motion_debugger
```

可选参数：

```bash
./target/release/ros2_motion_debugger \
  --planner-topic ControlPolicy/planner_command \
  --action-topic ControlPolicy/action_command \
  --hz 50
```

## 话题格式

外层 ROS2 类型都还是标准的：

- `std_msgs/msg/ByteMultiArray`

内层 `data` 是项目自定义的 `msgpack` payload。

### planner_command

`ControlPolicy/planner_command` 的 payload：

```python
{
  "planner_mode": 1,
  "movement_direction": [1.0, 0.0, 0.0],
  "facing_direction": [1.0, 0.0, 0.0],
  "movement_speed": 0.3,
  "height": -1.0,
  "control_action": 0,
  "ros_timestamp": 1712345678.123,
}
```

字段说明：

- `planner_mode`
  - `0 = idle`
  - `1 = slow walk`
  - `2 = walk`
  - `3 = run`
  - `4 = squat`
  - `6 = kneel`
- `movement_direction`
  - planner 最终使用的移动方向
- `facing_direction`
  - planner 最终使用的朝向方向
- `movement_speed`
  - `-1` 表示用 planner 默认速度
- `height`
  - `-1` 表示用 planner 默认高度
- `control_action`
  - `0 = none`
  - `1 = start`
  - `2 = stop`
  - `3 = toggle`

### action_command

`ControlPolicy/action_command` 的 payload：

```python
{
  "action": "play_once",
  "motion_name": "sonic_export_carrybox",
  "request_id": 1,
  "ros_timestamp": 1712345678.456,
}
```

语义：

- `action = "play_once"`
  - 播放一次 reference motion
- `motion_name`
  - 对应 `MotionDataReader` 中加载到的 motion 名称
- `request_id`
  - one-shot 去重 id

## 调试器命令

### 基础

```text
help
status
quit
exit
```

### 控制启停

```text
start
stop
toggle
sync on
sync off
```

### Planner mode

```text
mode idle
mode slow
mode walk
mode run
mode squat
mode kneel
```

### 速度和高度

```text
speed 0.3
speed default
height 0.6
height default
stand
squat 0.60
kneel 0.30
```

### 方向控制

```text
move f 0.3
move fl 0.3
move r 0.4
idle
face 90
turn -45
```

说明：

- `move` 会按照当前 `facing_angle` 生成 world-frame 的 `movement_direction`
- `face` 直接设置绝对朝向角
- `turn` 是相对角度增量，单位是度

### 一次性动作播放

```text
action carrybox
action sonic_export_carrybox
```

`action carrybox` 会向 `ControlPolicy/action_command` 发一条 one-shot 消息，部署程序收到后会：

1. 关闭 planner
2. 切到 `sonic_export_carrybox`
3. 从第 0 帧开始播放
4. 播放一次后自动停在末尾，再复位到第 0 帧

## 推荐流程

### 只测 planner 走路

```text
1. 启动 sim
2. 启动 deploy.sh --input-type manager sim
3. 按 ] 启动控制
4. 按 $ 切到 ROS2
5. 启动 ros2_motion_debugger
6. 输入:
   start
   mode walk
   move f
```

### 测 run

```text
start
mode run
speed 2.0
move f
```

### 播放一次 carrybox

```text
action carrybox
```

如果你想回到 planner：

```text
start
mode slow
move f
```

## 调试输出对应关系

新的 planner topic 会直接对应部署程序里的：

```text
[ROS2 DEBUG] Planner control values:
  Final mode: ...
  Final speed: ...
  Final height: ...
  Movement direction: ...
  Facing direction: ...
```

如果日志里出现：

```text
Source: planner_command
```

说明当前控制来自新的 planner-only ROS2 接口，而不是旧的 `upper_body_pose`。

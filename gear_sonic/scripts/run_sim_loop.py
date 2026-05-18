"""Entry point for running a MuJoCo simulation loop with the G1 robot model.

Parses a YAML-based WBC config via tyro CLI, instantiates the G1 robot model,
and launches the simulator (optionally with offscreen image publishing).
"""

from pathlib import Path
from typing import Dict

import tyro

from gear_sonic.utils.mujoco_sim.simulator_factory import SimulatorFactory, init_channel
from gear_sonic.utils.mujoco_sim.configs import SimLoopConfig
from gear_sonic.data.robot_model.instantiation.g1 import (
    instantiate_g1_robot_model,
)
from gear_sonic.data.robot_model.robot_model import RobotModel

ArgsConfig = SimLoopConfig

HOI_SCENE_XML = Path(
    "gear_sonic/data/robot_model/model_data/g1/scene_resmimic_carry_box.xml"
)
HOI_OBJECT_POSE_TOPIC = "rt/resmimic/object_pose"
HOI_ANCHOR_POSE_TOPIC = "rt/resmimic/anchor_pose"
HOI_OBJECT_BODY_NAME = "carry_box"
HOI_ANCHOR_BODY_NAME = "pelvis"
HOI_SIMULATE_DT = 0.002


class SimWrapper:
    def __init__(self, robot_model: RobotModel, env_name: str, config: Dict[str, any], **kwargs):
        self.robot_model = robot_model
        self.config = config

        init_channel(config=self.config)

        # Create simulator using factory
        self.sim = SimulatorFactory.create_simulator(
            config=self.config,
            env_name=env_name,
            **kwargs,
        )


def main(config: ArgsConfig):
    wbc_config = config.load_wbc_yaml()
    # NOTE: we will override the interface to local if it is not specified
    wbc_config["ENV_NAME"] = config.env_name

    if config.hoi:
        wbc_config["ROBOT_SCENE"] = str(HOI_SCENE_XML)
        # carry-box 场景在 0.005s 步长下会数值发散，沿用 MuJoCo 默认 0.002s 更稳定。
        wbc_config["SIMULATE_DT"] = HOI_SIMULATE_DT
        original_num_hand_motors = int(wbc_config.get("NUM_HAND_MOTORS", 0))
        wbc_config["NUM_HAND_MOTORS"] = 0
        wbc_config["NUM_HAND_JOINTS"] = 0
        wbc_config["with_hands"] = False
        # 原始 43 维力矩上限顺序是：
        #   左侧 body 22 维 + 左手 7 维 + 右侧 body 7 维 + 右手 7 维
        # HOI 29 维 body 需要跳过两段手部上限，不能直接取前 29 维。
        expected_motor_count = int(wbc_config["NUM_MOTORS"])
        motor_effort_limits = list(wbc_config.get("motor_effort_limit_list", []))
        required_limit_count = expected_motor_count + original_num_hand_motors * 2
        if len(motor_effort_limits) < required_limit_count:
            raise ValueError(
                "HOI scene requires motor_effort_limit_list to cover at least "
                f"{required_limit_count} entries, got {len(motor_effort_limits)}."
            )
        body_prefix_count = expected_motor_count - original_num_hand_motors
        if body_prefix_count < 0:
            raise ValueError(
                "HOI scene received an invalid body/hand split: "
                f"NUM_MOTORS={expected_motor_count}, NUM_HAND_MOTORS={original_num_hand_motors}."
            )
        body_suffix_count = expected_motor_count - body_prefix_count
        left_body_limits = motor_effort_limits[:body_prefix_count]
        right_body_limits = motor_effort_limits[
            body_prefix_count + original_num_hand_motors :
            body_prefix_count + original_num_hand_motors + body_suffix_count
        ]
        body_motor_effort_limits = left_body_limits + right_body_limits
        if len(body_motor_effort_limits) != expected_motor_count:
            raise ValueError(
                "HOI scene failed to rebuild the 29-dof body effort limits: "
                f"expected {expected_motor_count}, got {len(body_motor_effort_limits)}."
            )
        wbc_config["motor_effort_limit_list"] = body_motor_effort_limits
        wbc_config["HOI_ENABLED"] = True
        wbc_config["OBJECT_POSE_TOPIC"] = HOI_OBJECT_POSE_TOPIC
        wbc_config["OBJECT_BODY_NAME"] = HOI_OBJECT_BODY_NAME
        wbc_config["ANCHOR_POSE_TOPIC"] = HOI_ANCHOR_POSE_TOPIC
        wbc_config["ANCHOR_BODY_NAME"] = HOI_ANCHOR_BODY_NAME
        wbc_config["POSE_DEBUG_PRINT_INTERVAL_SEC"] = 1.0
        print(f"[HOI] Loaded scene: {HOI_SCENE_XML}")
        print(f"[HOI] Using simulate_dt={HOI_SIMULATE_DT:.3f}s for carry-box stability")
        print(
            f"[HOI] Publishing object pose on '{HOI_OBJECT_POSE_TOPIC}' and anchor pose on '{HOI_ANCHOR_POSE_TOPIC}'"
        )

    if config.enable_image_publish:
        assert (
            config.enable_offscreen
        ), "enable_offscreen must be True when enable_image_publish is True"

    robot_model = instantiate_g1_robot_model()

    sim_wrapper = SimWrapper(
        robot_model=robot_model,
        env_name=config.env_name,
        config=wbc_config,
        onscreen=wbc_config.get("ENABLE_ONSCREEN", True),
        offscreen=wbc_config.get("ENABLE_OFFSCREEN", False),
        enable_image_publish=config.enable_image_publish,
    )
    # Start simulator as independent process
    SimulatorFactory.start_simulator(
        sim_wrapper.sim,
        as_thread=False,
        enable_image_publish=config.enable_image_publish,
        mp_start_method=config.mp_start_method,
        camera_port=config.camera_port,
    )


if __name__ == "__main__":
    config = tyro.cli(ArgsConfig)
    main(config)

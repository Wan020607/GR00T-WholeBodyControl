#!/usr/bin/env python3

import argparse

import rclpy
from rclpy.node import Node

from benchmark_msg.msg import BenchmarkParams


class BenchmarkParamsPublisher(Node):
    def __init__(self, args: argparse.Namespace) -> None:
        super().__init__("benchmark_params_publisher")
        self._publisher = self.create_publisher(
            BenchmarkParams, "benchmark_params", 10
        )
        self._timer = self.create_timer(args.period, self._publish_once)
        self._message = BenchmarkParams()
        self._message.enable_adaptative = args.enable_adaptative
        self._message.full_payload = args.full_payload
        self._message.mu = args.mu
        self._message.mu_zone1 = args.mu_zone1
        self._message.mu_zone2 = args.mu_zone2
        self._message.mu_zone3 = args.mu_zone3
        self._message.new_vel_max = args.new_vel_max
        self._message.new_w_max = args.new_w_max
        self._message.dist_obst = args.dist_obst
        self._publish_once()

    def _publish_once(self) -> None:
        self._publisher.publish(self._message)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Publish adaptive TEB benchmark parameters."
    )
    parser.add_argument("--enable-adaptative", action="store_true")
    parser.add_argument("--full-payload", action="store_true")
    parser.add_argument("--mu", type=float, default=0.0)
    parser.add_argument("--mu-zone1", type=float, default=0.0)
    parser.add_argument("--mu-zone2", type=float, default=0.0)
    parser.add_argument("--mu-zone3", type=float, default=0.0)
    parser.add_argument("--new-vel-max", type=float, default=100.0)
    parser.add_argument("--new-w-max", type=float, default=100.0)
    parser.add_argument("--dist-obst", type=float, default=0.0)
    parser.add_argument("--period", type=float, default=0.5)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    rclpy.init()
    node = BenchmarkParamsPublisher(args)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()

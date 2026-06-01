#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/byte_multi_array.hpp>

#include <msgpack.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace {

constexpr int kControlActionNone = 0;
constexpr int kControlActionStart = 1;
constexpr int kControlActionStop = 2;
constexpr int kControlActionToggle = 3;

constexpr int kModeIdle = 0;
constexpr int kModeSlowWalk = 1;
constexpr int kModeWalk = 2;
constexpr int kModeRun = 3;
constexpr int kModeIdleSquat = 4;
constexpr int kModeIdleKneel = 6;

struct DebuggerState {
  int planner_mode = kModeIdle;
  std::array<double, 3> movement_direction{0.0, 0.0, 0.0};
  double movement_speed = -1.0;
  double height = -1.0;
  double facing_angle = 0.0;
  bool expected_control_active = false;
  int pending_control_action = kControlActionNone;
};

struct PlannerPreview {
  int final_mode = kModeIdle;
  double final_speed = -1.0;
  double final_height = -1.0;
  std::array<double, 3> movement_direction{0.0, 0.0, 0.0};
  std::array<double, 3> facing_direction{1.0, 0.0, 0.0};
};

struct Options {
  std::string planner_topic = "ControlPolicy/planner_command";
  std::string action_topic = "ControlPolicy/action_command";
  double publish_hz = 50.0;
};

std::string trim(const std::string& input) {
  const auto first = input.find_first_not_of(" \t\r\n");
  if (first == std::string::npos) {
    return "";
  }
  const auto last = input.find_last_not_of(" \t\r\n");
  return input.substr(first, last - first + 1);
}

std::vector<std::string> split_ws(const std::string& line) {
  std::istringstream iss(line);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::optional<double> parse_double(const std::string& token) {
  char* end = nullptr;
  const double value = std::strtod(token.c_str(), &end);
  if (end == token.c_str() || *end != '\0') {
    return std::nullopt;
  }
  return value;
}

double normalize_angle(double angle) {
  while (angle > M_PI) {
    angle -= 2.0 * M_PI;
  }
  while (angle < -M_PI) {
    angle += 2.0 * M_PI;
  }
  return angle;
}

std::array<double, 3> facing_direction_from_angle(double angle) {
  return {std::cos(angle), std::sin(angle), 0.0};
}

std::array<double, 3> relative_move_direction(const std::string& dir, double facing_angle) {
  double offset = 0.0;
  if (dir == "f") {
    offset = 0.0;
  } else if (dir == "fl") {
    offset = M_PI / 4.0;
  } else if (dir == "l") {
    offset = M_PI / 2.0;
  } else if (dir == "bl") {
    offset = 3.0 * M_PI / 4.0;
  } else if (dir == "b") {
    offset = M_PI;
  } else if (dir == "br") {
    offset = -3.0 * M_PI / 4.0;
  } else if (dir == "r") {
    offset = -M_PI / 2.0;
  } else if (dir == "fr") {
    offset = -M_PI / 4.0;
  } else {
    return {0.0, 0.0, 0.0};
  }

  const double world_angle = normalize_angle(facing_angle + offset);
  return {std::cos(world_angle), std::sin(world_angle), 0.0};
}

double sanitize_speed_for_mode(int mode, double requested_speed) {
  if (mode == kModeIdle || mode == kModeIdleSquat || mode == kModeIdleKneel) {
    return -1.0;
  }
  if (requested_speed < 0.0) {
    return -1.0;
  }
  if (mode == kModeSlowWalk) {
    return std::clamp(requested_speed, 0.2, 0.8);
  }
  if (mode == kModeRun) {
    return std::clamp(requested_speed, 1.5, 3.0);
  }
  return requested_speed;
}

double sanitize_height_for_mode(int mode, double requested_height) {
  if (mode == kModeIdle || mode == kModeSlowWalk || mode == kModeWalk || mode == kModeRun) {
    return -1.0;
  }
  if (requested_height < 0.0) {
    return mode == kModeIdleSquat ? 0.60 : 0.30;
  }
  return std::clamp(requested_height, 0.10, 0.88);
}

std::string planner_mode_name(int mode) {
  switch (mode) {
    case kModeIdle:
      return "idle";
    case kModeSlowWalk:
      return "slow_walk";
    case kModeWalk:
      return "walk";
    case kModeRun:
      return "run";
    case kModeIdleSquat:
      return "squat";
    case kModeIdleKneel:
      return "kneel";
    default:
      return "unknown";
  }
}

PlannerPreview compute_preview(const DebuggerState& state) {
  PlannerPreview preview;
  preview.final_mode = state.planner_mode;
  preview.movement_direction = state.movement_direction;
  preview.facing_direction = facing_direction_from_angle(state.facing_angle);
  preview.final_speed = sanitize_speed_for_mode(state.planner_mode, state.movement_speed);
  preview.final_height = sanitize_height_for_mode(state.planner_mode, state.height);
  return preview;
}

std::vector<uint8_t> pack_planner_command(const DebuggerState& state, double ros_timestamp, int control_action) {
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> pk(&sbuf);

  pk.pack_map(7);

  pk.pack(std::string("planner_mode"));
  pk.pack(state.planner_mode);

  pk.pack(std::string("movement_direction"));
  pk.pack(std::vector<double>{state.movement_direction[0], state.movement_direction[1], state.movement_direction[2]});

  const auto facing_direction = facing_direction_from_angle(state.facing_angle);
  pk.pack(std::string("facing_direction"));
  pk.pack(std::vector<double>{facing_direction[0], facing_direction[1], facing_direction[2]});

  pk.pack(std::string("movement_speed"));
  pk.pack(state.movement_speed);

  pk.pack(std::string("height"));
  pk.pack(state.height);

  pk.pack(std::string("control_action"));
  pk.pack(control_action);

  pk.pack(std::string("ros_timestamp"));
  pk.pack(ros_timestamp);

  return {reinterpret_cast<const uint8_t*>(sbuf.data()),
          reinterpret_cast<const uint8_t*>(sbuf.data()) + sbuf.size()};
}

std::vector<uint8_t> pack_action_command(const std::string& motion_name, uint64_t request_id, double ros_timestamp) {
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> pk(&sbuf);

  pk.pack_map(4);
  pk.pack(std::string("action"));
  pk.pack(std::string("play_once"));
  pk.pack(std::string("motion_name"));
  pk.pack(motion_name);
  pk.pack(std::string("request_id"));
  pk.pack(request_id);
  pk.pack(std::string("ros_timestamp"));
  pk.pack(ros_timestamp);

  return {reinterpret_cast<const uint8_t*>(sbuf.data()),
          reinterpret_cast<const uint8_t*>(sbuf.data()) + sbuf.size()};
}

void print_help() {
  std::cout
      << "Commands:\n"
      << "  help                              Show this help\n"
      << "  status                            Print current planner command state\n"
      << "  start | stop | toggle             Send one control_action pulse\n"
      << "  sync on|off                       Only update local expected control state\n"
      << "  mode idle|slow|walk|run           Set locomotion mode\n"
      << "  mode squat|kneel                  Set static mode\n"
      << "  speed <value>|default             Set planner speed (-1 for default)\n"
      << "  height <value>|default            Set planner height (-1 for default)\n"
      << "  stand                             Set mode idle and height default\n"
      << "  squat [height]                    Set squat mode\n"
      << "  kneel [height]                    Set kneel mode\n"
      << "  move <dir> [speed]                dir in {f,b,l,r,fl,fr,bl,br}\n"
      << "  idle                              Zero movement_direction\n"
      << "  face <deg>                        Set absolute facing angle in degrees\n"
      << "  turn <deg>                        Add relative facing angle in degrees\n"
      << "  action carrybox                   Play sonic_export_carrybox once\n"
      << "  action <motion_name>              Play the named reference motion once\n"
      << "  reset                             Restore default planner command\n"
      << "  quit | exit                       Stop publisher and exit\n";
}

void print_status(const DebuggerState& state) {
  const PlannerPreview preview = compute_preview(state);
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Current planner command:\n";
  std::cout << "  expected_control_active: " << (state.expected_control_active ? "true" : "false") << '\n';
  std::cout << "  planner_mode: " << state.planner_mode << " (" << planner_mode_name(state.planner_mode) << ")\n";
  std::cout << "  movement_speed: " << state.movement_speed << '\n';
  std::cout << "  height: " << state.height << '\n';
  std::cout << "  movement_direction: [" << state.movement_direction[0] << ", " << state.movement_direction[1] << ", "
            << state.movement_direction[2] << "]\n";
  std::cout << "  facing_angle_deg: " << (state.facing_angle * 180.0 / M_PI) << '\n';
  std::cout << "Planner preview:\n";
  std::cout << "  Final mode: " << preview.final_mode << " (0=idle, 1=slow, 2=walk, 3=run, 4=squat, 6=kneel)\n";
  std::cout << "  Final speed: " << preview.final_speed << '\n';
  std::cout << "  Final height: " << preview.final_height << '\n';
  std::cout << "  Movement direction: [" << preview.movement_direction[0] << ", " << preview.movement_direction[1] << ", "
            << preview.movement_direction[2] << "]\n";
  std::cout << "  Facing direction: [" << preview.facing_direction[0] << ", " << preview.facing_direction[1] << ", "
            << preview.facing_direction[2] << "]\n";
}

class Ros2MotionDebugger {
 public:
  explicit Ros2MotionDebugger(const Options& options)
      : options_(options),
        node_(rclcpp::Node::make_shared("ros2_motion_debugger")),
        planner_publisher_(node_->create_publisher<std_msgs::msg::ByteMultiArray>(options.planner_topic, 10)),
        action_publisher_(node_->create_publisher<std_msgs::msg::ByteMultiArray>(options.action_topic, 10)) {}

  ~Ros2MotionDebugger() {
    stop();
  }

  void start() {
    running_.store(true);
    publish_thread_ = std::thread(&Ros2MotionDebugger::publish_loop, this);
  }

  void stop() {
    const bool was_running = running_.exchange(false);
    if (was_running && publish_thread_.joinable()) {
      publish_thread_.join();
    }
  }

  DebuggerState snapshot() const {
    std::lock_guard<std::mutex> lock(state_mutex_);
    return state_;
  }

  void set_expected_control_active(bool active) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    state_.expected_control_active = active;
  }

  void queue_control_action(int action) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    state_.pending_control_action = action;
  }

  void with_state(const std::function<void(DebuggerState&)>& mutator) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    mutator(state_);
  }

  void publish_action_once(const std::string& motion_name) {
    std_msgs::msg::ByteMultiArray msg;
    const uint64_t request_id = next_action_request_id_.fetch_add(1);
    const double ros_timestamp = node_->get_clock()->now().nanoseconds() / 1e9;
    msg.data = pack_action_command(motion_name, request_id, ros_timestamp);
    action_publisher_->publish(msg);
  }

  double publish_hz() const {
    return options_.publish_hz;
  }

  const std::string& planner_topic() const {
    return options_.planner_topic;
  }

  const std::string& action_topic() const {
    return options_.action_topic;
  }

 private:
  void publish_loop() {
    rclcpp::WallRate rate(options_.publish_hz);
    while (running_.load() && rclcpp::ok()) {
      DebuggerState local_state;
      int control_action = kControlActionNone;
      {
        std::lock_guard<std::mutex> lock(state_mutex_);
        control_action = state_.pending_control_action;
        state_.pending_control_action = kControlActionNone;
        local_state = state_;
      }

      std_msgs::msg::ByteMultiArray msg;
      const double ros_timestamp = node_->get_clock()->now().nanoseconds() / 1e9;
      msg.data = pack_planner_command(local_state, ros_timestamp, control_action);
      planner_publisher_->publish(msg);
      rate.sleep();
    }
  }

  Options options_;
  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::Publisher<std_msgs::msg::ByteMultiArray>::SharedPtr planner_publisher_;
  rclcpp::Publisher<std_msgs::msg::ByteMultiArray>::SharedPtr action_publisher_;
  mutable std::mutex state_mutex_;
  DebuggerState state_;
  std::atomic<bool> running_{false};
  std::atomic<uint64_t> next_action_request_id_{1};
  std::thread publish_thread_;
};

void print_banner(const Ros2MotionDebugger& debugger) {
  std::cout << "ROS2 motion debugger started\n";
  std::cout << "  planner topic: " << debugger.planner_topic() << '\n';
  std::cout << "  action topic:  " << debugger.action_topic() << '\n';
  std::cout << "  rate:          " << debugger.publish_hz() << " Hz\n";
  std::cout << "  message type:  std_msgs/msg/ByteMultiArray (msgpack planner/action payloads)\n";
  std::cout << "Type 'help' for commands.\n";
}

std::optional<Options> parse_args(int argc, char** argv) {
  Options options;
  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      std::cout << "Usage: ros2_motion_debugger [--planner-topic <name>] [--action-topic <name>] [--hz <rate>]\n";
      return std::nullopt;
    }
    if (arg == "--planner-topic" && i + 1 < argc) {
      options.planner_topic = argv[++i];
      continue;
    }
    if (arg == "--action-topic" && i + 1 < argc) {
      options.action_topic = argv[++i];
      continue;
    }
    if (arg == "--hz" && i + 1 < argc) {
      const auto hz = parse_double(argv[++i]);
      if (!hz.has_value() || *hz <= 0.0) {
        std::cerr << "Invalid publish rate\n";
        return std::nullopt;
      }
      options.publish_hz = *hz;
      continue;
    }
    std::cerr << "Unknown argument: " << arg << '\n';
    return std::nullopt;
  }
  return options;
}

void reset_state(DebuggerState& state) {
  state.planner_mode = kModeIdle;
  state.movement_direction = {0.0, 0.0, 0.0};
  state.movement_speed = -1.0;
  state.height = -1.0;
  state.facing_angle = 0.0;
}

}  // namespace

int main(int argc, char** argv) {
  const auto options = parse_args(argc, argv);
  if (!options.has_value()) {
    return 0;
  }

  rclcpp::init(argc, argv);

  try {
    Ros2MotionDebugger debugger(*options);
    debugger.start();
    print_banner(debugger);
    print_status(debugger.snapshot());

    std::string line;
    while (rclcpp::ok()) {
      std::cout << "\nros2-debug> " << std::flush;
      if (!std::getline(std::cin, line)) {
        break;
      }

      line = trim(line);
      if (line.empty()) {
        continue;
      }

      const std::vector<std::string> args = split_ws(line);
      const std::string& cmd = args[0];
      bool should_print_status = true;

      if (cmd == "help") {
        print_help();
        should_print_status = false;
      } else if (cmd == "status") {
        print_status(debugger.snapshot());
        should_print_status = false;
      } else if (cmd == "start") {
        debugger.with_state([](DebuggerState& state) {
          state.pending_control_action = kControlActionStart;
          state.expected_control_active = true;
        });
      } else if (cmd == "stop") {
        debugger.with_state([](DebuggerState& state) {
          state.pending_control_action = kControlActionStop;
          state.expected_control_active = false;
        });
      } else if (cmd == "toggle") {
        debugger.with_state([](DebuggerState& state) {
          state.pending_control_action = kControlActionToggle;
          state.expected_control_active = !state.expected_control_active;
        });
      } else if (cmd == "sync" && args.size() == 2) {
        if (args[1] == "on") {
          debugger.set_expected_control_active(true);
        } else if (args[1] == "off") {
          debugger.set_expected_control_active(false);
        } else {
          std::cerr << "sync expects 'on' or 'off'\n";
          should_print_status = false;
        }
      } else if (cmd == "mode" && args.size() == 2) {
        int new_mode = -1;
        if (args[1] == "idle") {
          new_mode = kModeIdle;
        } else if (args[1] == "slow") {
          new_mode = kModeSlowWalk;
        } else if (args[1] == "walk") {
          new_mode = kModeWalk;
        } else if (args[1] == "run") {
          new_mode = kModeRun;
        } else if (args[1] == "squat") {
          new_mode = kModeIdleSquat;
        } else if (args[1] == "kneel") {
          new_mode = kModeIdleKneel;
        } else {
          std::cerr << "mode expects idle|slow|walk|run|squat|kneel\n";
          should_print_status = false;
        }
        if (should_print_status) {
          debugger.with_state([&](DebuggerState& state) {
            state.planner_mode = new_mode;
            if (new_mode == kModeIdle || new_mode == kModeIdleSquat || new_mode == kModeIdleKneel) {
              state.movement_direction = {0.0, 0.0, 0.0};
            }
          });
        }
      } else if (cmd == "speed" && args.size() == 2) {
        if (args[1] == "default") {
          debugger.with_state([](DebuggerState& state) { state.movement_speed = -1.0; });
        } else {
          const auto value = parse_double(args[1]);
          if (!value.has_value()) {
            std::cerr << "speed expects a number or 'default'\n";
            should_print_status = false;
          } else {
            debugger.with_state([&](DebuggerState& state) { state.movement_speed = *value; });
          }
        }
      } else if (cmd == "height" && args.size() == 2) {
        if (args[1] == "default") {
          debugger.with_state([](DebuggerState& state) { state.height = -1.0; });
        } else {
          const auto value = parse_double(args[1]);
          if (!value.has_value()) {
            std::cerr << "height expects a number or 'default'\n";
            should_print_status = false;
          } else {
            debugger.with_state([&](DebuggerState& state) { state.height = *value; });
          }
        }
      } else if (cmd == "stand" && args.size() == 1) {
        debugger.with_state([](DebuggerState& state) {
          state.planner_mode = kModeIdle;
          state.height = -1.0;
          state.movement_direction = {0.0, 0.0, 0.0};
        });
      } else if (cmd == "squat" && (args.size() == 1 || args.size() == 2)) {
        double height = 0.60;
        if (args.size() == 2) {
          const auto value = parse_double(args[1]);
          if (!value.has_value()) {
            std::cerr << "squat height must be numeric\n";
            should_print_status = false;
          } else {
            height = *value;
          }
        }
        if (should_print_status) {
          debugger.with_state([&](DebuggerState& state) {
            state.planner_mode = kModeIdleSquat;
            state.height = height;
            state.movement_direction = {0.0, 0.0, 0.0};
          });
        }
      } else if (cmd == "kneel" && (args.size() == 1 || args.size() == 2)) {
        double height = 0.30;
        if (args.size() == 2) {
          const auto value = parse_double(args[1]);
          if (!value.has_value()) {
            std::cerr << "kneel height must be numeric\n";
            should_print_status = false;
          } else {
            height = *value;
          }
        }
        if (should_print_status) {
          debugger.with_state([&](DebuggerState& state) {
            state.planner_mode = kModeIdleKneel;
            state.height = height;
            state.movement_direction = {0.0, 0.0, 0.0};
          });
        }
      } else if (cmd == "move" && (args.size() == 2 || args.size() == 3)) {
        double speed = -1.0;
        if (args.size() == 3) {
          const auto value = parse_double(args[2]);
          if (!value.has_value()) {
            std::cerr << "move speed must be numeric\n";
            should_print_status = false;
          } else {
            speed = *value;
          }
        }
        if (should_print_status) {
          debugger.with_state([&](DebuggerState& state) {
            const auto direction = relative_move_direction(args[1], state.facing_angle);
            if (direction == std::array<double, 3>{0.0, 0.0, 0.0} && args[1] != "f") {
              return;
            }
            state.movement_direction = direction;
            if (speed >= 0.0) {
              state.movement_speed = speed;
            }
          });
          if (args[1] != "f" && args[1] != "b" && args[1] != "l" && args[1] != "r" &&
              args[1] != "fl" && args[1] != "fr" && args[1] != "bl" && args[1] != "br") {
            std::cerr << "move dir expects f|b|l|r|fl|fr|bl|br\n";
            should_print_status = false;
          }
        }
      } else if (cmd == "idle" && args.size() == 1) {
        debugger.with_state([](DebuggerState& state) { state.movement_direction = {0.0, 0.0, 0.0}; });
      } else if (cmd == "face" && args.size() == 2) {
        const auto value = parse_double(args[1]);
        if (!value.has_value()) {
          std::cerr << "face expects degrees\n";
          should_print_status = false;
        } else {
          debugger.with_state([&](DebuggerState& state) { state.facing_angle = normalize_angle(*value * M_PI / 180.0); });
        }
      } else if (cmd == "turn" && args.size() == 2) {
        const auto value = parse_double(args[1]);
        if (!value.has_value()) {
          std::cerr << "turn expects degrees\n";
          should_print_status = false;
        } else {
          debugger.with_state([&](DebuggerState& state) {
            state.facing_angle = normalize_angle(state.facing_angle + (*value * M_PI / 180.0));
          });
        }
      } else if (cmd == "action" && args.size() >= 2) {
        std::string motion_name;
        if (args[1] == "carrybox") {
          motion_name = "sonic_export_carrybox";
        } else {
          motion_name = args[1];
        }
        debugger.publish_action_once(motion_name);
        std::cout << "Published one-shot action: " << motion_name << '\n';
      } else if (cmd == "reset" && args.size() == 1) {
        debugger.with_state([](DebuggerState& state) { reset_state(state); });
      } else if (cmd == "quit" || cmd == "exit") {
        break;
      } else {
        std::cerr << "Unknown command. Type 'help'.\n";
        should_print_status = false;
      }

      if (should_print_status) {
        print_status(debugger.snapshot());
      }
    }

    debugger.stop();
  } catch (const std::exception& e) {
    std::cerr << "ros2_motion_debugger failed: " << e.what() << '\n';
    rclcpp::shutdown();
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}

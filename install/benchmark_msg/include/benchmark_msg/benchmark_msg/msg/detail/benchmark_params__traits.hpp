// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#ifndef BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__TRAITS_HPP_
#define BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "benchmark_msg/msg/detail/benchmark_params__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace benchmark_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const BenchmarkParams & msg,
  std::ostream & out)
{
  out << "{";
  // member: enable_adaptative
  {
    out << "enable_adaptative: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_adaptative, out);
    out << ", ";
  }

  // member: full_payload
  {
    out << "full_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.full_payload, out);
    out << ", ";
  }

  // member: mu
  {
    out << "mu: ";
    rosidl_generator_traits::value_to_yaml(msg.mu, out);
    out << ", ";
  }

  // member: mu_zone1
  {
    out << "mu_zone1: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone1, out);
    out << ", ";
  }

  // member: mu_zone2
  {
    out << "mu_zone2: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone2, out);
    out << ", ";
  }

  // member: mu_zone3
  {
    out << "mu_zone3: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone3, out);
    out << ", ";
  }

  // member: new_vel_max
  {
    out << "new_vel_max: ";
    rosidl_generator_traits::value_to_yaml(msg.new_vel_max, out);
    out << ", ";
  }

  // member: new_w_max
  {
    out << "new_w_max: ";
    rosidl_generator_traits::value_to_yaml(msg.new_w_max, out);
    out << ", ";
  }

  // member: dist_obst
  {
    out << "dist_obst: ";
    rosidl_generator_traits::value_to_yaml(msg.dist_obst, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BenchmarkParams & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: enable_adaptative
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable_adaptative: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_adaptative, out);
    out << "\n";
  }

  // member: full_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.full_payload, out);
    out << "\n";
  }

  // member: mu
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mu: ";
    rosidl_generator_traits::value_to_yaml(msg.mu, out);
    out << "\n";
  }

  // member: mu_zone1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mu_zone1: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone1, out);
    out << "\n";
  }

  // member: mu_zone2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mu_zone2: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone2, out);
    out << "\n";
  }

  // member: mu_zone3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mu_zone3: ";
    rosidl_generator_traits::value_to_yaml(msg.mu_zone3, out);
    out << "\n";
  }

  // member: new_vel_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_vel_max: ";
    rosidl_generator_traits::value_to_yaml(msg.new_vel_max, out);
    out << "\n";
  }

  // member: new_w_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_w_max: ";
    rosidl_generator_traits::value_to_yaml(msg.new_w_max, out);
    out << "\n";
  }

  // member: dist_obst
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dist_obst: ";
    rosidl_generator_traits::value_to_yaml(msg.dist_obst, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BenchmarkParams & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace benchmark_msg

namespace rosidl_generator_traits
{

[[deprecated("use benchmark_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const benchmark_msg::msg::BenchmarkParams & msg,
  std::ostream & out, size_t indentation = 0)
{
  benchmark_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use benchmark_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const benchmark_msg::msg::BenchmarkParams & msg)
{
  return benchmark_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<benchmark_msg::msg::BenchmarkParams>()
{
  return "benchmark_msg::msg::BenchmarkParams";
}

template<>
inline const char * name<benchmark_msg::msg::BenchmarkParams>()
{
  return "benchmark_msg/msg/BenchmarkParams";
}

template<>
struct has_fixed_size<benchmark_msg::msg::BenchmarkParams>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<benchmark_msg::msg::BenchmarkParams>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<benchmark_msg::msg::BenchmarkParams>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__TRAITS_HPP_

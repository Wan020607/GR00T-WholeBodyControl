// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#ifndef BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__BUILDER_HPP_
#define BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "benchmark_msg/msg/detail/benchmark_params__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace benchmark_msg
{

namespace msg
{

namespace builder
{

class Init_BenchmarkParams_dist_obst
{
public:
  explicit Init_BenchmarkParams_dist_obst(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  ::benchmark_msg::msg::BenchmarkParams dist_obst(::benchmark_msg::msg::BenchmarkParams::_dist_obst_type arg)
  {
    msg_.dist_obst = std::move(arg);
    return std::move(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_new_w_max
{
public:
  explicit Init_BenchmarkParams_new_w_max(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_dist_obst new_w_max(::benchmark_msg::msg::BenchmarkParams::_new_w_max_type arg)
  {
    msg_.new_w_max = std::move(arg);
    return Init_BenchmarkParams_dist_obst(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_new_vel_max
{
public:
  explicit Init_BenchmarkParams_new_vel_max(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_new_w_max new_vel_max(::benchmark_msg::msg::BenchmarkParams::_new_vel_max_type arg)
  {
    msg_.new_vel_max = std::move(arg);
    return Init_BenchmarkParams_new_w_max(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_mu_zone3
{
public:
  explicit Init_BenchmarkParams_mu_zone3(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_new_vel_max mu_zone3(::benchmark_msg::msg::BenchmarkParams::_mu_zone3_type arg)
  {
    msg_.mu_zone3 = std::move(arg);
    return Init_BenchmarkParams_new_vel_max(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_mu_zone2
{
public:
  explicit Init_BenchmarkParams_mu_zone2(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_mu_zone3 mu_zone2(::benchmark_msg::msg::BenchmarkParams::_mu_zone2_type arg)
  {
    msg_.mu_zone2 = std::move(arg);
    return Init_BenchmarkParams_mu_zone3(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_mu_zone1
{
public:
  explicit Init_BenchmarkParams_mu_zone1(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_mu_zone2 mu_zone1(::benchmark_msg::msg::BenchmarkParams::_mu_zone1_type arg)
  {
    msg_.mu_zone1 = std::move(arg);
    return Init_BenchmarkParams_mu_zone2(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_mu
{
public:
  explicit Init_BenchmarkParams_mu(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_mu_zone1 mu(::benchmark_msg::msg::BenchmarkParams::_mu_type arg)
  {
    msg_.mu = std::move(arg);
    return Init_BenchmarkParams_mu_zone1(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_full_payload
{
public:
  explicit Init_BenchmarkParams_full_payload(::benchmark_msg::msg::BenchmarkParams & msg)
  : msg_(msg)
  {}
  Init_BenchmarkParams_mu full_payload(::benchmark_msg::msg::BenchmarkParams::_full_payload_type arg)
  {
    msg_.full_payload = std::move(arg);
    return Init_BenchmarkParams_mu(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

class Init_BenchmarkParams_enable_adaptative
{
public:
  Init_BenchmarkParams_enable_adaptative()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BenchmarkParams_full_payload enable_adaptative(::benchmark_msg::msg::BenchmarkParams::_enable_adaptative_type arg)
  {
    msg_.enable_adaptative = std::move(arg);
    return Init_BenchmarkParams_full_payload(msg_);
  }

private:
  ::benchmark_msg::msg::BenchmarkParams msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::benchmark_msg::msg::BenchmarkParams>()
{
  return benchmark_msg::msg::builder::Init_BenchmarkParams_enable_adaptative();
}

}  // namespace benchmark_msg

#endif  // BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__BUILDER_HPP_

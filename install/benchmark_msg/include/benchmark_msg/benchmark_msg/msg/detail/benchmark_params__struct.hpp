// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#ifndef BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_HPP_
#define BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__benchmark_msg__msg__BenchmarkParams __attribute__((deprecated))
#else
# define DEPRECATED__benchmark_msg__msg__BenchmarkParams __declspec(deprecated)
#endif

namespace benchmark_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BenchmarkParams_
{
  using Type = BenchmarkParams_<ContainerAllocator>;

  explicit BenchmarkParams_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable_adaptative = false;
      this->full_payload = false;
      this->mu = 0.0;
      this->mu_zone1 = 0.0;
      this->mu_zone2 = 0.0;
      this->mu_zone3 = 0.0;
      this->new_vel_max = 0.0;
      this->new_w_max = 0.0;
      this->dist_obst = 0.0;
    }
  }

  explicit BenchmarkParams_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable_adaptative = false;
      this->full_payload = false;
      this->mu = 0.0;
      this->mu_zone1 = 0.0;
      this->mu_zone2 = 0.0;
      this->mu_zone3 = 0.0;
      this->new_vel_max = 0.0;
      this->new_w_max = 0.0;
      this->dist_obst = 0.0;
    }
  }

  // field types and members
  using _enable_adaptative_type =
    bool;
  _enable_adaptative_type enable_adaptative;
  using _full_payload_type =
    bool;
  _full_payload_type full_payload;
  using _mu_type =
    double;
  _mu_type mu;
  using _mu_zone1_type =
    double;
  _mu_zone1_type mu_zone1;
  using _mu_zone2_type =
    double;
  _mu_zone2_type mu_zone2;
  using _mu_zone3_type =
    double;
  _mu_zone3_type mu_zone3;
  using _new_vel_max_type =
    double;
  _new_vel_max_type new_vel_max;
  using _new_w_max_type =
    double;
  _new_w_max_type new_w_max;
  using _dist_obst_type =
    double;
  _dist_obst_type dist_obst;

  // setters for named parameter idiom
  Type & set__enable_adaptative(
    const bool & _arg)
  {
    this->enable_adaptative = _arg;
    return *this;
  }
  Type & set__full_payload(
    const bool & _arg)
  {
    this->full_payload = _arg;
    return *this;
  }
  Type & set__mu(
    const double & _arg)
  {
    this->mu = _arg;
    return *this;
  }
  Type & set__mu_zone1(
    const double & _arg)
  {
    this->mu_zone1 = _arg;
    return *this;
  }
  Type & set__mu_zone2(
    const double & _arg)
  {
    this->mu_zone2 = _arg;
    return *this;
  }
  Type & set__mu_zone3(
    const double & _arg)
  {
    this->mu_zone3 = _arg;
    return *this;
  }
  Type & set__new_vel_max(
    const double & _arg)
  {
    this->new_vel_max = _arg;
    return *this;
  }
  Type & set__new_w_max(
    const double & _arg)
  {
    this->new_w_max = _arg;
    return *this;
  }
  Type & set__dist_obst(
    const double & _arg)
  {
    this->dist_obst = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> *;
  using ConstRawPtr =
    const benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__benchmark_msg__msg__BenchmarkParams
    std::shared_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__benchmark_msg__msg__BenchmarkParams
    std::shared_ptr<benchmark_msg::msg::BenchmarkParams_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BenchmarkParams_ & other) const
  {
    if (this->enable_adaptative != other.enable_adaptative) {
      return false;
    }
    if (this->full_payload != other.full_payload) {
      return false;
    }
    if (this->mu != other.mu) {
      return false;
    }
    if (this->mu_zone1 != other.mu_zone1) {
      return false;
    }
    if (this->mu_zone2 != other.mu_zone2) {
      return false;
    }
    if (this->mu_zone3 != other.mu_zone3) {
      return false;
    }
    if (this->new_vel_max != other.new_vel_max) {
      return false;
    }
    if (this->new_w_max != other.new_w_max) {
      return false;
    }
    if (this->dist_obst != other.dist_obst) {
      return false;
    }
    return true;
  }
  bool operator!=(const BenchmarkParams_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BenchmarkParams_

// alias to use template instance with default allocator
using BenchmarkParams =
  benchmark_msg::msg::BenchmarkParams_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace benchmark_msg

#endif  // BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_HPP_

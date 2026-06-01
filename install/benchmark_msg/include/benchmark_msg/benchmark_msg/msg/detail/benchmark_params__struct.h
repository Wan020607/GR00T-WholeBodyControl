// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#ifndef BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_H_
#define BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/BenchmarkParams in the package benchmark_msg.
typedef struct benchmark_msg__msg__BenchmarkParams
{
  bool enable_adaptative;
  bool full_payload;
  double mu;
  double mu_zone1;
  double mu_zone2;
  double mu_zone3;
  double new_vel_max;
  double new_w_max;
  double dist_obst;
} benchmark_msg__msg__BenchmarkParams;

// Struct for a sequence of benchmark_msg__msg__BenchmarkParams.
typedef struct benchmark_msg__msg__BenchmarkParams__Sequence
{
  benchmark_msg__msg__BenchmarkParams * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} benchmark_msg__msg__BenchmarkParams__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__STRUCT_H_

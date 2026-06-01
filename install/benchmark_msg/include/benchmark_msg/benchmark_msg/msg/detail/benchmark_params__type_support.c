// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "benchmark_msg/msg/detail/benchmark_params__rosidl_typesupport_introspection_c.h"
#include "benchmark_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "benchmark_msg/msg/detail/benchmark_params__functions.h"
#include "benchmark_msg/msg/detail/benchmark_params__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  benchmark_msg__msg__BenchmarkParams__init(message_memory);
}

void benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_fini_function(void * message_memory)
{
  benchmark_msg__msg__BenchmarkParams__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_member_array[9] = {
  {
    "enable_adaptative",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, enable_adaptative),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "full_payload",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, full_payload),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mu",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, mu),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mu_zone1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, mu_zone1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mu_zone2",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, mu_zone2),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mu_zone3",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, mu_zone3),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "new_vel_max",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, new_vel_max),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "new_w_max",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, new_w_max),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dist_obst",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(benchmark_msg__msg__BenchmarkParams, dist_obst),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_members = {
  "benchmark_msg__msg",  // message namespace
  "BenchmarkParams",  // message name
  9,  // number of fields
  sizeof(benchmark_msg__msg__BenchmarkParams),
  benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_member_array,  // message members
  benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_init_function,  // function to initialize message memory (memory has to be allocated)
  benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_type_support_handle = {
  0,
  &benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_benchmark_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, benchmark_msg, msg, BenchmarkParams)() {
  if (!benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_type_support_handle.typesupport_identifier) {
    benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &benchmark_msg__msg__BenchmarkParams__rosidl_typesupport_introspection_c__BenchmarkParams_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

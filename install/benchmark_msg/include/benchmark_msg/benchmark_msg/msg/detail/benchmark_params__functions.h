// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice

#ifndef BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__FUNCTIONS_H_
#define BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "benchmark_msg/msg/rosidl_generator_c__visibility_control.h"

#include "benchmark_msg/msg/detail/benchmark_params__struct.h"

/// Initialize msg/BenchmarkParams message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * benchmark_msg__msg__BenchmarkParams
 * )) before or use
 * benchmark_msg__msg__BenchmarkParams__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__init(benchmark_msg__msg__BenchmarkParams * msg);

/// Finalize msg/BenchmarkParams message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
void
benchmark_msg__msg__BenchmarkParams__fini(benchmark_msg__msg__BenchmarkParams * msg);

/// Create msg/BenchmarkParams message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * benchmark_msg__msg__BenchmarkParams__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
benchmark_msg__msg__BenchmarkParams *
benchmark_msg__msg__BenchmarkParams__create();

/// Destroy msg/BenchmarkParams message.
/**
 * It calls
 * benchmark_msg__msg__BenchmarkParams__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
void
benchmark_msg__msg__BenchmarkParams__destroy(benchmark_msg__msg__BenchmarkParams * msg);

/// Check for msg/BenchmarkParams message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__are_equal(const benchmark_msg__msg__BenchmarkParams * lhs, const benchmark_msg__msg__BenchmarkParams * rhs);

/// Copy a msg/BenchmarkParams message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__copy(
  const benchmark_msg__msg__BenchmarkParams * input,
  benchmark_msg__msg__BenchmarkParams * output);

/// Initialize array of msg/BenchmarkParams messages.
/**
 * It allocates the memory for the number of elements and calls
 * benchmark_msg__msg__BenchmarkParams__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__Sequence__init(benchmark_msg__msg__BenchmarkParams__Sequence * array, size_t size);

/// Finalize array of msg/BenchmarkParams messages.
/**
 * It calls
 * benchmark_msg__msg__BenchmarkParams__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
void
benchmark_msg__msg__BenchmarkParams__Sequence__fini(benchmark_msg__msg__BenchmarkParams__Sequence * array);

/// Create array of msg/BenchmarkParams messages.
/**
 * It allocates the memory for the array and calls
 * benchmark_msg__msg__BenchmarkParams__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
benchmark_msg__msg__BenchmarkParams__Sequence *
benchmark_msg__msg__BenchmarkParams__Sequence__create(size_t size);

/// Destroy array of msg/BenchmarkParams messages.
/**
 * It calls
 * benchmark_msg__msg__BenchmarkParams__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
void
benchmark_msg__msg__BenchmarkParams__Sequence__destroy(benchmark_msg__msg__BenchmarkParams__Sequence * array);

/// Check for msg/BenchmarkParams message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__Sequence__are_equal(const benchmark_msg__msg__BenchmarkParams__Sequence * lhs, const benchmark_msg__msg__BenchmarkParams__Sequence * rhs);

/// Copy an array of msg/BenchmarkParams messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_benchmark_msg
bool
benchmark_msg__msg__BenchmarkParams__Sequence__copy(
  const benchmark_msg__msg__BenchmarkParams__Sequence * input,
  benchmark_msg__msg__BenchmarkParams__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BENCHMARK_MSG__MSG__DETAIL__BENCHMARK_PARAMS__FUNCTIONS_H_

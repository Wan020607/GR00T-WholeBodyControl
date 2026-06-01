// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice
#include "benchmark_msg/msg/detail/benchmark_params__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
benchmark_msg__msg__BenchmarkParams__init(benchmark_msg__msg__BenchmarkParams * msg)
{
  if (!msg) {
    return false;
  }
  // enable_adaptative
  // full_payload
  // mu
  // mu_zone1
  // mu_zone2
  // mu_zone3
  // new_vel_max
  // new_w_max
  // dist_obst
  return true;
}

void
benchmark_msg__msg__BenchmarkParams__fini(benchmark_msg__msg__BenchmarkParams * msg)
{
  if (!msg) {
    return;
  }
  // enable_adaptative
  // full_payload
  // mu
  // mu_zone1
  // mu_zone2
  // mu_zone3
  // new_vel_max
  // new_w_max
  // dist_obst
}

bool
benchmark_msg__msg__BenchmarkParams__are_equal(const benchmark_msg__msg__BenchmarkParams * lhs, const benchmark_msg__msg__BenchmarkParams * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // enable_adaptative
  if (lhs->enable_adaptative != rhs->enable_adaptative) {
    return false;
  }
  // full_payload
  if (lhs->full_payload != rhs->full_payload) {
    return false;
  }
  // mu
  if (lhs->mu != rhs->mu) {
    return false;
  }
  // mu_zone1
  if (lhs->mu_zone1 != rhs->mu_zone1) {
    return false;
  }
  // mu_zone2
  if (lhs->mu_zone2 != rhs->mu_zone2) {
    return false;
  }
  // mu_zone3
  if (lhs->mu_zone3 != rhs->mu_zone3) {
    return false;
  }
  // new_vel_max
  if (lhs->new_vel_max != rhs->new_vel_max) {
    return false;
  }
  // new_w_max
  if (lhs->new_w_max != rhs->new_w_max) {
    return false;
  }
  // dist_obst
  if (lhs->dist_obst != rhs->dist_obst) {
    return false;
  }
  return true;
}

bool
benchmark_msg__msg__BenchmarkParams__copy(
  const benchmark_msg__msg__BenchmarkParams * input,
  benchmark_msg__msg__BenchmarkParams * output)
{
  if (!input || !output) {
    return false;
  }
  // enable_adaptative
  output->enable_adaptative = input->enable_adaptative;
  // full_payload
  output->full_payload = input->full_payload;
  // mu
  output->mu = input->mu;
  // mu_zone1
  output->mu_zone1 = input->mu_zone1;
  // mu_zone2
  output->mu_zone2 = input->mu_zone2;
  // mu_zone3
  output->mu_zone3 = input->mu_zone3;
  // new_vel_max
  output->new_vel_max = input->new_vel_max;
  // new_w_max
  output->new_w_max = input->new_w_max;
  // dist_obst
  output->dist_obst = input->dist_obst;
  return true;
}

benchmark_msg__msg__BenchmarkParams *
benchmark_msg__msg__BenchmarkParams__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  benchmark_msg__msg__BenchmarkParams * msg = (benchmark_msg__msg__BenchmarkParams *)allocator.allocate(sizeof(benchmark_msg__msg__BenchmarkParams), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(benchmark_msg__msg__BenchmarkParams));
  bool success = benchmark_msg__msg__BenchmarkParams__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
benchmark_msg__msg__BenchmarkParams__destroy(benchmark_msg__msg__BenchmarkParams * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    benchmark_msg__msg__BenchmarkParams__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
benchmark_msg__msg__BenchmarkParams__Sequence__init(benchmark_msg__msg__BenchmarkParams__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  benchmark_msg__msg__BenchmarkParams * data = NULL;

  if (size) {
    data = (benchmark_msg__msg__BenchmarkParams *)allocator.zero_allocate(size, sizeof(benchmark_msg__msg__BenchmarkParams), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = benchmark_msg__msg__BenchmarkParams__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        benchmark_msg__msg__BenchmarkParams__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
benchmark_msg__msg__BenchmarkParams__Sequence__fini(benchmark_msg__msg__BenchmarkParams__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      benchmark_msg__msg__BenchmarkParams__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

benchmark_msg__msg__BenchmarkParams__Sequence *
benchmark_msg__msg__BenchmarkParams__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  benchmark_msg__msg__BenchmarkParams__Sequence * array = (benchmark_msg__msg__BenchmarkParams__Sequence *)allocator.allocate(sizeof(benchmark_msg__msg__BenchmarkParams__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = benchmark_msg__msg__BenchmarkParams__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
benchmark_msg__msg__BenchmarkParams__Sequence__destroy(benchmark_msg__msg__BenchmarkParams__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    benchmark_msg__msg__BenchmarkParams__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
benchmark_msg__msg__BenchmarkParams__Sequence__are_equal(const benchmark_msg__msg__BenchmarkParams__Sequence * lhs, const benchmark_msg__msg__BenchmarkParams__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!benchmark_msg__msg__BenchmarkParams__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
benchmark_msg__msg__BenchmarkParams__Sequence__copy(
  const benchmark_msg__msg__BenchmarkParams__Sequence * input,
  benchmark_msg__msg__BenchmarkParams__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(benchmark_msg__msg__BenchmarkParams);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    benchmark_msg__msg__BenchmarkParams * data =
      (benchmark_msg__msg__BenchmarkParams *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!benchmark_msg__msg__BenchmarkParams__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          benchmark_msg__msg__BenchmarkParams__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!benchmark_msg__msg__BenchmarkParams__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

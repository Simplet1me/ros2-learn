// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice
#include "base_interface/msg/detail/example__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
base_interface__msg__Example__init(base_interface__msg__Example * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    base_interface__msg__Example__fini(msg);
    return false;
  }
  // money
  // coop_rank
  // damage
  return true;
}

void
base_interface__msg__Example__fini(base_interface__msg__Example * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // money
  // coop_rank
  // damage
}

bool
base_interface__msg__Example__are_equal(const base_interface__msg__Example * lhs, const base_interface__msg__Example * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // money
  if (lhs->money != rhs->money) {
    return false;
  }
  // coop_rank
  if (lhs->coop_rank != rhs->coop_rank) {
    return false;
  }
  // damage
  if (lhs->damage != rhs->damage) {
    return false;
  }
  return true;
}

bool
base_interface__msg__Example__copy(
  const base_interface__msg__Example * input,
  base_interface__msg__Example * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // money
  output->money = input->money;
  // coop_rank
  output->coop_rank = input->coop_rank;
  // damage
  output->damage = input->damage;
  return true;
}

base_interface__msg__Example *
base_interface__msg__Example__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interface__msg__Example * msg = (base_interface__msg__Example *)allocator.allocate(sizeof(base_interface__msg__Example), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interface__msg__Example));
  bool success = base_interface__msg__Example__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interface__msg__Example__destroy(base_interface__msg__Example * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interface__msg__Example__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interface__msg__Example__Sequence__init(base_interface__msg__Example__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interface__msg__Example * data = NULL;

  if (size) {
    data = (base_interface__msg__Example *)allocator.zero_allocate(size, sizeof(base_interface__msg__Example), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interface__msg__Example__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interface__msg__Example__fini(&data[i - 1]);
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
base_interface__msg__Example__Sequence__fini(base_interface__msg__Example__Sequence * array)
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
      base_interface__msg__Example__fini(&array->data[i]);
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

base_interface__msg__Example__Sequence *
base_interface__msg__Example__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interface__msg__Example__Sequence * array = (base_interface__msg__Example__Sequence *)allocator.allocate(sizeof(base_interface__msg__Example__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interface__msg__Example__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interface__msg__Example__Sequence__destroy(base_interface__msg__Example__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interface__msg__Example__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interface__msg__Example__Sequence__are_equal(const base_interface__msg__Example__Sequence * lhs, const base_interface__msg__Example__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interface__msg__Example__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interface__msg__Example__Sequence__copy(
  const base_interface__msg__Example__Sequence * input,
  base_interface__msg__Example__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interface__msg__Example);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interface__msg__Example * data =
      (base_interface__msg__Example *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interface__msg__Example__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interface__msg__Example__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interface__msg__Example__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

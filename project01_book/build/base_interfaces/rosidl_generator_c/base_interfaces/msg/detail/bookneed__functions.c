// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice
#include "base_interfaces/msg/detail/bookneed__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `company_name`
// Member `book_need_kind`
#include "rosidl_runtime_c/string_functions.h"

bool
base_interfaces__msg__Bookneed__init(base_interfaces__msg__Bookneed * msg)
{
  if (!msg) {
    return false;
  }
  // company_name
  if (!rosidl_runtime_c__String__init(&msg->company_name)) {
    base_interfaces__msg__Bookneed__fini(msg);
    return false;
  }
  // book_need_amount
  // book_need_kind
  if (!rosidl_runtime_c__String__init(&msg->book_need_kind)) {
    base_interfaces__msg__Bookneed__fini(msg);
    return false;
  }
  return true;
}

void
base_interfaces__msg__Bookneed__fini(base_interfaces__msg__Bookneed * msg)
{
  if (!msg) {
    return;
  }
  // company_name
  rosidl_runtime_c__String__fini(&msg->company_name);
  // book_need_amount
  // book_need_kind
  rosidl_runtime_c__String__fini(&msg->book_need_kind);
}

bool
base_interfaces__msg__Bookneed__are_equal(const base_interfaces__msg__Bookneed * lhs, const base_interfaces__msg__Bookneed * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // company_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->company_name), &(rhs->company_name)))
  {
    return false;
  }
  // book_need_amount
  if (lhs->book_need_amount != rhs->book_need_amount) {
    return false;
  }
  // book_need_kind
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->book_need_kind), &(rhs->book_need_kind)))
  {
    return false;
  }
  return true;
}

bool
base_interfaces__msg__Bookneed__copy(
  const base_interfaces__msg__Bookneed * input,
  base_interfaces__msg__Bookneed * output)
{
  if (!input || !output) {
    return false;
  }
  // company_name
  if (!rosidl_runtime_c__String__copy(
      &(input->company_name), &(output->company_name)))
  {
    return false;
  }
  // book_need_amount
  output->book_need_amount = input->book_need_amount;
  // book_need_kind
  if (!rosidl_runtime_c__String__copy(
      &(input->book_need_kind), &(output->book_need_kind)))
  {
    return false;
  }
  return true;
}

base_interfaces__msg__Bookneed *
base_interfaces__msg__Bookneed__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Bookneed * msg = (base_interfaces__msg__Bookneed *)allocator.allocate(sizeof(base_interfaces__msg__Bookneed), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interfaces__msg__Bookneed));
  bool success = base_interfaces__msg__Bookneed__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interfaces__msg__Bookneed__destroy(base_interfaces__msg__Bookneed * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interfaces__msg__Bookneed__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interfaces__msg__Bookneed__Sequence__init(base_interfaces__msg__Bookneed__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Bookneed * data = NULL;

  if (size) {
    data = (base_interfaces__msg__Bookneed *)allocator.zero_allocate(size, sizeof(base_interfaces__msg__Bookneed), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interfaces__msg__Bookneed__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interfaces__msg__Bookneed__fini(&data[i - 1]);
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
base_interfaces__msg__Bookneed__Sequence__fini(base_interfaces__msg__Bookneed__Sequence * array)
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
      base_interfaces__msg__Bookneed__fini(&array->data[i]);
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

base_interfaces__msg__Bookneed__Sequence *
base_interfaces__msg__Bookneed__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Bookneed__Sequence * array = (base_interfaces__msg__Bookneed__Sequence *)allocator.allocate(sizeof(base_interfaces__msg__Bookneed__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interfaces__msg__Bookneed__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interfaces__msg__Bookneed__Sequence__destroy(base_interfaces__msg__Bookneed__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interfaces__msg__Bookneed__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interfaces__msg__Bookneed__Sequence__are_equal(const base_interfaces__msg__Bookneed__Sequence * lhs, const base_interfaces__msg__Bookneed__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interfaces__msg__Bookneed__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interfaces__msg__Bookneed__Sequence__copy(
  const base_interfaces__msg__Bookneed__Sequence * input,
  base_interfaces__msg__Bookneed__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interfaces__msg__Bookneed);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interfaces__msg__Bookneed * data =
      (base_interfaces__msg__Bookneed *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interfaces__msg__Bookneed__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interfaces__msg__Bookneed__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interfaces__msg__Bookneed__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

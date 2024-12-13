// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_interfaces:msg/Booksupply.idl
// generated code does not contain a copyright notice
#include "base_interfaces/msg/detail/booksupply__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `company_name`
#include "rosidl_runtime_c/string_functions.h"

bool
base_interfaces__msg__Booksupply__init(base_interfaces__msg__Booksupply * msg)
{
  if (!msg) {
    return false;
  }
  // company_name
  if (!rosidl_runtime_c__String__init(&msg->company_name)) {
    base_interfaces__msg__Booksupply__fini(msg);
    return false;
  }
  // book_supply_price
  return true;
}

void
base_interfaces__msg__Booksupply__fini(base_interfaces__msg__Booksupply * msg)
{
  if (!msg) {
    return;
  }
  // company_name
  rosidl_runtime_c__String__fini(&msg->company_name);
  // book_supply_price
}

bool
base_interfaces__msg__Booksupply__are_equal(const base_interfaces__msg__Booksupply * lhs, const base_interfaces__msg__Booksupply * rhs)
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
  // book_supply_price
  if (lhs->book_supply_price != rhs->book_supply_price) {
    return false;
  }
  return true;
}

bool
base_interfaces__msg__Booksupply__copy(
  const base_interfaces__msg__Booksupply * input,
  base_interfaces__msg__Booksupply * output)
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
  // book_supply_price
  output->book_supply_price = input->book_supply_price;
  return true;
}

base_interfaces__msg__Booksupply *
base_interfaces__msg__Booksupply__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Booksupply * msg = (base_interfaces__msg__Booksupply *)allocator.allocate(sizeof(base_interfaces__msg__Booksupply), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interfaces__msg__Booksupply));
  bool success = base_interfaces__msg__Booksupply__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interfaces__msg__Booksupply__destroy(base_interfaces__msg__Booksupply * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interfaces__msg__Booksupply__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interfaces__msg__Booksupply__Sequence__init(base_interfaces__msg__Booksupply__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Booksupply * data = NULL;

  if (size) {
    data = (base_interfaces__msg__Booksupply *)allocator.zero_allocate(size, sizeof(base_interfaces__msg__Booksupply), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interfaces__msg__Booksupply__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interfaces__msg__Booksupply__fini(&data[i - 1]);
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
base_interfaces__msg__Booksupply__Sequence__fini(base_interfaces__msg__Booksupply__Sequence * array)
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
      base_interfaces__msg__Booksupply__fini(&array->data[i]);
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

base_interfaces__msg__Booksupply__Sequence *
base_interfaces__msg__Booksupply__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__msg__Booksupply__Sequence * array = (base_interfaces__msg__Booksupply__Sequence *)allocator.allocate(sizeof(base_interfaces__msg__Booksupply__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interfaces__msg__Booksupply__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interfaces__msg__Booksupply__Sequence__destroy(base_interfaces__msg__Booksupply__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interfaces__msg__Booksupply__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interfaces__msg__Booksupply__Sequence__are_equal(const base_interfaces__msg__Booksupply__Sequence * lhs, const base_interfaces__msg__Booksupply__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interfaces__msg__Booksupply__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interfaces__msg__Booksupply__Sequence__copy(
  const base_interfaces__msg__Booksupply__Sequence * input,
  base_interfaces__msg__Booksupply__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interfaces__msg__Booksupply);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interfaces__msg__Booksupply * data =
      (base_interfaces__msg__Booksupply *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interfaces__msg__Booksupply__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interfaces__msg__Booksupply__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interfaces__msg__Booksupply__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

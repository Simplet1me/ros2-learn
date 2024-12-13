// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice
#include "base_interfaces/srv/detail/recharge__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `user_name`
#include "rosidl_runtime_c/string_functions.h"

bool
base_interfaces__srv__Recharge_Request__init(base_interfaces__srv__Recharge_Request * msg)
{
  if (!msg) {
    return false;
  }
  // user_name
  if (!rosidl_runtime_c__String__init(&msg->user_name)) {
    base_interfaces__srv__Recharge_Request__fini(msg);
    return false;
  }
  // user_recharge_amount
  return true;
}

void
base_interfaces__srv__Recharge_Request__fini(base_interfaces__srv__Recharge_Request * msg)
{
  if (!msg) {
    return;
  }
  // user_name
  rosidl_runtime_c__String__fini(&msg->user_name);
  // user_recharge_amount
}

bool
base_interfaces__srv__Recharge_Request__are_equal(const base_interfaces__srv__Recharge_Request * lhs, const base_interfaces__srv__Recharge_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // user_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->user_name), &(rhs->user_name)))
  {
    return false;
  }
  // user_recharge_amount
  if (lhs->user_recharge_amount != rhs->user_recharge_amount) {
    return false;
  }
  return true;
}

bool
base_interfaces__srv__Recharge_Request__copy(
  const base_interfaces__srv__Recharge_Request * input,
  base_interfaces__srv__Recharge_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // user_name
  if (!rosidl_runtime_c__String__copy(
      &(input->user_name), &(output->user_name)))
  {
    return false;
  }
  // user_recharge_amount
  output->user_recharge_amount = input->user_recharge_amount;
  return true;
}

base_interfaces__srv__Recharge_Request *
base_interfaces__srv__Recharge_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Request * msg = (base_interfaces__srv__Recharge_Request *)allocator.allocate(sizeof(base_interfaces__srv__Recharge_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interfaces__srv__Recharge_Request));
  bool success = base_interfaces__srv__Recharge_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interfaces__srv__Recharge_Request__destroy(base_interfaces__srv__Recharge_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interfaces__srv__Recharge_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interfaces__srv__Recharge_Request__Sequence__init(base_interfaces__srv__Recharge_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Request * data = NULL;

  if (size) {
    data = (base_interfaces__srv__Recharge_Request *)allocator.zero_allocate(size, sizeof(base_interfaces__srv__Recharge_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interfaces__srv__Recharge_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interfaces__srv__Recharge_Request__fini(&data[i - 1]);
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
base_interfaces__srv__Recharge_Request__Sequence__fini(base_interfaces__srv__Recharge_Request__Sequence * array)
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
      base_interfaces__srv__Recharge_Request__fini(&array->data[i]);
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

base_interfaces__srv__Recharge_Request__Sequence *
base_interfaces__srv__Recharge_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Request__Sequence * array = (base_interfaces__srv__Recharge_Request__Sequence *)allocator.allocate(sizeof(base_interfaces__srv__Recharge_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interfaces__srv__Recharge_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interfaces__srv__Recharge_Request__Sequence__destroy(base_interfaces__srv__Recharge_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interfaces__srv__Recharge_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interfaces__srv__Recharge_Request__Sequence__are_equal(const base_interfaces__srv__Recharge_Request__Sequence * lhs, const base_interfaces__srv__Recharge_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interfaces__srv__Recharge_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interfaces__srv__Recharge_Request__Sequence__copy(
  const base_interfaces__srv__Recharge_Request__Sequence * input,
  base_interfaces__srv__Recharge_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interfaces__srv__Recharge_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interfaces__srv__Recharge_Request * data =
      (base_interfaces__srv__Recharge_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interfaces__srv__Recharge_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interfaces__srv__Recharge_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interfaces__srv__Recharge_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `user_vip_level`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
base_interfaces__srv__Recharge_Response__init(base_interfaces__srv__Recharge_Response * msg)
{
  if (!msg) {
    return false;
  }
  // user_vip_level
  if (!rosidl_runtime_c__String__init(&msg->user_vip_level)) {
    base_interfaces__srv__Recharge_Response__fini(msg);
    return false;
  }
  // user_points
  return true;
}

void
base_interfaces__srv__Recharge_Response__fini(base_interfaces__srv__Recharge_Response * msg)
{
  if (!msg) {
    return;
  }
  // user_vip_level
  rosidl_runtime_c__String__fini(&msg->user_vip_level);
  // user_points
}

bool
base_interfaces__srv__Recharge_Response__are_equal(const base_interfaces__srv__Recharge_Response * lhs, const base_interfaces__srv__Recharge_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // user_vip_level
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->user_vip_level), &(rhs->user_vip_level)))
  {
    return false;
  }
  // user_points
  if (lhs->user_points != rhs->user_points) {
    return false;
  }
  return true;
}

bool
base_interfaces__srv__Recharge_Response__copy(
  const base_interfaces__srv__Recharge_Response * input,
  base_interfaces__srv__Recharge_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // user_vip_level
  if (!rosidl_runtime_c__String__copy(
      &(input->user_vip_level), &(output->user_vip_level)))
  {
    return false;
  }
  // user_points
  output->user_points = input->user_points;
  return true;
}

base_interfaces__srv__Recharge_Response *
base_interfaces__srv__Recharge_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Response * msg = (base_interfaces__srv__Recharge_Response *)allocator.allocate(sizeof(base_interfaces__srv__Recharge_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(base_interfaces__srv__Recharge_Response));
  bool success = base_interfaces__srv__Recharge_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
base_interfaces__srv__Recharge_Response__destroy(base_interfaces__srv__Recharge_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    base_interfaces__srv__Recharge_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
base_interfaces__srv__Recharge_Response__Sequence__init(base_interfaces__srv__Recharge_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Response * data = NULL;

  if (size) {
    data = (base_interfaces__srv__Recharge_Response *)allocator.zero_allocate(size, sizeof(base_interfaces__srv__Recharge_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = base_interfaces__srv__Recharge_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        base_interfaces__srv__Recharge_Response__fini(&data[i - 1]);
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
base_interfaces__srv__Recharge_Response__Sequence__fini(base_interfaces__srv__Recharge_Response__Sequence * array)
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
      base_interfaces__srv__Recharge_Response__fini(&array->data[i]);
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

base_interfaces__srv__Recharge_Response__Sequence *
base_interfaces__srv__Recharge_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  base_interfaces__srv__Recharge_Response__Sequence * array = (base_interfaces__srv__Recharge_Response__Sequence *)allocator.allocate(sizeof(base_interfaces__srv__Recharge_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = base_interfaces__srv__Recharge_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
base_interfaces__srv__Recharge_Response__Sequence__destroy(base_interfaces__srv__Recharge_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    base_interfaces__srv__Recharge_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
base_interfaces__srv__Recharge_Response__Sequence__are_equal(const base_interfaces__srv__Recharge_Response__Sequence * lhs, const base_interfaces__srv__Recharge_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!base_interfaces__srv__Recharge_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
base_interfaces__srv__Recharge_Response__Sequence__copy(
  const base_interfaces__srv__Recharge_Response__Sequence * input,
  base_interfaces__srv__Recharge_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(base_interfaces__srv__Recharge_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    base_interfaces__srv__Recharge_Response * data =
      (base_interfaces__srv__Recharge_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!base_interfaces__srv__Recharge_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          base_interfaces__srv__Recharge_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!base_interfaces__srv__Recharge_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

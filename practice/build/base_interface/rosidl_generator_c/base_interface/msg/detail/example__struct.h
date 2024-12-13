// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_H_
#define BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Example in the package base_interface.
typedef struct base_interface__msg__Example
{
  rosidl_runtime_c__String name;
  int32_t money;
  int32_t coop_rank;
  int32_t damage;
} base_interface__msg__Example;

// Struct for a sequence of base_interface__msg__Example.
typedef struct base_interface__msg__Example__Sequence
{
  base_interface__msg__Example * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interface__msg__Example__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_H_

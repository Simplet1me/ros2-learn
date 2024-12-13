// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_H_
#define BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'company_name'
// Member 'book_need_kind'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Bookneed in the package base_interfaces.
typedef struct base_interfaces__msg__Bookneed
{
  rosidl_runtime_c__String company_name;
  int32_t book_need_amount;
  rosidl_runtime_c__String book_need_kind;
} base_interfaces__msg__Bookneed;

// Struct for a sequence of base_interfaces__msg__Bookneed.
typedef struct base_interfaces__msg__Bookneed__Sequence
{
  base_interfaces__msg__Bookneed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__msg__Bookneed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_H_

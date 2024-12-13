// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces:msg/Booksupply.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_H_
#define BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Booksupply in the package base_interfaces.
typedef struct base_interfaces__msg__Booksupply
{
  rosidl_runtime_c__String company_name;
  int32_t book_supply_price;
} base_interfaces__msg__Booksupply;

// Struct for a sequence of base_interfaces__msg__Booksupply.
typedef struct base_interfaces__msg__Booksupply__Sequence
{
  base_interfaces__msg__Booksupply * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__msg__Booksupply__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_H_

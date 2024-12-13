// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interface:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__MESSAGE__STRUCT_H_
#define BASE_INTERFACE__MSG__DETAIL__MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Message in the package base_interface.
typedef struct base_interface__msg__Message
{
  int32_t a;
  int32_t b;
} base_interface__msg__Message;

// Struct for a sequence of base_interface__msg__Message.
typedef struct base_interface__msg__Message__Sequence
{
  base_interface__msg__Message * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interface__msg__Message__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACE__MSG__DETAIL__MESSAGE__STRUCT_H_

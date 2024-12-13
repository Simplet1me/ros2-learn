// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_H_
#define BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'user_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Recharge in the package base_interfaces.
typedef struct base_interfaces__srv__Recharge_Request
{
  rosidl_runtime_c__String user_name;
  int32_t user_recharge_amount;
} base_interfaces__srv__Recharge_Request;

// Struct for a sequence of base_interfaces__srv__Recharge_Request.
typedef struct base_interfaces__srv__Recharge_Request__Sequence
{
  base_interfaces__srv__Recharge_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__srv__Recharge_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'user_vip_level'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Recharge in the package base_interfaces.
typedef struct base_interfaces__srv__Recharge_Response
{
  rosidl_runtime_c__String user_vip_level;
  int32_t user_points;
} base_interfaces__srv__Recharge_Response;

// Struct for a sequence of base_interfaces__srv__Recharge_Response.
typedef struct base_interfaces__srv__Recharge_Response__Sequence
{
  base_interfaces__srv__Recharge_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__srv__Recharge_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_H_

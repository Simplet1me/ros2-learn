// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "base_interface/msg/detail/example__rosidl_typesupport_introspection_c.h"
#include "base_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "base_interface/msg/detail/example__functions.h"
#include "base_interface/msg/detail/example__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  base_interface__msg__Example__init(message_memory);
}

void base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_fini_function(void * message_memory)
{
  base_interface__msg__Example__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_member_array[4] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(base_interface__msg__Example, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "money",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(base_interface__msg__Example, money),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coop_rank",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(base_interface__msg__Example, coop_rank),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "damage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(base_interface__msg__Example, damage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_members = {
  "base_interface__msg",  // message namespace
  "Example",  // message name
  4,  // number of fields
  sizeof(base_interface__msg__Example),
  base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_member_array,  // message members
  base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_init_function,  // function to initialize message memory (memory has to be allocated)
  base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_type_support_handle = {
  0,
  &base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_base_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, base_interface, msg, Example)() {
  if (!base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_type_support_handle.typesupport_identifier) {
    base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &base_interface__msg__Example__rosidl_typesupport_introspection_c__Example_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

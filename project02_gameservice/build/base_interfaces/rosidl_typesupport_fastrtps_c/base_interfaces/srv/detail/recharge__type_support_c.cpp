// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice
#include "base_interfaces/srv/detail/recharge__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "base_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "base_interfaces/srv/detail/recharge__struct.h"
#include "base_interfaces/srv/detail/recharge__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // user_name
#include "rosidl_runtime_c/string_functions.h"  // user_name

// forward declare type support functions


using _Recharge_Request__ros_msg_type = base_interfaces__srv__Recharge_Request;

static bool _Recharge_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Recharge_Request__ros_msg_type * ros_message = static_cast<const _Recharge_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: user_name
  {
    const rosidl_runtime_c__String * str = &ros_message->user_name;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: user_recharge_amount
  {
    cdr << ros_message->user_recharge_amount;
  }

  return true;
}

static bool _Recharge_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Recharge_Request__ros_msg_type * ros_message = static_cast<_Recharge_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: user_name
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->user_name.data) {
      rosidl_runtime_c__String__init(&ros_message->user_name);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->user_name,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'user_name'\n");
      return false;
    }
  }

  // Field name: user_recharge_amount
  {
    cdr >> ros_message->user_recharge_amount;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t get_serialized_size_base_interfaces__srv__Recharge_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Recharge_Request__ros_msg_type * ros_message = static_cast<const _Recharge_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name user_name
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->user_name.size + 1);
  // field.name user_recharge_amount
  {
    size_t item_size = sizeof(ros_message->user_recharge_amount);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Recharge_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_base_interfaces__srv__Recharge_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t max_serialized_size_base_interfaces__srv__Recharge_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: user_name
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: user_recharge_amount
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = base_interfaces__srv__Recharge_Request;
    is_plain =
      (
      offsetof(DataType, user_recharge_amount) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Recharge_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_base_interfaces__srv__Recharge_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Recharge_Request = {
  "base_interfaces::srv",
  "Recharge_Request",
  _Recharge_Request__cdr_serialize,
  _Recharge_Request__cdr_deserialize,
  _Recharge_Request__get_serialized_size,
  _Recharge_Request__max_serialized_size
};

static rosidl_message_type_support_t _Recharge_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Recharge_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, srv, Recharge_Request)() {
  return &_Recharge_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "base_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "base_interfaces/srv/detail/recharge__struct.h"
// already included above
// #include "base_interfaces/srv/detail/recharge__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

// already included above
// #include "rosidl_runtime_c/string.h"  // user_vip_level
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // user_vip_level

// forward declare type support functions


using _Recharge_Response__ros_msg_type = base_interfaces__srv__Recharge_Response;

static bool _Recharge_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Recharge_Response__ros_msg_type * ros_message = static_cast<const _Recharge_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: user_vip_level
  {
    const rosidl_runtime_c__String * str = &ros_message->user_vip_level;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: user_points
  {
    cdr << ros_message->user_points;
  }

  return true;
}

static bool _Recharge_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Recharge_Response__ros_msg_type * ros_message = static_cast<_Recharge_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: user_vip_level
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->user_vip_level.data) {
      rosidl_runtime_c__String__init(&ros_message->user_vip_level);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->user_vip_level,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'user_vip_level'\n");
      return false;
    }
  }

  // Field name: user_points
  {
    cdr >> ros_message->user_points;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t get_serialized_size_base_interfaces__srv__Recharge_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Recharge_Response__ros_msg_type * ros_message = static_cast<const _Recharge_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name user_vip_level
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->user_vip_level.size + 1);
  // field.name user_points
  {
    size_t item_size = sizeof(ros_message->user_points);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Recharge_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_base_interfaces__srv__Recharge_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t max_serialized_size_base_interfaces__srv__Recharge_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: user_vip_level
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: user_points
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = base_interfaces__srv__Recharge_Response;
    is_plain =
      (
      offsetof(DataType, user_points) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Recharge_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_base_interfaces__srv__Recharge_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Recharge_Response = {
  "base_interfaces::srv",
  "Recharge_Response",
  _Recharge_Response__cdr_serialize,
  _Recharge_Response__cdr_deserialize,
  _Recharge_Response__get_serialized_size,
  _Recharge_Response__max_serialized_size
};

static rosidl_message_type_support_t _Recharge_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Recharge_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, srv, Recharge_Response)() {
  return &_Recharge_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "base_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "base_interfaces/srv/recharge.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t Recharge__callbacks = {
  "base_interfaces::srv",
  "Recharge",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, srv, Recharge_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, srv, Recharge_Response)(),
};

static rosidl_service_type_support_t Recharge__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &Recharge__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, srv, Recharge)() {
  return &Recharge__handle;
}

#if defined(__cplusplus)
}
#endif

// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice
#include "base_interfaces/msg/detail/bookneed__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "base_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "base_interfaces/msg/detail/bookneed__struct.h"
#include "base_interfaces/msg/detail/bookneed__functions.h"
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

#include "rosidl_runtime_c/string.h"  // book_need_kind, company_name
#include "rosidl_runtime_c/string_functions.h"  // book_need_kind, company_name

// forward declare type support functions


using _Bookneed__ros_msg_type = base_interfaces__msg__Bookneed;

static bool _Bookneed__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Bookneed__ros_msg_type * ros_message = static_cast<const _Bookneed__ros_msg_type *>(untyped_ros_message);
  // Field name: company_name
  {
    const rosidl_runtime_c__String * str = &ros_message->company_name;
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

  // Field name: book_need_amount
  {
    cdr << ros_message->book_need_amount;
  }

  // Field name: book_need_kind
  {
    const rosidl_runtime_c__String * str = &ros_message->book_need_kind;
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

  return true;
}

static bool _Bookneed__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Bookneed__ros_msg_type * ros_message = static_cast<_Bookneed__ros_msg_type *>(untyped_ros_message);
  // Field name: company_name
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->company_name.data) {
      rosidl_runtime_c__String__init(&ros_message->company_name);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->company_name,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'company_name'\n");
      return false;
    }
  }

  // Field name: book_need_amount
  {
    cdr >> ros_message->book_need_amount;
  }

  // Field name: book_need_kind
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->book_need_kind.data) {
      rosidl_runtime_c__String__init(&ros_message->book_need_kind);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->book_need_kind,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'book_need_kind'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t get_serialized_size_base_interfaces__msg__Bookneed(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Bookneed__ros_msg_type * ros_message = static_cast<const _Bookneed__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name company_name
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->company_name.size + 1);
  // field.name book_need_amount
  {
    size_t item_size = sizeof(ros_message->book_need_amount);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name book_need_kind
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->book_need_kind.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _Bookneed__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_base_interfaces__msg__Bookneed(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_base_interfaces
size_t max_serialized_size_base_interfaces__msg__Bookneed(
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

  // member: company_name
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
  // member: book_need_amount
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: book_need_kind
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = base_interfaces__msg__Bookneed;
    is_plain =
      (
      offsetof(DataType, book_need_kind) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Bookneed__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_base_interfaces__msg__Bookneed(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Bookneed = {
  "base_interfaces::msg",
  "Bookneed",
  _Bookneed__cdr_serialize,
  _Bookneed__cdr_deserialize,
  _Bookneed__get_serialized_size,
  _Bookneed__max_serialized_size
};

static rosidl_message_type_support_t _Bookneed__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Bookneed,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, base_interfaces, msg, Bookneed)() {
  return &_Bookneed__type_support;
}

#if defined(__cplusplus)
}
#endif

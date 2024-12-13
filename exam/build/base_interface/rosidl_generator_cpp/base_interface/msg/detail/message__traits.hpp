// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interface:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__MESSAGE__TRAITS_HPP_
#define BASE_INTERFACE__MSG__DETAIL__MESSAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interface/msg/detail/message__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const Message & msg,
  std::ostream & out)
{
  out << "{";
  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Message & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Message & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace base_interface

namespace rosidl_generator_traits
{

[[deprecated("use base_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interface::msg::Message & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_interface::msg::Message & msg)
{
  return base_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_interface::msg::Message>()
{
  return "base_interface::msg::Message";
}

template<>
inline const char * name<base_interface::msg::Message>()
{
  return "base_interface/msg/Message";
}

template<>
struct has_fixed_size<base_interface::msg::Message>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<base_interface::msg::Message>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<base_interface::msg::Message>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACE__MSG__DETAIL__MESSAGE__TRAITS_HPP_

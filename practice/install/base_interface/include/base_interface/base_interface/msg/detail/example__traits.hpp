// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__EXAMPLE__TRAITS_HPP_
#define BASE_INTERFACE__MSG__DETAIL__EXAMPLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interface/msg/detail/example__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const Example & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: money
  {
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
    out << ", ";
  }

  // member: coop_rank
  {
    out << "coop_rank: ";
    rosidl_generator_traits::value_to_yaml(msg.coop_rank, out);
    out << ", ";
  }

  // member: damage
  {
    out << "damage: ";
    rosidl_generator_traits::value_to_yaml(msg.damage, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Example & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: money
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "money: ";
    rosidl_generator_traits::value_to_yaml(msg.money, out);
    out << "\n";
  }

  // member: coop_rank
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coop_rank: ";
    rosidl_generator_traits::value_to_yaml(msg.coop_rank, out);
    out << "\n";
  }

  // member: damage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "damage: ";
    rosidl_generator_traits::value_to_yaml(msg.damage, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Example & msg, bool use_flow_style = false)
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
  const base_interface::msg::Example & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_interface::msg::Example & msg)
{
  return base_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_interface::msg::Example>()
{
  return "base_interface::msg::Example";
}

template<>
inline const char * name<base_interface::msg::Example>()
{
  return "base_interface/msg/Example";
}

template<>
struct has_fixed_size<base_interface::msg::Example>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_interface::msg::Example>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_interface::msg::Example>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACE__MSG__DETAIL__EXAMPLE__TRAITS_HPP_

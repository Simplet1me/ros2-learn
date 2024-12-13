// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKNEED__TRAITS_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKNEED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interfaces/msg/detail/bookneed__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Bookneed & msg,
  std::ostream & out)
{
  out << "{";
  // member: company_name
  {
    out << "company_name: ";
    rosidl_generator_traits::value_to_yaml(msg.company_name, out);
    out << ", ";
  }

  // member: book_need_amount
  {
    out << "book_need_amount: ";
    rosidl_generator_traits::value_to_yaml(msg.book_need_amount, out);
    out << ", ";
  }

  // member: book_need_kind
  {
    out << "book_need_kind: ";
    rosidl_generator_traits::value_to_yaml(msg.book_need_kind, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Bookneed & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: company_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "company_name: ";
    rosidl_generator_traits::value_to_yaml(msg.company_name, out);
    out << "\n";
  }

  // member: book_need_amount
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "book_need_amount: ";
    rosidl_generator_traits::value_to_yaml(msg.book_need_amount, out);
    out << "\n";
  }

  // member: book_need_kind
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "book_need_kind: ";
    rosidl_generator_traits::value_to_yaml(msg.book_need_kind, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Bookneed & msg, bool use_flow_style = false)
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

}  // namespace base_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces::msg::Bookneed & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces::msg::Bookneed & msg)
{
  return base_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces::msg::Bookneed>()
{
  return "base_interfaces::msg::Bookneed";
}

template<>
inline const char * name<base_interfaces::msg::Bookneed>()
{
  return "base_interfaces/msg/Bookneed";
}

template<>
struct has_fixed_size<base_interfaces::msg::Bookneed>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_interfaces::msg::Bookneed>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_interfaces::msg::Bookneed>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKNEED__TRAITS_HPP_

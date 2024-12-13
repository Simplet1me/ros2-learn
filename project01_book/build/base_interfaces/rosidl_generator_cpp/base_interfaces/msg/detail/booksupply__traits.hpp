// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interfaces:msg/Booksupply.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__TRAITS_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interfaces/msg/detail/booksupply__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Booksupply & msg,
  std::ostream & out)
{
  out << "{";
  // member: company_name
  {
    out << "company_name: ";
    rosidl_generator_traits::value_to_yaml(msg.company_name, out);
    out << ", ";
  }

  // member: book_supply_price
  {
    out << "book_supply_price: ";
    rosidl_generator_traits::value_to_yaml(msg.book_supply_price, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Booksupply & msg,
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

  // member: book_supply_price
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "book_supply_price: ";
    rosidl_generator_traits::value_to_yaml(msg.book_supply_price, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Booksupply & msg, bool use_flow_style = false)
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
  const base_interfaces::msg::Booksupply & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces::msg::Booksupply & msg)
{
  return base_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces::msg::Booksupply>()
{
  return "base_interfaces::msg::Booksupply";
}

template<>
inline const char * name<base_interfaces::msg::Booksupply>()
{
  return "base_interfaces/msg/Booksupply";
}

template<>
struct has_fixed_size<base_interfaces::msg::Booksupply>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_interfaces::msg::Booksupply>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_interfaces::msg::Booksupply>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__TRAITS_HPP_

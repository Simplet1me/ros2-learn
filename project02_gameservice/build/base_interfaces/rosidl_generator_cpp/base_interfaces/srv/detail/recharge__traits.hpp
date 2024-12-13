// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__SRV__DETAIL__RECHARGE__TRAITS_HPP_
#define BASE_INTERFACES__SRV__DETAIL__RECHARGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interfaces/srv/detail/recharge__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Recharge_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: user_name
  {
    out << "user_name: ";
    rosidl_generator_traits::value_to_yaml(msg.user_name, out);
    out << ", ";
  }

  // member: user_recharge_amount
  {
    out << "user_recharge_amount: ";
    rosidl_generator_traits::value_to_yaml(msg.user_recharge_amount, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Recharge_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: user_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "user_name: ";
    rosidl_generator_traits::value_to_yaml(msg.user_name, out);
    out << "\n";
  }

  // member: user_recharge_amount
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "user_recharge_amount: ";
    rosidl_generator_traits::value_to_yaml(msg.user_recharge_amount, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Recharge_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace base_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces::srv::Recharge_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces::srv::Recharge_Request & msg)
{
  return base_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces::srv::Recharge_Request>()
{
  return "base_interfaces::srv::Recharge_Request";
}

template<>
inline const char * name<base_interfaces::srv::Recharge_Request>()
{
  return "base_interfaces/srv/Recharge_Request";
}

template<>
struct has_fixed_size<base_interfaces::srv::Recharge_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_interfaces::srv::Recharge_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_interfaces::srv::Recharge_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace base_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Recharge_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: user_vip_level
  {
    out << "user_vip_level: ";
    rosidl_generator_traits::value_to_yaml(msg.user_vip_level, out);
    out << ", ";
  }

  // member: user_points
  {
    out << "user_points: ";
    rosidl_generator_traits::value_to_yaml(msg.user_points, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Recharge_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: user_vip_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "user_vip_level: ";
    rosidl_generator_traits::value_to_yaml(msg.user_vip_level, out);
    out << "\n";
  }

  // member: user_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "user_points: ";
    rosidl_generator_traits::value_to_yaml(msg.user_points, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Recharge_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace base_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces::srv::Recharge_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces::srv::Recharge_Response & msg)
{
  return base_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces::srv::Recharge_Response>()
{
  return "base_interfaces::srv::Recharge_Response";
}

template<>
inline const char * name<base_interfaces::srv::Recharge_Response>()
{
  return "base_interfaces/srv/Recharge_Response";
}

template<>
struct has_fixed_size<base_interfaces::srv::Recharge_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<base_interfaces::srv::Recharge_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<base_interfaces::srv::Recharge_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<base_interfaces::srv::Recharge>()
{
  return "base_interfaces::srv::Recharge";
}

template<>
inline const char * name<base_interfaces::srv::Recharge>()
{
  return "base_interfaces/srv/Recharge";
}

template<>
struct has_fixed_size<base_interfaces::srv::Recharge>
  : std::integral_constant<
    bool,
    has_fixed_size<base_interfaces::srv::Recharge_Request>::value &&
    has_fixed_size<base_interfaces::srv::Recharge_Response>::value
  >
{
};

template<>
struct has_bounded_size<base_interfaces::srv::Recharge>
  : std::integral_constant<
    bool,
    has_bounded_size<base_interfaces::srv::Recharge_Request>::value &&
    has_bounded_size<base_interfaces::srv::Recharge_Response>::value
  >
{
};

template<>
struct is_service<base_interfaces::srv::Recharge>
  : std::true_type
{
};

template<>
struct is_service_request<base_interfaces::srv::Recharge_Request>
  : std::true_type
{
};

template<>
struct is_service_response<base_interfaces::srv::Recharge_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACES__SRV__DETAIL__RECHARGE__TRAITS_HPP_

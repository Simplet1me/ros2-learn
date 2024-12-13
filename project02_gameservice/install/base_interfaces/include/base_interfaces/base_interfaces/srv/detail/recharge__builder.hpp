// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__SRV__DETAIL__RECHARGE__BUILDER_HPP_
#define BASE_INTERFACES__SRV__DETAIL__RECHARGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces/srv/detail/recharge__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces
{

namespace srv
{

namespace builder
{

class Init_Recharge_Request_user_recharge_amount
{
public:
  explicit Init_Recharge_Request_user_recharge_amount(::base_interfaces::srv::Recharge_Request & msg)
  : msg_(msg)
  {}
  ::base_interfaces::srv::Recharge_Request user_recharge_amount(::base_interfaces::srv::Recharge_Request::_user_recharge_amount_type arg)
  {
    msg_.user_recharge_amount = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::srv::Recharge_Request msg_;
};

class Init_Recharge_Request_user_name
{
public:
  Init_Recharge_Request_user_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Recharge_Request_user_recharge_amount user_name(::base_interfaces::srv::Recharge_Request::_user_name_type arg)
  {
    msg_.user_name = std::move(arg);
    return Init_Recharge_Request_user_recharge_amount(msg_);
  }

private:
  ::base_interfaces::srv::Recharge_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::srv::Recharge_Request>()
{
  return base_interfaces::srv::builder::Init_Recharge_Request_user_name();
}

}  // namespace base_interfaces


namespace base_interfaces
{

namespace srv
{

namespace builder
{

class Init_Recharge_Response_user_points
{
public:
  explicit Init_Recharge_Response_user_points(::base_interfaces::srv::Recharge_Response & msg)
  : msg_(msg)
  {}
  ::base_interfaces::srv::Recharge_Response user_points(::base_interfaces::srv::Recharge_Response::_user_points_type arg)
  {
    msg_.user_points = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::srv::Recharge_Response msg_;
};

class Init_Recharge_Response_user_vip_level
{
public:
  Init_Recharge_Response_user_vip_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Recharge_Response_user_points user_vip_level(::base_interfaces::srv::Recharge_Response::_user_vip_level_type arg)
  {
    msg_.user_vip_level = std::move(arg);
    return Init_Recharge_Response_user_points(msg_);
  }

private:
  ::base_interfaces::srv::Recharge_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::srv::Recharge_Response>()
{
  return base_interfaces::srv::builder::Init_Recharge_Response_user_vip_level();
}

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__SRV__DETAIL__RECHARGE__BUILDER_HPP_

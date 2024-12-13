// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__EXAMPLE__BUILDER_HPP_
#define BASE_INTERFACE__MSG__DETAIL__EXAMPLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interface/msg/detail/example__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interface
{

namespace msg
{

namespace builder
{

class Init_Example_damage
{
public:
  explicit Init_Example_damage(::base_interface::msg::Example & msg)
  : msg_(msg)
  {}
  ::base_interface::msg::Example damage(::base_interface::msg::Example::_damage_type arg)
  {
    msg_.damage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interface::msg::Example msg_;
};

class Init_Example_coop_rank
{
public:
  explicit Init_Example_coop_rank(::base_interface::msg::Example & msg)
  : msg_(msg)
  {}
  Init_Example_damage coop_rank(::base_interface::msg::Example::_coop_rank_type arg)
  {
    msg_.coop_rank = std::move(arg);
    return Init_Example_damage(msg_);
  }

private:
  ::base_interface::msg::Example msg_;
};

class Init_Example_money
{
public:
  explicit Init_Example_money(::base_interface::msg::Example & msg)
  : msg_(msg)
  {}
  Init_Example_coop_rank money(::base_interface::msg::Example::_money_type arg)
  {
    msg_.money = std::move(arg);
    return Init_Example_coop_rank(msg_);
  }

private:
  ::base_interface::msg::Example msg_;
};

class Init_Example_name
{
public:
  Init_Example_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Example_money name(::base_interface::msg::Example::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Example_money(msg_);
  }

private:
  ::base_interface::msg::Example msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interface::msg::Example>()
{
  return base_interface::msg::builder::Init_Example_name();
}

}  // namespace base_interface

#endif  // BASE_INTERFACE__MSG__DETAIL__EXAMPLE__BUILDER_HPP_

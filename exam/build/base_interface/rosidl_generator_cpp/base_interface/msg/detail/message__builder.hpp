// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interface:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__MESSAGE__BUILDER_HPP_
#define BASE_INTERFACE__MSG__DETAIL__MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interface/msg/detail/message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interface
{

namespace msg
{

namespace builder
{

class Init_Message_b
{
public:
  explicit Init_Message_b(::base_interface::msg::Message & msg)
  : msg_(msg)
  {}
  ::base_interface::msg::Message b(::base_interface::msg::Message::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interface::msg::Message msg_;
};

class Init_Message_a
{
public:
  Init_Message_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Message_b a(::base_interface::msg::Message::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Message_b(msg_);
  }

private:
  ::base_interface::msg::Message msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interface::msg::Message>()
{
  return base_interface::msg::builder::Init_Message_a();
}

}  // namespace base_interface

#endif  // BASE_INTERFACE__MSG__DETAIL__MESSAGE__BUILDER_HPP_

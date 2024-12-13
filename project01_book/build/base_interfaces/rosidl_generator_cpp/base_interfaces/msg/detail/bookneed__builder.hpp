// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKNEED__BUILDER_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKNEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces/msg/detail/bookneed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces
{

namespace msg
{

namespace builder
{

class Init_Bookneed_book_need_kind
{
public:
  explicit Init_Bookneed_book_need_kind(::base_interfaces::msg::Bookneed & msg)
  : msg_(msg)
  {}
  ::base_interfaces::msg::Bookneed book_need_kind(::base_interfaces::msg::Bookneed::_book_need_kind_type arg)
  {
    msg_.book_need_kind = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::msg::Bookneed msg_;
};

class Init_Bookneed_book_need_amount
{
public:
  explicit Init_Bookneed_book_need_amount(::base_interfaces::msg::Bookneed & msg)
  : msg_(msg)
  {}
  Init_Bookneed_book_need_kind book_need_amount(::base_interfaces::msg::Bookneed::_book_need_amount_type arg)
  {
    msg_.book_need_amount = std::move(arg);
    return Init_Bookneed_book_need_kind(msg_);
  }

private:
  ::base_interfaces::msg::Bookneed msg_;
};

class Init_Bookneed_company_name
{
public:
  Init_Bookneed_company_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bookneed_book_need_amount company_name(::base_interfaces::msg::Bookneed::_company_name_type arg)
  {
    msg_.company_name = std::move(arg);
    return Init_Bookneed_book_need_amount(msg_);
  }

private:
  ::base_interfaces::msg::Bookneed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::msg::Bookneed>()
{
  return base_interfaces::msg::builder::Init_Bookneed_company_name();
}

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKNEED__BUILDER_HPP_

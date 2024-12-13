// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces:msg/Booksupply.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__BUILDER_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces/msg/detail/booksupply__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces
{

namespace msg
{

namespace builder
{

class Init_Booksupply_book_supply_price
{
public:
  explicit Init_Booksupply_book_supply_price(::base_interfaces::msg::Booksupply & msg)
  : msg_(msg)
  {}
  ::base_interfaces::msg::Booksupply book_supply_price(::base_interfaces::msg::Booksupply::_book_supply_price_type arg)
  {
    msg_.book_supply_price = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::msg::Booksupply msg_;
};

class Init_Booksupply_company_name
{
public:
  Init_Booksupply_company_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Booksupply_book_supply_price company_name(::base_interfaces::msg::Booksupply::_company_name_type arg)
  {
    msg_.company_name = std::move(arg);
    return Init_Booksupply_book_supply_price(msg_);
  }

private:
  ::base_interfaces::msg::Booksupply msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::msg::Booksupply>()
{
  return base_interfaces::msg::builder::Init_Booksupply_company_name();
}

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__BUILDER_HPP_

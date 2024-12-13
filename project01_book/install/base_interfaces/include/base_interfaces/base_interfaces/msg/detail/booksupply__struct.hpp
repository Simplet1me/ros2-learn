// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_interfaces:msg/Booksupply.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_interfaces__msg__Booksupply __attribute__((deprecated))
#else
# define DEPRECATED__base_interfaces__msg__Booksupply __declspec(deprecated)
#endif

namespace base_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Booksupply_
{
  using Type = Booksupply_<ContainerAllocator>;

  explicit Booksupply_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->company_name = "";
      this->book_supply_price = 0l;
    }
  }

  explicit Booksupply_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : company_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->company_name = "";
      this->book_supply_price = 0l;
    }
  }

  // field types and members
  using _company_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _company_name_type company_name;
  using _book_supply_price_type =
    int32_t;
  _book_supply_price_type book_supply_price;

  // setters for named parameter idiom
  Type & set__company_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->company_name = _arg;
    return *this;
  }
  Type & set__book_supply_price(
    const int32_t & _arg)
  {
    this->book_supply_price = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interfaces::msg::Booksupply_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interfaces::msg::Booksupply_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Booksupply_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Booksupply_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interfaces__msg__Booksupply
    std::shared_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interfaces__msg__Booksupply
    std::shared_ptr<base_interfaces::msg::Booksupply_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Booksupply_ & other) const
  {
    if (this->company_name != other.company_name) {
      return false;
    }
    if (this->book_supply_price != other.book_supply_price) {
      return false;
    }
    return true;
  }
  bool operator!=(const Booksupply_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Booksupply_

// alias to use template instance with default allocator
using Booksupply =
  base_interfaces::msg::Booksupply_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKSUPPLY__STRUCT_HPP_

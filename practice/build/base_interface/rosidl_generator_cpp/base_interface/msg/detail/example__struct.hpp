// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_interface:msg/Example.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_HPP_
#define BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_interface__msg__Example __attribute__((deprecated))
#else
# define DEPRECATED__base_interface__msg__Example __declspec(deprecated)
#endif

namespace base_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Example_
{
  using Type = Example_<ContainerAllocator>;

  explicit Example_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->money = 0l;
      this->coop_rank = 0l;
      this->damage = 0l;
    }
  }

  explicit Example_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->money = 0l;
      this->coop_rank = 0l;
      this->damage = 0l;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _money_type =
    int32_t;
  _money_type money;
  using _coop_rank_type =
    int32_t;
  _coop_rank_type coop_rank;
  using _damage_type =
    int32_t;
  _damage_type damage;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__money(
    const int32_t & _arg)
  {
    this->money = _arg;
    return *this;
  }
  Type & set__coop_rank(
    const int32_t & _arg)
  {
    this->coop_rank = _arg;
    return *this;
  }
  Type & set__damage(
    const int32_t & _arg)
  {
    this->damage = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interface::msg::Example_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interface::msg::Example_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interface::msg::Example_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interface::msg::Example_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interface::msg::Example_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interface::msg::Example_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interface::msg::Example_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interface::msg::Example_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interface::msg::Example_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interface::msg::Example_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interface__msg__Example
    std::shared_ptr<base_interface::msg::Example_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interface__msg__Example
    std::shared_ptr<base_interface::msg::Example_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Example_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->money != other.money) {
      return false;
    }
    if (this->coop_rank != other.coop_rank) {
      return false;
    }
    if (this->damage != other.damage) {
      return false;
    }
    return true;
  }
  bool operator!=(const Example_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Example_

// alias to use template instance with default allocator
using Example =
  base_interface::msg::Example_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace base_interface

#endif  // BASE_INTERFACE__MSG__DETAIL__EXAMPLE__STRUCT_HPP_

// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_HPP_
#define BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_interfaces__msg__Bookneed __attribute__((deprecated))
#else
# define DEPRECATED__base_interfaces__msg__Bookneed __declspec(deprecated)
#endif

namespace base_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Bookneed_
{
  using Type = Bookneed_<ContainerAllocator>;

  explicit Bookneed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->company_name = "";
      this->book_need_amount = 0l;
      this->book_need_kind = "";
    }
  }

  explicit Bookneed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : company_name(_alloc),
    book_need_kind(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->company_name = "";
      this->book_need_amount = 0l;
      this->book_need_kind = "";
    }
  }

  // field types and members
  using _company_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _company_name_type company_name;
  using _book_need_amount_type =
    int32_t;
  _book_need_amount_type book_need_amount;
  using _book_need_kind_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _book_need_kind_type book_need_kind;

  // setters for named parameter idiom
  Type & set__company_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->company_name = _arg;
    return *this;
  }
  Type & set__book_need_amount(
    const int32_t & _arg)
  {
    this->book_need_amount = _arg;
    return *this;
  }
  Type & set__book_need_kind(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->book_need_kind = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interfaces::msg::Bookneed_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interfaces::msg::Bookneed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Bookneed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Bookneed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interfaces__msg__Bookneed
    std::shared_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interfaces__msg__Bookneed
    std::shared_ptr<base_interfaces::msg::Bookneed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bookneed_ & other) const
  {
    if (this->company_name != other.company_name) {
      return false;
    }
    if (this->book_need_amount != other.book_need_amount) {
      return false;
    }
    if (this->book_need_kind != other.book_need_kind) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bookneed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bookneed_

// alias to use template instance with default allocator
using Bookneed =
  base_interfaces::msg::Bookneed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKNEED__STRUCT_HPP_

// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_interfaces:srv/Recharge.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_HPP_
#define BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_interfaces__srv__Recharge_Request __attribute__((deprecated))
#else
# define DEPRECATED__base_interfaces__srv__Recharge_Request __declspec(deprecated)
#endif

namespace base_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Recharge_Request_
{
  using Type = Recharge_Request_<ContainerAllocator>;

  explicit Recharge_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user_name = "";
      this->user_recharge_amount = 0l;
    }
  }

  explicit Recharge_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : user_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user_name = "";
      this->user_recharge_amount = 0l;
    }
  }

  // field types and members
  using _user_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _user_name_type user_name;
  using _user_recharge_amount_type =
    int32_t;
  _user_recharge_amount_type user_recharge_amount;

  // setters for named parameter idiom
  Type & set__user_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->user_name = _arg;
    return *this;
  }
  Type & set__user_recharge_amount(
    const int32_t & _arg)
  {
    this->user_recharge_amount = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interfaces::srv::Recharge_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interfaces::srv::Recharge_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interfaces::srv::Recharge_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interfaces::srv::Recharge_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interfaces__srv__Recharge_Request
    std::shared_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interfaces__srv__Recharge_Request
    std::shared_ptr<base_interfaces::srv::Recharge_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Recharge_Request_ & other) const
  {
    if (this->user_name != other.user_name) {
      return false;
    }
    if (this->user_recharge_amount != other.user_recharge_amount) {
      return false;
    }
    return true;
  }
  bool operator!=(const Recharge_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Recharge_Request_

// alias to use template instance with default allocator
using Recharge_Request =
  base_interfaces::srv::Recharge_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace base_interfaces


#ifndef _WIN32
# define DEPRECATED__base_interfaces__srv__Recharge_Response __attribute__((deprecated))
#else
# define DEPRECATED__base_interfaces__srv__Recharge_Response __declspec(deprecated)
#endif

namespace base_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Recharge_Response_
{
  using Type = Recharge_Response_<ContainerAllocator>;

  explicit Recharge_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user_vip_level = "";
      this->user_points = 0l;
    }
  }

  explicit Recharge_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : user_vip_level(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->user_vip_level = "";
      this->user_points = 0l;
    }
  }

  // field types and members
  using _user_vip_level_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _user_vip_level_type user_vip_level;
  using _user_points_type =
    int32_t;
  _user_points_type user_points;

  // setters for named parameter idiom
  Type & set__user_vip_level(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->user_vip_level = _arg;
    return *this;
  }
  Type & set__user_points(
    const int32_t & _arg)
  {
    this->user_points = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interfaces::srv::Recharge_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interfaces::srv::Recharge_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interfaces::srv::Recharge_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interfaces::srv::Recharge_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interfaces__srv__Recharge_Response
    std::shared_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interfaces__srv__Recharge_Response
    std::shared_ptr<base_interfaces::srv::Recharge_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Recharge_Response_ & other) const
  {
    if (this->user_vip_level != other.user_vip_level) {
      return false;
    }
    if (this->user_points != other.user_points) {
      return false;
    }
    return true;
  }
  bool operator!=(const Recharge_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Recharge_Response_

// alias to use template instance with default allocator
using Recharge_Response =
  base_interfaces::srv::Recharge_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace base_interfaces

namespace base_interfaces
{

namespace srv
{

struct Recharge
{
  using Request = base_interfaces::srv::Recharge_Request;
  using Response = base_interfaces::srv::Recharge_Response;
};

}  // namespace srv

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__SRV__DETAIL__RECHARGE__STRUCT_HPP_

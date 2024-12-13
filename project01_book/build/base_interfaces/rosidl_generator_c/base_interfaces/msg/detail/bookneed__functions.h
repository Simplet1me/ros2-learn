// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from base_interfaces:msg/Bookneed.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__BOOKNEED__FUNCTIONS_H_
#define BASE_INTERFACES__MSG__DETAIL__BOOKNEED__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "base_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "base_interfaces/msg/detail/bookneed__struct.h"

/// Initialize msg/Bookneed message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * base_interfaces__msg__Bookneed
 * )) before or use
 * base_interfaces__msg__Bookneed__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__init(base_interfaces__msg__Bookneed * msg);

/// Finalize msg/Bookneed message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
void
base_interfaces__msg__Bookneed__fini(base_interfaces__msg__Bookneed * msg);

/// Create msg/Bookneed message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * base_interfaces__msg__Bookneed__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
base_interfaces__msg__Bookneed *
base_interfaces__msg__Bookneed__create();

/// Destroy msg/Bookneed message.
/**
 * It calls
 * base_interfaces__msg__Bookneed__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
void
base_interfaces__msg__Bookneed__destroy(base_interfaces__msg__Bookneed * msg);

/// Check for msg/Bookneed message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__are_equal(const base_interfaces__msg__Bookneed * lhs, const base_interfaces__msg__Bookneed * rhs);

/// Copy a msg/Bookneed message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__copy(
  const base_interfaces__msg__Bookneed * input,
  base_interfaces__msg__Bookneed * output);

/// Initialize array of msg/Bookneed messages.
/**
 * It allocates the memory for the number of elements and calls
 * base_interfaces__msg__Bookneed__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__Sequence__init(base_interfaces__msg__Bookneed__Sequence * array, size_t size);

/// Finalize array of msg/Bookneed messages.
/**
 * It calls
 * base_interfaces__msg__Bookneed__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
void
base_interfaces__msg__Bookneed__Sequence__fini(base_interfaces__msg__Bookneed__Sequence * array);

/// Create array of msg/Bookneed messages.
/**
 * It allocates the memory for the array and calls
 * base_interfaces__msg__Bookneed__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
base_interfaces__msg__Bookneed__Sequence *
base_interfaces__msg__Bookneed__Sequence__create(size_t size);

/// Destroy array of msg/Bookneed messages.
/**
 * It calls
 * base_interfaces__msg__Bookneed__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
void
base_interfaces__msg__Bookneed__Sequence__destroy(base_interfaces__msg__Bookneed__Sequence * array);

/// Check for msg/Bookneed message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__Sequence__are_equal(const base_interfaces__msg__Bookneed__Sequence * lhs, const base_interfaces__msg__Bookneed__Sequence * rhs);

/// Copy an array of msg/Bookneed messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_base_interfaces
bool
base_interfaces__msg__Bookneed__Sequence__copy(
  const base_interfaces__msg__Bookneed__Sequence * input,
  base_interfaces__msg__Bookneed__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__MSG__DETAIL__BOOKNEED__FUNCTIONS_H_

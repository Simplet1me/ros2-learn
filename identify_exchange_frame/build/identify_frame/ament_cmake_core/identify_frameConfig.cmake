# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_identify_frame_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED identify_frame_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(identify_frame_FOUND FALSE)
  elseif(NOT identify_frame_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(identify_frame_FOUND FALSE)
  endif()
  return()
endif()
set(_identify_frame_CONFIG_INCLUDED TRUE)

# output package information
if(NOT identify_frame_FIND_QUIETLY)
  message(STATUS "Found identify_frame: 0.0.1 (${identify_frame_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'identify_frame' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${identify_frame_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(identify_frame_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${identify_frame_DIR}/${_extra}")
endforeach()

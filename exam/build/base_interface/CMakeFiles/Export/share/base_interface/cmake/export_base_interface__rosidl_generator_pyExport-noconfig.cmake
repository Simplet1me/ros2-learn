#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "base_interface::base_interface__rosidl_generator_py" for configuration ""
set_property(TARGET base_interface::base_interface__rosidl_generator_py APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(base_interface::base_interface__rosidl_generator_py PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbase_interface__rosidl_generator_py.so"
  IMPORTED_SONAME_NOCONFIG "libbase_interface__rosidl_generator_py.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS base_interface::base_interface__rosidl_generator_py )
list(APPEND _IMPORT_CHECK_FILES_FOR_base_interface::base_interface__rosidl_generator_py "${_IMPORT_PREFIX}/lib/libbase_interface__rosidl_generator_py.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

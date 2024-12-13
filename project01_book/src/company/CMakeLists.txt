cmake_minimum_required(VERSION 3.8)
project(company)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(base_interfaces REQUIRED)


add_executable(company_a src/company_a.cpp)
add_executable(company_b src/company_b.cpp)
add_executable(company_c src/company_c.cpp)

target_include_directories(company_a PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(company_a PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


ament_target_dependencies(
  company_a
  "rclcpp"
  "std_msgs"
  "base_interfaces"
)

ament_target_dependencies(
  company_b
  "rclcpp"
  "std_msgs"
  "base_interfaces"
)

ament_target_dependencies(
  company_c
  "rclcpp"
  "std_msgs"
  "base_interfaces"
)

install(TARGETS company_a
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS company_b
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS company_c
  DESTINATION lib/${PROJECT_NAME})



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

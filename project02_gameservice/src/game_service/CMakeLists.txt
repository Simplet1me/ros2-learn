cmake_minimum_required(VERSION 3.8)
project(game_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(base_interfaces REQUIRED)

add_executable(game_server src/game_server.cpp)
add_executable(game_client src/game_client.cpp)



target_include_directories(game_server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(game_server PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


ament_target_dependencies(
  game_server
  "rclcpp"
  "base_interfaces"
)

ament_target_dependencies(
  game_client
  "rclcpp"
  "base_interfaces"
)



install(TARGETS game_server
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS game_client
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

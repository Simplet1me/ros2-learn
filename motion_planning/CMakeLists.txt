cmake_minimum_required(VERSION 3.8)
project(motion_planning)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(tf2_ros REQUIRED)

find_package(pcl_conversions REQUIRED)

find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

add_executable(motion_demo_node
  src/motion_demo.cpp
)

target_link_libraries(motion_demo_node
  ${PCL_LIBRARIES}
  TBB::tbb
)

ament_target_dependencies(motion_demo_node
  "rclcpp"
  "geometry_msgs"
  "nav_msgs"
  "pcl_ros"
  "sensor_msgs"
  "visualization_msgs"
)

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

# install executable file
install(TARGETS 
  motion_demo_node
  DESTINATION lib/${PROJECT_NAME} 
)

ament_package()

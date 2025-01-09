cmake_minimum_required(VERSION 3.8)
project(cpp01_png_sreach)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(base_interfaces REQUIRED)
find_package(pcl_conversions REQUIRED)

add_executable(demo01_map_pub src/demo01_map_pub.cpp)

add_executable(demo02_astart src/demo02_astart.cpp)

add_executable(demo03_astart_practice src/demo03_astart_practice.cpp)

add_executable(demo04_tf_pub src/demo04_tf_pub.cpp)

add_executable(demo04_astar_srv src/demo04_astar_srv.cpp)

add_executable(demo05_labmap src/demo05_labmap.cpp)

target_include_directories(demo01_map_pub PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

include_directories(
  /usr/include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${RVIZ2_INCLUDE_DIRS}
  /usr/include/OGRE
)
target_compile_features(demo01_map_pub PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17


ament_target_dependencies(
  demo01_map_pub
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
)

ament_target_dependencies(
  demo02_astart
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
)

ament_target_dependencies(
  demo03_astart_practice
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
)

ament_target_dependencies(
  demo04_tf_pub
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
  "base_interfaces"
)

ament_target_dependencies(
  demo04_astar_srv
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
  "base_interfaces"
)

ament_target_dependencies(
  demo05_labmap
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "sensor_msgs"
  "nav_msgs"
  "base_interfaces"
  "pcl_conversions"
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

install(TARGETS demo01_map_pub DESTINATION lib/${PROJECT_NAME})
install(TARGETS demo02_astart DESTINATION lib/${PROJECT_NAME})
install(TARGETS demo03_astart_practice DESTINATION lib/${PROJECT_NAME})
install(TARGETS demo04_tf_pub DESTINATION lib/${PROJECT_NAME})
install(TARGETS demo04_astar_srv DESTINATION lib/${PROJECT_NAME})
install(TARGETS demo05_labmap DESTINATION lib/${PROJECT_NAME})

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

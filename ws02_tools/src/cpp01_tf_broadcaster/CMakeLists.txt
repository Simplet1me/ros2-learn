cmake_minimum_required(VERSION 3.8)
project(cpp01_tf_broadcaster)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

find_package(sensor_msgs REQUIRED)
find_package(PCL REQUIRED)
find_package(rviz2 REQUIRED)
find_package(pcl_conversions REQUIRED)

# 外部库
find_package(Eigen3 REQUIRED)

include_directories(
  /usr/include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${RVIZ2_INCLUDE_DIRS}
  /usr/include/OGRE
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

add_executable(demo01_static_tf_broadcaster src/demo01_static_tf_broadcaster.cpp)
add_executable(demo00_run src/demo00_run.cpp)
add_executable(demo02_dynamic_tf_broadcaster src/demo02_dynamic_tf_broadcaster.cpp)
add_executable(demo00_run1 src/demo00_run1.cpp)
add_executable(demo03_tf_listener src/demo03_tf_listener.cpp)
add_executable(demo04_pcl_reader src/demo04_pcl_reader.cpp)
add_executable(demo05_point_tf_broadcaster src/demo05_point_tf_broadcaster.cpp)
add_executable(demo06_buffer src/demo06_buffer.cpp)
add_executable(demo07_msg_filter src/demo07_msg_filter.cpp)

target_include_directories(demo01_static_tf_broadcaster PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)


target_compile_features(demo01_static_tf_broadcaster PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

target_link_libraries(demo04_pcl_reader
  ${PCL_LIBRARIES}
)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

ament_target_dependencies(
  demo01_static_tf_broadcaster
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
  
)
ament_target_dependencies(
  demo06_buffer
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
  
)

ament_target_dependencies(
  demo00_run
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  demo02_dynamic_tf_broadcaster
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  demo00_run1
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  demo03_tf_listener
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  demo05_point_tf_broadcaster
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  demo07_msg_filter
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "tf2_geometry_msgs"
  "turtlesim"
  "message_filters"
)

ament_target_dependencies(
  demo04_pcl_reader
  "rclcpp"
  "tf2"
  "tf2_ros"
  "geometry_msgs"
  "turtlesim"
  "sensor_msgs"
  "pcl_conversions"
)

#ament_target_dependencies(reg_pcl rclcpp sensor_msgs)

install(TARGETS demo01_static_tf_broadcaster
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo05_point_tf_broadcaster
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo06_buffer
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo07_msg_filter
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo03_tf_listener
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo00_run
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo02_dynamic_tf_broadcaster
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo00_run1
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo04_pcl_reader
  DESTINATION lib/${PROJECT_NAME})  

install(TARGETS 
demo04_pcl_reader 
  EXPORT export_${PROJECT_NAME}
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

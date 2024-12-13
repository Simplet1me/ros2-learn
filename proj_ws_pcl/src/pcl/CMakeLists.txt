cmake_minimum_required(VERSION 3.5)
project(pcl)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

#########################################################
# 寻找依赖库（标准库）
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)
find_package(pcl_conversions REQUIRED)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# 寻找依赖库（外部库）
find_package(Eigen3 REQUIRED)
# 针对PCL库版本不适配会出现warning，做的取消注释，其实没有解决问题，真正补丁在pcl的github的4431，如果不用补丁需要升级pcl的版本为1.12.我使用的是1.8版本会报错
#if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
#  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
#endif()


# 添加包含路径
include_directories(
  /usr/include
  ${EIGEN3_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${RVIZ2_INCLUDE_DIRS}
  /usr/include/OGRE
)



# 添加可执行文件
add_executable(reg_pcl src/reg_pcl.cpp)
ament_target_dependencies(reg_pcl 
    rclcpp 
    sensor_msgs
    pcl_conversions
)

target_link_libraries(reg_pcl
  ${PCL_LIBRARIES}
)

target_include_directories(reg_pcl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS reg_pcl
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS 
  reg_pcl 
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()


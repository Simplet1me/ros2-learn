#在cmake项目中，执行cmake命令，是会先找到本目录的顶层cmakelists文件，为它生成makefile
#在笔者看来，colcon无非就是加了一些东西，例如amment_package()此类的指令，可以识别它是ros2项目，
#然后利用cmake结合脚本实现命令行自动化构建项目
cmake_minimum_required(VERSION 3.8)
project(identify_frame)
#set cxx standard
#设置c++标准，每个标准的语法要求不同
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#打开编译器警告选项，不同编译器，会有不同选项
#开启编译器警告选项，有利于编译期发现潜在问题
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()
#REQUIRED参数，如果没有在系统下找对对应包，就会终止生成makefile过程
#如果找到，他们就会为每个包定义变量：头文件路径，库路径，下面的OpenCV_LIBS就是
find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(rclcpp_components REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
#find_package(image_transport_plugins REQUIRED)
################
#Custom Library#
################
#指定库搜索路径，以便运行程序时，能够定位到相应动态库，将它加载至内存中
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}")

#头文件路径
#所有target目标（cmakelists中生成的executable,library)都会去搜索本路径下的头文件
include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
#生成动态库
add_library(Slover SHARED
${CMAKE_CURRENT_SOURCE_DIR}/include/filter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/keyPoints.cpp
)

#链接第三方库Eigen,Opencv
target_link_libraries(
  Slover
  PUBLIC
  Eigen3::Eigen
)


###############
#Test Progaram#
###############
#此为测试程序
add_executable(
  progaram
  ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
)

target_link_libraries(
  progaram
  PRIVATE
  Slover
)
INSTALL(
  TARGETS progaram
  DESTINATION lib/${PROJECT_NAME}
)
INSTALL(
  FILES include/keyPoints.hpp include/filter.hpp
  DESTINATION include
)
#################
#Auto complement#
#################
set(target_dependenices_list
image_transport_plugins
rclcpp
cv_bridge
image_transport
visualization_msgs
sensor_msgs
)
set(FOUND_INCLUDE_DIRS "")
set(FOUND_LIBRARY_DIRS "")
foreach(dep_ ${target_dependenices_list})
  if(${dep_}_FOUND)
  list(APPEND FOUND_INCLUDE_DIRS ${${dep_}_INCLUDE_DIRS})
  list(APPEND FOUND_LIBRARY_DIRS ${${dep_}_LIBRARIES})
  endif()
endforeach()
#生成动态库
set(RM_PROJECT engineering)
add_library(${RM_PROJECT}
SHARED src/identify_node.cpp)

target_include_directories(${RM_PROJECT}
PRIVATE ${FOUND_INCLUDE_DIRS} 
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
#链接Slover(自定义库)和一些第三方库
target_link_libraries(${RM_PROJECT}
PRIVATE Slover 
PRIVATE ${FOUND_LIBRARY_DIRS})

rclcpp_components_register_node(${RM_PROJECT}
  PLUGIN Identify::identify_node
  EXECUTABLE ${RM_PROJECT}_node
)

###########
##Install##
###########
#下载至指定install目录的项目lib目录下
install(
  TARGETS Slover ${RM_PROJECT}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
#下载启动脚本
install(
    DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

########
##Test##
########

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

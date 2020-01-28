cmake_minimum_required(VERSION 2.8.3)
project(cmd_vel_mux)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cmd_vel_mux_node
CATKIN_DEPENDS roscpp geometry_msgs
#  DEPENDS system_lib
)

include_directories( ${catkin_INCLUDE_DIRS} )

add_executable(cmd_vel_mux_node src/cmd_vel_mux.cpp)
target_link_libraries(cmd_vel_mux_node ${catkin_LIBRARIES})
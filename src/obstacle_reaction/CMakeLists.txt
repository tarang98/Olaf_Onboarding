cmake_minimum_required(VERSION 2.8.3)
project(obstacle_reaction)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES obstacle_reaction
#  CATKIN_DEPENDS roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(obstacle_reaction src/obstacle_reaction.cpp)
target_link_libraries(obstacle_reaction ${catkin_LIBRARIES})



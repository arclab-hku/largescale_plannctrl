cmake_minimum_required(VERSION 2.8)
project(plannctrl)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_LIST_DIR}/../cmake)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

# CMake module(s) path
#SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR} )

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(
catkin REQUIRED COMPONENTS

  roscpp
  std_msgs
  
  mavros
  control_msgs
  gazebo_msgs
  gazebo_plugins
  geometry_msgs
  nav_msgs
  roslib
  std_srvs
  sensor_msgs
)
find_package(Eigen3 REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

catkin_package()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EIGEN3_INCLUDE_DIRS}
  include
)

set(RFR 
${CMAKE_CURRENT_SOURCE_DIR}/include/planners/trajgen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/planners/wayp_reader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/planners/fast/traj_min_jerk.hpp
${CMAKE_CURRENT_SOURCE_DIR}/include/planners/fast/root_finder.hpp
)

## backstepping
add_executable(track_node
  src/run_plannctrl.cpp 
  include/controllers/backstepping.cpp
  include/Tools.cpp
  include/offboard_env/ros_missn.cpp 
  # include/logs/log_flight.cpp
  ${RFR}
)

target_link_libraries(track_node ${catkin_LIBRARIES})

install(TARGETS track_node
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

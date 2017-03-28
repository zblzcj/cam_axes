cmake_minimum_required(VERSION 2.8.3)
project(cam_axes)

## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
	sensor_msgs
  std_msgs
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cam_axes
  CATKIN_DEPENDS cv_bridge image_transport roscpp std_msgs
  DEPENDS OpenCV
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(cam_axes_node src/camAxesNode.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(cam_axes_node ${catkin_LIBRARIES} ${OpenCV_LIBS})


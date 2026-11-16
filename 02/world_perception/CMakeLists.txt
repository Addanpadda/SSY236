cmake_minimum_required(VERSION 3.5)
project(world_perception)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(include)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Object.msg"
  "srv/UpdateObject.srv"
  DEPENDENCIES
    geometry_msgs
)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(direct_perception_node src/direct_perception_node.cpp)
ament_target_dependencies(direct_perception_node
                          rclcpp
                          std_msgs
                          geometry_msgs
                          gazebo_msgs
                          tf2
                          tf2_ros)

add_executable(map_generation_node src/map_generation_node.cpp)
ament_target_dependencies(map_generation_node
                          rclcpp
                          std_msgs
                          geometry_msgs
                          tf2
                          tf2_ros)
target_link_libraries(map_generation_node "${cpp_typesupport_target}")

add_executable(perception_node src/perception_node.cpp)
ament_target_dependencies(perception_node
                          rclcpp
                          std_msgs
                          geometry_msgs
                          gazebo_msgs
                          tf2
                          tf2_ros)
target_link_libraries(perception_node "${cpp_typesupport_target}")

install(TARGETS
  direct_perception_node
  map_generation_node
  perception_node
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch worlds
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

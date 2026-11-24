cmake_minimum_required(VERSION 3.5)
project(world_symbolic_perception)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(btcpp_ros2_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(robot_swiss_knife_msgs REQUIRED)

set(THIS_PACKAGE_DEPS
    behaviortree_ros2::behaviortree_ros2
    ${btcpp_ros2_interfaces_TARGETS}
    ${std_msgs_TARGETS}
    ${geometry_msgs_TARGETS}
    ${vision_msgs_TARGETS}
    ${gazebo_msgs_TARGETS}
    ${robot_swiss_knife_msgs_TARGETS}
    ${tf2_TARGETS}
    ${tf2_ros_TARGETS}
)

include_directories(include)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Object.msg"
  DEPENDENCIES
    geometry_msgs
    vision_msgs
)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

#############################################
# Gazebo model states subscription behaviour
#############################################
add_library(model_states_sub_plugin SHARED src/behaviours/model_states_sub_behaviour.cpp)
target_compile_definitions(model_states_sub_plugin PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(model_states_sub_plugin ${THIS_PACKAGE_DEPS} "${cpp_typesupport_target}")

#############################################
# Gazebo bounding box subscription behaviour
#############################################
add_library(bbox_sub_plugin SHARED src/behaviours/bbox_sub_behaviour.cpp)
target_compile_definitions(bbox_sub_plugin PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(bbox_sub_plugin ${THIS_PACKAGE_DEPS} "${cpp_typesupport_target}")

#############################################################
# Behaviour for checking whether an object is near the robot
#############################################################
add_library(check_object_nearby_plugin SHARED src/behaviours/check_object_nearby_behaviour.cpp)
target_compile_definitions(check_object_nearby_plugin PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(check_object_nearby_plugin ${THIS_PACKAGE_DEPS} "${cpp_typesupport_target}")

##################################################
# Behaviour for calculating the values of symbols
##################################################
add_library(calculate_symbol_values_plugin SHARED
    src/behaviours/calculate_symbol_values_behaviour.cpp
    src/symbol_library.cpp)
target_compile_definitions(calculate_symbol_values_plugin PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(calculate_symbol_values_plugin ${THIS_PACKAGE_DEPS} "${cpp_typesupport_target}")

##################################################
# Behaviour for updating a robot's knowledge base
##################################################
add_library(update_kb_plugin SHARED src/behaviours/update_kb_behaviour.cpp)
target_compile_definitions(update_kb_plugin PRIVATE BT_PLUGIN_EXPORT)
target_link_libraries(update_kb_plugin ${THIS_PACKAGE_DEPS} "${cpp_typesupport_target}")

##################
# Behaviour trees
##################
add_executable(tree_executor src/tree_executor.cpp)
target_link_libraries(tree_executor ${THIS_PACKAGE_DEPS})

install(TARGETS
  model_states_sub_plugin
  bbox_sub_plugin
  check_object_nearby_plugin
  calculate_symbol_values_plugin
  update_kb_plugin
  tree_executor
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  model_states_sub_plugin
  bbox_sub_plugin
  check_object_nearby_plugin
  calculate_symbol_values_plugin
  update_kb_plugin
  LIBRARY DESTINATION share/${PROJECT_NAME}/bt_plugins
  ARCHIVE DESTINATION share/${PROJECT_NAME}/bt_plugins
  RUNTIME DESTINATION share/${PROJECT_NAME}/bt_plugins
)

install(DIRECTORY
  launch
  config
  worlds
  behaviour_trees
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

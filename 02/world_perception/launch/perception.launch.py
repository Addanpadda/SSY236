from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    model_state_topic = "/gazebo/model_states"
    object_update_srv_name = "/update_object_list"

    map_generation_node = Node(package="world_perception",
                               executable="map_generation_node",
                               name="map_generation_node",
                               parameters = [{"object_update_srv_name": object_update_srv_name}])

    perception_node = Node(package="world_perception",
                           executable="perception_node",
                           name="perception_node",
                           parameters = [{"model_state_topic": model_state_topic,
                                          "object_update_srv_name": object_update_srv_name,
                                          "perception_dist_threshold_m": 1.}])

    static_tf_publisher_node = Node(package="tf2_ros",
                                    executable="static_transform_publisher",
                                    arguments=["0", "0", "0", "0", "0", "0", "odom", "world"])

    ld = LaunchDescription([
        map_generation_node,
        perception_node,
        static_tf_publisher_node
    ])

    return ld

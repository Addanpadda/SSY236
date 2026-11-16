from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    direct_perception_node = Node(package="world_perception",
                                  executable="direct_perception_node",
                                  name="direct_perception_node",
                                  parameters = [{"model_state_topic": "/gazebo/model_states"}])

    static_tf_publisher_node = Node(package="tf2_ros",
                                    executable="static_transform_publisher",
                                    arguments=["0", "0", "0", "0", "0", "0", "odom", "world"])

    ld = LaunchDescription([
        direct_perception_node,
        static_tf_publisher_node
    ])

    return ld

#ifndef CHECK_OBJECT_NEARBY_BEHAVIOUR_HPP
#define CHECK_OBJECT_NEARBY_BEHAVIOUR_HPP

#include <behaviortree_cpp/action_node.h>
#include <behaviortree_ros2/ros_node_params.hpp>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/exceptions.h>

#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

#include "world_symbolic_perception/msg/object.hpp"

using namespace std::placeholders;
using namespace BT;

/**
 * A behaviour that checks whether any objects are close to a robot.
 */
class CheckObjectNearbyBehaviour : public SyncActionNode
{
public:
    CheckObjectNearbyBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);

    /**
     * Sets the ports of the behaviour:
     * - Input ports:
     *     * objects (world_symbolic_perception::msg::Object)
     *     * distance_threshold_m (float)
     * - Output ports:
     *     * visible_objects (std::vector<world_symbolic_perception::msg::Object>)
     */
    static PortsList providedPorts();

    NodeStatus tick() override;
private:
    void get_current_robot_position();

    rclcpp::Node::SharedPtr node;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener;
    std::unique_ptr<tf2_ros::Buffer> tf_buffer;

    geometry_msgs::msg::TransformStamped transform_stamped;
    geometry_msgs::msg::Pose current_robot_pose;
    std::vector<std::string> objects_to_ignore;
};

#endif
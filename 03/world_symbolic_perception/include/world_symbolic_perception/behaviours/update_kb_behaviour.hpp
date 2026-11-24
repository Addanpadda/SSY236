#ifndef UPDATE_KB_BEHAVIOUR_HPP
#define UPDATE_KB_BEHAVIOUR_HPP

#include <behaviortree_cpp/action_node.h>
#include <behaviortree_ros2/ros_node_params.hpp>

#include "robot_swiss_knife_msgs/srv/update_kb.hpp"
#include "robot_swiss_knife_msgs/msg/fluent.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;
using namespace BT;

/**
 * A behaviour for interacting with a service of type robot_swiss_knife_msgs::srv::UpdateKB.
 */
class UpdateKBBehaviour : public SyncActionNode
{
public:
    UpdateKBBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);

    /**
     * Sets the ports of the behaviour:
     * - Input ports:
     *     * kb_update_srv_name (std::string)
     *     * scene_symbols (std::vector<robot_swiss_knife_msgs::msg::Fluent>)
     */
    static PortsList providedPorts();

    NodeStatus tick() override;
private:
    rclcpp::Node::SharedPtr node;
    rclcpp::Client<robot_swiss_knife_msgs::srv::UpdateKB>::SharedPtr kb_update_client;

    std::string kb_update_srv_name;
};

#endif
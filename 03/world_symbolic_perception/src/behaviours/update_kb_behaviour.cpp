#include "world_symbolic_perception/behaviours/update_kb_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

UpdateKBBehaviour::UpdateKBBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: SyncActionNode(name, conf), node(params.nh)
{
    this->getInput("kb_update_srv_name", this->kb_update_srv_name);

    RCLCPP_INFO(this->node->get_logger(), "Creating a KB update client for server %s", this->kb_update_srv_name.c_str());
    this->kb_update_client = node->create_client<robot_swiss_knife_msgs::srv::UpdateKB>(this->kb_update_srv_name);
    while (!this->kb_update_client->wait_for_service(1s))
    {
        RCLCPP_INFO(this->node->get_logger(), "Service %s not available, waiting...", this->kb_update_srv_name.c_str());
    }
    RCLCPP_INFO(this->node->get_logger(), "Client for service %s created", this->kb_update_srv_name.c_str());
}

PortsList UpdateKBBehaviour::providedPorts()
{
    return { InputPort<std::string>("kb_update_srv_name"),
             InputPort<std::vector<robot_swiss_knife_msgs::msg::Fluent>>("scene_symbols") };
}

NodeStatus UpdateKBBehaviour::tick()
{
    std::vector<robot_swiss_knife_msgs::msg::Fluent> scene_symbols;
    this->getInput("scene_symbols", scene_symbols);

    ////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Call the service that updates the knowledge base with the contents in scene_symbols
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return NodeStatus::SUCCESS;
}

CreateRosNodePlugin(UpdateKBBehaviour, "UpdateKBBehaviour");
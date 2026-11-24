#ifndef CALCULATE_SYMBOL_VALUES_BEHAVIOUR_HPP
#define CALCULATE_SYMBOL_VALUES_BEHAVIOUR_HPP

#include <behaviortree_cpp/action_node.h>
#include <behaviortree_ros2/ros_node_params.hpp>

#include "robot_swiss_knife_msgs/msg/knowledge_item.hpp"
#include "robot_swiss_knife_msgs/msg/fluent.hpp"
#include "world_symbolic_perception/msg/object.hpp"
#include "world_symbolic_perception/symbol_library.hpp"

using namespace BT;

/**
 * A behaviour that finds all predicates (from a given library) that hold for a set of objects.
 */
class CalculateSymbolValuesBehaviour : public SyncActionNode
{
public:
    CalculateSymbolValuesBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);

    /**
     * Sets the ports of the behaviour:
     * - Input ports:
     *     * visible_objects (std::vector<world_symbolic_perception::msg::Object>)
     * - Output ports:
     *     * scene_symbols (std::vector<robot_swiss_knife_msgs::msg::Fluent>)
     */
    static PortsList providedPorts();

    NodeStatus tick() override;
private:
    rclcpp::Node::SharedPtr node;
};

#endif

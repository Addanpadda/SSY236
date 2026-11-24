#include "world_symbolic_perception/behaviours/calculate_symbol_values_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

CalculateSymbolValuesBehaviour::CalculateSymbolValuesBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: SyncActionNode(name, conf), node(params.nh)
{}

PortsList CalculateSymbolValuesBehaviour::providedPorts()
{
    return { InputPort<std::vector<world_symbolic_perception::msg::Object>>("visible_objects"),
             OutputPort<std::vector<robot_swiss_knife_msgs::msg::Fluent>>("scene_symbols") };
}

NodeStatus CalculateSymbolValuesBehaviour::tick()
{
    std::vector<world_symbolic_perception::msg::Object> visible_objects;
    this->getInput("visible_objects", visible_objects);

    std::vector<robot_swiss_knife_msgs::msg::Fluent> scene_symbols;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Calculate the predicate values for all pairs of visible objects, and add all predicates that hold to scene_symbols
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (scene_symbols.size() == 0)
    {
        return NodeStatus::FAILURE;
    }

    this->setOutput("scene_symbols", scene_symbols);
    return NodeStatus::SUCCESS;
}

CreateRosNodePlugin(CalculateSymbolValuesBehaviour, "CalculateSymbolValuesBehaviour");

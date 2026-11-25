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

	//loop over all combinations of objects
	for(int ix = 0; ix < visible_objects.size(); ++ix)
		for(int jx = 0; jx < visible_objects.size(); ++jx){
			if(ix == jx)
				continue;
			world_symbolic_perception::msg::Object obj1 = visible_objects[ix];
			world_symbolic_perception::msg::Object obj2 = visible_objects[jx];

			//check each prediacte
			if(SymbolLibrary::on(obj1,obj2, this->node_)){
				robot_swiss_knife_msgs::msg::Fluent fluent;
				fluent.name = "on";
				fluent.args = {obj1.name,obj2.name};
				scene_symbols.push_back(fluent);
			}
			if(SymbolLibrary::leftOf(obj1,obj2, this->node_)){
				robot_swiss_knife_msgs::msg::Fluent fluent;
				fluent.name = "leftOf";
				fluent.args = {obj1.name,obj2.name};
				scene_symbols.push_back(fluent);
			}
			if(SymbolLibrary::rightOf(obj1,obj2, this->node_)){
				robot_swiss_knife_msgs::msg::Fluent fluent;
				fluent.name = "rightOf";
				fluent.args = {obj1.name,obj2.name};
				scene_symbols.push_back(fluent);
			}

		}

    if (scene_symbols.size() == 0)
    {
        return NodeStatus::FAILURE;
    }

    this->setOutput("scene_symbols", scene_symbols);
    return NodeStatus::SUCCESS;
}

CreateRosNodePlugin(CalculateSymbolValuesBehaviour, "CalculateSymbolValuesBehaviour");

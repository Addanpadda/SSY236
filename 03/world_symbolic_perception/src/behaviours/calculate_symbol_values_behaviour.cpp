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
	for(size_t ix = 0; ix < visible_objects.size(); ++ix)
		for(size_t jx = 0; jx < visible_objects.size(); ++jx){
			if(ix == jx)
				continue;
			world_symbolic_perception::msg::Object obj1 = visible_objects[ix];
			world_symbolic_perception::msg::Object obj2 = visible_objects[jx];

			//check each prediacte
			if(SymbolLibrary::on(obj1,obj2, this->node)){
				robot_swiss_knife_msgs::msg::Fluent fluent = scene_symbols.emplace_back();
				fluent.name = "on";
				fluent.value = "true";
				
				robot_swiss_knife_msgs::msg::KnowledgeItem param1 = fluent.params.emplace_back();
				param1.name = obj1.name;
				robot_swiss_knife_msgs::msg::KnowledgeItem param2 = fluent.params.emplace_back();
				param2.name = obj2.name;
			}
			if(SymbolLibrary::leftOf(obj1,obj2, this->node)){
				robot_swiss_knife_msgs::msg::Fluent fluent = scene_symbols.emplace_back();
				fluent.name = "leftOf";
				fluent.value = "true";
				
				robot_swiss_knife_msgs::msg::KnowledgeItem param1 = fluent.params.emplace_back();
				param1.name = obj1.name;
				robot_swiss_knife_msgs::msg::KnowledgeItem param2 = fluent.params.emplace_back();
				param2.name = obj2.name;
			}
			if(SymbolLibrary::rightOf(obj1,obj2, this->node)){
				robot_swiss_knife_msgs::msg::Fluent fluent = scene_symbols.emplace_back();
				fluent.name = "leftOf";
				fluent.value = "true";
				
				robot_swiss_knife_msgs::msg::KnowledgeItem param1 = fluent.params.emplace_back();
				param1.name = obj1.name;
				robot_swiss_knife_msgs::msg::KnowledgeItem param2 = fluent.params.emplace_back();
				param2.name = obj2.name;
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

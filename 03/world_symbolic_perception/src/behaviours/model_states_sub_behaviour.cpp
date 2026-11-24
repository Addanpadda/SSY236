#include "world_symbolic_perception/behaviours/model_states_sub_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

ModelStatesSubBehaviour::ModelStatesSubBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: RosTopicSubNode<gazebo_msgs::msg::ModelStates>(name, conf, params)
{}

PortsList ModelStatesSubBehaviour::providedPorts()
{
    return providedBasicPorts({
        OutputPort<std::vector<world_symbolic_perception::msg::Object>>("latest_objects")
    });
}

NodeStatus ModelStatesSubBehaviour::onTick(const std::shared_ptr<gazebo_msgs::msg::ModelStates>& msg)
{
    if(msg)
    {
        std::vector<world_symbolic_perception::msg::Object> objects;
        unsigned int model_count = msg->name.size();

        for (unsigned int i=0; i<model_count; i++)
        {
            world_symbolic_perception::msg::Object obj;
            obj.name = msg->name[i];
            obj.pose = msg->pose[i];
            objects.push_back(obj);
        }
        this->setOutput("latest_objects", objects);
        return NodeStatus::SUCCESS;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return NodeStatus::FAILURE;
}

CreateRosNodePlugin(ModelStatesSubBehaviour, "ModelStatesSubBehaviour");
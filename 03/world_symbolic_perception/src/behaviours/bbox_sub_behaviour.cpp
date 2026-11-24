#include "world_symbolic_perception/behaviours/bbox_sub_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

BoundingBoxSubBehaviour::BoundingBoxSubBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: RosTopicSubNode<vision_msgs::msg::Detection3DArray>(name, conf, params)
{}

PortsList BoundingBoxSubBehaviour::providedPorts()
{
    return providedBasicPorts({
        BidirectionalPort<std::vector<world_symbolic_perception::msg::Object>>("latest_objects")
    });
}

NodeStatus BoundingBoxSubBehaviour::onTick(const std::shared_ptr<vision_msgs::msg::Detection3DArray>& msg)
{
    if(msg)
    {
        std::vector<world_symbolic_perception::msg::Object> latest_objects;
        this->getInput("latest_objects", latest_objects);

        for (vision_msgs::msg::Detection3D &detection : msg->detections)
        {
            for (world_symbolic_perception::msg::Object &obj : latest_objects)
            {
                if (obj.name == detection.id)
                {
                    obj.bbox = detection.bbox;
                    break;
                }
            }
        }
        this->setOutput("latest_objects", latest_objects);
        return NodeStatus::SUCCESS;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return NodeStatus::FAILURE;
}

CreateRosNodePlugin(BoundingBoxSubBehaviour, "BoundingBoxSubBehaviour");

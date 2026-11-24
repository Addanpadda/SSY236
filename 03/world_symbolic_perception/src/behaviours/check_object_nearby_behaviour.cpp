#include "world_symbolic_perception/behaviours/check_object_nearby_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

CheckObjectNearbyBehaviour::CheckObjectNearbyBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: SyncActionNode(name, conf), node(params.nh)
{
    this->tf_buffer = std::make_unique<tf2_ros::Buffer>(this->node->get_clock());
    this->tf_listener = std::make_shared<tf2_ros::TransformListener>(*this->tf_buffer);
    this->objects_to_ignore = {"tiago"};
}

PortsList CheckObjectNearbyBehaviour::providedPorts()
{
    return { InputPort<std::vector<world_symbolic_perception::msg::Object>>("objects"),
             InputPort<float>("distance_threshold_m"),
             OutputPort<std::vector<world_symbolic_perception::msg::Object>>("visible_objects") };
}

NodeStatus CheckObjectNearbyBehaviour::tick()
{
    std::vector<world_symbolic_perception::msg::Object> objects;
    float distance_threshold_m;

    this->getInput("objects", objects);
    this->getInput("distance_threshold_m", distance_threshold_m);

    std::vector<world_symbolic_perception::msg::Object> visible_objects;
    this->get_current_robot_position();
    for (const world_symbolic_perception::msg::Object &obj : objects)
    {
        if (std::find(this->objects_to_ignore.begin(), this->objects_to_ignore.end(), obj.name) != this->objects_to_ignore.end())
        {
            // we skip objects we are not interested in or that we have seen before
            continue;
        }

        float dx = this->current_robot_pose.position.x - obj.pose.position.x;
        float dy = this->current_robot_pose.position.y - obj.pose.position.y;
        float dist_robot_obj = sqrt((dx * dx) + (dy * dy));
        if (dist_robot_obj < distance_threshold_m)
        {
            visible_objects.push_back(obj);
        }
    }

    if (visible_objects.size() > 0)
    {
        this->setOutput("visible_objects", visible_objects);
        return NodeStatus::SUCCESS;
    }
    return NodeStatus::FAILURE;
}

void CheckObjectNearbyBehaviour::get_current_robot_position()
{
    try
    {
        this->transform_stamped = this->tf_buffer->lookupTransform("world", "base_link", tf2::TimePointZero);
        this->current_robot_pose.position.x = this->transform_stamped.transform.translation.x;
        this->current_robot_pose.position.y = this->transform_stamped.transform.translation.y;
        RCLCPP_INFO(this->node->get_logger(), "Robot position: (%.2f, %2f)",
                    this->current_robot_pose.position.x,
                    this->current_robot_pose.position.y);
    }
    catch (const tf2::TransformException & ex)
    {
        RCLCPP_INFO( this->node->get_logger(), "Could not transform base_link to world: %s", ex.what());
        return;
    }
}

CreateRosNodePlugin(CheckObjectNearbyBehaviour, "CheckObjectNearbyBehaviour");
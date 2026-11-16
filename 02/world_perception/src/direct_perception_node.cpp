#include "world_perception/direct_perception_node.hpp"

DirectPerceptionNode::DirectPerceptionNode(const rclcpp::NodeOptions &node_options)
    : rclcpp::Node("direct_perception_node", node_options)
{
    this->declare_parameter("model_state_topic", "/gazebo/model_states");
    this->get_parameter("model_state_topic", this->model_state_topic);

    this->tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    RCLCPP_INFO(this->get_logger(), "Subscribing to gazebo_msgs/msg/ModelStates on topic %s", this->model_state_topic.c_str());

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Initialise the Gazebo model subscriber. Note that the correct topic name is stored in this->model_state_topic.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    this->model_state_sub = ...;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void DirectPerceptionNode::model_state_cb(const gazebo_msgs::msg::ModelStates &model_state_msg)
{
    unsigned int model_count = model_state_msg.name.size();
    std::vector<geometry_msgs::msg::TransformStamped> model_transforms;
    rclcpp::Time current_time = this->get_clock()->now();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Set all transforms and add them to model_transforms so that they can be published in the TF tree
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (...)
    {

    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    this->tf_broadcaster->sendTransform(model_transforms);
}

void spin(rclcpp::Node::SharedPtr node)
{
    rclcpp::executors::SingleThreadedExecutor exec;
    rclcpp::WallRate loop_rate(20ms);
    while(rclcpp::ok())
    {
        exec.spin_node_some(node);
        loop_rate.sleep();
    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options = rclcpp::NodeOptions().allow_undeclared_parameters(true);
    auto direct_perception_node = std::make_shared<DirectPerceptionNode>(options);

    rclcpp::WallRate loop_rate(500ms);
    std::thread spinner(spin, direct_perception_node);

    while (rclcpp::ok())
    {
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
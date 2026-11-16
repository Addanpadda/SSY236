#include "world_perception/perception_node.hpp"

PerceptionNode::PerceptionNode(const rclcpp::NodeOptions &node_options)
    : rclcpp::Node("perception_node", node_options)
{
    this->declare_parameter("model_state_topic", "/gazebo/model_states");
    this->declare_parameter("object_update_srv_name", "/update_object_list");
    this->declare_parameter("perception_dist_threshold_m", 1.0);

    this->get_parameter("model_state_topic", this->model_state_topic);
    this->get_parameter("object_update_srv_name", this->object_update_srv_name);
    this->get_parameter("perception_dist_threshold_m", this->perception_dist_threshold_m);

    this->seen_objects.push_back("tiago");
    this->seen_objects.push_back("ground_plane");

    this->tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    this->tf_listener = std::make_shared<tf2_ros::TransformListener>(*this->tf_buffer);

    RCLCPP_INFO(this->get_logger(), "Creating an object update client for server %s", this->object_update_srv_name.c_str());
    this->object_update_client = this->create_client<world_perception::srv::UpdateObject>(this->object_update_srv_name);
    while (!this->object_update_client->wait_for_service(1s))
    {
        RCLCPP_INFO(this->get_logger(), "Service %s not available, waiting...", this->object_update_srv_name.c_str());
    }
    RCLCPP_INFO(this->get_logger(), "Client for service %s created", this->object_update_srv_name.c_str());

    RCLCPP_INFO(this->get_logger(), "Subscribing to gazebo_msgs/msg/ModelStates on topic %s", this->model_state_topic.c_str());
    this->model_state_sub = this->create_subscription<gazebo_msgs::msg::ModelStates>(this->model_state_topic,
                                                                                     10,
                                                                                     std::bind(&PerceptionNode::model_state_cb, this, _1));
}

void PerceptionNode::model_state_cb(const gazebo_msgs::msg::ModelStates &model_state_msg)
{
    unsigned int model_count = model_state_msg.name.size();
    rclcpp::Time current_time = this->get_clock()->now();

    this->get_current_robot_position();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Check which of the objects in the list are close to the robot (based on this->perception_dist_threshold_m).
    //       For each object that is close to the robot, send a request to the server (this->object_update_client defines
    //       the server client). Note that the robot's position with respect to the world frame is stored in
    //       this->current_robot_pose.position. In your implementation, ignore objects that appear in this->seen_objects.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void PerceptionNode::get_current_robot_position()
{
    try
    {
        this->transform_stamped = this->tf_buffer->lookupTransform("world", "base_link", tf2::TimePointZero);
        this->current_robot_pose.position.x = this->transform_stamped.transform.translation.x;
        this->current_robot_pose.position.y = this->transform_stamped.transform.translation.y;
    }
    catch (const tf2::TransformException & ex)
    {
        RCLCPP_INFO( this->get_logger(), "Could not transform base_link to world: %s", ex.what());
        return;
    }
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
    auto perception_node = std::make_shared<PerceptionNode>(options);

    rclcpp::WallRate loop_rate(500ms);
    std::thread spinner(spin, perception_node);

    while (rclcpp::ok())
    {
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
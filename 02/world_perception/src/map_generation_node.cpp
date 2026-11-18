#include "world_perception/map_generation_node.hpp"

MapGenerationNode::MapGenerationNode(const rclcpp::NodeOptions &node_options)
    : rclcpp::Node("map_generation_node", node_options)
{
    this->declare_parameter("object_update_srv_name", "/update_object_list");
    this->get_parameter("object_update_srv_name", this->object_update_srv_name);

    RCLCPP_INFO(this->get_logger(), "Exposing object update service %s", this->object_update_srv_name.c_str());
    this->object_update_srv = this->create_service<world_perception::srv::UpdateObject>(this->object_update_srv_name,
                                                                                        std::bind(&MapGenerationNode::update_object, this, _1, _2));

    this->tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    this->cb_timer = this->create_wall_timer(1000ms, std::bind(&MapGenerationNode::object_tf_publisher_cb, this));
}

void MapGenerationNode::update_object(const std::shared_ptr<world_perception::srv::UpdateObject::Request> request,
                                      std::shared_ptr<world_perception::srv::UpdateObject::Response> response)
{
    RCLCPP_INFO(this->get_logger(), "Received an object update request for object %s", request->object.name.c_str());

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Update the list of tracked objects. If the object in the service request exists, update its pose;
    //       if it doesn't, add it to the list. Note that objects should be stored in this->map_objects.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool object_found = false;
    for (auto &obj : this->map_objects)
    {
        if (obj.name == request->object.name)
        {
            obj.pose = request->object.pose;
            object_found = true;
            break;
        }
    }
    if (!object_found)
    {
        this->map_objects.push_back(request->object);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    response->success = true;
    RCLCPP_INFO(this->get_logger(), "Object update complete");
}

void MapGenerationNode::object_tf_publisher_cb()
{
    std::vector<geometry_msgs::msg::TransformStamped> object_transforms;
    rclcpp::Time current_time = this->get_clock()->now();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Set all transforms based on the list of known objects and add them
    //       to object_transforms so that they can be published in the TF tree
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Add your code here

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    this->tf_broadcaster->sendTransform(object_transforms);
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
    auto direct_perception_node = std::make_shared<MapGenerationNode>(options);

    rclcpp::WallRate loop_rate(500ms);
    std::thread spinner(spin, direct_perception_node);

    while (rclcpp::ok())
    {
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
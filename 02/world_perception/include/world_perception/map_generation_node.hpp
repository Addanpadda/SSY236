#ifndef MAP_GENERATION_NODE_HPP
#define MAP_GENERATION_NODE_HPP

#include <thread>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/exceptions.h>

#include "world_perception/msg/object.hpp"
#include "world_perception/srv/update_object.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class MapGenerationNode : public rclcpp::Node
{
public:
    MapGenerationNode(const rclcpp::NodeOptions &node_options);
private:
    /**
     * Service callback that inserts a new object into the list of known objects, or,
     * if an object with the provided name already exists, updates the object's pose.
     *
     * @param request Service request containing object information
     * @param response Service response indicating whether the update was successful
     */
    void update_object(const std::shared_ptr<world_perception::srv::UpdateObject::Request> request,
                       std::shared_ptr<world_perception::srv::UpdateObject::Response> response);

    /**
     * Periodically publishes transforms for all known objects.
     * All transforms are published in the "world" frame.
     */
    void object_tf_publisher_cb();

    std::string object_update_srv_name;

    rclcpp::Service<world_perception::srv::UpdateObject>::SharedPtr object_update_srv;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;
    rclcpp::TimerBase::SharedPtr cb_timer;

    std::vector<world_perception::msg::Object> map_objects;
};

#endif
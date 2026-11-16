#ifndef PERCEPTION_NODE_HPP
#define PERCEPTION_NODE_HPP

#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <gazebo_msgs/msg/model_states.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2/exceptions.h>

#include "world_perception/msg/object.hpp"
#include "world_perception/srv/update_object.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class PerceptionNode : public rclcpp::Node
{
public:
    PerceptionNode(const rclcpp::NodeOptions &node_options);
private:
    void model_state_cb(const gazebo_msgs::msg::ModelStates &model_state_msg);
    void get_current_robot_position();

    rclcpp::Subscription<gazebo_msgs::msg::ModelStates>::SharedPtr model_state_sub;
    rclcpp::Client<world_perception::srv::UpdateObject>::SharedPtr object_update_client;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener;
    std::unique_ptr<tf2_ros::Buffer> tf_buffer;

    std::string model_state_topic;
    std::string object_update_srv_name;
    float perception_dist_threshold_m;

    geometry_msgs::msg::TransformStamped transform_stamped;
    geometry_msgs::msg::Pose current_robot_pose;
    std::vector<std::string> seen_objects;
};

#endif
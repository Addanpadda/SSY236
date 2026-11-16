#ifndef DIRECT_PERCEPTION_NODE_HPP
#define DIRECT_PERCEPTION_NODE_HPP

#include <thread>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <gazebo_msgs/msg/model_states.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/exceptions.h>

using namespace std::chrono_literals;
using std::placeholders::_1;

class DirectPerceptionNode : public rclcpp::Node
{
public:
    DirectPerceptionNode(const rclcpp::NodeOptions &node_options);
private:
    void model_state_cb(const gazebo_msgs::msg::ModelStates &model_state_msg);
    rclcpp::Subscription<gazebo_msgs::msg::ModelStates>::SharedPtr model_state_sub;

    std::string model_state_topic;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;
};

#endif
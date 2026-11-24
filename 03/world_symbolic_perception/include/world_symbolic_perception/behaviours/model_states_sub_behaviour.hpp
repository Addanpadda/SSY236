#ifndef MODEL_STATES_SUB_BEHAVIOUR_HPP
#define MODEL_STATES_SUB_BEHAVIOUR_HPP

#include <behaviortree_ros2/bt_topic_sub_node.hpp>
#include <gazebo_msgs/msg/model_states.hpp>

#include "world_symbolic_perception/msg/object.hpp"

using namespace BT;

/**
 * A behaviour that subscribes to a ModelStates message and returns success or
 * failure based on the message value
 */
class ModelStatesSubBehaviour : public RosTopicSubNode<gazebo_msgs::msg::ModelStates>
{
public:
    ModelStatesSubBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);

    /**
     * Sets the ports of the behaviour:
     * - Output ports:
     *     * latest_objects (std::vector<world_symbolic_perception::msg::Object>)
     */
    static PortsList providedPorts();

    /**
     * Returns SUCCESS upon receiving a new message.
     */
    virtual NodeStatus onTick(const std::shared_ptr<gazebo_msgs::msg::ModelStates>& msg) override;
};

#endif
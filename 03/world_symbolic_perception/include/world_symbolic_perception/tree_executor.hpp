#ifndef TREE_EXECUTOR_CPP
#define TREE_EXECUTOR_CPP

#include <behaviortree_ros2/tree_execution_server.hpp>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>

/**
 * Tree execution server
 */
class TreeExecutor : public BT::TreeExecutionServer
{
public:
    TreeExecutor(const rclcpp::NodeOptions& options);

    virtual void onTreeCreated(BT::Tree& tree) override;
    virtual std::optional<std::string> onTreeExecutionCompleted(BT::NodeStatus status, bool was_cancelled) override;
private:
    std::shared_ptr<BT::StdCoutLogger> logger_cout;
};

#endif
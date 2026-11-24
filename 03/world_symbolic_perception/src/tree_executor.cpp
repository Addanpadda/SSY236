#include "world_symbolic_perception/tree_executor.hpp"

TreeExecutor::TreeExecutor(const rclcpp::NodeOptions& options)
: TreeExecutionServer(options) {}

void TreeExecutor::onTreeCreated(BT::Tree& tree)
{
    this->logger_cout = std::make_shared<BT::StdCoutLogger>(tree);
}

std::optional<std::string> TreeExecutor::onTreeExecutionCompleted(BT::NodeStatus, bool)
{
    this->logger_cout.reset();
    return std::nullopt;
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::NodeOptions options;
    auto tree_execution_server = std::make_shared<TreeExecutor>(options);

    rclcpp::executors::MultiThreadedExecutor exec(rclcpp::ExecutorOptions(), 0, false, std::chrono::milliseconds(250));
    exec.add_node(tree_execution_server->node());
    exec.spin();
    exec.remove_node(tree_execution_server->node());

    rclcpp::shutdown();
}
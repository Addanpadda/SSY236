#ifndef SYMBOL_LIBRARY_HPP
#define SYMBOL_LIBRARY_HPP

#include <rclcpp/rclcpp.hpp>

#include "world_symbolic_perception/msg/object.hpp"

class SymbolLibrary
{
public:
    static std::vector<std::string> symbol_names;
    static bool on(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr);
    static bool leftOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr);
    static bool rightOf(world_symbolic_perception::msg::Object obj1, world_symbolic_perception::msg::Object obj2, rclcpp::Node::SharedPtr);
};

#endif

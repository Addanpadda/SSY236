#include <cstdio>
#include <chrono>
#include "navi_interfaces/msg/coord2d.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;


class NaviPublisher : public rclcpp::Node
{
public:
  NaviPublisher() : Node("navi_publisher"), count(0) {
    publisher = this->create_publisher<navi_interfaces::msg::Coord2d>("navi_topic", 10);
    timer = this->create_wall_timer(
      500ms, std::bind(&NaviPublisher::publish_callback, this)
    );
  }

private:
  void publish_callback() {}

  unsigned int count;
  rclcpp::Publisher<navi_interfaces::msg::Coord2d>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  printf("hello world navigation_pkg package\n");
  return 0;
}

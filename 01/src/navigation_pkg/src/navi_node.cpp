#include <cstdio>
#include "navi_interfaces/msg/coord2d.hpp"
#include "rclcpp/rclcpp.hpp"

class NaviPublisher : public rclcpp::Node
{

};

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  printf("hello world navigation_pkg package\n");
  return 0;
}

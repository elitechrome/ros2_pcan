#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "can_msgs/msg/frame.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MacPCANNode : public rclcpp::Node
{
public:
  MacPCANNode()
  : Node("mac_pcan"), count_(0)
  {
    publisher_ = this->create_publisher<can_msgs::msg::Frame>("topic");
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MacPCANNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = can_msgs::msg::Frame();
    message.data[0] = 0x01;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%x'", message.data[0]);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MacPCANNode>());
  rclcpp::shutdown();
  return 0;
}

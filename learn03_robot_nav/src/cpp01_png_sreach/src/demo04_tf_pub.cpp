#include "base_interfaces/srv/path.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
using namespace std::chrono_literals;
using base_interfaces::srv::Path;
using std::placeholders::_1;
using std::placeholders::_2;

class TFPublisher : public rclcpp::Node {
public:
  TFPublisher() : Node("tf_broadcaster_node_cpp") {
    tfpublisher_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    client_ = this->create_client<Path>("find_path");
    timer_ = this->create_wall_timer(2s, std::bind(&TFPublisher::pub, this));
  }

  bool connect_server() {
    while (!client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "stop");
        return false;
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "connecting...");
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "connected");
    return true;
  }

  void send_request(int start_x, int start_y, int end_x, int end_y) {
    request = std::make_shared<Path::Request>();
    request->start_x = start_x;
    request->start_y = start_y;
    request->end_x = end_x;
    request->end_y = end_y;
    //client_->async_send_request(request,std::bind(TFPublisher::handle_result,this,_1));
    
  }


private:
  std::shared_ptr<base_interfaces::srv::Path::Request> request;
  rclcpp::Client<Path>::SharedPtr client_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tfpublisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  double ray;
  
  void handle_result(rclcpp::Client<Path>::SharedFuture result_future){
    auto path = result_future.get();

  }

  void pub() {
    geometry_msgs::msg::TransformStamped transform_wheel;
    tf2::Quaternion qtn;
    transform_wheel.header.stamp = this->now();
    transform_wheel.header.frame_id = "base_link";
    transform_wheel.child_frame_id = "wheel";
    transform_wheel.transform.translation.x = 0;
    transform_wheel.transform.translation.y = 0;
    transform_wheel.transform.translation.z = -0.13;
    qtn.setRPY(0, 0, 0);
    transform_wheel.transform.rotation.x = qtn.x();
    transform_wheel.transform.rotation.y = qtn.y();
    transform_wheel.transform.rotation.z = qtn.z();
    transform_wheel.transform.rotation.w = qtn.w();

    geometry_msgs::msg::TransformStamped transform_base = transform_wheel;
    transform_base.header.frame_id = "map";
    transform_base.child_frame_id = "base_link";
    transform_base.transform.translation.z = 0.15;

    geometry_msgs::msg::TransformStamped transform_camera = transform_wheel;
    transform_camera.header.frame_id = "base_link";
    transform_camera.child_frame_id = "camera";
    transform_camera.transform.translation.z = 0.02;
/*     auto path = send_request(0, 0, 150, 70);
    for (auto &point : path) {
      std::cout << "X:" << point.x << "Y:" << point.y << std::endl;
    } */
    tfpublisher_->sendTransform(transform_wheel);
    tfpublisher_->sendTransform(transform_base);
    tfpublisher_->sendTransform(transform_camera);
  }
};

int main(int argc, char const *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TFPublisher>();
  bool flag = node->connect_server();
  if (!flag) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "服务器连接失败");
    return 0;
  }
  rclcpp::spin(node);
  rclcpp::shutdown();
}
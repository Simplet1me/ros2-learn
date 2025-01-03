#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
using namespace std::chrono_literals;

class TFPublisher : public rclcpp::Node{
public:
  TFPublisher():Node("tf_broadcaster_node_cpp"){
    tfpublisher_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(20ms,std::bind(&TFPublisher::pub,this));
  }
private:
  std::shared_ptr<tf2_ros::TransformBroadcaster> tfpublisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  double ray;

  void pub(){
    geometry_msgs::msg::TransformStamped transform;
    tf2::Quaternion qtn;
    transform.header.stamp = this->now();
    transform.header.frame_id = "base_link";
    transform.child_frame_id = "wheel";
    transform.transform.translation.x = 0;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = -0.13;
    qtn.setRPY(0,0,0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();

    geometry_msgs::msg::TransformStamped transform_base = transform;
    transform_base.header.frame_id = "map";
    transform_base.child_frame_id = "base_link";
    transform_base.transform.translation.z = 0.15;

    geometry_msgs::msg::TransformStamped transform_camera = transform;
    transform_camera.header.frame_id = "base_link";
    transform_camera.child_frame_id = "camera";
    transform_camera.transform.translation.z = 0.02;
    
    tfpublisher_->sendTransform(transform);
    tfpublisher_->sendTransform(transform_base);
    tfpublisher_->sendTransform(transform_camera);
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<TFPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
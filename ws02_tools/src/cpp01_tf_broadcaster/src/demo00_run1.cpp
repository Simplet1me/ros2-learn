#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include <cmath>
using namespace std::chrono_literals;
//x y z roll pitch pitch yaw frame child_frame

class TFDynBroadcaster : public rclcpp::Node{
public:
  TFDynBroadcaster():Node("tf_broadcaster_node_cpp1"){
    //tf2_ros::StaticTransformBroadcaster
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(20ms,std::bind(&TFDynBroadcaster::pub_tf,this));
  }

private:
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
  geometry_msgs::msg::TransformStamped transform;
  tf2::Quaternion qtn;
  double ray;
  void pub_tf(){

    transform.header.stamp = this->now();
    transform.header.frame_id = "a";
    transform.child_frame_id = "b";

    //设置偏移量
    transform.transform.translation.x = 0;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = -1;
    //设置四元数
    ray += 0.05;
    //欧拉角变四元数
    qtn.setRPY(0,0,ray);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();

    broadcaster_->sendTransform(transform);
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto tfs = std::make_shared<TFDynBroadcaster>();
  rclcpp::spin(tfs);
  rclcpp::shutdown();
}
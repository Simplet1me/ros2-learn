#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
//x y z roll pitch pitch yaw frame child_frame

class TFStaticBroadcaster : public rclcpp::Node{
public:
  TFStaticBroadcaster():Node("tf_static_broadcaster_node_cpp"){
    //tf2_ros::StaticTransformBroadcaster
    broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
    pub_stattic_tf();
  }

private:
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;
  void pub_stattic_tf(){
    geometry_msgs::msg::TransformStamped transform;
    transform.header.stamp = this->now();
    transform.header.frame_id = "a";
    transform.child_frame_id = "b";
    
    //设置偏移量
    transform.transform.translation.x = 0;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = 1;
    //设置四元数
    //欧拉角变四元数
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();
    RCLCPP_INFO(this->get_logger(),"pub");
    broadcaster_->sendTransform(transform);
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto tfs = std::make_shared<TFStaticBroadcaster>();
  rclcpp::spin(tfs);
  rclcpp::shutdown();
}
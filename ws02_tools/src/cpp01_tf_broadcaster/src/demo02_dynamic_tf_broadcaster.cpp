#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"

class TFDynBroadcaster : public rclcpp::Node{
public:
  TFDynBroadcaster():Node("tf_dyn_broadcaster_node_cpp"){
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    pose_sub_ = this->create_subscription<geometry_msgs::msg::TransformStamped>("/tf_static",10,std::bind(&TFDynBroadcaster::do_pose,this,std::placeholders::_1));
  }



private:
  void do_pose(const geometry_msgs::msg::TransformStamped & center){
    geometry_msgs::msg::TransformStamped ts;
    ts.header.stamp = this->now();
    ts.header.frame_id = "b";
    ts.child_frame_id = "c";

    x+=0.001;
    ts.transform.translation.x = x;
    ts.transform.translation.y = 0;
    ts.transform.translation.z = 0;
    RCLCPP_INFO(this->get_logger(),"x:%f y:%f z:%f",ts.transform.translation.x,ts.transform.translation.y,ts.transform.translation.z);
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,0);

    ts.transform.rotation.x = qtn.x();
    ts.transform.rotation.y = qtn.y();
    ts.transform.rotation.z = qtn.z();
    ts.transform.rotation.w = qtn.w();
    broadcaster_->sendTransform(ts);
  }

  float x = 0;
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr pose_sub_;
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto tfs = std::make_shared<TFDynBroadcaster>();
  rclcpp::spin(tfs);
  rclcpp::shutdown();
}
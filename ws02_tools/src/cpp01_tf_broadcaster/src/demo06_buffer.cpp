#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/utils.h"
using namespace std::chrono_literals;

class TFListener : public rclcpp::Node{
public:
  TFListener():Node("tf_listener_node_cpp"){
    buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
    timer_ = this->create_wall_timer(0.1s,std::bind(&TFListener::do_cb,this));
  }

private:
  std::unique_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  rclcpp::TimerBase::SharedPtr timer_;
  void do_cb(){
    try{
    auto ts = buffer_->lookupTransform("frame_a","frame_b",tf2::TimePointZero);
    RCLCPP_INFO(this->get_logger(),
    "NewdadFrame: %s  NewchildFrame%s \n X:%f Y:%f Z:%f \n"
    ,ts.header.frame_id.c_str(),ts.child_frame_id.c_str(),ts.transform.translation.x,ts.transform.translation.y,ts.transform.translation.z);
    }
    catch(const tf2::LookupException& e){
      RCLCPP_INFO(this->get_logger(),"异常");
    }
    
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<TFListener>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
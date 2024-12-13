#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/utils.h"
using namespace std::chrono_literals;

class TFListener : public rclcpp::Node{
public:
  TFListener():Node("tf_listener_node_cpp"){
    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
    timer_ = this->create_wall_timer(6s,std::bind(&TFListener::getTransform,this));
  }

private:

  void getTransform(){
    try{
      const auto tranform = buffer_->lookupTransform(
        "base_link",
        "target_point",
        this->get_clock()->now(),
        rclcpp::Duration::from_seconds(1.0f)
        );
        auto translation = tranform.transform.translation;
        auto rotation = tranform.transform.rotation;
        double y,p,r;
        //tf2::getEulerYPR(rotation,y,p,r);
        RCLCPP_INFO(this->get_logger(),"平移：%f,%f,%f",translation.x,translation.y,translation.z);
        RCLCPP_INFO(this->get_logger(),"旋转：%f,%f,%f,%f",rotation.x,rotation.y,rotation.z,rotation.w);
    }
    catch(const std::exception& e){
      RCLCPP_INFO(this->get_logger(),"%s",e.what());
    }
  }
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::Buffer> buffer_;
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto tfl = std::make_shared<TFListener>();
  rclcpp::spin(tfl);
  rclcpp::shutdown();
}
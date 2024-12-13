#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "message_filters/subscriber.h"
#include "geometry_msgs/msg/point_stamped.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
using namespace std::chrono_literals;

class TFPointListener : public rclcpp::Node{
public:
    TFPointListener() : Node("tf_point_listener"){
        buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        timer_ = std::make_shared<tf2_ros::CreateTimerROS>(this->get_node_base_interface(),this->get_node_timers_interface());
        buffer_->setCreateTimerInterface(timer_);
        listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
        point_sub.subscribe(this,"point");
        filter_ = std::make_shared<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>>(
            point_sub
            ,*buffer_
            ,"frame_b"
            ,10
            ,this->get_node_logging_interface()
            ,this->get_node_clock_interface()
            ,1s
            );
        filter_->registerCallback(&TFPointListener::transform_point,this);
    }

private:
    std::shared_ptr<tf2_ros::Buffer> buffer_;
    std::shared_ptr<tf2_ros::TransformListener> listener_;
    std::shared_ptr<tf2_ros::CreateTimerInterface> timer_;
    message_filters::Subscriber<geometry_msgs::msg::PointStamped> point_sub;
    std::shared_ptr<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>> filter_;

    void transform_point(const geometry_msgs::msg::PointStamped & ps){
        auto out = buffer_->transform(ps,"frame_b");
        RCLCPP_INFO(this->get_logger(),"父级坐标系:%s,X:%f Y:%f Z:%f",out.header.frame_id.c_str(),out.point.x,out.point.y,out.point.z);
    }
};

int main(int argc ,char *argv[]){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TFPointListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}
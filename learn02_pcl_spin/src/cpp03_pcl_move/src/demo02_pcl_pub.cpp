#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_sensor_msgs/tf2_sensor_msgs.hpp"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "message_filters/subscriber.h"
#include "geometry_msgs/msg/point_stamped.hpp"
using namespace std::chrono_literals;

class TFPublisher : public rclcpp::Node{
public:
  TFPublisher():Node("tf_broadcaster_node_cpp"){

    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    timer_ = std::make_shared<tf2_ros::CreateTimerROS>(this->get_node_base_interface(),this->get_node_timers_interface());
    buffer_->setCreateTimerInterface(timer_);
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
    pc_sub.subscribe(this,"pt");
    filter_ = std::make_shared<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>>(
            pc_sub
            ,*buffer_
            ,"frame_b"
            ,10
            ,this->get_node_logging_interface()
            ,this->get_node_clock_interface()
            ,1s
            );
    filter_->registerCallback(&TFPublisher::do_cb,this);


    pcpublisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pt_fin",10);
  }
private:
  std::shared_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  std::shared_ptr<tf2_ros::CreateTimerInterface> timer_;
  message_filters::Subscriber<sensor_msgs::msg::PointCloud2> pc_sub;
  std::shared_ptr<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>> filter_;


  
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;

  void do_cb(const sensor_msgs::msg::PointCloud2 & get_cloud_msg){
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);
    pcl::PointCloud<pcl::PointXYZ> get_cloud;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointXYZ p;
    auto trun_cloud_msg = buffer_->transform(get_cloud_msg,"frame_b");
    pcl::fromROSMsg(trun_cloud_msg,get_cloud);

    //cloud.clear();
    //墙角+小cube
    for (size_t i = 0; i < 50; i++){
      for (size_t j = 0; j < 50; j++){
        p.x = -5;
        p.y = j*0.1*-1;
        p.z = i*0.1;
        cloud.points.push_back(p);
      }
    }
    for (size_t i = 0; i < 50; i++){
      for (size_t j = 0; j < 50; j++){
        p.x = j*0.1*-1;
        p.y = -5;
        p.z = i*0.1;
        cloud.points.push_back(p);
      }
    }
    for (size_t i = 0; i < 50; i++){
      for (size_t j = 0; j < 50; j++){
        p.x = j*0.1*-1;
        p.y = i*0.1*-1;
        p.z = 0;
        cloud.points.push_back(p);
      }
    }
    for (size_t z = 0; z < 10; z++){
      for (size_t y = 0; y < 10; y++){
        for (size_t x = 0; x < 10; x++){
          p.x = x * 0.05 - 4;
          p.y = y * 0.05 - 4;
          p.z = z * 0.05 + 3;
          cloud.push_back(p);
        }
      }
    }
    
    for(auto& point : get_cloud){
      cloud.push_back(point);
    }

    pcl::toROSMsg(cloud,*cloud_msg);
    cloud_msg->header.frame_id = "frame_b";
    cloud_msg->header.stamp = this->now();

    pcpublisher_->publish(std::move(cloud_msg));
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<TFPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
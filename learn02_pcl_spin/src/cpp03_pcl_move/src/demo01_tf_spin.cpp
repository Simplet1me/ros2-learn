#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
using namespace std::chrono_literals;

class TFPublisher : public rclcpp::Node{
public:
  TFPublisher():Node("tf_broadcaster_node_cpp"){
    tfpublisher_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    pcpublisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pt",10);
    timer_ = this->create_wall_timer(20ms,std::bind(&TFPublisher::pub,this));
  }
  void setCloud(pcl::PointCloud<pcl::PointXYZ> cloudfile){
    cloud = cloudfile;
  }
private:

  pcl::PointCloud<pcl::PointXYZ> cloud;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tfpublisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  double ray=0;
  void pub(){
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);
    geometry_msgs::msg::TransformStamped transform;
    tf2::Quaternion qtn;
    transform.header.stamp = this->now();
    transform.header.frame_id = "frame_a";
    transform.child_frame_id = "cube";
    transform.transform.translation.x = 1;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = 0;
    qtn.setRPY(0,0,0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();


    pcl::toROSMsg(cloud,*cloud_msg);
    cloud_msg->header.frame_id = "cube";
    cloud_msg->header.stamp = this->now();

    tfpublisher_->sendTransform(transform);
    pcpublisher_->publish(std::move(cloud_msg));
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointXYZ p;
  for (size_t z = 0; z < 10; z++){
    for (size_t y = 0; y < 10; y++){
      for (size_t x = 0; x < 10; x++){
        p.x = x * 0.05;
        p.y = y * 0.05;
        p.z = z * 0.05;
        cloud->push_back(p);
      }
    }
  }

  auto node = std::make_shared<TFPublisher>();


  node->setCloud(*cloud);
  rclcpp::spin(node);
  rclcpp::shutdown();
}
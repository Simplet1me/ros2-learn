#include "geometry_msgs/msg/transform_stamped.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"

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
  double ray;

  void pub(){
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);
    geometry_msgs::msg::TransformStamped transform;
    tf2::Quaternion qtn;
    transform.header.stamp = this->now();
    transform.header.frame_id = "base_link";
    transform.child_frame_id = "frame_b";
    transform.transform.translation.x = 1;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = 0;
    qtn.setRPY(0,0,0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();

    pcl::toROSMsg(cloud,*cloud_msg);
    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();

    tfpublisher_->sendTransform(transform);
    pcpublisher_->publish(std::move(cloud_msg));
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  int size = 20;
  std::string path = "/home/simpletime/Project/learn03_robot_nav/cloud_filtered.pcd";
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if(pcl::io::loadPCDFile<pcl::PointXYZ>(path,*cloud) == -1){
        PCL_ERROR("Failed to load PCD file\n");
  }
  auto node = std::make_shared<TFPublisher>();
  node->setCloud(*cloud);
  rclcpp::spin(node);
  rclcpp::shutdown();
}
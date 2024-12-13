#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl/point_types.h"
#include "pcl/point_cloud.h"
#include "pcl_conversions/pcl_conversions.h"
using namespace std::chrono_literals;

class PointCouldPublisher : public rclcpp::Node{
public:
  PointCouldPublisher():Node("pcl_pub_node_cpp"){
    count = 2133;
    publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pt",10);
    timer_ = this->create_wall_timer(1s,std::bind(&PointCouldPublisher::Pub_pcl,this));
  }

private:
  void Pub_pcl(){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    std::string path = "/home/simpletime/Project/ws02_tools/source/top3.pcd";
    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>(path,*cloud) == -1){
        PCL_ERROR("Failed to load PCD file\n");
    }
    count++;
    RCLCPP_INFO(this->get_logger(),"Pubing : %d",count);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);
    pcl::toROSMsg(*cloud,*cloud_msg);
    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();
    publisher_->publish(std::move(cloud_msg));
  }
  int count;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto pclpub = std::make_shared<PointCouldPublisher>();
  rclcpp::spin(pclpub);
  rclcpp::shutdown();
}
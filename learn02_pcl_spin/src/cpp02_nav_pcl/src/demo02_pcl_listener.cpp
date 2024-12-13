#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "nav_msgs/msg/occupancy_grid.hpp"
using namespace std::chrono_literals;

class DepthMapPublisher : public rclcpp::Node{
public:
  DepthMapPublisher():Node("tf_broadcaster_node_cpp"){
    listener_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("pt",10,std::bind(&DepthMapPublisher::do_cb,this,std::placeholders::_1));
    publisher_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("depthmap",10);
    pcpublisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pta",10);
    ocg.info.width = width;
    ocg.info.height = height;
    ocg.info.resolution = resolution;
    ocg.info.origin.position.x = -5;
    ocg.info.origin.position.y = -5;
    ocg.info.origin.position.z = 0;
    ocg.info.origin.orientation.w = 1.0;
    ocg.data.resize(width * height, -1);
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr listener_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr publisher_;

  nav_msgs::msg::OccupancyGrid ocg;
  int width = 1000;
  int height = 1000;
  double resolution = 0.01;
  double distance_max = 0;

  void do_cb(const sensor_msgs::msg::PointCloud2::SharedPtr cloud_msg){
    sensor_msgs::msg::PointCloud2::UniquePtr newcloud_msg(new sensor_msgs::msg::PointCloud2);
    double x = 1;
    double y = 1;
    double z = 2;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointCloud<pcl::PointXYZ> newcloud;
    pcl::fromROSMsg(*cloud_msg,cloud);
    std::fill(ocg.data.begin(),ocg.data.end(),100);
    for(auto& point : cloud.points){
      pcl::PointXYZ p;
      float t = -point.z / z;
      if (z != 0) {
          p.x = point.x + t * x;
          p.y = point.y + t * y;
          p.z = 0;
          double distance = sqrt(pow(x-point.x,2)+pow(y-point.y,2)+pow(z-point.z,2));
          if (distance >= distance_max){
            distance_max = distance;
          }
          
          newcloud.points.push_back(p);
      }
    }
    RCLCPP_INFO(this->get_logger(),"Distance_max = %f",distance_max);
    newcloud.width = static_cast<uint32_t>(newcloud.points.size());
    newcloud.height = 1;
    newcloud.is_dense = true;
    
    for (auto& point : newcloud.points){
      int grid_x = ((point.x+5.0) / resolution)+0.5;
      int grid_y = ((point.y+5.0) / resolution)+0.5;
      double distance_rate = (sqrt(pow(x-point.x,2)+pow(y-point.y,2)+pow(z-point.z,2))+0.5) / distance_max;
      ocg.data[grid_y * width + grid_x] = static_cast<int>(100 * distance_rate);
    }

    ocg.header.stamp = this->get_clock()->now();
    ocg.header.frame_id = "frame_b";

    pcl::toROSMsg(newcloud,*newcloud_msg);

    newcloud_msg->header.frame_id = "frame_b";
    newcloud_msg->header.stamp = this->get_clock()->now();

    pcpublisher_->publish(std::move(newcloud_msg));
    publisher_->publish(ocg);
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<DepthMapPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
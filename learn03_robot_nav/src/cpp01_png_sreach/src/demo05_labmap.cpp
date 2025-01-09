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

class MapPublisher : public rclcpp::Node {
public:
  MapPublisher() : Node("tf_broadcaster_node_cpp") {
    publisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);
    pcpublisher_ =
        this->create_publisher<sensor_msgs::msg::PointCloud2>("pta", 10);
    if (pcl::io::loadPCDFile(path, cloud) == -1) {
      PCL_ERROR("pcl load error");
    }
    //求边界
    int width_min = 0, width_max = 0, height_min = 0, height_max = 0;
    for (auto &point : cloud.points) {
      if (point.x < width_min)
        width_min = point.x;
      if (point.x > width_max)
        width_max = point.x;
      if (point.y < height_min)
        height_min = point.y;
      if (point.y > height_max)
        height_max = point.y;
    }
    width = (width_max - width_min + 0.5) / resolution;
    height = (height_max - height_min + 0.5) / resolution;
    //地图初始化
    map.info.width = width;
    map.info.height = height;
    map.info.resolution = resolution;
    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.origin.position.z = 0;
    map.info.origin.orientation.w = 1.0;
    map.data.resize(width * height, 80);
    //点云投影地图
    for (auto &point : cloud.points) {
      int grid_x = (point.x / resolution) + 0.5;
      int grid_y = (point.y / resolution) + 0.5;
      map.data[grid_y * width + grid_x] = -1;
    }
    //清除孤点
    for (int grid_y = 0; grid_y < height; grid_y++) {
      for (int grid_x = 0; grid_x < width; grid_x++) {
        if (map.data[grid_y * width + grid_x] == 80) {
          if (map.data[grid_y * width + grid_x + width] == -1 &&
              map.data[grid_y * width + grid_x + width + 1] == -1 &&
              map.data[grid_y * width + grid_x + 1] == -1 &&
              map.data[grid_y * width + grid_x - width + 1] == -1 &&
              map.data[grid_y * width + grid_x - width] == -1 &&
              map.data[grid_y * width + grid_x - width - 1] == -1 &&
              map.data[grid_y * width + grid_x - 1] == -1 &&
              map.data[grid_y * width + grid_x + width - 1] == -1) {
            map.data[grid_y * width + grid_x] = -1;
          }
        }
      }
    }

    //障碍物膨胀2.0增加了边界检测
    for (int i = 80; i >= 75; i -= 5) {
      for (int grid_y = 0; grid_y < height; grid_y++) {
        for (int grid_x = 0; grid_x < width; grid_x++) {
          // 遍历到障碍物80
          if (map.data[grid_y * width + grid_x] == i) {
            // 判断周围障碍物是否为80，如果否就将其变为75，逐级递减
            // 上
            if (map.data[grid_y * width + grid_x + width] < i && grid_y * width + grid_x + width < map.data.size())
              map.data[grid_y * width + grid_x + width] = i - 5;
            // 右上
            if (map.data[grid_y * width + grid_x + width + 1] < i && grid_y * width + grid_x + width + 1 < map.data.size())
              map.data[grid_y * width + grid_x + width + 1] = i - 5;
            // 右
            if (map.data[grid_y * width + grid_x + 1] < i && grid_y * width + grid_x + 1 < map.data.size())
              map.data[grid_y * width + grid_x + 1] = i - 5;
            // 右下
            if (map.data[grid_y * width + grid_x - width + 1] < i && grid_y * width + grid_x - width + 1 < map.data.size())
              map.data[grid_y * width + grid_x - width + 1] = i - 5;
            // 下
            if (map.data[grid_y * width + grid_x - width] < i && grid_y * width + grid_x - width < map.data.size())
              map.data[grid_y * width + grid_x - width] = i - 5;
            // 左下
            if (map.data[grid_y * width + grid_x - width - 1] < i && grid_y * width + grid_x - width - 1 < map.data.size())
              map.data[grid_y * width + grid_x - width - 1] = i - 5;
            // 左
            if (map.data[grid_y * width + grid_x - 1] < i && grid_y * width + grid_x - 1 < map.data.size())
              map.data[grid_y * width + grid_x - 1] = i - 5;
            // 左上
            if (map.data[grid_y * width + grid_x + width - 1] < i && grid_y * width + grid_x + width - 1 < map.data.size())
              map.data[grid_y * width + grid_x + width - 1] = i - 5;
          }
        }
      }
    }

    map.header.frame_id = "base_link";
    map.header.stamp = this->now();
    timer_ = this->create_wall_timer(2s, std::bind(&MapPublisher::do_cb, this));
  }

private:
  std::string path =
      "/home/simpletime/Project/learn03_robot_nav/source/map.pcd";
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr listener_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr publisher_;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  rclcpp::TimerBase::SharedPtr timer_;

  nav_msgs::msg::OccupancyGrid map;
  int width;
  int height;
  double resolution = 0.1;
  double distance_max = 0;

  void do_cb() {

    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(
        new sensor_msgs::msg::PointCloud2);

    pcl::toROSMsg(cloud, *cloud_msg);
    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();
    pcpublisher_->publish(std::move(cloud_msg));
    publisher_->publish(map);
  }
};

int main(int argc, char const *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MapPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
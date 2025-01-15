#include "astar.cpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2_ros/transform_broadcaster.h"
using namespace std::chrono_literals;

class MapPublisher : public rclcpp::Node {
public:
  MapPublisher() : Node("tf_broadcaster_node_cpp") {
    map_publisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);
    travel_map_publisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("travel_map", 10);
    pcpublisher_ =
        this->create_publisher<sensor_msgs::msg::PointCloud2>("pta", 10);
    if (pcl::io::loadPCDFile(path, cloud) == -1) {
      PCL_ERROR("pcl load error");
    }
    for (auto &point : cloud) {
      point.z = 0;
    }
    // 求边界
    double width_min = 0, width_max = 0, height_min = 0, height_max = 0;
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
    // 地图初始化
    map.info.width = width;
    map.info.height = height;
    map.info.resolution = resolution;
    map.info.origin.position.x = width_min;
    map.info.origin.position.y = height_min;
    map.info.origin.position.z = 0;
    map.info.origin.orientation.w = 1.0;
    map.data.resize(width * height, 80);
    // 点云投影地图
    for (auto &point : cloud.points) {
      int grid_x = ((point.x - width_min) / resolution) + 0.5;
      int grid_y = ((point.y - height_min) / resolution) + 0.5;
      map.data[grid_y * width + grid_x] = -1;
    }
    // 清除孤点
    clearSinglePoint(map);
    travel_map = map;
    // 障碍物膨胀
    updateTravelMap(travel_map);
    map.header.frame_id = "base_link";
    map.header.stamp = this->now();
    travel_map.header.frame_id = "base_link";
    travel_map.header.stamp = this->now();
    timer_ = this->create_wall_timer(2s, std::bind(&MapPublisher::do_cb, this));
  }

private:
  std::string path = "cloud_filtered.pcd";
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_publisher_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr travel_map_publisher_;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  rclcpp::TimerBase::SharedPtr timer_;
  nav_msgs::msg::OccupancyGrid map;
  nav_msgs::msg::OccupancyGrid travel_map;
  int width;
  int height;
  double resolution = 0.1;
  double distance_max = 0;

  void do_cb() {

    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);

    point *start_point = new point(30, 10);
    point *end_point = new point(200, 75);

    map.data[start_point->y * width + start_point->x] = 30;
    map.data[end_point->y * width + end_point->x] = 30;

    auto path = Astar(start_point, end_point, travel_map);

    for (const auto &p : path) {
      map.data[p.y() * width + p.x()] = 1;
      travel_map.data[p.y() * width + p.x()] = 1;
    }

    pcl::toROSMsg(cloud, *cloud_msg);
    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();
    pcpublisher_->publish(std::move(cloud_msg));
    map_publisher_->publish(map);
    travel_map_publisher_->publish(travel_map);
  }
};

int main(int argc, char const *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MapPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
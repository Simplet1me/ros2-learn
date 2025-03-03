#include "astar.cpp"
#include "message_filters/subscriber.h"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_sensor_msgs/tf2_sensor_msgs.hpp"
using namespace std::chrono_literals;

class MapPublisher : public rclcpp::Node {
public:
  MapPublisher() : Node("domo_node_cpp") {
    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    timer_ = std::make_shared<tf2_ros::CreateTimerROS>(
        this->get_node_base_interface(), this->get_node_timers_interface());
    buffer_->setCreateTimerInterface(timer_);
    map_publisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);
    travel_map_publisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("travel_map", 10);
    // pcpublisher_ =
    // this->create_publisher<sensor_msgs::msg::PointCloud2>("pta", 10);
    tflistener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
    pcdlistener_.subscribe(this, "pt");
    filter_ =
        std::make_shared<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>>(
            pcdlistener_, *buffer_, "base_link", 10,
            this->get_node_logging_interface(),
            this->get_node_clock_interface(), 1s);
    filter_->registerCallback(&MapPublisher::subscriptionCallback, this);
  }

private:
  // std::string path = "cloud_filtered.pcd";
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_publisher_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr
      travel_map_publisher_;
  std::shared_ptr<tf2_ros::TransformListener> tflistener_;
  message_filters::Subscriber<sensor_msgs::msg::PointCloud2> pcdlistener_;
  std::shared_ptr<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>>
      filter_;
  std::shared_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::CreateTimerInterface> timer_;
  nav_msgs::msg::OccupancyGrid map;
  nav_msgs::msg::OccupancyGrid travel_map;
  int width;
  int height;
  double resolution = 0.1;
  double distance_max = 0;

  void subscriptionCallback(const sensor_msgs::msg::PointCloud2 &cloud_msg) {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    auto trun_cloud_msg = buffer_->transform(cloud_msg, "base_link");
    pcl::fromROSMsg(trun_cloud_msg, cloud);
    // 压平
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
    map.info.origin.orientation.x = 0;
    map.info.origin.orientation.y = 0;
    map.info.origin.orientation.z = 0;
    map.info.origin.orientation.w = 1.0;
    map.data.resize(width * height, 80);
    RCLCPP_INFO(this->get_logger(), "map h:%d w:%d size:%d", width, height,
                map.data.size());
    // 点云投影地图
    for (auto &point : cloud.points) {
      int grid_x = ((point.x - width_min) / resolution) + 0.5;
      int grid_y = ((point.y - height_min) / resolution) + 0.5;
      map.data[grid_y * width + grid_x] = -1;
    }
    travel_map = map;
    // 障碍物膨胀
    updateTravelMap(travel_map);
    map.header.frame_id = "map";
    map.header.stamp = this->now();
    travel_map.header.frame_id = "map";
    travel_map.header.stamp = this->now();

    map_publisher_->publish(map);
    travel_map_publisher_->publish(travel_map);
  }

  void Findpath() {

    point *start_point = new point(30, 10);
    point *end_point = new point(180, 75);

    map.data[start_point->y * width + start_point->x] = 30;
    map.data[end_point->y * width + end_point->x] = 30;

    auto path = Astar(start_point, end_point, travel_map);

    for (const auto &p : path) {
      map.data[p.y() * width + p.x()] = 1;
      travel_map.data[p.y() * width + p.x()] = 1;
    }
  }
};

int main(int argc, char const *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MapPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
#include "geometry_msgs/msg/point_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "message_filters/subscriber.h"
#include "pcl_conversions/pcl_conversions.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_sensor_msgs/tf2_sensor_msgs.hpp"
using namespace std::chrono_literals;

class PointCouldPublisher : public rclcpp::Node {
public:
  PointCouldPublisher() : Node("pc_broadcaster_node_cpp1") {
    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    timer_ = std::make_shared<tf2_ros::CreateTimerROS>(
        this->get_node_base_interface(), this->get_node_timers_interface());
    buffer_->setCreateTimerInterface(timer_);
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
    pc_sub.subscribe(this, "pt");
    filter_ =
        std::make_shared<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>>(
            pc_sub, *buffer_, "frame_b", 10, this->get_node_logging_interface(),
            this->get_node_clock_interface(), 1s);
    filter_->registerCallback(&PointCouldPublisher::do_cb, this);

    pcpublisher_ =
        this->create_publisher<sensor_msgs::msg::PointCloud2>("pt_trun", 10);
  }

private:
  std::shared_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  std::shared_ptr<tf2_ros::CreateTimerInterface> timer_;
  message_filters::Subscriber<sensor_msgs::msg::PointCloud2> pc_sub;
  std::shared_ptr<tf2_ros::MessageFilter<sensor_msgs::msg::PointCloud2>>
      filter_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcpublisher_;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  std::string path =
      "/home/simpletime/Project/learn02_pcl_spin/source/top3.pcd";

  void do_cb(const sensor_msgs::msg::PointCloud2 &get_cloud_msg) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_sml(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_big(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_total(
        new pcl::PointCloud<pcl::PointXYZ>);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(
        new sensor_msgs::msg::PointCloud2);
    // 转换点云坐标
    auto trun_cloud_msg = buffer_->transform(get_cloud_msg, "frame_b");
    pcl::fromROSMsg(trun_cloud_msg, *cloud_sml);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(path, *cloud_big) == -1) {
      PCL_ERROR("Failed to load PCD file\n");
    }
    for (auto &point : *cloud_big) {
      point.x *= 100;
      point.y *= 100;
      point.z *= 100;
    }
    // 网格大小
    double voxel_size = 0.15f;

    // 点云边界
    double min_x = cloud_sml->points[0].x;
    double min_y = cloud_sml->points[0].y;
    double min_z = cloud_sml->points[0].z;
    double max_x = min_x;
    double max_y = min_y;
    double max_z = min_z;
    // 计算网格边界(小点云)
    for (auto &point : cloud_sml->points) {
      if (point.x < min_x)
        min_x = point.x;
      if (point.y < min_y)
        min_y = point.y;
      if (point.z < min_z)
        min_z = point.z;
      if (point.x > max_x)
        max_x = point.x;
      if (point.y > max_y)
        max_y = point.y;
      if (point.z > max_z)
        max_z = point.z;
    }
    // 由小点云扩展，直至包围大点云
    for (auto &point : cloud_big->points) {
      if (point.x < min_x)
        min_x = point.x;
      if (point.y < min_y)
        min_y = point.y;
      if (point.z < min_z)
        min_z = point.z;
      if (point.x > max_x)
        max_x = point.x;
      if (point.y > max_y)
        max_y = point.y;
      if (point.z > max_z)
        max_z = point.z;
    }

    // 三维网格大小（边界）
    int grid_size_x = ((max_x - min_x) / voxel_size) + 1;
    int grid_size_y = ((max_y - min_y) / voxel_size) + 1;
    int grid_size_z = ((max_z - min_z) / voxel_size) + 1;

    // 三维数组
    // XYZ三轴个一个vector，每个网格一个vector，共四维
    // 每个网格内会有一个或多个点
    std::vector<std::vector<std::vector<std::vector<pcl::PointXYZ>>>>
        voxel_grid(grid_size_x,
                   std::vector<std::vector<std::vector<pcl::PointXYZ>>>(
                       grid_size_y,
                       std::vector<std::vector<pcl::PointXYZ>>(grid_size_z)));

    // 将点存入网格(小点云)
    for (auto &point : cloud_sml->points) {
      // 点的X坐标-网格最小边界 / 网格大小 = 当前网格坐标 （即X轴上第几个网格）
      // = 网格坐标
      int voxel_x = ((point.x - min_x) / voxel_size);
      int voxel_y = ((point.y - min_y) / voxel_size);
      int voxel_z = ((point.z - min_z) / voxel_size);
      // 确保点在所有边界内
      if (voxel_x >= 0 && voxel_x < grid_size_x && voxel_y >= 0 &&
          voxel_y < grid_size_y && voxel_z >= 0 && voxel_z < grid_size_z) {
        // 往网格内存入点
        voxel_grid[voxel_x][voxel_y][voxel_z].push_back(point);
      }
    }

    // 将点存入网格(大点云)
    for (auto &point : cloud_big->points) {
      // 点的X坐标-网格最小边界 / 网格大小 = 当前网格坐标 （即X轴上第几个网格）
      // = 网格坐标
      int voxel_x = ((point.x - min_x) / voxel_size);
      int voxel_y = ((point.y - min_y) / voxel_size);
      int voxel_z = ((point.z - min_z) / voxel_size);
      // 确保点在所有边界内
      if (voxel_x >= 0 && voxel_x < grid_size_x && voxel_y >= 0 &&
          voxel_y < grid_size_y && voxel_z >= 0 && voxel_z < grid_size_z) {
        // 往网格内存入点
        voxel_grid[voxel_x][voxel_y][voxel_z].push_back(point);
      }
    }
    // 扫描网格，每个网格内提取第一个点,将点存入新点云
    for (int x = 0; x < grid_size_x; ++x) {
      for (int y = 0; y < grid_size_y; ++y) {
        for (int z = 0; z < grid_size_z; ++z) {
          if (!voxel_grid[x][y][z].empty()) {
            cloud_total->points.push_back(voxel_grid[x][y][z][0]);
          }
        }
      }
    }
    // 更新new点云
    cloud_total->width = cloud_total->points.size();
    cloud_total->height = 1;
    // new完全的大小点云
    pcl::toROSMsg(*cloud_total, *cloud_msg);

    cloud_msg->header.frame_id = "frame_b";
    cloud_msg->header.stamp = this->now();
    RCLCPP_INFO(this->get_logger(), "Points: %ld", cloud_total->points.size());
    pcpublisher_->publish(std::move(cloud_msg));
  }
};

int main(int argc, char const *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointCouldPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
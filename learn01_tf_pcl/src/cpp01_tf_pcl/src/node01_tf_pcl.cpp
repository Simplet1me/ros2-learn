#include "geometry_msgs/msg/transform_stamped.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
using namespace std::chrono_literals;

pcl::PointCloud<pcl::PointXYZ> voxelCloud(pcl::PointCloud<pcl::PointXYZ> cloud,
                                          double size) {
  pcl::PointCloud<pcl::PointXYZ> cloud_new;
  double voxel_size = size;
  double min_x = cloud.points[0].x;
  double min_y = cloud.points[0].y;
  double min_z = cloud.points[0].z;
  double max_x = min_x;
  double max_y = min_y;
  double max_z = min_z;
  for (auto &point : cloud.points) {
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
  int grid_size_x = ((max_x - min_x) / voxel_size) + 1;
  int grid_size_y = ((max_y - min_y) / voxel_size) + 1;
  int grid_size_z = ((max_z - min_z) / voxel_size) + 1;
  std::vector<std::vector<std::vector<std::vector<pcl::PointXYZ>>>> voxel_grid(
      grid_size_x,
      std::vector<std::vector<std::vector<pcl::PointXYZ>>>(
          grid_size_y, std::vector<std::vector<pcl::PointXYZ>>(grid_size_z)));
  for (auto &point : cloud.points) {
    // 点的X坐标-网格最小边界 / 网格大小 = 当前网格坐标 （即X轴上第几个网格） =
    // 网格坐标
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
  for (int x = 0; x < grid_size_x; ++x) {
    for (int y = 0; y < grid_size_y; ++y) {
      for (int z = 0; z < grid_size_z; ++z) {
        if (!voxel_grid[x][y][z].empty()) {
          cloud_new.points.push_back(voxel_grid[x][y][z][0]);
        }
      }
    }
  }

  cloud_new.width = cloud_new.points.size();
  cloud_new.height = 1;

  return cloud_new;
}

class TFBroadcaster : public rclcpp::Node {
public:
  TFBroadcaster() : Node("Node_cpp_broadcaster") {
    RCLCPP_INFO(this->get_logger(), "节点创建");
    pclpub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("ptc", 10);
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ =
        this->create_wall_timer(1s, std::bind(&TFBroadcaster::do_cb, this));
  }

private:
  std::string path =
      "/home/simpletime/Project/learn01_tf_pcl/source/cloud_out_1.pcd";
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pclpub_;
  rclcpp::TimerBase::SharedPtr timer_;

  void do_cb() {
    geometry_msgs::msg::TransformStamped transform;
    tf2::Quaternion qtn;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_new(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ground(
        new pcl::PointCloud<pcl::PointXYZ>);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(
        new sensor_msgs::msg::PointCloud2);

    transform.header.stamp = this->now();
    transform.header.frame_id = "base_link";
    transform.child_frame_id = "6";

    transform.transform.translation.x = 0;
    transform.transform.translation.y = 0;
    transform.transform.translation.z = 0;

    qtn.setRPY(0, 0, 0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();

    if (pcl::io::loadPCDFile(path, *cloud) == -1) {
      PCL_ERROR("加载PCD文件失败\n");
    }

    *cloud_new = voxelCloud(*cloud, 0.1f);

    for (auto &point : cloud_new->points) {
      if (point.z < 0.5 && point.z > -0.5) {
        point.z = 0;
        cloud_ground->push_back(point);
      }
    }
    float min_x = 0, min_y = 0;
    for (auto &point : cloud_ground->points) {
      if (point.x < min_x) {
        min_x = point.x;
      }
      if (point.y < min_y) {
        min_y = point.y;
      }
    }

    float dx = -min_x;
    float dy = -min_y;

    for (auto &point : cloud_ground->points) {
      point.x += dx;
      point.y += dy;
    }

    pcl::io::savePCDFile("map.pcd",*cloud_ground);
    pcl::toROSMsg(*cloud_ground, *cloud_msg);

    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();


    broadcaster_->sendTransform(transform);
    pclpub_->publish(std::move(cloud_msg));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TFBroadcaster>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <pcl/filters/passthrough.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <rclcpp/rclcpp.hpp>
#include <vector>

class GridMap {
public:
  GridMap()
      : map_size_x_(0), map_size_y_(0), resolution_(0.1), grid_map_(nullptr),
        travel_map_(nullptr), is_init_index_(false) {}

  ~GridMap() {
    delete[] grid_map_;
    delete[] travel_map_;
  }

  void initGridMaps(Eigen::Vector2d boundary_min,
                    Eigen::Vector2d boundary_max) {
    boundary_min_ = boundary_min;
    boundary_max_ = boundary_max;

    map_size_x_ =
        std::ceil((boundary_max_(0) - boundary_min_(0)) / resolution_);
    map_size_y_ =
        std::ceil((boundary_max_(1) - boundary_min_(1)) / resolution_);

    // 动态分配网格计数和旅行信息数组
    grid_map_ = new int[map_size_x_ * map_size_y_]; // 一维数组表示二维网格
    travel_map_ =
        new float[map_size_x_ * map_size_y_]; // 一维数组表示二维旅行信息

    // 初始化网格计数和旅行信息
    for (int i = 0; i < map_size_x_ * map_size_y_; i++) {
      grid_map_[i] = 0;      // 初始化网格计数为0
      travel_map_[i] = 0.0f; // 初始化旅行信息为0.0
    }

    // 根据条件初始化索引数组
    if (!is_init_index_) {
      index_map_x_ = new int[map_size_x_];
      for (int i = 0; i < map_size_x_; i++) {
        index_map_x_[i] = i;
      }

      index_map_y_ = new int[map_size_y_];
      for (int i = 0; i < map_size_y_; i++) {
        index_map_y_[i] = i;
      }

      is_init_index_ = true;
    }

    RCLCPP_INFO(rclcpp::get_logger("GridMap"),
                "Grid map initialized with size: (%d, %d)", map_size_x_,
                map_size_y_);
  }

  void incrementGridCount(Eigen::Vector2d pos) {
    if (isInMap(pos)) {
      Eigen::Vector2i index = getGridIndex(pos);
      if (index(0) >= 0 && index(0) < map_size_x_ && index(1) >= 0 &&
          index(1) < map_size_y_) {
        grid_map_[index(0) * map_size_y_ + index(1)]++; // 更新网格计数
      }
    }
  }

  Eigen::Vector2i getGridIndex(Eigen::Vector2d pos) {
    if (!isInMap(pos))
      return Eigen::Vector2i(0, 0); // 返回无效索引

    int index_x = std::floor((pos(0) - boundary_min_(0)) / resolution_);
    int index_y = std::floor((pos(1) - boundary_min_(1)) / resolution_);
    return Eigen::Vector2i(index_x, index_y);
  }

  bool isInMap(Eigen::Vector2d pos) {
    return (pos(0) >= boundary_min_(0) && pos(0) <= boundary_max_(0) &&
            pos(1) >= boundary_min_(1) && pos(1) <= boundary_max_(1));
  }

  void printGridMap() {
    for (int x = 0; x < map_size_x_; ++x) {
      for (int y = 0; y < map_size_y_; ++y) {
        std::cout << grid_map_[x * map_size_y_ + y] << " ";
      }
      std::cout << std::endl;
    }
  }

  void updateGridMap() {
    for (int x = 0; x < map_size_x_; ++x) {
      for (int y = 0; y < map_size_y_; ++y) {
        if (grid_map_[x * map_size_y_ + y] > 2) {
          grid_map_[x * map_size_y_ + y] = 1; // 如果计数大于2（2可改），设为1
        } else {
          grid_map_[x * map_size_y_ + y] = 0; // 否则设置为0
        }
      }
    }
  }

private:
  Eigen::Vector2d boundary_min_;
  Eigen::Vector2d boundary_max_;
  int map_size_x_;
  int map_size_y_;
  double resolution_; // 分辨率

  int *grid_map_;
  float *travel_map_;
  int *index_map_x_;
  int *index_map_y_;
  bool is_init_index_;
};

class PcdProcessor : public rclcpp::Node {
public:
  PcdProcessor() : Node("pcd_processor") { process_pcd(); }

private:
  void process_pcd() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(
        new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("cloud_out_1.pcd", *cloud) == -1) {
      RCLCPP_ERROR(this->get_logger(), "Couldn't read file cloud_out_1.pcd");
      return;
    }

    // 进行z轴截断
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(-1.0, 1.0);
    pass.filter(*cloud_filtered);

    // 计算边界
    Eigen::Vector2d boundary_min(std::numeric_limits<double>::max(),
                                 std::numeric_limits<double>::max());
    Eigen::Vector2d boundary_max(std::numeric_limits<double>::lowest(),
                                 std::numeric_limits<double>::lowest());

    for (const auto &point : cloud_filtered->points) {
      boundary_min(0) = std::min(boundary_min(0), static_cast<double>(point.x));
      boundary_min(1) = std::min(boundary_min(1), static_cast<double>(point.y));
      boundary_max(0) = std::max(boundary_max(0), static_cast<double>(point.x));
      boundary_max(1) = std::max(boundary_max(1), static_cast<double>(point.y));
    }

    // 初始化网格地图
    GridMap grid_map;
    grid_map.initGridMaps(boundary_min, boundary_max);

    // 遍历截断后的点云并更新网格计数
    for (const auto &point : cloud_filtered->points) {
      Eigen::Vector2d pos(point.x, point.y);
      // 检查点是否在边界内
      if (pos(0) > boundary_min(0) && pos(0) < boundary_max(0) &&
          pos(1) > boundary_min(1) && pos(1) < boundary_max(1)) {
        grid_map.incrementGridCount(pos);
      }
    }

    // 更新网格地图
    grid_map.updateGridMap();

    // 打印网格计数
    grid_map.printGridMap();

    // 保存截断后的点云
    pcl::io::savePCDFileASCII("cloud_filtered.pcd", *cloud_filtered);
    RCLCPP_INFO(this->get_logger(),
                "Processing completed. File saved as cloud_filtered.pcd");
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PcdProcessor>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
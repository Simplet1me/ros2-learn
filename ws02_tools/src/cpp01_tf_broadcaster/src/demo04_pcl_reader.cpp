#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "pcl/point_types.h"
#include "pcl/point_cloud.h"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/filters/voxel_grid.h"
using namespace std::chrono_literals;
class PointCouldPublisher : public rclcpp::Node{
public:
  PointCouldPublisher():Node("pcl_pub_node_cpp"){
    publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pt",10);
    publisher1_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pt1",10);
    timer_ = this->create_wall_timer(1s,std::bind(&PointCouldPublisher::Pub_pcl,this));
  }

private:
  void Pub_pcl(){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtercloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    std::string path = "/home/simpletime/Project/ws02_tools/source/top3.pcd";
    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>(path,*cloud) == -1){
        PCL_ERROR("Failed to load PCD file\n");
    }


    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg(new sensor_msgs::msg::PointCloud2);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msg1(new sensor_msgs::msg::PointCloud2);
    //放大点云
    for(auto& point: *cloud){
      point.x *= size;
      point.y *= size;
      point.z *= size;
    }
    //封装未过滤消息
    pcl::toROSMsg(*cloud,*cloud_msg);
    //过滤
    /*
    pcl::VoxelGrid<pcl::PointXYZRGB> filter;
    filter.setInputCloud(cloud);
    filter.setLeafSize(0.1f,0.1f,0.1f);
    filter.filter(*filtercloud);
    */
    voxelDownsample(cloud,filtercloud,0.1f);
    RCLCPP_INFO(this->get_logger(),"Points:%ld",filtercloud->points.size());
    pcl::toROSMsg(*filtercloud,*cloud_msg1);
    //输出
    

    cloud_msg->header.frame_id = "base_link";
    cloud_msg->header.stamp = this->now();
    cloud_msg1->header.frame_id = "base_link";
    cloud_msg1->header.stamp = this->now();
    
    publisher_->publish(std::move(cloud_msg));
    publisher1_->publish(std::move(cloud_msg1));
  }


  void voxelDownsample(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& input_cloud,
                     pcl::PointCloud<pcl::PointXYZRGB>::Ptr& output_cloud,
                     float voxel_size) {
    // 计算体素网格尺寸
    float min_x = input_cloud->points[0].x,min_y = input_cloud->points[0].y, min_z = input_cloud->points[0].z;
    float max_x = min_x, max_y = min_y, max_z = min_z;

    // 找到点云的边界
    for (const auto& point : input_cloud->points) {
        if (point.x < min_x) min_x = point.x;
        if (point.x > max_x) max_x = point.x;
        if (point.y < min_y) min_y = point.y;
        if (point.y > max_y) max_y = point.y;
        if (point.z < min_z) min_z = point.z;
        if (point.z > max_z) max_z = point.z;
    }

    // 计算三维网格的大小
    int grid_size_x = static_cast<int>((max_x - min_x) / voxel_size) + 1;
    int grid_size_y = static_cast<int>((max_y - min_y) / voxel_size) + 1;
    int grid_size_z = static_cast<int>((max_z - min_z) / voxel_size) + 1;

    // 创建三维数组以存储体素内的点坐标
    std::vector<std::vector<std::vector<std::vector<pcl::PointXYZRGB>>>> voxel_grid(grid_size_x,
        std::vector<std::vector<std::vector<pcl::PointXYZRGB>>>(grid_size_y,
            std::vector<std::vector<pcl::PointXYZRGB>>(grid_size_z)));

    // 将点分配给体素
    for (const auto& point : input_cloud->points) {
        int voxel_x = static_cast<int>((point.x - min_x) / voxel_size);
        int voxel_y = static_cast<int>((point.y - min_y) / voxel_size);
        int voxel_z = static_cast<int>((point.z - min_z) / voxel_size);

        // 确保在范围内
        if (voxel_x >= 0 && voxel_x < grid_size_x &&
            voxel_y >= 0 && voxel_y < grid_size_y &&
            voxel_z >= 0 && voxel_z < grid_size_z) {
            voxel_grid[voxel_x][voxel_y][voxel_z].push_back(point);
        }
    }

    // 从体素网格中提取点
    for (int x = 0; x < grid_size_x; ++x) {
        for (int y = 0; y < grid_size_y; ++y) {
            for (int z = 0; z < grid_size_z; ++z) {
                if (!voxel_grid[x][y][z].empty()) {
                    // 使用第一个点作为代表点
                    output_cloud->points.push_back(voxel_grid[x][y][z][0]);
                }
            }
        }
    }

    // 更新输出点云的宽高
    output_cloud->width = output_cloud->points.size();
    output_cloud->height = 1; // 表示无序的点云
}


  int count;
  int size = 80;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher1_;
  rclcpp::TimerBase::SharedPtr timer_;
  
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto pclpub = std::make_shared<PointCouldPublisher>();
  rclcpp::spin(pclpub);
  rclcpp::shutdown();
}
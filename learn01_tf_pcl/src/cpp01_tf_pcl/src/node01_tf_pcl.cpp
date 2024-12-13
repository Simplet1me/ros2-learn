#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "pcl/point_types.h"
#include "pcl/point_cloud.h"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"
using namespace std::chrono_literals;

class TFBroadcaster : public rclcpp::Node{
public:
  TFBroadcaster() : Node("Node_cpp_broadcaster"){
    RCLCPP_INFO(this->get_logger(),"节点创建");
    pclpubf_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("ptf",10);
    pclpubc_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("ptc",10);
    broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(1s,std::bind(&TFBroadcaster::do_cb,this));



  }

private:
  void do_cb(){
    geometry_msgs::msg::TransformStamped transform;
    tf2::Quaternion qtn;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudf(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudc(new pcl::PointCloud<pcl::PointXYZRGB>);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msgf(new sensor_msgs::msg::PointCloud2);
    sensor_msgs::msg::PointCloud2::UniquePtr cloud_msgc(new sensor_msgs::msg::PointCloud2);

    transform.header.stamp = this->now();
    transform.header.frame_id = "base_link";
    transform.child_frame_id = "base_link_child";

    transform.transform.translation.x = 1;
    transform.transform.translation.y = 1;
    transform.transform.translation.z = 1;

    qtn.setRPY(0,0,0);
    transform.transform.rotation.x = qtn.x();
    transform.transform.rotation.y = qtn.y();
    transform.transform.rotation.z = qtn.z();
    transform.transform.rotation.w = qtn.w();


    if(pcl::io::loadPCDFile(path,*cloudf) == -1){
      PCL_ERROR("加载PCD文件失败\n");
    }
    if(pcl::io::loadPCDFile(path,*cloudc) == -1){
      PCL_ERROR("加载PCD文件失败\n");
    }

    for (size_t i = 0; i < cloudf->size(); i++){
      cloudf->points[i].x = cloudf->points[i].x+0.5;
      cloudf->points[i].y = cloudf->points[i].y+0.5;
      cloudf->points[i].z = cloudf->points[i].z+0.5;
    }
    
    for (size_t i = 0; i < cloudc->size(); i++){
      cloudc->points[i].x = cloudc->points[i].x-0.5;
      cloudc->points[i].y = cloudc->points[i].y-0.5;
      cloudc->points[i].z = cloudc->points[i].z-0.5;
    }

    pcl::toROSMsg(*cloudf,*cloud_msgf);
    pcl::toROSMsg(*cloudc,*cloud_msgc);
    cloud_msgf->header.frame_id = "base_link";
    cloud_msgf->header.stamp = this->now();
    cloud_msgc->header.frame_id = "base_link_child";
    cloud_msgc->header.stamp = this->now();

    //double a = cloud->points[0].x;
    count++;
    RCLCPP_INFO(this->get_logger(),"发布中:%d",count);
    //RCLCPP_INFO(this->get_logger(),"%f",a);
    broadcaster_->sendTransform(transform);
    pclpubf_->publish(std::move(cloud_msgf));
    pclpubc_->publish(std::move(cloud_msgc));
  }


  int count = 0;
  std::string path = "/home/simpletime/Project/learn01_tf_pcl/source/top3.pcd";
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pclpubf_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pclpubc_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc,char *argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<TFBroadcaster>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
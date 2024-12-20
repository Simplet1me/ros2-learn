#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
using namespace std::chrono_literals;

struct point
{
  int x;
  int y;
  int data;
};

class MapPublisher : public rclcpp::Node{
public:
  MapPublisher() : Node("map_pub_node"){
    navpublisher_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map",10);
    timer_ = create_wall_timer(0.1s,std::bind(&MapPublisher::do_cb,this));
    map.info.width = width;
    map.info.height = height;
    map.info.resolution = resolution;
    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.origin.position.z = 0;
    map.info.origin.orientation.w = 0;
    map.data.resize(width * height,-1);
    map.header.stamp = this->now();
    map.header.frame_id = "base_link";
  }
private:
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr navpublisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  nav_msgs::msg::OccupancyGrid map;
  int width = 160;
  int height = 90;
  double resolution = 0.1;
  void do_cb(){
    //起点终点初始化
    point start_point={0,0,100};
    point end_point={150,79,100};
    map.data[start_point.y * width + start_point.x] = start_point.data;
    map.data[end_point.y * width + end_point.x] = end_point.data;

    //生产障碍物
    for (size_t i = 20; i <= 70; i++){//列
      for (size_t j = 50; j <= 100; j++){//行
          map.data[i * width + j] = 80;
      }
    }

    
    //障碍物膨胀算法，空心可用
    for (int i = 80; i >= 55; i-=5){
      for (size_t grid_y = 0; grid_y < height; grid_y++){
        for (size_t grid_x = 0; grid_x < width; grid_x++){
          //遍历到障碍物80
          if(map.data[grid_y * width + grid_x] == i){
            //判断周围障碍物是否为80，如果否就将其变为70
            //上
            if(map.data[grid_y * width + grid_x + width] < i) map.data[grid_y * width + grid_x + width] = i-5;
            //右上
            if(map.data[grid_y * width + grid_x + width + 1] < i) map.data[grid_y * width + grid_x + width + 1] = i-5;
            //右
            if(map.data[grid_y * width + grid_x + 1] < i) map.data[grid_y * width + grid_x + 1] = i-5;
            //右下
            if(map.data[grid_y * width + grid_x - width + 1] < i) map.data[grid_y * width + grid_x - width + 1] = i-5;
            //下
            if(map.data[grid_y * width + grid_x - width] < i) map.data[grid_y * width + grid_x - width] = i-5;
            //左下
            if(map.data[grid_y * width + grid_x - width - 1] < i) map.data[grid_y * width + grid_x - width - 1] = i-5;
            //左
            if(map.data[grid_y * width + grid_x - 1] < i) map.data[grid_y * width + grid_x - 1] = i-5;
            //左上
            if(map.data[grid_y * width + grid_x + width - 1] < i) map.data[grid_y * width + grid_x + width - 1] = i-5;
          }
        }
      }
    }


    navpublisher_->publish(map);
  }
};

int main(int argc,char const * argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<MapPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
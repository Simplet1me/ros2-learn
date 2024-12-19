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
        if(i>30&&i<60 && j>60&&j<90){
          
        }
        else{
          map.data[i * width + j] = 80;
        }
          
      }
    }

    //障碍物膨胀-行
    for (size_t grid_y = 0; grid_y < height; grid_y++){
      for (size_t grid_x = 0; grid_x < width; grid_x++){
        if (map.data[grid_y * width + grid_x] == 80){
          
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
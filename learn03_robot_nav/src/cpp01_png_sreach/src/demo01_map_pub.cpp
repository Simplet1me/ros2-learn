#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <memory>
using namespace std::chrono_literals;

struct point{
  int x;
  int y;
  float g;
  float h;
  float f;
  point* parent;
  point(int x,int y) : x(x),y(y),g(0),h(0),f(0), parent(nullptr){}
  bool operator==(const point& n) const{
    return x == n.x && y == n.y;
  }

  bool operator!=(const point& n) const{
    return !(*this == n);
  }

  struct Hash{
    size_t operator()(const point& n) const {
      return std::hash<int>()(n.x) ^ std::hash<int>()(n.y);
      }
  };
};

//求两点间的曼哈顿距离，用于启发搜索
float eular(point* a, point* b){
  //绝对距离
  return sqrt(pow(a->x - b->x,2) + pow(a->y - b->y,2));
}

class MapPublisher : public rclcpp::Node{
 public:
  MapPublisher() : Node("map_pub_node"){
    navpublisher_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map",10);
    timer_ = create_wall_timer(5s,std::bind(&MapPublisher::do_cb,this));
    RCLCPP_INFO(this->get_logger(),"初始化");
    map.info.width = width;
    map.info.height = height;
    map.info.resolution = resolution;
    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.origin.position.z = 0;
    map.info.origin.orientation.w = 0;
    map.data.resize(width * height,-1);
    map.header.stamp = this->get_clock()->now();
    map.header.frame_id = "map";
  }
private:
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr navpublisher_;
  std::vector<point*> openlist;
  std::unordered_set<point, point::Hash> closedlist;
  rclcpp::TimerBase::SharedPtr timer_;
  nav_msgs::msg::OccupancyGrid map;
  int width = 160;
  int height = 90;
  double resolution = 0.1;

  void sort(){
    for(size_t j = 0;j<openlist.size()-1;j++){
        for (size_t i = 0; i < openlist.size()-j-1; i++){
            if(openlist[i]->f < openlist[i+1]->f){
                std::swap(openlist[i],openlist[i+1]);
            }
        }
    }
  }

  void do_cb(){
    //清空地图
    for (size_t i = 0; i < map.data.size(); i++){
      map.data[i] = -1;
    }

    //起点终点初始化
    point* start_point = new point(0,0);
    point* end_point = new point(130,60);
    map.data[start_point->y * width + start_point->x] = 30;
    map.data[end_point->y * width + end_point->x] = 30;


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
            //判断周围障碍物是否为80，如果否就将其变为75，逐级递减
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


    //A*搜索路径

    //将起始点加入openlist
    openlist.push_back(start_point);

    while (!openlist.empty()){
      sort();
      //将当前点设为open里最低点
      point* current = openlist.back();
      openlist.pop_back();

      //抵达终点，直接跳出
      if(current->x == end_point->x && current->y == end_point->y){
        RCLCPP_INFO(this->get_logger(),"抵达终点");
        std::vector<std::pair<int,int>> path;
        while (current){ 
          path.push_back({current->x,current->y});     
          current = current->parent;
        }
        std::reverse(path.begin(),path.end());
        RCLCPP_INFO(this->get_logger(),"完成路径队列");
        for(const auto& p : path){  
          map.data[p.second * width + p.first] = 1;
        }
        RCLCPP_INFO(this->get_logger(),"路径打印完成");
        break;
      }
      //将当前点塞入闭合列表
      closedlist.insert(*current);


      std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
      //右下左上依次遍历
      for (const auto& d : directions){
        int newX = current->x + d.first;
        int newY = current->y + d.second;
        //RCLCPP_INFO(this->get_logger(),"遍历邻点");

        //检查上方点的障碍及边界
        //上方点0<=x<边界160 && 上方点0<=y<边界90  障碍物范围是80-55 取65为可走路径   
        if(newX >= 0 && newX < width && newY >= 0 && newY < height && map.data[newY * width + newX] <= 65){

          point* point_neighbor = new point(newX,newY);
          //绝对代价
          point_neighbor->g = current->g + 1;
          //启发代价
          point_neighbor->h = eular(point_neighbor,end_point); 
          //总代价= 绝对代价 + 启发代价
          point_neighbor->f = point_neighbor->g + point_neighbor->h;
          //指针指向父级，用于回溯路径
          point_neighbor->parent = current;

          //检查是否在闭合列表
          if(closedlist.find(*point_neighbor) != closedlist.end()){
            delete point_neighbor;//删除邻点
            continue;
          }

          //检查是否在开放列表中
          bool inOpenlist = false;
          std::vector<point*> tempOpenlist = openlist;
          while (!tempOpenlist.empty()){
            point* n = tempOpenlist.back();
            tempOpenlist.pop_back();
            if(n->x == point_neighbor->x && n->y == point_neighbor->y && point_neighbor->g >= n->g){
              inOpenlist =true;
              delete point_neighbor;
              break;
            }
          }

          if(!inOpenlist){
            openlist.push_back(point_neighbor);
          }
        }
      }

      std::vector<std::pair<int, int>> directions_2 = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
      //右下左上依次遍历
      for (const auto& d : directions_2){
        int newX = current->x + d.first;
        int newY = current->y + d.second;
        //RCLCPP_INFO(this->get_logger(),"遍历邻点");

        //检查上方点的障碍及边界
        //上方点0<=x<边界160 && 上方点0<=y<边界90  障碍物范围是80-55 取65为可走路径   
        if(newX >= 0 && newX < width && newY >= 0 && newY < height && map.data[newY * width + newX] <= 65){

          point* point_neighbor = new point(newX,newY);
          //绝对代价
          point_neighbor->g = current->g + 1.4;
          //启发代价
          point_neighbor->h = eular(point_neighbor,end_point); 
          //总代价= 绝对代价 + 启发代价
          point_neighbor->f = point_neighbor->g + point_neighbor->h;
          //指针指向父级，用于回溯路径
          point_neighbor->parent = current;

          //检查是否在闭合列表
          if(closedlist.find(*point_neighbor) != closedlist.end()){
            delete point_neighbor;//删除邻点
            continue;
          }

          //检查是否在开放列表中
          bool inOpenlist = false;
          std::vector<point*> tempOpenlist = openlist;
          while (!tempOpenlist.empty()){
            point* n = tempOpenlist.back();
            tempOpenlist.pop_back();
            if(n->x == point_neighbor->x && n->y == point_neighbor->y && point_neighbor->g >= n->g){
              inOpenlist =true;
              delete point_neighbor;
              break;
            }
          }

          if(!inOpenlist){
            openlist.push_back(point_neighbor);
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
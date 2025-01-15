#include "astar.h"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include <Eigen/Dense>
#include <math.h>
#include <unordered_set>

float eular(point *a, point *b) {
  // 绝对距离
  return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

void clearSinglePoint(nav_msgs::msg::OccupancyGrid &map) {
  int width = map.info.width;
  int height = map.info.height;
  for (int grid_y = 0; grid_y < height; grid_y++) {
    for (int grid_x = 0; grid_x < width; grid_x++) {
      if (map.data[grid_y * width + grid_x] == 80) {
        if (map.data[grid_y * width + grid_x + width] == -1 &&
            map.data[grid_y * width + grid_x + width + 1] == -1 &&
            map.data[grid_y * width + grid_x + 1] == -1 &&
            map.data[grid_y * width + grid_x - width + 1] == -1 &&
            map.data[grid_y * width + grid_x - width] == -1 &&
            map.data[grid_y * width + grid_x - width - 1] == -1 &&
            map.data[grid_y * width + grid_x - 1] == -1 &&
            map.data[grid_y * width + grid_x + width - 1] == -1) {
          map.data[grid_y * width + grid_x] = -1;
        }
      }
    }
  }
}

void updateTravelMap(nav_msgs::msg::OccupancyGrid &travel_map) {
  int width = travel_map.info.width;
  int height = travel_map.info.height;
  for (int i = 80; i >= 75; i -= 5) {
    for (int grid_y = 0; grid_y < height; grid_y++) {
      for (int grid_x = 0; grid_x < width; grid_x++) {
        // 遍历到障碍物80
        if (travel_map.data[grid_y * width + grid_x] == i) {
          // 判断周围障碍物是否为80，如果否就将其变为75，逐级递减
          // 上
          if (travel_map.data[grid_y * width + grid_x + width] < i &&
              grid_y * width + grid_x + width < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x + width] = i - 5;
          // 右上
          if (travel_map.data[grid_y * width + grid_x + width + 1] < i &&
              grid_y * width + grid_x + width + 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x + width + 1] = i - 5;
          // 右
          if (travel_map.data[grid_y * width + grid_x + 1] < i &&
              grid_y * width + grid_x + 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x + 1] = i - 5;
          // 右下
          if (travel_map.data[grid_y * width + grid_x - width + 1] < i &&
              grid_y * width + grid_x - width + 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x - width + 1] = i - 5;
          // 下
          if (travel_map.data[grid_y * width + grid_x - width] < i &&
              grid_y * width + grid_x - width < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x - width] = i - 5;
          // 左下
          if (travel_map.data[grid_y * width + grid_x - width - 1] < i &&
              grid_y * width + grid_x - width - 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x - width - 1] = i - 5;
          // 左
          if (travel_map.data[grid_y * width + grid_x - 1] < i &&
              grid_y * width + grid_x - 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x - 1] = i - 5;
          // 左上
          if (travel_map.data[grid_y * width + grid_x + width - 1] < i &&
              grid_y * width + grid_x + width - 1 < travel_map.data.size())
            travel_map.data[grid_y * width + grid_x + width - 1] = i - 5;
        }
      }
    }
  }
}

void sort(std::vector<point *> &openlist) {
  for (size_t j = 0; j < openlist.size() - 1; j++) {
    for (size_t i = 0; i < openlist.size() - j - 1; i++) {
      if (openlist[i]->f < openlist[i + 1]->f) {
        std::swap(openlist[i], openlist[i + 1]);
      }
    }
  }
}

std::vector<Eigen::Vector2f> Astar(point *start_point, point *end_point,
                                   nav_msgs::msg::OccupancyGrid map) {
  std::unordered_set<point, point::Hash> closedlist;
  std::vector<point *> openlist;
  int width = map.info.width;
  int height = map.info.height;
  // A*搜索路径
  // 将起始点加入openlist
  openlist.push_back(start_point);

  while (!openlist.empty()) {
    sort(openlist);
    // 将当前点设为open里最低点
    point *current = openlist.back();
    openlist.pop_back();

    // 抵达终点，直接跳出
    if (current->x == end_point->x && current->y == end_point->y) {
      std::vector<Eigen::Vector2f> path;
      while (current) {
        path.push_back({current->x, current->y});
        current = current->parent;
      }
      std::reverse(path.begin(), path.end());

      return path;
    }
    // 将当前点塞入闭合列表
    closedlist.insert(*current);

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    // 右下左上依次遍历
    for (const auto &d : directions) {
      int newX = current->x + d.first;
      int newY = current->y + d.second;
      // RCLCPP_INFO(this->get_logger(),"遍历邻点");

      // 检查上方点的障碍及边界
      // 上方点0<=x<边界160 && 上方点0<=y<边界90  障碍物范围是80-55
      // 取65为可走路径
      if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
          map.data[newY * width + newX] <= 65) {

        point *point_neighbor = new point(newX, newY);
        // 绝对代价
        point_neighbor->g = current->g + 1;
        // 启发代价
        point_neighbor->h = eular(point_neighbor, end_point);
        // 总代价= 绝对代价 + 启发代价
        point_neighbor->f = point_neighbor->g + point_neighbor->h;
        // 指针指向父级，用于回溯路径
        point_neighbor->parent = current;

        // 检查是否在闭合列表
        if (closedlist.find(*point_neighbor) != closedlist.end()) {
          delete point_neighbor; // 删除邻点
          continue;
        }

        // 检查是否在开放列表中
        bool inOpenlist = false;
        std::vector<point *> tempOpenlist = openlist;
        while (!tempOpenlist.empty()) {
          point *n = tempOpenlist.back();
          tempOpenlist.pop_back();
          if (n->x == point_neighbor->x && n->y == point_neighbor->y &&
              point_neighbor->g >= n->g) {
            inOpenlist = true;
            delete point_neighbor;
            break;
          }
        }

        if (!inOpenlist) {
          openlist.push_back(point_neighbor);
        }
      }
    }

    std::vector<std::pair<int, int>> directions_2 = {
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    // 右下左上依次遍历
    for (const auto &d : directions_2) {
      int newX = current->x + d.first;
      int newY = current->y + d.second;
      // RCLCPP_INFO(this->get_logger(),"遍历邻点");

      // 检查上方点的障碍及边界
      // 上方点0<=x<边界160 && 上方点0<=y<边界90  障碍物范围是80-55
      // 取65为可走路径
      if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
          map.data[newY * width + newX] <= 75) {

        point *point_neighbor = new point(newX, newY);
        // 绝对代价
        point_neighbor->g = current->g + 1.4;
        // 启发代价
        point_neighbor->h = eular(point_neighbor, end_point);
        // 总代价= 绝对代价 + 启发代价
        point_neighbor->f = point_neighbor->g + point_neighbor->h;
        // 指针指向父级，用于回溯路径
        point_neighbor->parent = current;

        // 检查是否在闭合列表
        if (closedlist.find(*point_neighbor) != closedlist.end()) {
          delete point_neighbor; // 删除邻点
          continue;
        }

        // 检查是否在开放列表中
        bool inOpenlist = false;
        std::vector<point *> tempOpenlist = openlist;
        while (!tempOpenlist.empty()) {
          point *n = tempOpenlist.back();
          tempOpenlist.pop_back();
          if (n->x == point_neighbor->x && n->y == point_neighbor->y &&
              point_neighbor->g >= n->g) {
            inOpenlist = true;
            delete point_neighbor;
            break;
          }
        }

        if (!inOpenlist) {
          openlist.push_back(point_neighbor);
        }
      }
    }
  }
}
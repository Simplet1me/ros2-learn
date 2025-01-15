#ifndef astar_H
#define astar_H
#include <boost/hana/fwd/integral_constant.hpp>
#include <functional>
#include <Eigen/Dense>
#include "nav_msgs/msg/occupancy_grid.hpp"

struct point {
  int x;
  int y;
  float g;
  float h;
  float f;
  point *parent;
  point(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}
  bool operator==(const point &n) const { return x == n.x && y == n.y; }

  bool operator!=(const point &n) const { return !(*this == n); }

  struct Hash {
    size_t operator()(const point &n) const {
      return std::hash<int>()(n.x) ^ std::hash<int>()(n.y);
    }
  };
};

float eular(point *a, point *b);

void clearSinglePoint(nav_msgs::msg::OccupancyGrid &map);

void updateTravelMap(nav_msgs::msg::OccupancyGrid &travel_map);

void sort(std::vector<point *> &openlist);

std::vector<Eigen::Vector2f> Astar(point *start_point, point *end_point,nav_msgs::msg::OccupancyGrid map);

#endif
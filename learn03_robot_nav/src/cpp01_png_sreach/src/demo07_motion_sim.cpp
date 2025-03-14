#include <Eigen/Dense>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Quaternion.h>

using namespace std::chrono_literals;

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

float eular(point *a, point *b) {
  // 绝对距离
  return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

class PointMotionSim : public rclcpp::Node {
public:
  PointMotionSim() : Node("point_motion_sim") {
    // 初始化变量
    current_position(0, 0);
    current_velocity(0, 0);
    max_acceleration = 2;
    max_velocity = 1;
    isArried = false;
    havePath = false;
    map.info.width = width;
    map.info.height = height;
    map.info.resolution = resolution;
    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.origin.position.z = 0;
    // 旋转地图对齐坐标点
    qtn.setRPY(0, M_PI * 2, 0);
    map.info.origin.orientation.x = qtn.x();
    map.info.origin.orientation.y = qtn.y();
    map.info.origin.orientation.z = qtn.z();
    map.info.origin.orientation.w = qtn.w();
    map.data.resize(width * height, -1);
    map.header.stamp = this->now();
    map.header.frame_id = "map";
    nav_path.header.stamp = this->now();
    nav_path.header.frame_id = "map";
    point_publisher_ =
        this->create_publisher<geometry_msgs::msg::PointStamped>("point", 10);
    poselistener_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        "/goal_pose", 10,
        std::bind(&PointMotionSim::GetPose, this, std::placeholders::_1));
    mappublisher_ =
        this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);
    pathpublisher_ = this->create_publisher<nav_msgs::msg::Path>("path",10);
    timer_ = this->create_wall_timer(
        100ms, std::bind(&PointMotionSim::timer_callback, this));
  }

private:
  bool isArried;
  bool havePath;
  float max_velocity;
  float max_acceleration;
  tf2::Quaternion qtn;
  int width = 320;
  int height = 180;
  double resolution = 0.05;
  std::vector<Eigen::Vector2f> path;
  Eigen::Vector2f current_position;
  Eigen::Vector2f goal_position;
  Eigen::Vector2f current_velocity;
  rclcpp::TimerBase::SharedPtr timer_;
  nav_msgs::msg::OccupancyGrid map;
  nav_msgs::msg::Path nav_path;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr
      point_publisher_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr
      poselistener_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr mappublisher_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathpublisher_;
  void timer_callback() {
    // 运动解算
    if (!isArried && havePath) {
      Eigen::Vector2f start = path[0];
      Eigen::Vector2f end = path[1];
      Eigen::Vector2f direction = end - start;
      float distance = direction.norm();
      Eigen::Vector2f unitDirection =
          distance > 0 ? direction.normalized() : Eigen::Vector2f::Zero();
      Eigen::Vector2f nextDirection;
      if (path.size() >= 2) {
        Eigen::Vector2f nextEnd = path[2];
        nextDirection = nextEnd - end;
      } else {
        nextDirection = end - start;
        isArried = true;
        havePath = false;
      }
      float curvature = calculateCurvature(direction, nextDirection);
      float corneringFactor = (curvature > 0.1f) ? 0.5f : 1.0f;

      Eigen::Vector2f targetVelocity =
          unitDirection * max_velocity * corneringFactor;
      float timeToAcc = (targetVelocity - current_velocity).norm() /
                        max_acceleration; // 加速所需时间，速度差/最大加速度
      if (timeToAcc > 0) {
        accelerate(timeToAcc, targetVelocity);
      }

      if (path.size() <= 2) {
        decelerateToStop();
      }

      moveTowards();
      path.erase(path.begin());
      nav_path.poses.erase(nav_path.poses.begin());
    }

    // 消息发布
    auto position_msg = geometry_msgs::msg::PointStamped();
    position_msg.header.frame_id = "map";
    position_msg.header.stamp = this->now();
    position_msg.point.x = current_position.x();
    position_msg.point.y = current_position.y();
    position_msg.point.z = 0;
    //RCLCPP_INFO(this->get_logger(), "发布位置%.2f %.2f", current_position.x(),current_position.y());
    RCLCPP_INFO(this->get_logger(), "当前速度v:%.2f", current_velocity.norm());
    pathpublisher_->publish(nav_path);
    mappublisher_->publish(map);
    point_publisher_->publish(position_msg);
  }

  void GetPose(const geometry_msgs::msg::PoseStamped &msg) {
    current_velocity = current_velocity * 0;
    Eigen::Vector2f goal_position(msg.pose.position.x, msg.pose.position.y);
    RCLCPP_INFO(this->get_logger(), "收到目标点信息X Y:%.2f %.2f",goal_position.x(), goal_position.y());
    for(auto &p : map.data){
      p = -1;
    }
    this->path = Astar(current_position, goal_position);
    for(auto &p : path){
      geometry_msgs::msg::PoseStamped pose;
      pose.header.stamp = this->now();
      pose.header.frame_id = "map";
      pose.pose.position.x = p.x();
      pose.pose.position.y = p.y();
      pose.pose.position.z = 0;
      pose.pose.orientation.w = 1.0;
      nav_path.poses.push_back(pose); 
    }

    havePath = true;
    isArried = false;
    std::cout<<"路径长度："<<path.size()<<std::endl;
  }
  // 曲率计算
  float calculateCurvature(const Eigen::Vector2f &direction,
                           const Eigen::Vector2f &nextDirection) {
    float dx1 = direction.x();
    float dy1 = direction.y();
    float dx2 = nextDirection.x();
    float dy2 = nextDirection.y();
    return std::abs(dx1 * dy2 - dy1 * dx2) /
           (direction.norm() * nextDirection.norm() + 1e-6); // 避免除以零
  }

  // 执行加速
  void accelerate(float timeToAcc, const Eigen::Vector2f &targetVelocity) {
    Eigen::Vector2f acceleration =
        (targetVelocity - current_velocity).normalized() * max_acceleration;

    current_velocity += acceleration * timeToAcc;

    // 限制速度不超过最大速度
    if (current_velocity.norm() > max_velocity) {
      current_velocity.normalize();
      current_velocity *= max_velocity;
    }
  }

  // 停车
  void decelerateToStop() {
    current_velocity.setZero(); // 将速度设为0
    std::cout << "Stopped at: (" << current_position.x() << ", "
              << current_position.y() << ")\n";
  }

  // 执行速度解算
  void moveTowards() {
    float deltaTime = 0.1f; // 时间步长，需要和Timer的间隔对应
    current_position += current_velocity * deltaTime;
  }

  int Floattoint(float a) {
    int result = a / resolution + 0.5;
    return result;
  }

  std::vector<Eigen::Vector2f> Astar(Eigen::Vector2f start, Eigen::Vector2f end) {
    std::unordered_set<point, point::Hash> closedlist;
    std::vector<point *> openlist;
    int width = map.info.width;
    int height = map.info.height;
    RCLCPP_INFO(this->get_logger(),"START:%d %d",Floattoint(start.x()),Floattoint(start.y()));
    RCLCPP_INFO(this->get_logger(),"END:%d %d",Floattoint(end.x()),Floattoint(end.y()));
    point *start_point =
        new point(Floattoint(start.x()), Floattoint(start.y()));
    point *end_point = new point(Floattoint(end.x()), Floattoint(end.y()));

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
          path.push_back({current->x * resolution, current->y * resolution});
          map.data[current->y * width + current->x] = 1;
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
            map.data[newY * width + newX] <= 65) {

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

  void sort(std::vector<point *> &openlist) {
    for (size_t j = 0; j < openlist.size() - 1; j++) {
      for (size_t i = 0; i < openlist.size() - j - 1; i++) {
        if (openlist[i]->f < openlist[i + 1]->f) {
          std::swap(openlist[i], openlist[i + 1]);
        }
      }
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointMotionSim>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
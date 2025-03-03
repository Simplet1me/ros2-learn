#include <Eigen/Dense>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class PointMotionSim : public rclcpp::Node {
public:
  PointMotionSim() : Node("point_motion_sim") {
    // 初始化变量
    current_position(0, 0);
    current_velocity(0, 0);
    max_acceleration = 2;
    max_velocity = 5;
    isArried = false;
    path = {Eigen::Vector2f(0, 0), Eigen::Vector2f(3, 2), Eigen::Vector2f(6, 5),
            Eigen::Vector2f(8, 3), Eigen::Vector2f(10, 10)};
    point_publisher_ =
        this->create_publisher<geometry_msgs::msg::PointStamped>("point", 10);

    timer_ = this->create_wall_timer(
        100ms, std::bind(&PointMotionSim::timer_callback, this));
  }

private:
  bool isArried;
  float max_velocity;
  float max_acceleration;
  std::vector<Eigen::Vector2f> path;
  Eigen::Vector2f current_position;
  Eigen::Vector2f goal_position;
  Eigen::Vector2f current_velocity;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_publisher_;
  void timer_callback() {
    //运动解算
    if (!isArried) {
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
      }
      float curvature = calculateCurvature(direction, nextDirection);
      float corneringFactor = (curvature > 0.1f) ? 0.5f : 1.0f;

      Eigen::Vector2f targetVelocity =
          unitDirection * max_velocity * corneringFactor;
      float timeToAcc = (targetVelocity - current_velocity).norm() / max_acceleration; // 加速所需时间，速度差/最大加速度
      if (timeToAcc > 0) {
        accelerate(timeToAcc, targetVelocity);
      }

      if (path.size() <= 2) {
        decelerateToStop();
      }

      moveTowards();
      path.erase(path.begin());
      for (int i = 0; i < path.size(); i++) {
        std::cout << path[i].x() << " " << path[i].y() << std::endl;
      }
    }


    //消息发布
    auto position_msg = geometry_msgs::msg::PointStamped();
    position_msg.header.frame_id = "map";
    position_msg.header.stamp = this->now();
    position_msg.point.x = current_position.x();
    position_msg.point.y = current_position.y();
    position_msg.point.z = 0;
    RCLCPP_INFO(this->get_logger(), "发布位置%.2f %.2f", current_position.x(),
                current_position.y());
    point_publisher_->publish(position_msg);
  }

  //曲率计算
  float calculateCurvature(const Eigen::Vector2f &direction,
                           const Eigen::Vector2f &nextDirection) {
    float dx1 = direction.x();
    float dy1 = direction.y();
    float dx2 = nextDirection.x();
    float dy2 = nextDirection.y();
    return std::abs(dx1 * dy2 - dy1 * dx2) /
           (direction.norm() * nextDirection.norm() + 1e-6); // 避免除以零
  }

  //执行加速
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

  //停车
  void decelerateToStop() {
    current_velocity.setZero(); // 将速度设为0
    std::cout << "Stopped at: (" << current_position.x() << ", "
              << current_position.y() << ")\n";
  }

  //执行速度解算
  void moveTowards() {
    float deltaTime = 0.1f;//时间步长，需要和Timer的间隔对应
    current_position += current_velocity * deltaTime;

    std::cout << "Moving to: (" << current_position.x() << ", "
              << current_position.y() << ")\n";
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<PointMotionSim>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
using namespace std::chrono_literals;
class PointBroadcaster : public rclcpp::Node{
public:
    PointBroadcaster():Node("point_broadcaster"){
        point_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("point",10);
        timer_ = this->create_wall_timer(0.3s,std::bind(&PointBroadcaster::on_timer,this));
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    double x =0.0;
    void on_timer(){
        geometry_msgs::msg::PointStamped ps;
        x += 0.05;
        ps.header.frame_id = "frame_a";
        ps.header.stamp = this->now();
        ps.point.x = x;
        ps.point.y = 0.0;
        ps.point.z = -0.1;
        point_pub_->publish(ps);
    }
};

int main(int argc,char * argv[]){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<PointBroadcaster>();
    rclcpp::spin(node);
    return 0;
}
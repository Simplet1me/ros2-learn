#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

class Listener:public rclcpp::Node{
public:
    Listener():Node("listener_node_cpp"){
        RCLCPP_INFO(this->get_logger(),"Listener create");
        subscription_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("goal_pose",10,std::bind(&Listener::do_cb,this,std::placeholders::_1));

    }

private:
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscription_;
    void do_cb(const geometry_msgs::msg::PoseStamped &msg){
        RCLCPP_INFO(this->get_logger(),"XYZ:%.2f %.2f %.2f",msg.pose.position.x,msg.pose.position.y,msg.pose.position.z);
        RCLCPP_INFO(this->get_logger(),"XYZ:%.2f %.2f %.2f %.2f",msg.pose.orientation.x,msg.pose.orientation.y,msg.pose.orientation.z,msg.pose.orientation.w);
    }
};



int main(int argc,char const *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Listener>());
    rclcpp::shutdown();
    return 0;
}
#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/message.hpp"
using base_interface::msg::Message;
using namespace std::chrono_literals;


class Talker : public rclcpp::Node{
public:
  Talker():Node("Talker"){
    RCLCPP_INFO(this->get_logger(),"创建发布者");
    pub_ = this->create_publisher<Message>("exam",10);
    timer_ = this->create_wall_timer(1s,std::bind(&Talker::on_timer,this));
  }


private:

  void on_timer(){
    auto exam = Message();
    exam.a = 1;
    exam.b = 2;
    pub_->publish(exam);
    RCLCPP_INFO(this->get_logger(),"发布");
  }
  rclcpp::Publisher<Message>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc,char * argv[]){
  rclcpp::init(argc,argv);
  auto talker = std::make_shared<Talker>();
  rclcpp::spin(talker);
  rclcpp::shutdown();
}
#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/example.hpp"
using base_interface::msg::Example;
using namespace std::chrono_literals;

class Talker : public rclcpp::Node{
public:
  Talker():Node("talker_node"){
    RCLCPP_INFO(this->get_logger(),"create talker");
    publisher_ = this->create_publisher<Example>("example",10);
    timer_ = this->create_wall_timer(500ms,std::bind(&Talker::on_timer,this));
  }

private:
  void on_timer(){
    auto exm = Example();
    exm.coop_rank = 1;
    exm.damage = 99;
    exm.money = 100;
    exm.name = "joker";
    publisher_->publish(exm);
    RCLCPP_INFO(this->get_logger(),"fafaffafaff");
  }
  rclcpp::Publisher<Example>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc,char * argv[]){
  rclcpp::init(argc,argv);
  auto talker = std::make_shared<Talker>();

  rclcpp::spin(talker);
  rclcpp::shutdown();
}
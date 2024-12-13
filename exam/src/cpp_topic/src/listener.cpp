#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/message.hpp"
using base_interface::msg::Message;

class Listener : public rclcpp::Node{
public:
    Listener():Node("listener"){
        RCLCPP_INFO(this->get_logger(),"监听方创建");
        sub_ = this->create_subscription<Message>("exam",10,std::bind(&Listener::do_cb,this,std::placeholders::_1));
    }


private:

    void do_cb(const Message msg){
        RCLCPP_INFO(this->get_logger(),"a=%d b=%d",msg.a,msg.b);
    }
    rclcpp::Subscription<Message>::SharedPtr sub_;

};

int main(int argc,char * argv[]){
  rclcpp::init(argc,argv);
  auto listener = std::make_shared<Listener>();
  rclcpp::spin(listener);
  rclcpp::shutdown();
}
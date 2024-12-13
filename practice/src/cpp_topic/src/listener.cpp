#include "rclcpp/rclcpp.hpp"
#include "base_interface/msg/example.hpp"
using base_interface::msg::Example;
using std::placeholders::_1;

class Listener : public rclcpp::Node{
public:
    Listener():Node("listener"){
        RCLCPP_INFO(this->get_logger(),"create");
        sub_ = this->create_subscription<Example>("example",10,std::bind(&Listener::do_cb,this,_1));
    }

private:
    void do_cb(const Example exm){
        RCLCPP_INFO(this->get_logger(),"name=%s",exm.name.c_str());
    }
    rclcpp::Subscription<Example>::SharedPtr sub_;
};


int main(int argc,char * argv[]){
    rclcpp::init(argc,argv);
    auto listener = std::make_shared<Listener>();
    rclcpp::spin(listener);
    rclcpp::shutdown();
}
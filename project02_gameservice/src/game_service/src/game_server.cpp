#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/srv/recharge.hpp"
using base_interfaces::srv::Recharge;
using std::placeholders::_1;
using std::placeholders::_2;

class GameServer : public rclcpp::Node{
public:
    GameServer():Node("Game_Server"){
        //创建Service类，绑定recharge作为回调函数
        RCLCPP_INFO(this->get_logger(),"游戏服务器创建");
        server_ = this->create_service<Recharge>("game_recharge",std::bind(&GameServer::recharge,this,_1,_2));

    }

private:
    //回调函数，处理充值请求，计算用户所得点卷和VIP等级
    void recharge(const Recharge::Request::SharedPtr req,const Recharge::Response::SharedPtr res){
        //点卷=金额*10
        res->user_points = req->user_recharge_amount * 10;
        //vip等级判断
        if(req->user_recharge_amount > 6480){
            res->user_vip_level = "supervip";
        }else if (req->user_recharge_amount > 648){
            res->user_vip_level = "vip6";
        }else if (req->user_recharge_amount > 328){
            res->user_vip_level = "vip5";
        }else if (req->user_recharge_amount > 200){
            res->user_vip_level = "vip4";
        }else if (req->user_recharge_amount > 120){
            res->user_vip_level = "vip3";
        }else if (req->user_recharge_amount > 60){
            res->user_vip_level = "vip2";
        }else if (req->user_recharge_amount > 20){
            res->user_vip_level = "vip1";
        }else if (req->user_recharge_amount > 0){
            res->user_vip_level = "vip0";
        }else{
            res->user_vip_level = "???";
        }
        //日志输出
        RCLCPP_INFO(this->get_logger(),"用户:%s 充值金额:%d 获得点卷;%d VIP等级为:%s"
                                            ,req->user_name.c_str(),req->user_recharge_amount,res->user_points,res->user_vip_level.c_str());
    }
    rclcpp::Service<Recharge>::SharedPtr server_;
};

int main(int argc,char const *argv[]){
    rclcpp::init(argc,argv);
    auto server = std::make_shared<GameServer>();
    //回旋启动服务器
    rclcpp::spin(server);
    rclcpp::shutdown();
}

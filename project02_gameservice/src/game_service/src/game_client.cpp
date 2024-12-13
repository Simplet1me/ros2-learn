#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/srv/recharge.hpp"
using base_interfaces::srv::Recharge;
using namespace std::chrono_literals;

/*
食用方法：
1.启动服务器
2.启动客户端，需要在启动命令后面加上用户名和金额的参数
3.获取对应信息，结束

Recharge.srv文件内容如下

string user_name
int32 user_recharge_amount
---
string user_vip_level
int32 user_points


关于为何在客户端本地判断VIP等级
可以看到我在Server也写了一个vip判断，同时srv文件里也有vip等级的响应
但是我在调用下方main函数里的future.get()时发现
他只能调用一次
如果出现第二次调用就会报No associated state的错误
神奇的是在测试的时候发现user_vip_level和user_points都是有数据的
初步怀疑是future中get()函数在执行后会断开和main函数中client的关联
或是自动销毁
被这个future弄没办法了，只好本地判断VIP等级了
*/


//游戏客户端类
class GameClient: public rclcpp::Node{
public:
  GameClient():Node("Game_Client"){
    RCLCPP_INFO(this->get_logger(),"游戏客户端创建");
    client_ = this->create_client<Recharge>("game_recharge");
  }
  //判断是否连接上服务器
  bool connect_server(){
    //每一秒连接一次
    while (!client_->wait_for_service(1s)){
      //按下Ctrl+C强行终止
      if (!rclcpp::ok()){
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强行终止客户端");
        return false;
      }
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务连接中...");
    }
    return true;
  }

  //发送充值请求(用户名+金额)
  rclcpp::Client<Recharge>::FutureAndRequestId send_request(std::string name,int recharge_amount){
    auto request = std::make_shared<Recharge::Request>();
    request->user_name = name;
    request->user_recharge_amount = recharge_amount;
    return client_->async_send_request(request);
  }

private:
  rclcpp::Client<Recharge>::SharedPtr client_;
};

int main(int argc,const char *argv[]){
  //判断参数是否满足来两个
  if(argc != 3){
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"请提交用户名和充值金额");
    return 1;
  }

  rclcpp::init(argc,argv);
  auto client = std::make_shared<GameClient>();
  //判断服务器是否连接成功
  bool flag = client->connect_server();
  if(!flag){
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务连接失败，程序退出");
    return 0;
  }

  //本地判断vip
  std::string vip;
  int recharge_amount = atoi(argv[2]);
  if(recharge_amount > 6480){
    vip = "supervip";
    }else if (recharge_amount > 648){
      vip = "vip6";
    }else if (recharge_amount > 328){
      vip = "vip5";
    }else if (recharge_amount > 200){
      vip = "vip4";
    }else if (recharge_amount > 120){
      vip = "vip3";
    }else if (recharge_amount > 60){
      vip = "vip2";
    }else if (recharge_amount > 20){
      vip = "vip1";
    }else if (recharge_amount > 0){
      vip = "vip0";
    }else{
      vip = "???";
  }

  //发送充值请求并获取响应
  auto future = client->send_request(argv[1],atoi(argv[2]));
  //如果请求成功就是充值成功
  if(rclcpp::spin_until_future_complete(client,future) == rclcpp::FutureReturnCode::SUCCESS){
    RCLCPP_INFO(client->get_logger(),"充值成功！用户:%s 充值金额:%s 获得点卷:%d 恭喜您成为尊贵的%s"
                                            ,argv[1],argv[2],future.get()->user_points,future.get()->user_vip_level.c_str());
                                                            //这个future.get()只能调用一次，不然也不会在客户端本地判断vip等级
  }else{
    RCLCPP_INFO(client->get_logger(),"充值失败，请检查网络连接");
  }

  rclcpp::shutdown();
  return 0;
}
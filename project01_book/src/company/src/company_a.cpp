#include "rclcpp/rclcpp.hpp"
#include "base_interfaces/msg/bookneed.hpp"
#include "base_interfaces/msg/booksupply.hpp"
using base_interfaces::msg::Bookneed;
using base_interfaces::msg::Booksupply;

/*
食用方法：
1.启动company_a company_b company_c三个可执行程序
2.在company_a的终端中输入公司名称a 书本种类 书本数量
3.收到乙(b)，丙(c)的报价并求出较小方
4.手动停止b，c的终端终止发布

公司乙书本种类及价格
booka 6
bookb 10
bookc 15

公司丙书本种类及价格
booka 8
bookb 9
bookc 10

写的很屎还请见谅🙏
*/

//发布类
class Talker : public rclcpp::Node{
public:
  Talker():Node("Talker_a"){
    RCLCPP_INFO(this->get_logger(),"甲方(a)创建");//日志输出
    publisher_ = this->create_publisher<Bookneed>("book_need",10);//话题book_need，发布需求
  }
  //发布函数
  void publish_need(const Bookneed bookneed){
    publisher_->publish(bookneed);
  }

private:
  rclcpp::Publisher<Bookneed>::SharedPtr publisher_;
};

//监听类
class Listener : public rclcpp::Node{
public:
    Listener():Node("Listener_a"){
        //创建两个监听器接收乙丙两个公司的供应，乙公司通过话题"book_supplyb"通信，丙公司通过话题"book_supplyc"
        subscriptionb_ = this->create_subscription<Booksupply>("book_supplyb",10,std::bind(&Listener::do_cbb,this,std::placeholders::_1));
        subscriptionc_ = this->create_subscription<Booksupply>("book_supplyc",10,std::bind(&Listener::do_cbc,this,std::placeholders::_1));
        
    }
    //类外传输变量
    Booksupply getBooksupplyb(){
      return booksupplyb;
    }
    Booksupply getBooksupplyc(){
      return booksupplyc;
    }

private:
    //回调函数，用于监听话题后的处理，将收到的报价传入类内储存
    void do_cbb(const Booksupply lisbooksupply){
        RCLCPP_INFO(this->get_logger(),"收到公司乙(%s) 报价%d",lisbooksupply.company_name.c_str(),lisbooksupply.book_supply_price);
        booksupplyb = lisbooksupply;
    }
    void do_cbc(const Booksupply lisbooksupply){
        RCLCPP_INFO(this->get_logger(),"收到公司丙(%s) 报价%d",lisbooksupply.company_name.c_str(),lisbooksupply.book_supply_price);
        booksupplyc = lisbooksupply;
    }

    Booksupply booksupplyb;
    Booksupply booksupplyc;
    rclcpp::Subscription<Booksupply>::SharedPtr subscriptionb_;
    rclcpp::Subscription<Booksupply>::SharedPtr subscriptionc_;
};



int main(int argc,char const *argv[]){
  rclcpp::init(argc,argv);
  //三个变量用于处理和储存数据
  Bookneed bookneed;
  Booksupply booksupplyb;
  Booksupply booksupplyc;
  auto talker = std::make_shared<Talker>();
  std::cout<<"输入甲方的需求：公司名，书本种类，书本数量"<<std::endl;
  std::cin>>bookneed.company_name>>bookneed.book_need_kind>>bookneed.book_need_amount;
  //输入并发布需求
  talker->publish_need(bookneed);
  RCLCPP_INFO(talker->get_logger(),"发布需求：公司：%s 书本种类：%s 书本数量：%d",bookneed.company_name.c_str(),bookneed.book_need_kind.c_str(),bookneed.book_need_amount);

  auto listener = std::make_shared<Listener>();
  //通过无限执行spin_some函数来手动回旋，方便随时停止，通过检测两个报价的子变量（名称）判断是否获取成功。
  //将监听到的数据送至类外处理。
  while (1){
    rclcpp::spin_some(listener);
    booksupplyb = listener->getBooksupplyb();
    booksupplyc = listener->getBooksupplyc();
    if (booksupplyb.company_name == "b" && booksupplyc.company_name == "c"){
      break;//获取到两个报价，跳出循环
    }
  }
  //比大小然后输出小的
  if(booksupplyb.book_supply_price <= booksupplyc.book_supply_price){
    std::cout<<"接受公司乙"<<booksupplyb.company_name<<"报价："<<booksupplyb.book_supply_price<<std::endl;
    }else{
    std::cout<<"接受公司丙"<<booksupplyc.company_name<<"报价："<<booksupplyc.book_supply_price<<std::endl;
  }
  std::cout<<"finish";
  return 0;
}
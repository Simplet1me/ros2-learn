#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "base_interfaces/msg/bookneed.hpp"
#include "base_interfaces/msg/booksupply.hpp"
using base_interfaces::msg::Bookneed;
using base_interfaces::msg::Booksupply;
using namespace std::chrono_literals;

//创建书本类，包括名称，价格
class Book{
public:
    Book(std::string name,int price){
        name_ = name;
        price_ = price;
    }
    std::string getName(){
        return name_;
    }
    int getPrice(){
        return price_;
    }
private:
    std::string name_;
    int price_;
};


//发布报价类
class Talker : public rclcpp::Node{
public:
  Talker():Node("Talker_b"){
    RCLCPP_INFO(this->get_logger(),"乙方(b)创建");
    //创建发布器和计时器，每0.5s发布一次报价确保甲收到
    publisher_ = this->create_publisher<Booksupply>("book_supplyb",10);
    timer_ = this->create_wall_timer(500ms,std::bind(&Talker::on_timer,this));
  }
  //发布报价函数
  void publish_supply(const Booksupply pubbooksupply){
    RCLCPP_INFO(this->get_logger(),"发送报价：公司乙(%s) 报价%d",pubbooksupply.company_name.c_str(),pubbooksupply.book_supply_price);
    publisher_->publish(pubbooksupply);
  }
  //类外传进类内
  void setBooksupply(Booksupply set){
    this->booksupply = set;
  }

private:
  //计时器回调函数
  void on_timer(){
    publish_supply(booksupply);
  }
  Booksupply booksupply;
  rclcpp::Publisher<Booksupply>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


//监听需求
class Listener : public rclcpp::Node{
public:
    Listener():Node("Listener_b"){
        //创建监听器，监听book_need甲方需求
        subscription_ = this->create_subscription<Bookneed>("book_need",10,std::bind(&Listener::do_cb,this,std::placeholders::_1));
    }
    //类外传输
    Bookneed getBookneed(){
        return bookneed;
    }
private:
    //回调函数，将接受到的消息储存在类内，通过释放节点来结束回旋
    void do_cb(const Bookneed lisbookneed){
        RCLCPP_INFO(this->get_logger(),"收到消息，正在处理");
        bookneed = lisbookneed;
        rclcpp::shutdown();
    }
    Bookneed bookneed;
    rclcpp::Subscription<Bookneed>::SharedPtr subscription_;
};



int main(int argc,char const *argv[]){
  //书本初始化
  Book booka("booka",6);
  Book bookb("bookb",10);
  Book bookc("bookc",15);
  Booksupply booksupply;
  booksupply.company_name = "b";
  rclcpp::init(argc,argv);
  auto listener = std::make_shared<Listener>();
  //回旋监听
  rclcpp::spin(listener);
  //结束回旋后将类内数据传出
  Bookneed book_need = listener->getBookneed();
  //处理需求，种类和数量计算出报价
  if (book_need.book_need_kind == booka.getName()){
    booksupply.book_supply_price = booka.getPrice() * book_need.book_need_amount;
  }else if (book_need.book_need_kind == bookb.getName()){
        booksupply.book_supply_price = bookb.getPrice() * book_need.book_need_amount;
  }else if (book_need.book_need_kind == bookc.getName()){
        booksupply.book_supply_price = bookc.getPrice() * book_need.book_need_amount;
  }
  //重新初始化并创建发布方
  rclcpp::init(argc,argv);
  auto talker = std::make_shared<Talker>();
  talker->setBooksupply(booksupply);
  //回旋发布确保甲方收到报价
  rclcpp::spin(talker);
  rclcpp::shutdown();
  return 0;
}
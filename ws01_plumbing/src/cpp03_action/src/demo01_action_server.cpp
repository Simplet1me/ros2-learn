#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"
using base_interfaces_demo::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;

class ProgressActionServer : public rclcpp::Node{
public:
  ProgressActionServer():Node("progress_action_server_node_cpp"){
    RCLCPP_INFO(this->get_logger(),"Action服务端创建");
    server_ = rclcpp_action::create_server<Progress>(
      this,
      "get_sum",
      std::bind(&ProgressActionServer::handle_goal,this,_1,_2),
      std::bind(&ProgressActionServer::handle_cancel,this,_1),
      std::bind(&ProgressActionServer::handle_accepted,this,_1)
      );
  }


private:
  rclcpp_action::Server<Progress>::SharedPtr server_;

  /*
  std::function<GoalResponse(
        const GoalUUID &, std::shared_ptr<const typename ActionT::Goal>)>;
  */
  //处理目标提交值
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const Progress::Goal> goal){
    (void)uuid;
    //判断提交的数字是否大于1
    if(goal->num <= 1){
      RCLCPP_INFO(this->get_logger(),"提交的目标值必须大于1");
      return rclcpp_action::GoalResponse::REJECT;
    }
    RCLCPP_INFO(this->get_logger(),"提交success");
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  /*
  std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>;
  */
  //处理取消请求
  rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle){
    (void)goal_handle;
    RCLCPP_INFO(this->get_logger(),"任务被取消");
    return rclcpp_action::CancelResponse::ACCEPT;

  }

  /*
  std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>;
  */
  //连续反馈和最终响应
  void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle){
    //新建线程处理耗时逻辑
    std::thread(std::bind(&ProgressActionServer::execute,this,goal_handle)).detach();
  }

  void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle){
    //生成连续反馈
    //void publish_feedback(std::shared_ptr<base_interfaces_demo::action::Progress_Feedback> feedback_msg)
    //goal_handle->publish_feedback();
    int num = goal_handle->get_goal()->num;
    int sum = 0;
    auto feedback = std::make_shared<Progress::Feedback>();
    auto result = std::make_shared<Progress::Result>();
    //休眠
    rclcpp::Rate rate(1.0);
    
    for (int i = 1; i <= num; i++){
      sum += i;
      double progress = i / (double)num;  //计算进度
      feedback->progress = progress;
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(),"连续反馈中，进度：%.2f",progress);
      //判读是否接收到了取消请求
      //goal_handle->is_canceling();
      //goal_handle->canceled();
      if(goal_handle->is_canceling()){
        result->sum = sum;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(),"任务被取消");
        return;
      }
      rate.sleep();
    }
    
    //生成最终响应
    if(rclcpp::ok()){
      result->sum = sum;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(),"最终结果%d",sum);
    }
  }
};

int main(int argc,char const *argv[]){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<ProgressActionServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}
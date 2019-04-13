#include <ros/ros.h>
#include <mini_multi_agent/feedback.h>
#include <mini_multi_agent/task1.h>
#include <mini_multi_agent/task2.h>

//ROS标准msg头文件
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <string>

using std::string;

struct RobotAgent{
  int ID;
  int task_ID;
  bool finished;
  string state;
};

class FactoryServer{
public:
  FactoryServer();
  void feedbackCallback(const mini_multi_agent::feedback::ConstPtr &msg);
  bool runRobotTask1(ros::ServiceClient& client1,int task_ID);
  bool runRobotTask2(ros::ServiceClient& client2,int task_ID);
  void taskScheduler();

  ~FactoryServer(){}

private:
  ros::NodeHandle n;
  ros::Subscriber sub;
  ros::ServiceClient client1;
  ros::ServiceClient client2;
  RobotAgent robot1;
  RobotAgent robot2;
  mini_multi_agent::task1 srv1;
  mini_multi_agent::task2 srv2;
};

FactoryServer::FactoryServer(){
  // initial service & topic & robot state
  sub = n.subscribe("/agent_feedback", 1, &FactoryServer::feedbackCallback, this);
  client1 = n.serviceClient<mini_multi_agent::task1>("/agent_task_1");
  client2 = n.serviceClient<mini_multi_agent::task2>("/agent_task_2");
  robot1 = {ID:1, task_ID:0,finished:false,state:"ready"};
  robot2 = {ID:2, task_ID:0,finished:false,state:"ready"};
}

void FactoryServer::feedbackCallback(const mini_multi_agent::feedback::ConstPtr &msg)
{ 
  // update robot state
  if(msg->robot_ID==1)
  {
    robot1.state = msg->state;
  }
  else if(msg->robot_ID==2)
  {
    robot2.state = msg->state;
  }
  else
    ROS_INFO("topic feedback error");
}

bool FactoryServer::runRobotTask1(ros::ServiceClient& client1,int task_ID){
    srv1.request.task_ID = task_ID;
    srv1.request.robot_name = "robot_1";
    if(client1.call(srv1))
    {
      ROS_INFO("Response from server: %s", srv1.response.feedback.c_str());
      robot1.state = "executing";
      ros::Duration(5).sleep();
      return true;
    }
    else{
      ROS_ERROR("Failed to call service");    
      return false;
    }
}

bool FactoryServer::runRobotTask2(ros::ServiceClient& client2,int task_ID){
    srv2.request.task_ID = task_ID;
    srv2.request.robot_name = "robot_2";
    if(client2.call(srv2))
    {
      ROS_INFO("Response from server: %s", srv2.response.feedback.c_str());
      robot2.state = "executing";
      ros::Duration(3).sleep();
      return true;
    }
    else{
      ROS_ERROR("Failed to call service");    
      return false;
    }
}

void FactoryServer::taskScheduler()
{

  if(robot1.task_ID>=5) robot1.finished = true;
  if(robot2.task_ID>=5) robot2.finished = true;

  if(robot1.finished && robot2.finished)
  {
    ROS_INFO("All task is finished.");
    ros::shutdown();
  }

  if(robot1.state=="ready" && !robot1.finished){
    robot1.task_ID++;
    runRobotTask1(client1,robot1.task_ID);
  }
  // 一次发一个request
  else if(robot2.state=="ready" && !robot2.finished){
    robot2.task_ID++;
    runRobotTask2(client2,robot2.task_ID);     
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node_mini_factory_server");

  // ros::spin()用于调用所有可触发的回调函数。
  // 将进入循环，不会返回，类似于在循环里反复调用ros::spinOnce()。
  FactoryServer server;
  ros::Rate loop_rate(100);
	while(ros::ok()){
		server.taskScheduler();
		loop_rate.sleep();
    // while反复调用ros::spinOnce() == ros::spin(); 
		ros::spinOnce();
	}
  
  return 0;
}


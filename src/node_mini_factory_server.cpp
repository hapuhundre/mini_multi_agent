#include <ros/ros.h>
#include <mini_multi_agent/feedback.h>
#include <mini_multi_agent/task.h>
//ROS标准msg头文件
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <string>

using std::string;

bool runRobotTask(ros::ServiceClient& client,int task_ID, string robot_name){
    mini_multi_agent::task srv;
    srv.request.task_ID = task_ID;
    srv.request.robot_name = robot_name;
    if(client.call(srv))
    {
      ROS_INFO("Response from server: %s", srv.response.feedback.c_str());
      return true;
    }
    else{
      ROS_ERROR("Failed to call service");    
      return false;
    }
}

void feedbackCallback(const mini_multi_agent::feedback::ConstPtr &msg)
{  
  ROS_INFO("robot_%d feedback state: %s",msg->robot_ID, msg->state.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node_mini_factory_server");
  ros::NodeHandle n;
  // topic
  ros::Subscriber sub = n.subscribe("/agent_feedback", 1, feedbackCallback);
  
  // service agent_task_1
  ros::ServiceClient client1 = n.serviceClient<mini_multi_agent::task>("/agent_task_1");
  // ros::ServiceClient client2 = n.serviceClient<mini_multi_agent::task>("/agent_task_2");  
  runRobotTask(client1, 1, "robot 1");
  // runRobotTask(client2, 2, "robot 2");

  // ros::spin()用于调用所有可触发的回调函数。
  // 将进入循环，不会返回，类似于在循环里反复调用ros::spinOnce()。
  ros::spin(); 
  return 0;
}


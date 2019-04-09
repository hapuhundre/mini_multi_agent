#include <ros/ros.h>
#include <mini_multi_agent/feedback.h>
//ROS标准msg头文件
#include <std_msgs/Float32.h>

void feedbackCallback(const mini_multi_agent::feedback::ConstPtr &msg)
{  
    ROS_INFO("robot feedback state: %s",msg->state.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node_mini_factory_server");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/agent_feedback", 1, feedbackCallback);
  //ros::spin()用于调用所有可触发的回调函数。将进入循环，不会返回，类似于在循环里反复调用ros::spinOnce()。
  ros::spin(); 
  return 0;
}


//ROS头文件
#include <ros/ros.h>
//自定义msg产生的头文件
#include <mini_multi_agent/feedback.h>
#include <mini_multi_agent/task.h>

bool handle_task(mini_multi_agent::task::Request &req, mini_multi_agent::task::Response &res)
{
  ROS_INFO("publish the task %s.", req.task_name.c_str());
  res.feedback = "Task is to give " + req.robot_name + " to handle.";
  return true;    
}

int main(int argc, char **argv)
{
  //用于解析ROS参数，第三个参数为本节点名
  ros::init(argc, argv, "node_robot_1");

  //实例化句柄，初始化node
  ros::NodeHandle nh;

  //自定义gps msg
  mini_multi_agent::feedback msg;
  msg.state = "ready";

  //创建publisher
  ros::Publisher pub = nh.advertise<mini_multi_agent::feedback>("/agent_feedback", 1);

  // //定义发布的频率 
  // ros::Rate loop_rate(1.0);
  // //循环发布msg
  // while (ros::ok())
  // {
  //   //以1Hz的频率发布msg
  //   pub.publish(msg);
  //   //根据前面定义的频率, sleep 1s
  //   loop_rate.sleep();//根据前面的定义的loop_rate,设置1s的暂停
  // }

  ros::ServiceServer service = nh.advertiseService("/agent_task_1", handle_task);
  ros::spin(); 
  return 0;
} 


//ROS头文件
#include <ros/ros.h>
#include <robot.h>

int main(int argc, char **argv)
{
  //用于解析ROS参数，第三个参数为本节点名
  ros::init(argc, argv, "node_robot_1");
  // ID  task_time_cost topic_feedback_step_time
  Robot robot_1(1, 5, 0.1);
  
  ros::spin(); 
  return 0;
} 


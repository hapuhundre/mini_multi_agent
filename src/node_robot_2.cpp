#include <ros/ros.h>
#include <robot.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node_robot_2");
  
  Robot robot_2(2, 3, 0.1);
  
  ros::spin(); 
  return 0;
} 


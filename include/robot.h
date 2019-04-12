#pragma once
#include <ros/ros.h>
//自定义msg产生的头文件
#include <mini_multi_agent/feedback.h>
#include <mini_multi_agent/task1.h>
#include <mini_multi_agent/task2.h>

#include <string>
using std::string;

class Robot{
public:
  Robot(int, float, float);
  ~Robot(){};
  bool handle_task1(mini_multi_agent::task1::Request &req,
                   mini_multi_agent::task1::Response &res);
  bool handle_task2(mini_multi_agent::task2::Request &req,
                   mini_multi_agent::task2::Response &res);
  void timer_callback(const ros::TimerEvent&);
private:
  int robot_ID;
  float task_time;
  int counter;
  float clock;
  float max_steps;
  string robot_state;
  ros::NodeHandle nh;
  ros::Timer timer;
  ros::Publisher pub;
  ros::ServiceServer srv1;
  ros::ServiceServer srv2;
};

Robot::Robot(int ID, float task_time, float clock_time){
  robot_ID = ID;
  task_time = task_time;
  clock = clock_time;
  max_steps = task_time/clock;
  robot_state = "ready";
  //
  srv1 = nh.advertiseService("/agent_task_1", &Robot::handle_task1, this);
  srv2 = nh.advertiseService("/agent_task_2", &Robot::handle_task2, this);
  timer = nh.createTimer(ros::Duration(clock), &Robot::timer_callback, this);
  pub = nh.advertise<mini_multi_agent::feedback>("/agent_feedback",1); 
}

bool Robot::handle_task1(mini_multi_agent::task1::Request &req,
                        mini_multi_agent::task1::Response &res){
  robot_state = "executing";
  res.feedback = "Robot 1 is "+ robot_state + " task " + std::to_string(req.task_ID);
  return true;
}

bool Robot::handle_task2(mini_multi_agent::task2::Request &req,
                        mini_multi_agent::task2::Response &res){
  robot_state = "executing";
  res.feedback = "Robot 2 is " + robot_state+ " task " + std::to_string(req.task_ID);
  return true;
}

void Robot::timer_callback(const ros::TimerEvent&){
  if(robot_state == "executing"){
    if(counter > max_steps){
      robot_state = "ready";
      counter = 0;
    }
    counter++;
  }
  else counter=0;
  
  // topic publisher
  mini_multi_agent::feedback msg;
  msg.robot_ID = robot_ID;
  msg.state = robot_state;
  pub.publish(msg);
}
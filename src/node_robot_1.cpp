//ROS头文件
#include <ros/ros.h>
//自定义msg产生的头文件
// #include <mini_multi_agent/feedback.h>
// #include <mini_multi_agent/task.h>
// #include <string>
// using std::string;
#include <robot.h>

/*
class Robot{
public:
  Robot(int, int, float);
  ~Robot(){};
  bool handle_task(mini_multi_agent::task::Request &req,
                   mini_multi_agent::task::Response &res);
  void timer_callback(const ros::TimerEvent&);
private:
  int robot_ID;
  int task_time;
  int counter;
  float clock;
  float max_steps;
  string robot_state;
  ros::NodeHandle nh;
  ros::Timer timer;
  ros::Publisher pub;
  ros::ServiceServer srv;
};

Robot::Robot(int ID, int task_time, float clock_time){
  robot_ID = ID;
  task_time = task_time;
  clock = clock_time;
  max_steps = task_time/clock;
  robot_state = "ready";
  //
  srv = nh.advertiseService("/agent_task_1", &Robot::handle_task, this);
  timer = nh.createTimer(ros::Duration(clock), &Robot::timer_callback, this);
  pub = nh.advertise<mini_multi_agent::feedback>("/agent_feedback",1); 
}

bool Robot::handle_task(mini_multi_agent::task::Request &req,
                        mini_multi_agent::task::Response &res){
  ROS_INFO("Robot %d begin to take task, task id: %d", robot_ID, req.task_ID);
  robot_state = "executing";
  res.feedback = "Robot" + std::to_string(robot_ID)+" is working";
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
*/

int main(int argc, char **argv)
{
  //用于解析ROS参数，第三个参数为本节点名
  ros::init(argc, argv, "node_robot_1");
  Robot robot_1(1, 5, 0.1);

  ros::spin(); 
  return 0;
} 


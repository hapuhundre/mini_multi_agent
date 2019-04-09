# mini_multi_agent
a ros package of multi agent.


1 创建一个ros包（可编译)  
`catkin_create_pkg mini_multi_agent roscpp std_msgs`

2 将第一个节点命名为`node_mini_factory_server`，并创建一个topic订阅(命名为"/agent_feedback"),用于接收agent反馈信息  
[topic in roscpp][1]

3 在第二个节点中，命名节点为`node_robot_1`，并创建一个service server  
[service in roscpp][2]

[1]: https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/chapter6/6.3.html
[2]: https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/chapter6/6.4.html

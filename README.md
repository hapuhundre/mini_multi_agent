# Mini Multi Agent System

a mini multi agent system by using roscpp

## 使用



## 运行结果

![][imgs\running_result.png]


## 描述

 1.创建可编辑的ROS包



 2.在第一个ROS节点中，将其命名为node_mini_factoryserver，创建一个ROS主题订户（主题名称“/ agent_feedback”）以接收代理反馈信息。 



 3.在第二个ROS节点中，将其命名为node_robot_1，创建一个ROS服务服务器（主题名称“/ agent_task_1”）以从mini factory_server接收任务。在node_mini_factory_服务器ROS节点中，创建ROS服务客户端（主题名称/ agent_task_1“）以发送代理任务信息。



4.在第三个ROS节点中，将其命名为node_robot_2，创建一个ROS服务服务器（名称“/ agent_task_2”）以从mini_factory_server接收任务。在node_mini_factory_server ROS节点中，创建ROS服务客户端（主题名称“/ agent_task_2”）以发送代理任务信息。



 5.使用至少2个状态实现`node_robot_1`。启动时，机器人处于“就绪状态”。从`node_mini_factory_server`接收任务后，它将转换为“执行”状态。大约5秒后，机器人从“执行”转换为“准备好”。



 6.使用至少2个状态实现`node_robot 2`。启动时，机器人处于“就绪”状态。从node_mini_factory_server接收任务后，它将转换为“”状态。大约3秒后机器人从“执行”转换到“准备好”。 



7  使用标识为id = 1,2,3,4,5的5个初始任务实现`node_mini_ factory_server`：`node_mini_factory_server`将在收到来自`“/agent_feedback”`机器人节点反馈后知道有2个机器人节点及其状态。
 如果该节点处于`“ready”`状态，则`node_mini_factory_server`应该将任务发送给该节点。请注意`
node_mini_factory_ server`应该一次只向一个发送一个任务。当机器人完成任务（状态从`“executing”`转换为`“ready”`）时，如果不是所有5个任务都完成，则`node_mini_factory_server`应该向该机器人发送另一个任务。 



 8.创建ROS消息`“/agent_feedback”`和ROS服务`“agent_task_x”`（x = 1,2）以满足上述需求。



 9.创建一个roslaunch，将启动前面提到的所有三个节点，结果应清晰地打印到屏幕上。结果应显示每个机器人状态，哪个工厂任务已完成或待处理等。

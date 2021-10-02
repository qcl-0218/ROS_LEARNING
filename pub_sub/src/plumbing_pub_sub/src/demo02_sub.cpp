#include "ros/ros.h"
#include "std_msgs/String.h"

/*
    发布方实现：
        1.包含头文件；
            ROS文本类型 --> std_msgs/String.h
        2.初始化 ROS 节点；
        3.创建节点句柄；
        4.创建订阅者者对象；
        5.处理订阅到的数据；
        6.spin()函数；
*/

void doMsg(const std_msgs::String::ConstPtr &msg)//传入的消息是std_msgs::String类型，ConstPtr是常量指针的引用
{
    setlocale(LC_ALL,"");//防止乱码
    
    //通过msgs获取并且操作订阅得到的数据
    ROS_INFO("翠花订阅到的数据：%s",msg->data.c_str());//msgs是一个指针的引用
}

int main(int argc,char *argv[])
{
    //2.初始化 ROS 节点；
    ros::init(argc,argv,"cuiHua");//节点不能重名，不然新启动的会干掉原来的节点
    //3.创建节点句柄；
    ros::NodeHandle nh;
    //4.创建订阅者者对象；
    ros::Subscriber sub = nh.subscribe("fang",10,doMsg);//doMsg--回调函数,每订阅一次就会被执行一次
    //5.处理订阅到的数据；

    ros::spin();//执行到这的时候会去回头处理doMsg回调函数（如果没有这行命令，很有可能消息是订阅不到的，结果打印不出来）

    return 0;
}
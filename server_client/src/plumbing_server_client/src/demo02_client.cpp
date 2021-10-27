#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
/*
    客户端实现：提交两个数据，并处理响应的结果
        1.包含头文件；
        2.初始化ROS节点；
        3.创建节点句柄；
        4.创建一个客户端对象；
        5.提交请求并处理响应

    实现参数的动态提交：
        1.格式：rosrun xxxx xxxx 12 34
        2.节点执行时需要获取命令中的参数，并组织进request

    问题：
        如果先启动客户端，那么会请求异常
    需求：
        如果先启动客户端，不要直接抛出异常，而是挂起，等服务器启动后，再正常请求；
    解决：
        在ROS中内置了相关函数，这些函数可以让客户端启动后挂起，等待服务器启动
        client.waitForExistence();
        ros::service::waitForService("服务的话题名");
*/

int main(int argc,char *argv[])//argc是命令行总的参数个数，argv[]为保存命令行参数的字符串指针
{
    setlocale(LC_ALL,"");
    //优化实现，获取命令中的参数
    //在启动客户端的时候，要在rosrun plumbing_server_client demo02_client num1 num2,不然会报参数不足的错误
    if(argc != 3)
    {
        ROS_INFO("提交的参数个数不对");
        return 1;
    }

    // 2.初始化ROS节点；
    ros::init(argc,argv,"daBao");
    // 3.创建节点句柄；
    ros::NodeHandle nh;
    // 4.创建一个客户端对象；
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addInts");//提交要提交数据的话题名
    
    // 5.提交请求并处理响应
    //创建被发布的数据/创建AddInts对象
    plumbing_server_client::AddInts ai;
    //5.1 组织请求
    //在请求里封装两个参数
    ai.request.num1 = atoi(argv[1]);//argv[1]是字符串类型的，需要调用atoi()函数变成整型值
    ai.request.num2 = atoi(argv[2]);
    //5.2 处理响应
    //挂起的实际是在客户端对象创建之后，发送请求之前
    //调用判断服务器状态的函数
    //调用函数1：
    //client.waitForExistence();//如果服务器没启动，就会挂起客户端，不会往下执行
    //调用函数2：
    ros::service::waitForService("addInts");

    //响应回来的结果sum也会封装到ai对象中的response，然后可以通过ai的response获取数据
    bool flag = client.call(ai);//客户端访问服务器，提交了ai对象
    if(flag)
    {
        ROS_INFO("响应成功！");
        //获取结果
        ROS_INFO("响应结果 = %d",ai.response.sum);
    }
    else
    {
        ROS_INFO("处理失败...");
    }
    return 0;  
}

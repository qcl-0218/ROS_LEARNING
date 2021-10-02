#include "ros/ros.h"
#include "std_msgs/String.h"//普通文本类型的消息
#include <sstream>//字符串流
/*
    发布方实现：
        1.包含头文件；
            ROS文本类型 --> std_msgs/String.h
        2.初始化 ROS 节点；
        3.创建节点句柄；
        4.创建发布者对象；
        5.编写发布逻辑并发布数据；
*/

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"");//防止乱码

    //2.初始化 ROS 节点；
    ros::init(argc,argv,"erGouZi");//erGouzi-节点名；fang-话题名

    //3.创建节点句柄；
    ros::NodeHandle nh;

    //4.创建发布者对象；
    //std_msgs::String--设置泛型类型，就是你发布的消息类型
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang",10);//fangzi-话题；10-缓存的队列长度，队列里面就缓存10条，超过10条的话前面的数据会被依次移除掉
    
    //5.编写发布逻辑并发布数据；
    //要求以10Hz的频率发布出去，并且文本后添加编号
    //先创建被发布的消息
    std_msgs::String msg;//std_msgs是标准消息类型
    //发布频率
    ros::Rate rate(1);
    //设置编号
    int count = 0;
    //编写循环，循环中发布数据
    ros::Duration(3).sleep();//休眠3s-发布者在master出注册需要时间，避免先打开订阅者时候收不到前几个数据
    while(ros::ok())//如果这个节点还活着，为真
    {
        count++;
        //实现字符串的拼接数字
        std::stringstream ss;//std::stringstream主要实现消息的拼接
        ss << "hello -->" << count;//向ss中插入"hello -->"和count
        //msg.data = "hello";//给消息添加数据
        msg.data = ss.str();//将msg.data设置成流里的字符串

        pub.publish(msg);
        //添加日志
        ROS_INFO("发布的数据是：%s",ss.str().c_str());//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同;通过string类对象的成员函数c_str()把string对象转换成C中的字符串样式。
        rate.sleep();//延时0.1s
        ros::spinOnce();//官方建议添加（虽然没有回调函数）每次循环都回头一次，处理循环当中的回调函数
    }

    return 0;
}

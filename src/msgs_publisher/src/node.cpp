#include <ros/ros.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "spamer");
    ros::NodeHandle nh;
    ros::Duration seconds(1);
    while (ros::ok())
    {
    ROS_INFO("Hello world!");
    ros::Duration(1.5).sleep();
    ROS_ERROR("Hello error!");
    ros::Duration(1.7).sleep();
    ROS_FATAL("Hello fatal!");
    ros::Duration(1.4).sleep();
    ROS_WARN("Hello warn!");
    ros::Duration(1.9).sleep();
    ROS_DEBUG("Hello debug!");
//    ROS_FATAL("Hello fatal!");
    seconds.sleep();
    }
}

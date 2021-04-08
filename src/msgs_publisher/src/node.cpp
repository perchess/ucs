#include <ros/ros.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node");
    ros::NodeHandle nh;
    ros::Duration seconds(0.5);
    while (ros::ok())
    {
    ROS_INFO("Hello world!");
    ROS_ERROR("Hello error!");
    ROS_WARN("Hello warn!");
    ROS_DEBUG("Hello debug!");
    ROS_FATAL("Hello fatal!");
    seconds.sleep();
    }
}

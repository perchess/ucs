#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "slam_module_node");
  ros::NodeHandle nh;

  ROS_INFO("Hello world!");
}

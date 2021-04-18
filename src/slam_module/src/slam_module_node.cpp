#include <ros/ros.h>
#include <slam_module/slam_life_support.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "slam_module_node");


  SLAMLifeSupport test;
  test.spin();

return 0;
}

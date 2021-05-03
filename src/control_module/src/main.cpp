#include <ros/ros.h>
#include <ros/package.h>


#include <control_module/control.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "control_node");
  ros::NodeHandle nh;
  ros::Duration(1.0).sleep();
  ros::Rate loop_rate(10);


  ControlModule conrtl_obj;
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}


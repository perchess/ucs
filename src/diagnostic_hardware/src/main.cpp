#include <diagnostic_hardware/diagnostic_creator.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "diagnostic_hardware_node");

  ros::NodeHandle nh;

  diagnostic_updater::Updater updater;

  updater.setHardwareID("none");


  DiagnosticCreator test_node_handler("/lidar_driver", nh, &updater, "Лидар");
  DiagnosticCreator test_node_handler2("/imu_driver", nh, &updater, "imu");
  updater.add(test_node_handler);
  updater.add(test_node_handler2);

  updater.broadcast(0, "Doing important initialization stuff.");


  while (nh.ok())
  {


    test_node_handler.processing();
    test_node_handler2.processing();


    ros::spinOnce();
    ros::Duration(0.1).sleep();
  }

  return 0;
}

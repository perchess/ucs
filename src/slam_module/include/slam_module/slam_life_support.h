#pragma once

#include <slam_module/self_diagnostic.h>


#include <std_srvs/Trigger.h>
#include <std_msgs/String.h>


struct SlamAlgorithm : public Algorithm
{
  using Algorithm::Algorithm;
  void publish_to_rosparam(bool turn)
  {
    setParam("/gui_config/features/SLAM/pkg", pkg_, true);
    setParam("/gui_config/features/SLAM/launch", launch_file_, true);
    setParam("/gui_config/features/SLAM/turn", turn, true);
  }
};



class SLAMLifeSupport : DiagnosticMain
{
public:
  SLAMLifeSupport();
  void report_status();
  void feedback_callback(const diagnostic_msgs::DiagnosticArrayConstPtr &msg);


  // Цикл, в котором будет крутиться проверка работоспособности
  // аппаратуры
  void feedback_processing();

  bool update_sensor_system();
  // Основной цикл
  void spin();
  void set_sensor_hierarchy(std::map<std::string, SlamAlgorithm>& in) {sensor_hierarchy_ = in;}

private:
  void create_hierarchy();

  ros::NodeHandle nh_;
  ros::Subscriber diagnostic_sub_;
  ros::Publisher status_pub_;
  ros::Rate loop_rate_;

  diagnostic_msgs::DiagnosticArray diagnost_msg_;
  ros::ServiceClient updt_srv_;
  std::vector<SlamAlgorithm> algorithms_;
  std::map<std::string, SlamAlgorithm> sensor_hierarchy_;


};




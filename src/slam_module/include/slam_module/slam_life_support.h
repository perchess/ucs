#pragma once

#include <slam_module/self_diagnostic.h>

#include <ros/ros.h>


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

private:
  void create_hierarchy();

  ros::NodeHandle nh_;
  ros::Subscriber diagnostic_sub_;
  ros::Publisher status_pub_;
  ros::Rate loop_rate_;

  diagnostic_msgs::DiagnosticArray diagnost_msg_;


};


//! @brief Шаблоннная функция для чтения параметров
template <typename T>
void readParam(const std::string param_name, T& param_value,
               const T default_value) {
  if (!ros::param::get(param_name, param_value)) {
    ROS_WARN_STREAM("Parameter \""
                        << param_name << "\" didn' find in Parameter Server."
                        << "\nSetting default value: " << &default_value);
    param_value = default_value;
  }
}

template <class T>
void setParam(const std::string param_name, const T& value, bool create = false)
{
  if (ros::param::has(param_name))
  {
    ros::param::set(param_name, value);
  }
  else if (create)
    ros::param::set(param_name, value);
  else
  {
    ROS_WARN_STREAM("Parameter \"" << param_name << "\" didn' find in Parameter Server.");
  }
}

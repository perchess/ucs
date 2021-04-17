#pragma once

#include <slam_module/self_diagnostic.h>

#include <ros/ros.h>


class SLAMLifeSupport : DiagnosticMain
{
  SLAMLifeSupport();
  virtual void report_status();
  virtual void feedback_callback(const diagnostic_msgs::DiagnosticArrayConstPtr &msg);
  void set_hierarchy();

  // Цикл, в котором будет крутиться проверка работоспособности
  // аппаратуры
  void feedback_processing();

  bool find_alternative();
  // Основной цикл
  void spin();

private:
  ros::NodeHandle nh_;
  ros::Subscriber diagnostic_sub_;
  ros::Publisher status_pub_;

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

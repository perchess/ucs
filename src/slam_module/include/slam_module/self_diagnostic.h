#pragma once
#include <iostream>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <ros/ros.h>

//typedef enum{
//  OK        = 0,
//  WARNING   = 1,
//  ERROR     = 2,
//  STALE     = 3,
//}Status;

struct Algorithm
{
  Algorithm(std::string name, std::string sensor_type,
            std::string pkg, std::string launch_file, int priority)
    : name_(name)
    , sensor_type_(sensor_type)
    , pkg_(pkg)
    , launch_file_(launch_file)
    , priority_(priority)  {}

  Algorithm()
    : name_()
    , sensor_type_()
    , pkg_()
    , launch_file_()
    , priority_(0)  {}

  virtual void publish_to_rosparam(){};

  std::string name_;
  std::string sensor_type_;
  std::string pkg_;
  std::string launch_file_;
  int priority_;
};

using status_type = diagnostic_msgs::DiagnosticStatus;

class DiagnosticMain
{
public:
  virtual void report_status() = 0;
  virtual void feedback_callback(const diagnostic_msgs::DiagnosticArrayConstPtr &msg) = 0;

  void set_state(status_type::_level_type state) {state_.level = state;}
  void set_msg(std::string msg) {state_.message = msg;}
  status_type get_state() {return state_;}
  std::string get_msg() {return state_.message;}
//  virtual std::map<std::string, Algorithm> get_sensor_hierarchy() {return sensor_hierarchy_;}
//  virtual void set_sensor_hierarchy(std::map<std::string, Algorithm>& in) {sensor_hierarchy_ = in;}


protected:
  status_type state_;
  /*
 * Таблица типов сенсоров с соответствующими приоритетами
 * */
//  std::map<std::string, Algorithm> sensor_hierarchy_;
  /*
 * Таблица типов сенсоров с
 * */
  //std::map<std::string, bool> sensor_info_;
  //std::string msg_;
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

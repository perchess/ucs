#pragma once
#include <iostream>
#include <diagnostic_msgs/DiagnosticArray.h>

//typedef enum{
//  OK        = 0,
//  WARNING   = 1,
//  ERROR     = 2,
//  STALE     = 3,
//}Status;

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
  std::map<std::string, int> get_sensor_hierarchy() {return sensor_hierarchy_;}
  void set_sensor_hierarchy(std::map<std::string, int>& in) {sensor_hierarchy_ = in;}


protected:
status_type state_;
/*
 * Таблица типов сенсоров с соответствующими приоритетами
 * */
std::map<std::string, int> sensor_hierarchy_;
/*
 * Таблица типов сенсоров с
 * */
//std::map<std::string, bool> sensor_info_;
//std::string msg_;
};

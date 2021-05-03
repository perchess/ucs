#pragma once
#include <ros/ros.h>
#include <ros/package.h>

#include <QProcess>
#include <std_srvs/Trigger.h>


struct Module
{

  Module(bool state, std::string pkg, std::string node)
    : state_(state)
    , package_(pkg)
    , node_(node) {}

  Module()
    : state_(0)
    , package_()
    , node_()
    , console_(new QProcess()) {}

  bool state_;
  std::string package_;
  std::string node_;
  std::string name_;
  QProcess * console_;
};


class ControlModule
{
public:
  explicit ControlModule();
  ~ControlModule();

  void update();
  void updateParams();
  void start();
  void fillStruct(Module& struc, std::string prefix);
  bool callbackUpdate(std_srvs::Trigger::Request& request,
                      std_srvs::Trigger::Response& response);

private:
  std::vector<Module> modules_;
  std::vector<std::string> names_;
  ros::ServiceServer srv_update_;
  ros::NodeHandle nh_;
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

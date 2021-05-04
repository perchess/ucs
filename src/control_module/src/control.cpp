#include "control_module/control.h"

template<>
void readParam(const std::string param_name, QString& param_value,
               const QString default_value)
{
  std::string tmp_str = param_value.toStdString();
  if (!ros::param::get(param_name, tmp_str))
  {
    ROS_WARN_STREAM("Parameter \""
                        << param_name << "\" didn' find in Parameter Server."
                        << "\nSetting default value: " << &default_value);
    param_value = default_value;
  }
  param_value = QString::fromStdString(tmp_str);
}

ControlModule::ControlModule()
  : nh_()
  , simulator_(false)
{
  srv_update_ = nh_.advertiseService("updateParams", &ControlModule::callbackUpdate, this);
  readParam("/gui_config/sensor_types", names_, names_);
  // init
  modules_.resize(names_.size());
  for (size_t i = 0; i < modules_.size(); i++)
    modules_.at(i).name_ = QString::fromStdString(names_.at(i));

  updateParams();

  start();
}


bool ControlModule::callbackUpdate(std_srvs::Trigger::Request& request,
                    std_srvs::Trigger::Response& response)
{
  update();
  response.success = true;
  response.message = " Update modules states. ";
  return true;
}


ControlModule::~ControlModule()
{
  for (auto it: modules_)
    it.console_->terminate();
}


void ControlModule::updateParams()
{
  bool delete_success = ros::param::del("/gui_config/");
  QProcess console;
  static QString pkg_path(ros::package::getPath("gui_control_system").c_str());
  console.start("rosparam", {"load", pkg_path + "/config/qt_out.yaml"});
  console.waitForFinished();
  for (auto& it : modules_)
  {
    fillStruct(it, "/gui_config/" + it.name_);
  }
  readParam("/gui_config/simulation", simulator_, false);
}


void ControlModule::fillStruct(Sensor& struc, QString prefix)
{
  readParam(prefix.toStdString() + "/turn", struc.state_, false);
  readParam(prefix.toStdString() + "/pkg", struc.package_, QString());
  readParam(prefix.toStdString() + "/node", struc.node_, QString());
}


void ControlModule::start()
{
  for (auto it : modules_)
  {
    if (it.state_)
    {
      QStringList args = simulator_ ? QStringList{
                                     "sensor_node", "start_node.launch",
                                     "node_name:=" + it.node_ + "_autoname",
                                     "subscribe_topic_name:=" + it.package_}
                                   : QStringList{
                                     "control_module", "node_launcher.launch",
                                     "name:=" + it.node_ + "_autoname",
                                     "pkg:=" + it.package_,
                                     "type:=" + it.node_ };
      it.console_->start("roslaunch", args);
    }
  }
}


void ControlModule::update()
{
  auto old_modules = modules_;
  updateParams();
  for (size_t i = 0; i < modules_.size(); i++)
  {
    // Если изменился статус
    if (modules_.at(i).state_ != old_modules.at(i).state_)
    {
      if (modules_.at(i).state_)
      {
        QStringList args = simulator_ ? QStringList{
                                       "sensor_node", "start_node.launch",
                                       "node_name:=" + modules_.at(i).node_ + "_autoname",
                                       "subscribe_topic_name:=" + modules_.at(i).package_}
                                     : QStringList{
                                       "control_module", "node_launcher.launch",
                                       "name:=" + modules_.at(i).node_ + "_autoname",
                                       "pkg:=" + modules_.at(i).package_,
                                       "type:=" + modules_.at(i).node_ };
        modules_.at(i).console_->start("roslaunch", args);
      }

      else
      {
        modules_.at(i).console_->terminate();
        modules_.at(i).console_->waitForFinished();
      }
    }
  }
}

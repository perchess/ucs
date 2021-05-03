#include "control_module/control.h"



ControlModule::ControlModule()
  : nh_()
{
  srv_update_ = nh_.advertiseService("updateParams", &ControlModule::callbackUpdate, this);
  readParam("/gui_config/sensor_types", names_, names_);
  // init
  modules_.resize(names_.size());
  for (size_t i = 0; i < modules_.size(); i++)
    modules_.at(i).name_ = names_.at(i);

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
  ros::param::del("/gui_config/");
  QProcess console;
  static QString pkg_path(ros::package::getPath("gui_control_system").c_str());
  console.start("rosparam load " + pkg_path + "/config/qt_out.yaml");
  console.waitForFinished();
  for (auto& it : modules_)
  {
    fillStruct(it, "/gui_config/" + it.name_);
  }
}


void ControlModule::fillStruct(Module& struc, std::string prefix)
{
  readParam(prefix + "/turn", struc.state_, false);
  readParam(prefix + "/pkg", struc.package_, std::string("none"));
  readParam(prefix + "/node", struc.node_, std::string("none"));
}


void ControlModule::start()
{
  for (auto it : modules_)
  {
    std::string cmd("roslaunch control_module node_launcher.launch name:=" +
                     it.node_ + "_name" + " pkg:=" + it.package_ + " type:=" + it.node_);
    if (it.state_)
      it.console_->start(QString::fromStdString(cmd));
  }
}


void ControlModule::update()
{
  auto old_modules = modules_;
  updateParams();
  for (size_t i = 0; i < modules_.size(); i++)
  {
    std::string cmd("roslaunch control_module node_launcher.launch name:=" +
                     modules_.at(i).node_ + "_name" + " pkg:=" + modules_.at(i).package_ +
                    " type:=" + modules_.at(i).node_);

    // Если изменился статус
    if (modules_.at(i).state_ != old_modules.at(i).state_)
    {
      if (modules_.at(i).state_)
        modules_.at(i).console_->start(QString::fromStdString(cmd));
      else
        modules_.at(i).console_->terminate();
    }
  }
}

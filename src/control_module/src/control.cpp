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
  : nh_("~")
  , simulator_(false)
{
  srv_update_ = nh_.advertiseService("update_params", &ControlModule::callbackUpdate, this);
  readParam("/gui_config/sensor_types", sensor_list_, sensor_list_);
  readParam("/gui_config/features_list", features_List_, features_List_);
  // init
  modules_.resize(sensor_list_.size());
  for (size_t i = 0; i < modules_.size(); i++)
    modules_.at(i).name_ = QString::fromStdString(sensor_list_.at(i));

  features_.resize(features_List_.size());
  for (size_t i = 0; i < features_.size(); i++)
    features_.at(i).name_ = QString::fromStdString(features_List_.at(i));

  update();
//  updateParams();

//  start();
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
//  bool delete_success = ros::param::del("/gui_config/");
//  QProcess console;
//  static QString pkg_path(ros::package::getPath("gui_control_system").c_str());
//  console.start("rosparam", {"load", pkg_path + "/config/qt_out.yaml"});
//  console.waitForFinished();
  for (auto& it : modules_)
  {
    fillStruct(it, "/gui_config/" + it.name_);
  }
  for (auto& it : features_)
  {
    fillStruct(it, "/gui_config/features", it.name_);
  }

  readParam("/gui_config/simulation", simulator_, false);
}


void ControlModule::fillStruct(Sensor& struc, QString prefix)
{
  readParam(prefix.toStdString() + "/turn", struc.state_, false);
  readParam(prefix.toStdString() + "/pkg", struc.package_, QString());
  readParam(prefix.toStdString() + "/node", struc.node_, QString());
}

void ControlModule::fillStruct(Feature& struc, QString prefix, QString feature_name)
{
  XmlRpc::XmlRpcValue rosparam;
  readParam(prefix.toStdString(), rosparam, rosparam);

  if (!rosparam.valid())
  {
    ROS_WARN("Rosparam [%s] doesn,t valid", prefix.toStdString().c_str());
    return;
  }

  if(rosparam.getType() == XmlRpc::XmlRpcValue::Type::TypeStruct &&
     rosparam.hasMember(feature_name.toStdString()))
  {
      if(rosparam[feature_name.toStdString()].getType() == XmlRpc::XmlRpcValue::Type::TypeStruct)
      {
        struc.turn_ = bool(rosparam[feature_name.toStdString()]["turn"]);
        struc.package_ = QString::fromStdString(std::string(rosparam[feature_name.toStdString()]["pkg"]));
        struc.launch_file_ = QString::fromStdString(std::string(rosparam[feature_name.toStdString()]["launch"]));
      }
  }
}


void ControlModule::start()
{
  for (auto it : modules_)
  {
    if (it.state_)
    {
      QStringList args = simulator_ ? QStringList{
                                     "sensor_node", "start_node.launch",
                                     "node_name:=" + it.node_,
                                     "subscribe_topic_name:=" + it.package_}
                                   : QStringList{
                                     "control_module", "node_launcher.launch",
                                     "name:=" + it.node_,
                                     "pkg:=" + it.package_,
                                     "type:=" + it.node_ };
      it.console_->start("roslaunch", args);
    }
  }
}


void ControlModule::update()
{
  auto old_modules = modules_;
  auto old_features = features_;
  updateParams();
  for (size_t i = 0; i < modules_.size(); i++)
  {
    // Если изменился статус
    if (modules_.at(i).state_ != old_modules.at(i).state_)
    {
      launch_item(modules_.at(i));
    }

  }
  for (size_t i = 0; i < features_.size(); i++)
  {
    // Если изменился статус
    if (features_.at(i).turn_ != old_features.at(i).turn_)
    {
      launch_item(features_.at(i));
    }

  }

}

void ControlModule::launch_item(const Sensor& item)
{
  if (item.state_)
  {
    QStringList args = simulator_ ? QStringList{
                                   "sensor_node", "start_node.launch",
                                   "node_name:=" + item.node_,
                                   "subscribe_topic_name:=" + item.package_}
                                 : QStringList{
                                   "control_module", "node_launcher.launch",
                                   "name:=" + item.node_,
                                   "pkg:=" + item.package_,
                                   "type:=" + item.node_ };
    item.console_->start("roslaunch", args);
  }
  else
  {
    item.console_->terminate();
    item.console_->waitForFinished();
  }
}


void ControlModule::launch_item(const Feature& item)
{
  if (item.turn_)
  {
    QStringList args = simulator_ ? QStringList{
                                    item.package_,
                                    item.launch_file_}
                                 : QStringList{
                                    item.package_,
                                    item.launch_file_};
    item.console_->start("roslaunch", args);
  }
  else
  {
    item.console_->terminate();
    item.console_->waitForFinished();
  }
}

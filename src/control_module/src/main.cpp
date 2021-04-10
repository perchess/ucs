#include <ros/ros.h>
#include <ros/package.h>
#include <QProcess>
#include <std_srvs/Trigger.h>

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
  explicit ControlModule(std::vector<std::string>);
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


int main(int argc, char **argv)
{
  ros::init(argc, argv, "control_node");
  ros::NodeHandle nh("~");
  ros::Rate loop_rate(100);

//  ControlModule conrtl_obj({"imu", "lidar", "radar", "rgb", "rgbd"});
  ControlModule conrtl_obj({"test"});
  while(ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  };
  return 0;
}



ControlModule::ControlModule(std::vector<std::string> names)
  : names_(names)
  , nh_()
{
  srv_update_ = nh_.advertiseService("updateParams", &ControlModule::callbackUpdate, this);
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
  readParam(prefix + "_turn", struc.state_, false);
  readParam(prefix + "_pkg", struc.package_, std::string("none"));
  readParam(prefix + "_node", struc.node_, std::string("none"));
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

#pragma once

#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <rosgraph_msgs/Log.h>

class DiagnosticCreator : public diagnostic_updater::DiagnosticTask
{
public:
  DiagnosticCreator(std::string node_name, ros::NodeHandle& nh, diagnostic_updater::Updater * updater,
                    std::string sensor_type);


  void run(diagnostic_updater::DiagnosticStatusWrapper &stat);
  void callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg);
  void processing();
  void spin();
private:
  ros::NodeHandle& nh_;
  ros::Subscriber rosoutSub_;
  ros::Publisher diagnostic_pub_;
  std::string node_name_;
  rosgraph_msgs::Log rosout_msg_;
  diagnostic_updater::DiagnosticStatusWrapper stat_;
  std::vector<rosgraph_msgs::Log::ConstPtr> rosout_buffer_;
  size_t buffer_size_;
  diagnostic_updater::Updater * updater_;
  std::string sensor_type_;
};


diagnostic_msgs::DiagnosticStatus::_level_type convert_to_diagnostic_status(rosgraph_msgs::Log::_level_type);

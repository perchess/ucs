#include <diagnostic_hardware/diagnostic_creator.h>

DiagnosticCreator::DiagnosticCreator(std::string node_name, ros::NodeHandle& nh,
                                     diagnostic_updater::Updater * updater, std::string sensor_type)
  : DiagnosticTask("Check all sensor nodes")
  , nh_(nh)
  , rosoutSub_(nh_.subscribe("rosout", 100, &DiagnosticCreator::callbackRosout, this) )
  , node_name_(node_name)
  , stat_()
  , buffer_size_(50)
  , updater_(updater)
  , sensor_type_(sensor_type)
{
  ROS_INFO("Looking for [%s] node ", node_name.c_str());
}


void DiagnosticCreator::run(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  stat = stat_;
  stat.name = "From " + node_name_;
}

void DiagnosticCreator::callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg)
{
//  static std::vector<rosgraph_msgs::Log::ConstPtr> buffer;
  rosout_buffer_.reserve( buffer_size_ );
//  static ros::Time prev_time = ros::Time::now();

//  ros::Time curr_time = ros::Time::now();

//  const ros::Duration delay( 1.1 );

  if(rosout_buffer_.size() < buffer_size_)
  {
    rosout_buffer_.push_back( msg );
  }
  else
  {
//    prev_time = curr_time;
    rosout_buffer_.clear();
  }
}

diagnostic_msgs::DiagnosticStatus::_level_type convert_to_diagnostic_status(rosgraph_msgs::Log::_level_type level)
{
  switch (level) {
  case rosgraph_msgs::Log::DEBUG:
    return diagnostic_msgs::DiagnosticStatus::OK;
    break;
  case rosgraph_msgs::Log::ERROR:
    return diagnostic_msgs::DiagnosticStatus::ERROR;
    break;
  case rosgraph_msgs::Log::FATAL:
    return diagnostic_msgs::DiagnosticStatus::ERROR;
    break;
  case rosgraph_msgs::Log::INFO:
    return diagnostic_msgs::DiagnosticStatus::OK;
    break;
  case rosgraph_msgs::Log::WARN:
    return diagnostic_msgs::DiagnosticStatus::WARN;
    break;
  default:
    return diagnostic_msgs::DiagnosticStatus::STALE;
    break;
  }
}


void DiagnosticCreator::processing()
{
  diagnostic_updater::DiagnosticStatusWrapper status;
  for (auto msg : rosout_buffer_)
  {
    if (msg->name == node_name_)
    {
      status.summaryf(convert_to_diagnostic_status(msg->level),
                     "Get from %s ", msg->name.c_str());
      status.add("Msg", msg->msg);
      status.add("File", msg->file);
      status.add("Function", msg->function);
      status.add("Line", msg->line);
      // Тип сенсора дб ПОСЛЕДНИМ аргументом!!!!!
      status.add("Sensor type", sensor_type_);
      stat_ = status;
      updater_->update();
    }
  }
  rosout_buffer_.clear();
}

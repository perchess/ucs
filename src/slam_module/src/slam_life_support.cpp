#include <slam_module/slam_life_support.h>

SLAMLifeSupport::SLAMLifeSupport()
  : nh_("slam_failsafe")
  , diagnostic_sub_(nh_.subscribe("/diagnostics", 100,
                                  &SLAMLifeSupport::feedback_callback, this) )
  , status_pub_(nh_.advertise<diagnostic_msgs::DiagnosticArray>("slam_status", 100))
  , loop_rate_(100)
  , updt_srv_(nh_.serviceClient<std_srvs::Trigger>("/control_node/update_params"))
{
  set_state(diagnostic_msgs::DiagnosticStatus::OK);
  create_hierarchy();
  set_msg("Инициализация пройдена");
}


void SLAMLifeSupport::feedback_callback(const diagnostic_msgs::DiagnosticArrayConstPtr &msg)
{
  diagnost_msg_ = *msg;
}


void SLAMLifeSupport::report_status()
{
  status_pub_.publish(get_state());
}


// Метод для хардкода приоритетов
void SLAMLifeSupport::create_hierarchy()
{
  std::map<std::string, int> out;

  out["lidar"] = 3;
  out["rgbd"] = 2;
  out["radar"] = 0;
  out["rgb"] = 0;
  out["imu"] = 0;

  set_sensor_hierarchy(out);
}

void SLAMLifeSupport::feedback_processing()
{
  // Первым делом - отловить ошибку
  for (auto& it: diagnost_msg_.status)
  {
    switch (it.level)
    {
    case diagnostic_msgs::DiagnosticStatus::ERROR:
      state_.message = "Catch ERROR from " + it.name + " MSG : " + it.message;
      ROS_WARN(state_.message.c_str());
      state_.level = diagnostic_msgs::DiagnosticStatus::WARN;
      // ОБЕСПЕЧИТЬ СОВПАДЕНИЕ it.name и имени в map!!!!!
      // Сделал это путем добавления значения в сообщение диагностики diagnostic_msg_
      sensor_hierarchy_[it.values.back().value] = -1; // Помечаем, что выпала ошибка
      setParam("/gui_config/" + it.values.back().value + "/turn", false);
      update_sensor_system();
      // Стираю информацию из сообщения,
      // чтобы не триггериться несколько раз на ошибку
      it = diagnostic_msgs::DiagnosticStatus();
      break;

    case diagnostic_msgs::DiagnosticStatus::WARN:
      state_.message = "Catch WARN from " + it.name + " MSG : " + it.message;
      state_.level = diagnostic_msgs::DiagnosticStatus::WARN;
      break;

    case diagnostic_msgs::DiagnosticStatus::STALE:
      state_.message = "Catch STALE from " + it.name + " MSG : " + it.message;
      state_.level = diagnostic_msgs::DiagnosticStatus::STALE;
      break;

    case diagnostic_msgs::DiagnosticStatus::OK:
      state_.message = "It's OK";
      state_.level = diagnostic_msgs::DiagnosticStatus::OK;
      break;

    default:
      state_.message = "Default message";
      break;
    }
  }
}


bool SLAMLifeSupport::update_sensor_system()
{
  using pair_type = decltype(sensor_hierarchy_)::value_type;
  auto candidate = std::max_element (
        sensor_hierarchy_.begin(), sensor_hierarchy_.end(),
        [] (const pair_type & p1, const pair_type & p2)
  {return p1.second < p2.second;}
  );

  // Если сенсор найден и он валидный. Изменяем конфиг и даем команду запуска
  if (candidate != sensor_hierarchy_.end() && candidate->second > 0)
  {
    std::string ros_param("/gui_config/" + candidate->first + "/turn");
    ROS_INFO("Turning on this component : [%s]", candidate->first);
    setParam(ros_param, true, true);
    setParam("/gui_config/" + candidate->first + "/launch", true, true);
    std_srvs::Trigger srv;
    updt_srv_.call(srv);
  }
  return false;
}

void SLAMLifeSupport::spin()
{
  while(nh_.ok())
  {
    feedback_processing();
    loop_rate_.sleep();
    ros::spinOnce();
  }
}


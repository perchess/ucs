#include <slam_module/slam_life_support.h>

SLAMLifeSupport::SLAMLifeSupport()
  : nh_()
  , diagnostic_sub_(nh_.subscribe("slam_diagn_topic", 100,
                                  &SLAMLifeSupport::feedback_callback, this) )
  , status_pub_(nh_.advertise<diagnostic_msgs::DiagnosticArray>("slam_status", 100))
{
  set_state(diagnostic_msgs::DiagnosticStatus::OK);
  set_hierarchy();
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
void SLAMLifeSupport::set_hierarchy()
{
  std::map<std::string, int> out;

  out["Лидар"] = 3;
  out["RGBD камера"] = 2;
  out["Радар"] = 0;
  out["RGB камера"] = 0;
  out["IMU"] = 0;

  set_sensor_hierarchy(out);
}

void SLAMLifeSupport::feedback_processing()
{
  // Первым делом - отловить ошибку
  for (auto it: diagnost_msg_.status)
  {
    switch (it.level)
    {
    case diagnostic_msgs::DiagnosticStatus::ERROR:
      state_.message = "Catch ERROR from " + it.name + " MSG : " + it.message;
      state_.level = diagnostic_msgs::DiagnosticStatus::ERROR;
      // ОБЕСПЕЧИТЬ СОВПАДЕНИЕ it.name и имени в map!!!!!
      sensor_hierarchy_[it.name] = -1; // Помечаем, что выпала ошибка

    case diagnostic_msgs::DiagnosticStatus::WARN:
      state_.message = "Catch WARN from " + it.name + " MSG : " + it.message;
      state_.level = diagnostic_msgs::DiagnosticStatus::WARN;

    case diagnostic_msgs::DiagnosticStatus::STALE:
      state_.message = "Catch STALE from " + it.name + " MSG : " + it.message;
      state_.level = diagnostic_msgs::DiagnosticStatus::STALE;
    }
  }
}


bool SLAMLifeSupport::find_alternative()
{
  using pair_type = decltype(sensor_hierarchy_)::value_type;
  auto pr = std::max_element (
        sensor_hierarchy_.begin(), sensor_hierarchy_.end(),
        [] (const pair_type & p1, const pair_type & p2)
  {return p1.second < p2.second;}  );
  // ДОПИСАТЬ!!!
  if (pr)
    return true;
  else
    return false;
}


#include <diagnostic_hardware/diagnostic_creator.h>
#include <xmlrpcpp/XmlRpcValue.h>

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

void get_sensor_data_from_rosparam(std::map<std::string, std::string>& sensor_info)
{
  std::vector<std::string> sen_types;
  readParam("/gui_config/sensor_types", sen_types, sen_types);
  for (auto it: sen_types)
  {
    XmlRpc::XmlRpcValue v;
    readParam("/gui_config/" + it + "/", v, v);
    if (!v.valid())
      continue;
    if(v.getType() == XmlRpc::XmlRpcValue::Type::TypeStruct && v.hasMember("turn"))
    {
       if (bool(v["turn"]) == true)
           sensor_info[it] = std::string(v["node"]);
    }
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "diagnostic_hardware_node");

  ros::NodeHandle nh;

  ros::Duration(1).sleep();

  diagnostic_updater::Updater updater;

  updater.setHardwareID("none");

  std::map<std::string, std::string> sensor_info;
  get_sensor_data_from_rosparam(sensor_info);

  std::vector<DiagnosticCreator*> diagnostic_objects;

  for (auto it: sensor_info)
  {
    diagnostic_objects.push_back(new DiagnosticCreator("/" + it.second, nh, &updater, it.first));
    updater.add(*diagnostic_objects.back());
  }



//  DiagnosticCreator test_node_handler("/lidar_driver", nh, &updater, "Лидар");
//  DiagnosticCreator test_node_handler2("/imu_driver", nh, &updater, "imu");
//  updater.add(test_node_handler);
//  updater.add(test_node_handler2);

  updater.broadcast(0, "Doing important initialization stuff.");


  while (ros::ok())
  {
  for (auto it: diagnostic_objects)
    it->processing();

//    test_node_handler.processing();
//    test_node_handler2.processing();


    ros::spinOnce();
    ros::Duration(0.1).sleep();
  }

  return 0;
}

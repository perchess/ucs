#include <wrappers/qml_wrapper.h>



CppWrapper::CppWrapper(QQmlApplicationEngine * qmlEng, QObject *parent)
  : QObject(parent)
  , packagePath_(ros::package::getPath("gui_control_system"))
  , qmlEnginePtr_(qmlEng)
  , translator_()
  , locale_(QLocale("ru_RU"))
  , terminals_()
{

  qDebug() << "Is translate valid : " << translator_.load(locale_, "main", "_", ":/");
  QCoreApplication::installTranslator(&translator_);
}

CppWrapper::~CppWrapper()
{
  configFile_.close();
  if(ros::isStarted())
  {
    ros::shutdown();
    ros::waitForShutdown();
  }
  for (auto it : terminals_)
  {
    it->terminate();
    it->waitForFinished();
  }
}


void CppWrapper::setProperty(QString parametr, QString name)
{
  yamlNode_[name] = parametr;
  applyChanges();
}

void CppWrapper::setProperty(bool parametr, QString name)
{
  yamlNode_[name] = parametr;
  applyChanges();
}
void CppWrapper::setProperty(QString name, QMap<QString, QVariant> parametr)
{
  string_map_type sensor_map;
  sensor_map = toStringMap(parametr.toStdMap());
  yamlNode_[name] = sensor_map;
  applyChanges();
}


//template<class T>
//void setProperty(T parametr, QString name)
//{
//    yamlNode_[name] = parametr;
//    applyChanges();
//}


string_map_type CppWrapper::toStringMap(const std::map<QString, QVariant>& in)
{
  string_map_type out;
  for (auto& it: in)
  {
    out[it.first.toStdString()] = it.second.toString().toStdString();
  }
  return out;
}


void CppWrapper::setSensorType(QString name)
{
  sensor_node_names_.push_back(name.toStdString());
  yamlNode_["sensor_types"] = sensor_node_names_;
  applyChanges();
}





// Запись конфига в файл
void CppWrapper::applyChanges()
{
  if (configFile_.is_open())
    configFile_.close();

  configFile_.open(packagePath_ + CONFIG_PATH);
  static YAML::Node parentNode;
  parentNode["gui_config"] = yamlNode_;
  configFile_ << parentNode << std::endl;
  configFile_.close();

}

void CppWrapper::systemCmd(QString command)
{
  system((command + " &").toStdString().c_str());
}


void CppWrapper::callSystem(QString program, QStringList args)
{
  QProcess* console = new QProcess(this);
  console->start(program, args);
  console->waitForStarted();
  terminals_.push_back(console);
}


void CppWrapper::setLocale(QLocale locale)
{
  this->locale_ = locale;
}

void CppWrapper::setLanguage(QString localeStr)
{
  setLocale(QLocale(localeStr));
  translator_.load(locale_, "tr_file", "_", ":/");
  qmlEnginePtr_->retranslate();
}


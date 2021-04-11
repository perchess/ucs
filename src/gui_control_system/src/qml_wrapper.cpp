#include <qml_wrapper.h>



CppWrapper::CppWrapper(QQmlApplicationEngine * qmlEng, QObject *parent)
  : QObject(parent)
  , packagePath_(ros::package::getPath("gui_control_system"))
  , qmlEnginePtr_(qmlEng)
  , translator_()
  , locale_(QLocale("ru_RU"))
  , terminals_(){

  qDebug() << "Is translate valid : " << translator_.load(locale_, "main", "_", ":/");
  QCoreApplication::installTranslator(&translator_);
}

CppWrapper::~CppWrapper(){
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


void CppWrapper::setProperty(QString parametr, QString name){
  yamlNode_[name] = parametr;
  applyChanges();
}



void CppWrapper::setProperty(bool parametr, QString name){
  yamlNode_[name] = parametr;
  applyChanges();
}

// Запись конфига в файл
void CppWrapper::applyChanges(){
  if (configFile_.is_open())
    configFile_.close();
  configFile_.open(packagePath_ + CONFIG_PATH);
  static YAML::Node parentNode;
  parentNode["gui_config"] = yamlNode_;
  configFile_ << parentNode;
  configFile_.close();

}

void CppWrapper::systemCmd(QString command){
  system((command + " &").toStdString().c_str());
}


void CppWrapper::callSystem(QString program, QStringList args){
  QProcess* console = new QProcess(this);
  console->start(program, args);
  console->waitForStarted();
  terminals_.push_back(console);
}


void CppWrapper::setLocale(QLocale locale){
  this->locale_ = locale;
}

void CppWrapper::setLanguage(QString localeStr){
  setLocale(QLocale(localeStr));
  translator_.load(locale_, "tr_file", "_", ":/");
  qmlEnginePtr_->retranslate();
}


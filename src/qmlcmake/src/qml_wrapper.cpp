#include <qml_wrapper.h>
#include <fstream>

RosWrapper::RosWrapper(ros::NodeHandle * nh, ros::Publisher * pub, QObject *parent)
    : QObject(parent)
    , msg_(std::string())
    , nh_(nh)
    , pub_(pub)
    , topicStringList_()
{}


void RosWrapper::setMsg(std::string str){
    if (str != msg_) {
    msg_=str;
    std_msgs::String ros_msg;
    ros_msg.data = msg_;
    pub_->publish(ros_msg);

    emit valueChanged(QString(msg_.c_str()));
    }
}

void RosWrapper::setConstMsg(){

    msg_=std::string("Button clicked const msg");
    std_msgs::String ros_msg;
    ros_msg.data = msg_;
    pub_->publish(ros_msg);

    emit valueChanged(QString::fromStdString(msg_));

}

void RosWrapper::createRosTopicList(){
    ros::master::V_TopicInfo topics;
    ros::master::getTopics(topics);
    topicStringList_.clear();
    for (auto it : topics){
        topicStringList_.append(QString::fromStdString(it.name));
    }
    for (auto it : appendedStrings_){
        topicStringList_.append(it);
    }
    emit modelChanged(topicStringList_);

}

void RosWrapper::appendList( QString str){
    appendedStrings_.insert(str);
    createRosTopicList();
}


QStringList RosWrapper::getTopicList() const{
    return topicStringList_;

}




CppWrapper::CppWrapper(QQmlApplicationEngine * qmlEng, QObject *parent)
    : QObject(parent)
    , packagePath_(ros::package::getPath("qmlcmake"))
    , qmlEnginePtr_(qmlEng)
//    , qCoreAppPtr_(nullptr)
    , translator_()
    , locale_(QLocale::system()){

    qDebug() << translator_.load(locale_, "helloworld", "_", ":/");
    QCoreApplication::installTranslator(&translator_);
}

CppWrapper::~CppWrapper(){

    configFile_.close();
}


void CppWrapper::setProperty(QString parametr, QString name){
    strParams_[name.toStdString()] = parametr.toStdString();
    applyChanges();
//    configFile_ << TAB << name.toStdString() << ": " << "\""<< parametr.toStdString() << "\"" << std::endl;

}



void CppWrapper::setProperty(bool parametr, QString name){
    boolParams_[name.toStdString()] = parametr;
    applyChanges();
//    configFile_ << TAB << name.toStdString() << ": " << std::boolalpha << parametr << std::endl;

}

void CppWrapper::applyChanges(){
    // Надо очистить файл, но без первой строчки (ns)
    // затем можно записывать
    if (configFile_.is_open())
      configFile_.close();
    configFile_.open(packagePath_ + CONFIG_PATH);
    configFile_ << "qtout: " << std::endl;
    for (auto it : strParams_){
        configFile_ << TAB << it.first << ": " << "\""<< it.second << "\"" << std::endl;
    }
    for (auto it : boolParams_){
      configFile_ << TAB << it.first << ": " << std::boolalpha << it.second << std::endl;
    }
}

void CppWrapper::systemCmd(QString command){
    system((command + " &").toStdString().c_str());
}

void CppWrapper::setLocale(QLocale locale){
    this->locale_ = locale;
}

void CppWrapper::setLanguage(QString localeStr){
    setLocale(QLocale(localeStr));
    translator_.load(locale_, "helloworld", "_", ":/");
//    qCoreAppPtr_->installTranslator(&translator_);
    qmlEnginePtr_->retranslate();
}


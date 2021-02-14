#include <ros_wrapper.h>
#include <fstream>

RosWrapper::RosWrapper(ros::NodeHandle * nh, ros::Publisher * pub, QObject *parent)
    : QObject(parent)
    , msg_(std::string())
    , nh_(nh)
    , pub_(pub)
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


CppWrapper::CppWrapper(QObject *parent)
    :QObject(parent){

    //Create namespace
    configFile_.open(CURRENT_DIR CONFIG_PATH);
    configFile_ << "qtout: " << std::endl;
//    configFile_.close();
}

CppWrapper::~CppWrapper(){

    configFile_.close();
}


void CppWrapper::setProperty(QString parametr, QString name){
    if (name == "urdf_path")
      systemCmd("export UCS_URDF_PATH=" + parametr);

    strParams_[name.toStdString()] = parametr.toStdString();
    applyChanges();
//    configFile_ << TAB << name.toStdString() << ": " << "\""<< parametr.toStdString() << "\"" << std::endl;

}



void CppWrapper::setProperty(bool parametr, QString name){

    configFile_ << TAB << name.toStdString() << ": " << std::boolalpha << parametr << std::endl;

}

void CppWrapper::applyChanges(){
    // Надо очистить файл, но без первой строчки (ns)
    // затем можно записывать
    for (auto it : strParams_){
        configFile_ << TAB << it.first << ": " << "\""<< it.second << "\"" << std::endl;
    }
}

void CppWrapper::systemCmd(QString command){
    system((command + " &").toStdString().c_str());
}


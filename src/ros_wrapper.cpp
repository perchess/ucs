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
    //Create config file
//    configFile_.(CONFIG_PATH);
}

CppWrapper::~CppWrapper(){
    configFile_.close();
}


void CppWrapper::setUrdfPath(QString path){

    configFile_.open(CONFIG_PATH);
    configFile_ << path.toStdString() << std::endl;
    configFile_.close();

}


#pragma once
#include <QObject>
#include <QString>
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <iostream>
#include <fstream>

//#include "main.moc"


#pragma message ("add currrent path macros")
#define CONFIG_PATH "/home/den/QtProjects/qmlcmake/config/qt_out.yaml"
#define TAB "  "


class RosWrapper : public QObject{
    Q_OBJECT
public:
    explicit RosWrapper(ros::NodeHandle * nh, ros::Publisher * pub, QObject *parent = nullptr);


public slots:
    void setMsg(std::string str);
    void setConstMsg();


signals:
   void valueChanged(QString newValue);

private:
    std::string msg_;
    ros::NodeHandle * nh_;
    ros::Publisher * pub_;
};





class CppWrapper : public QObject{
    Q_OBJECT
public:
    explicit CppWrapper(QObject *parent = nullptr);
    ~CppWrapper();

public slots:
    void setUrdfPath(QString path);


signals:


private:
//    std::string configPath_;
    std::ofstream configFile_;

};

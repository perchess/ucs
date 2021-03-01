#pragma once
#include <QObject>
#include <QString>
#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QStringListModel>
#include <QQmlEngine>
#include <QLocale>
#include <QTranslator>
#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>

#include <iostream>
#include <fstream>
#include <any>

//#include "main.moc"



#define CURRENT_DIR "/home/den/QtProjects/qmlcmake/"
#define CONFIG_PATH "/config/qt_out.yaml"
#define TAB "  "


class RosWrapper : public QObject{
    Q_OBJECT
  //declaration in QObject derived class
    Q_PROPERTY(QStringList myModel READ getTopicList NOTIFY modelChanged)

public:
    explicit RosWrapper(ros::NodeHandle * nh, ros::Publisher * pub, QObject *parent = nullptr);
    QStringList getTopicList() const;



public slots:
    void setMsg(std::string str);
    void setConstMsg();
    void createRosTopicList();
    void appendList(QString);


signals:
   void valueChanged(QString newValue);
   void topicListSend(QList<QString> topics);
   void modelChanged(QStringList);



private:
    std::string msg_;
    ros::NodeHandle * nh_;
    ros::Publisher * pub_;
    QStringList topicStringList_;
    std::set<QString> appendedStrings_;
};





class CppWrapper : public QObject{
    Q_OBJECT
public:
    explicit CppWrapper(QQmlApplicationEngine * qmlEng, QObject *parent = nullptr);
    void applyChanges();
    ~CppWrapper();

    // Setters
    void setLocale(QLocale);

public slots:
    void setProperty(QString parametr, QString name);
    void setProperty(bool parametr, QString name);
    void systemCmd(QString command);
    void setLanguage(QString localeStr);


signals:
    void languageChanged();



private:
    std::ofstream configFile_;
    std::map<std::string, std::string> strParams_;
    std::map<std::string, bool> boolParams_;
    std::string packagePath_;
    QQmlApplicationEngine * qmlEnginePtr_;
//    QCoreApplication * qCoreAppPtr_;
    QTranslator translator_;
    QLocale locale_;

};

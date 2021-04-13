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
#include <QProcess>

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>

#include <iostream>
#include <fstream>
#include <any>


#include "yaml-cpp/yaml.h"
#include <qtyaml.h>

//#include "main.moc"



//#define CURRENT_DIR "/home/den/QtProjects/qmlcmake/"
#define CONFIG_PATH "/config/qt_out.yaml"
#define TAB "  "


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
    void callSystem(QString program, QStringList args);
    void setLanguage(QString localeStr);


signals:
    void languageChanged();



private:
    std::ofstream configFile_;
    YAML::Node yamlNode_;
    std::string packagePath_;
    QQmlApplicationEngine * qmlEnginePtr_;
    QTranslator translator_;
    QLocale locale_;
    std::vector<QProcess*> terminals_;

};

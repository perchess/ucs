#pragma once

#include <QObject>
#include <QStringListModel>

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>

#include <logs_table_model.h>


class RosWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList myModel READ getTopicList NOTIFY modelChanged)

public:
    explicit RosWrapper(QObject *parent = nullptr);
    ~RosWrapper();
    QStringList getTopicList() const;
    void callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg);




public slots:
    void setMsg(std::string str);
    void setConstMsg();
    void createRosTopicList();
    void appendList(QString);
    void spin();


signals:
   void valueChanged(QString newValue);
   void topicListSend(QList<QString> topics);
   void modelChanged(QStringList);



private:
    std::string msg_;

    ros::NodeHandle nh_;
//    ros::Publisher * pub_;
    ros::Subscriber rosoutSub_;

    QStringList topicStringList_;
    std::set<QString> appendedStrings_;
    LogsTableModel model_;
};

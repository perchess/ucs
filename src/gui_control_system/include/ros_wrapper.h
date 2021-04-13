#pragma once

#include <QObject>
#include <QStringListModel>

#include <ros/ros.h>
#include <ros/package.h>
#include <ros/datatypes.h>
#include <std_msgs/String.h>

#include <logs_table_model.h>
#include <modelfilter.h>


class RosWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList myTopicModel READ getTopicList NOTIFY myTopicModelChanged)
    Q_PROPERTY(QStringList myNodeModel READ getNodeList NOTIFY myNodeModelChanged)
    Q_PROPERTY(QString node MEMBER node_ WRITE setNode NOTIFY nodeChanged)
    Q_PROPERTY(QVariant severity WRITE setSeverity NOTIFY severityChanged)

public:
    explicit RosWrapper(QObject *parent = nullptr);
    ~RosWrapper();
    QStringList getTopicList() const;
    QStringList getNodeList() const;
    void callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg);
    ModelFilter * getTableModel();




public slots:
    void setMsg(std::string str);
    void setConstMsg();
    void createRosTopicList();
    void createRosNodeList();
    void appendList(QString);
    void spin();
    void setNode(QString node);
    void setSeverity(QVariant sev);

signals:
   void valueChanged(QString newValue);
   void topicListSend(QList<QString> topics);
   void myTopicModelChanged(QStringList);
   void myNodeModelChanged(QStringList);
   void nodeChanged(const QString &newNode);
   void severityChanged(const QVariant &newSeverity);



private:
    std::string msg_;

    ros::NodeHandle nh_;
//    ros::Publisher * pub_;
    ros::Subscriber rosoutSub_;

    QStringList topicStringList_;
    QStringList nodeStringList_;
    std::set<QString> appendedStrings_;
    LogsTableModel* model_;
    ModelFilter* sort_model_;
    QString node_;
};

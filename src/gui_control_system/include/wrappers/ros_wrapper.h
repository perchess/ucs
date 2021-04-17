#pragma once

#include <QObject>
#include <QProcess>

#include <QStringListModel>
#include <QKeySequence>

#include <ros/ros.h>
#include <ros/package.h>
#include <ros/datatypes.h>
#include <std_srvs/Trigger.h>
#include <std_msgs/String.h>

#include <rosbag_parser/logs_table_model.h>
#include <rosbag_parser/modelfilter.h>


class RosWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList myTopicModel READ getTopicList NOTIFY myTopicModelChanged)
    Q_PROPERTY(QStringList myNodeModel READ getNodeList NOTIFY myNodeModelChanged)
    Q_PROPERTY(QString node MEMBER node_ WRITE setNode NOTIFY nodeChanged)
    Q_PROPERTY(QVariant severity WRITE setSeverity NOTIFY severityChanged)
    Q_PROPERTY(QStringList pacakgeListModel READ getPacakgeListModel NOTIFY pacakgeListModelChanged)

public:
    explicit RosWrapper(QObject *parent = nullptr);
    ~RosWrapper();
    QStringList getTopicList() const;
    QStringList getNodeList() const;
    QStringList getPacakgeListModel() const;
    void callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg);
    ModelFilter * getTableModel();




public slots:
    void setMsg(std::string str);
    void setConstMsg();
    void createRosTopicList();
    void createRosNodeList();
    void createRosPackageList();
    void appendList(QString);
    void spin();
    void setNode(QString node);
    void setSeverity(QVariant sev);
    bool isNodeStarted(QString node_name);
    void callUpdateService();
    QString find(QString pkg_name);
    void startKeyTeleop();
    void sendTeleopCmd(QString key);


signals:
   void valueChanged(QString newValue);
   void topicListSend(QList<QString> topics);
   void myTopicModelChanged(QStringList);
   void myNodeModelChanged(QStringList);
   void nodeChanged(const QString &newNode);
   void severityChanged(const QVariant &newSeverity);
   void pacakgeListModelChanged(QStringList);



private:
    std::string msg_;

    ros::NodeHandle nh_;
//    ros::Publisher * pub_;
    ros::Subscriber rosoutSub_;
    ros::ServiceClient updt_srv_;

    QStringList topicStringList_;
    QStringList nodeStringList_;
    QStringList packageStringList_;
    std::set<QString> appendedStrings_;
    LogsTableModel* model_;
    ModelFilter* sort_model_;
    QString node_;
    QProcess* teleop_terminal_;
};

#include <wrappers/ros_wrapper.h>


RosWrapper::RosWrapper(QObject *parent)
  : QObject(parent)
  , msg_(std::string())
  , nh_()
  , topicStringList_()
  , rosoutSub_(nh_.subscribe("rosout", 100, &RosWrapper::callbackRosout, this) )
  , updt_srv_(nh_.serviceClient<std_srvs::Trigger>("updateParams"))
  , model_(new LogsTableModel)
  , sort_model_(new ModelFilter(this))
  , teleop_terminal_(new QProcess())
{
    sort_model_->setSourceModel(model_);
    sort_model_->setSeverityDebugEnabled(false);
    sort_model_->setSeverityWarningsEnabled( false);
    sort_model_->setSeverityErrorEnabled( true);
    sort_model_->setSeverityInfoEnabled( false );

    sort_model_->setMessageFilterEnabled( false );
    sort_model_->setNodeFilterEnabled( true);
    sort_model_->setTimeFilterEnabled( false );
}

RosWrapper::~RosWrapper()
{
  if(ros::isStarted())
  {
    ros::shutdown();
    ros::waitForShutdown();
  }
  teleop_terminal_->terminate();
  teleop_terminal_->waitForFinished();
}

ModelFilter * RosWrapper::getTableModel()
{
  return sort_model_;
}


void RosWrapper::spin()
{
  ros::spinOnce();
}

void RosWrapper::callbackRosout(const rosgraph_msgs::Log::ConstPtr &msg)
{
  static std::vector<rosgraph_msgs::Log::ConstPtr> buffer;
  buffer.reserve( 250 );
  static ros::Time prev_time = ros::Time::now();

  ros::Time curr_time = ros::Time::now();

  const ros::Duration delay( 0.1 );

  if( curr_time - prev_time < delay &&  buffer.size() < 250)
  {
    buffer.push_back( msg );
  }
  else
  {
    prev_time = curr_time;
    model_->appendRow( buffer );
    buffer.clear();
  }
}


void RosWrapper::setMsg(std::string str){
  //    if (str != msg_) {
  //    msg_=str;
  //    std_msgs::String ros_msg;
  //    ros_msg.data = msg_;
  //    pub_->publish(ros_msg);

  //    emit valueChanged(QString(msg_.c_str()));
  //    }
}

void RosWrapper::setConstMsg(){

  //    msg_=std::string("Button clicked const msg");
  //    std_msgs::String ros_msg;
  //    ros_msg.data = msg_;
  //    pub_->publish(ros_msg);

  //    emit valueChanged(QString::fromStdString(msg_));

}


QString RosWrapper::find(QString pkg_name)
{
    return QString::fromStdString(ros::package::getPath(pkg_name.toStdString()));
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
    emit myTopicModelChanged(topicStringList_);

}

void RosWrapper::createRosNodeList(){
    ros::V_string nodes;
    ros::master::getNodes(nodes);
    nodeStringList_.clear();
    for (auto it : nodes){
        nodeStringList_.append(QString::fromStdString(it));
    }
//    for (auto it : appendedStrings_){
//        topicStringList_.append(it);
//    }
    emit myNodeModelChanged(nodeStringList_);
}

void RosWrapper::createRosPackageList() {
  ros::V_string packages;
  ros::package::getAll(packages);

  packageStringList_.clear();
  for (auto it : packages){
    packageStringList_.append(QString::fromStdString(it));
  }
  for (auto it : appendedStrings_){
    packageStringList_.append(it);
  }
  emit pacakgeListModelChanged(packageStringList_);
}


void RosWrapper::appendList( QString str){
  appendedStrings_.clear();
  appendedStrings_.insert(str);
//  createRosTopicList();
}

bool RosWrapper::isNodeStarted(QString node_name)
{
  ros::V_string nodes;
  ros::master::getNodes(nodes);

  auto it = std::find(nodes.begin(), nodes.end(), node_name.toStdString());
  return it != nodes.end();
}


QStringList RosWrapper::getTopicList() const{
    return topicStringList_;
}

QStringList RosWrapper::getNodeList() const{
    return nodeStringList_;
}


void RosWrapper::setNode(QString node)
{
    node_ = node;
    sort_model_->nodeFilterUpdated(ModelFilter::FilterMode::CONTAINS_ONE, node);
    emit nodeChanged(node);
}


void RosWrapper::setSeverity(QVariant sev)
{

    sort_model_->severityFilterUpdated(sev.toInt());
    emit severityChanged(sev);
}

void RosWrapper::callUpdateService()
{
  std_srvs::Trigger srv;
  updt_srv_.call(srv);
}


QStringList RosWrapper::getPacakgeListModel() const{
  return packageStringList_;
}

void RosWrapper::startKeyTeleop()
{
  teleop_terminal_->start("roslaunch robot_teleop robot_teleop_key.launch");
  teleop_terminal_->waitForStarted();
}


void RosWrapper::sendTeleopCmd(QString key)
{
  teleop_terminal_->write(key.toStdString().c_str(), key.size());
}

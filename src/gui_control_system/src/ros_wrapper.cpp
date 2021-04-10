#include <ros_wrapper.h>


RosWrapper::RosWrapper(QObject *parent)
  : QObject(parent)
  , msg_(std::string())
  , nh_()
  , topicStringList_()
  , rosoutSub_(nh_.subscribe("rosout", 100, &RosWrapper::callbackRosout, this) )
  , model_(new LogsTableModel)
  , sort_model_(new ModelFilter(this))
{
  sort_model_->setSourceModel(model_);
  sort_model_->setSeverityDebugEnabled(true);
  sort_model_->setSeverityWarningsEnabled( true);
  sort_model_->setSeverityErrorEnabled( false);
  sort_model_->setSeverityInfoEnabled( true );

  sort_model_->setMessageFilterEnabled( true );
  sort_model_->setNodeFilterEnabled( false);
  sort_model_->setTimeFilterEnabled( false );
}

RosWrapper::~RosWrapper()
{
  if(ros::isStarted())
  {
    ros::shutdown();
    ros::waitForShutdown();
  }
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


void RosWrapper::createRosPackageList(){
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


QStringList RosWrapper::getTopicList() const{
  return topicStringList_;
}


QStringList RosWrapper::getPacakgeListModel() const{
  return packageStringList_;
}

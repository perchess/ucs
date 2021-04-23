#!/usr/bin/env python
import rospy
import rostopic
from std_msgs.msg import String

rospy.init_node('sensor_sim_node')
topic_name = rospy.get_param('~sensor_topic_name')
topicinfo = rostopic.get_topic_type(topic_name)
topicclass = rostopic.get_topic_class(topic_name)
pub = rospy.Publisher(topic_name + "_sim", topicclass[0], queue_size=10)

def callback(data):
    pub.publish(data)

def listener():
    rospy.Subscriber(topic_name, topicclass[0], callback)


if __name__ == '__main__':
    try:
        listener()
        rospy.loginfo("Redirecting from %s to %s", topic_name, topic_name + "_sim")
        rospy.spin()
    except rospy.ROSInterruptException:
        pass

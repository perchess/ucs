#!/usr/bin/env python
import rospy
import rostopic
from std_msgs.msg import String
from sensor_node.srv import emit_error, emit_errorResponse

rospy.init_node('sensor_sim_node')
topic_name = rospy.get_param('~sensor_topic_name')
topicclass = rostopic.get_topic_class(topic_name)
pub = rospy.Publisher(topic_name[:-7], topicclass[0], queue_size=10)


def handle_server(req):
    if (req.level == "ERROR"):
        rospy.logerr(req.msg)
    if (req.level == "WARN"):
        rospy.logwarn(req.msg)
    if (req.level == "OK"):
        rospy.loginfo(req.msg)
    return emit_errorResponse(True)

def callback(data):
    pub.publish(data)

def listener():
    rospy.Subscriber(topic_name, topicclass[0], callback)


if __name__ == '__main__':
    srv = rospy.Service("~emit", emit_error, handle_server)
    try:
        listener()
        rospy.loginfo("Redirecting from %s to %s", topic_name, topic_name[:-7])
        rospy.spin()
    except rospy.ROSInterruptException:
        pass

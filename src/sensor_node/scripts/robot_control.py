#!/usr/bin/env python
import rospy
import rostopic
from std_msgs.msg import String
from std_srvs.srv import SetBool, SetBoolResponse
from geometry_msgs.msg import Twist

rospy.init_node('robot_control')
topic_name = rospy.get_param('~topic_name')
topicclass = rostopic.get_topic_class(topic_name)
pub = rospy.Publisher(topic_name + "_source", topicclass[0], queue_size=10)
stop = False
vel_msg = Twist()
vel_msg.linear.x = 0
vel_msg.linear.y = 0
vel_msg.linear.z = 0
vel_msg.angular.x = 0
vel_msg.angular.y = 0
vel_msg.angular.z = 0


def handle_service(req):
    global stop
    stop = req.data
    msg = "Get stop signal. Don't moving!!" if stop else "Moving on!!"
    rospy.loginfo("Get bool service 'STOP'")
    rospy.loginfo(msg)
    return SetBoolResponse(
                                success=True,
                                message=msg)

def callback(data):
    global stop
    global vel_msg
    if (not stop):
        pub.publish(data)
    else:
        pub.publish(vel_msg)

def listener():
    rospy.Subscriber(topic_name, topicclass[0], callback)


if __name__ == '__main__':
    srv = rospy.Service("~stop", SetBool, handle_service)
    try:
        listener()
        rospy.loginfo("Redirecting from %s to %s", topic_name, topic_name + "_source")
        rospy.spin()
    except rospy.ROSInterruptException:
        pass

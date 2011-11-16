#!/usr/bin/env python
import roslib; roslib.load_manifest('MockBotVelocity2Servo')
import rospy
from std_msgs.msg import String
def callback(data):
    rospy.loginfo(rospy.get_name()+"RECV: %s",data.data)

def listener():
    rospy.init_node('velocity2servo', anonymous=True)
    rospy.Subscriber("cmd_vel", String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()


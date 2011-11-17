#!/usr/bin/env python
import roslib; roslib.load_manifest('MockBotVelocity2Servo')
import rospy

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist
from nav_msgs.msg import *


def callback(data):
    rospy.loginfo(rospy.get_name()+"READ: %s",data.data)

def velocmdlistener():
    rospy.init_node('velocmdlistener', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, callback)
    rospy.spin()

def servo():
    pub1 = rospy.Publisher('servo1', UInt16)
    pub2 = rospy.Publisher('servo2', UInt16)
    rospy.init_node('servo')
    while not rospy.is_shutdown():
        s1 = 90
        s2 = 90
        rospy.loginfo(s1)
        rospy.loginfo(s2)
        pub1.publish(UInt16(s1))
        pub2.publish(UInt16(s2))
        rospy.sleep(0.5)

if __name__ == '__main__':
    try:
        servo()
	velocmdlistener()
    except rospy.ROSInterruptException: pass



#!/usr/bin/env python
import roslib; roslib.load_manifest('MockBotVelocity2Servo')
import rospy

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist
from nav_msgs.msg import *

def cmd_vel_callback(cmd_vel):
    ROBOT_WIDTH=0.44
    left_speed_out = cmd_vel.linear.x - cmd_vel.angular.z*ROBOT_WIDTH/2
    right_speed_out = cmd_vel.linear.x + cmd_vel.angular.z*ROBOT_WIDTH/2
    v = cmd_vel.linear.x        # m/s
    omega = cmd_vel.angular.z      # rad/s
    rospy.loginfo("Handling twist command: " + str(v) + "," + str(omega))

def velocmdlistener():
    rospy.Subscriber("cmd_vel", Twist, cmd_vel_callback)

def servo():
    servo1 = rospy.Publisher('servo1', UInt16)
    servo2 = rospy.Publisher('servo2', UInt16)
    while not rospy.is_shutdown():
        s1 = 90
        s2 = 90
        rospy.loginfo("S1:"+ str(s1) + " S2:" + str(s2))
        servo1.publish(UInt16(s1))
        servo2.publish(UInt16(s2))
        rospy.sleep(0.5)

if __name__ == '__main__':
    try:
    	rospy.init_node('MockBotVelocity2Servo')
        servo()
	velocmdlistener()
    	rospy.spin()
    except rospy.ROSInterruptException: pass



#!/usr/bin/env python
##############################################################################
# MobileBase controller for MockBot2
# This is a simple control of the 2 servos connected to the Arduino UNO board
# Author: chrimo@moccy.xdsnet.de
#
# Todo: calibration of mockbot2 motors and motor controller
# Todo: 
#
##############################################################################

import roslib
import rospy

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist
from nav_msgs.msg import *

def cmd_vel_callback(cmd_vel):
    ROBOT_WIDTH=0.44
    left_speed_out = cmd_vel.linear.x - cmd_vel.angular.z*ROBOT_WIDTH/2
    right_speed_out = cmd_vel.linear.x + cmd_vel.angular.z*ROBOT_WIDTH/2
    v = cmd_vel.linear.x        # speed m/s
    theta = cmd_vel.angular.z      # angle rad/s
    rospy.loginfo("VEL_CMD: " + str(v) + "," + str(theta))
    servo_publisher(left_speed_out, right_speed_out)

def vel_cmd_listener():
    rospy.Subscriber("cmd_vel", Twist, cmd_vel_callback)

def servo_publisher(s1,s2):
    servo1 = rospy.Publisher('/MockBot/servo1', UInt16)
    servo2 = rospy.Publisher('/MockBot/servo2', UInt16)
    rospy.loginfo("S1:"+ str(s1) + " S2:" + str(s2))
    # Servo mapping for motorcontoller: 
    # 180 => full speed forward
    # 90 => STOP
    # 0 => full speed back
    # scalefactor for m/s -> servo speed
    sf=1.5
    s1=sf*s1
    s2=sf*s2
    ints1=int(s1*100+90)
    ints2=int(s2*100+90)
    rospy.loginfo("IntS1:"+ str(ints1) + " IntS2:" + str(ints2))
    servo1.publish(UInt16(ints1))
    servo2.publish(UInt16(ints2))
    rospy.sleep(0.1)

if __name__ == '__main__':
    try:
    	rospy.init_node('MockBotBaseController')
	vel_cmd_listener()
    	rospy.spin()
    except rospy.ROSInterruptException: pass



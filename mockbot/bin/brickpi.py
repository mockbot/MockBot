#!/usr/bin/env python
##############################################################################
# Base controller for MockBotBrickPi
# This is a simple control of the 4 servos connected to the BrickPi board
# Author: chrimo@moccy.xdsnet.de
#
##############################################################################

import roslib
import rospy

from BrickPi import *   

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist
#from nav_msgs.msg import *

#Model dependend settings
PI=3.141
ROBOT_WIDTH=0.16
WHEEL_DIAMETER=0.055
WHEEL_RADIUS=WHEEL_DIAMETER/2
WHEEL_PERIMETER=2*PI*WHEEL_RADIUS

#RPM dependant from voltage without load
#9.0V = 120 RPM
#7.5V = 80 RPM
# with load 60-80 rpm is a good average
MAX_RPM=80.0
RPS=MAX_RPM/60.0

MPS=RPS*WHEEL_PERIMETER

PWRDIV=1000*RPS

rospy.loginfo("PWRDIV:"+str(PWRDIV))

RF_WHEEL=PORT_A
LF_WHEEL=PORT_D

RB_WHEEL=PORT_B
LB_WHEEL=PORT_C

FWDIR=-1

BrickPiSetup()

BrickPi.MotorEnable[RF_WHEEL] = 1
BrickPi.MotorEnable[LF_WHEEL] = 1
BrickPi.MotorEnable[RB_WHEEL] = 1
BrickPi.MotorEnable[LB_WHEEL] = 1

BrickPi.SensorType[PORT_1] = TYPE_SENSOR_ULTRASONIC_CONT

BrickPiSetupSensors()

def cmd_vel_callback(cmd_vel):
    left_speed_out = cmd_vel.linear.x - cmd_vel.angular.z*ROBOT_WIDTH/2
    right_speed_out = cmd_vel.linear.x + cmd_vel.angular.z*ROBOT_WIDTH/2
    v = cmd_vel.linear.x        # speed m/s
    theta = cmd_vel.angular.z      # angle rad/s
    rospy.loginfo("VEL_CMD_CB: v:" + str(v) + ", theta:" + str(theta))
    motor_control(left_speed_out, right_speed_out)

def vel_cmd_listener():
    rospy.Subscriber("cmd_vel", Twist, cmd_vel_callback)

def motor_control(left_speed_out,right_speed_out):
    rospy.loginfo("LSPEED:"+ str(left_speed_out) + " RSPEED:" + str(right_speed_out))
    rospy.loginfo("LSPEED:"+ str(left_speed_out) + " RSPEED:" + str(right_speed_out))
    BrickPi.MotorSpeed[RF_WHEEL] = int(-right_speed_out*PWRDIV)
    rospy.loginfo("RF:"+str(BrickPi.MotorSpeed[RF_WHEEL]))
    BrickPi.MotorSpeed[LF_WHEEL] = int(-left_speed_out*PWRDIV)
    rospy.loginfo("LF:"+str(BrickPi.MotorSpeed[LF_WHEEL]))
    BrickPi.MotorSpeed[RB_WHEEL] = int(right_speed_out*PWRDIV)
    rospy.loginfo("RB:"+str(BrickPi.MotorSpeed[RB_WHEEL]))
    BrickPi.MotorSpeed[LB_WHEEL] = int(left_speed_out*PWRDIV)
    rospy.loginfo("LB:"+str(BrickPi.MotorSpeed[LB_WHEEL]))
    BrickPiUpdateValues()
    time.sleep(.01)
    scan_publisher()

def scan_publisher():
    result = BrickPiUpdateValues()
    if not result :
	range = BrickPi.Sensor[PORT_1] 
        us = rospy.Publisher('scan', UInt16)
        us.publish(UInt16(range))
	rospy.loginfo ("SCAN:" + str(range))

if __name__ == '__main__':
    try:
    	rospy.init_node('MockBotBrickPiBaseController')
	vel_cmd_listener()
	time.sleep(.01)
    	rospy.spin()
    except rospy.ROSInterruptException: pass



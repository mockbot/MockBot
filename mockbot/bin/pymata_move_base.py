#!/usr/bin/python

import time
from PyMata.pymata import PyMata

import roslib
import rospy

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist

#Model dependend settings
PI=3.141
ROBOT_WIDTH=0.45
WHEEL_DIAMETER=0.40
WHEEL_RADIUS=WHEEL_DIAMETER/2
WHEEL_PERIMETER=2*PI*WHEEL_RADIUS

# PIN DEFINITIONS
BOARD_LED = 13 

SERVO1 = 9
SERVO2 = 10

deg_min = 1
deg_max = 180
deg_mid = 90
deg_step = 10

# ARDUINO PORT
firmata = PyMata("/dev/ttyACM0")

firmata.refresh_report_firmware()
print firmata.get_firmata_firmware_version()

firmata.set_pin_mode(BOARD_LED, firmata.OUTPUT, firmata.DIGITAL)

#RPM dependant from voltage without load
#9.0V = 120 RPM
#7.5V = 80 RPM
# with load 60-80 rpm is a good average
MAX_RPM=80.0
RPS=MAX_RPM/60.0

MPS=RPS*WHEEL_PERIMETER

PWRDIV=500*RPS

rospy.loginfo("PWRDIV:"+str(PWRDIV))

FWDIR=-1

# set servo parameters
def init_servos():
   firmata.servo_config(SERVO1)
   firmata.servo_config(SERVO2)
   time.sleep(1)

def init_servo_middle():
   print "-middle position "+str(deg_mid)
   firmata.analog_write(SERVO1, deg_mid)
   firmata.analog_write(SERVO2, deg_mid)
   time.sleep(1)

def init_servo_forward():
   print "-forward position "+str(deg_max)
   firmata.analog_write(SERVO1, deg_max)
   firmata.analog_write(SERVO2, deg_max)
   time.sleep(1)

def init_servo_back():
   print "-backward position "+str(deg_min)
   firmata.analog_write(SERVO1, deg_min)
   firmata.analog_write(SERVO2, deg_min)
   time.sleep(1)

def servo_move(servo,s_degree):
   firmata.analog_write(servo, s_degree)
   time.sleep(0.1)

def calibrate_servos():
   print "Calibrate Servos"
   init_servo_middle()
   init_servo_forward()
   init_servo_middle()
   init_servo_back()
   init_servo_middle()

def toggle_led():
   firmata.digital_write(BOARD_LED, 1)
   firmata.digital_write(BOARD_LED, 0)

init_servos()
#calibrate_servos()

#for deg in range(deg_min,deg_max,deg_step):
#    print "Servo degree "+str(deg)
#    toggle_led()
#    servo_move(SERVO1,deg)
#    servo_move(SERVO2,deg)
#    time.sleep(0.1)
#
#for deg in range(deg_max,deg_min,-deg_step):
#    print "Servo degree "+str(deg)
#    toggle_led()
#    servo_move(SERVO1,deg)
#    servo_move(SERVO2,deg)
#    time.sleep(0.1)
#
# close PyMata 
#time.sleep(1)
#firmata.close()

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
    rospy.loginfo("L_SPEED:"+ str(left_speed_out) + " R_SPEED:" + str(right_speed_out))
    #servo_move(SERVO1,int(-right_speed_out*PWRDIV))  
    rospy.loginfo("servo_move(SERVO1,"+str(left_speed_out*PWRDIV)+")")
    #servo_move(SERVO2,int(-left_speed_out*PWRDIV))
    rospy.loginfo("servo_move(SERVO2,"+str(right_speed_out*PWRDIV)+")")
    # Servo mapping for motorcontoller: 
    # 180 => full speed forward
    # 90 => STOP
    # 0 => full speed back
    # scalefactor for m/s -> servo speed
    sf=1.5
    s1=sf*left_speed_out
    s2=sf*right_speed_out
    ints1=int(s1*100+90)
    ints2=int(s2*100+90)
    rospy.loginfo("IntS1:"+ str(ints1) + " IntS2:" + str(ints2))


if __name__ == '__main__':
    try:
        rospy.init_node('MockBotMoveBaseController')
        vel_cmd_listener()
        time.sleep(.01)
        rospy.spin()
    except rospy.ROSInterruptException: pass


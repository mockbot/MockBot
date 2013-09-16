#!/usr/bin/env python
import roslib; #roslib.load_manifest('MockBotAntBrainController')
import rospy

from std_msgs.msg import String
from std_msgs.msg import UInt16
from geometry_msgs.msg import Twist
from nav_msgs.msg import *

from sensor_msgs.msg import LaserScan
from std_msgs.msg import Int16
from std_msgs.msg import Float32


def scan_callback(scan):
    rospy.loginfo((len(scan.ranges), min(scan.ranges)))
    

def scan_listener():
    rospy.Subscriber("base_scan", LaserScan, scan_callback)

#def cmd_vel_publisher(cmd_vel):
#    rospy.loginfo("Publish CMD")
#    rospy.sleep(0.1)

if __name__ == '__main__':
    try:
    	rospy.init_node('MockBotAntBrainController')
	scan_listener()
    	rospy.spin()
    except rospy.ROSInterruptException: pass



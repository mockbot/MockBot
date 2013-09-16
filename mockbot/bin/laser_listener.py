#!/usr/bin/env python
import roslib; #roslib.load_manifest('ros_liv_wander')
import rospy
from sensor_msgs.msg import LaserScan

def scan_callback(scan):
    rospy.loginfo((len(scan.ranges), min(scan.ranges)))

def listener():
    rospy.init_node('laser_listener')
    rospy.Subscriber('scan', LaserScan, scan_callback)
    rospy.spin()

if __name__ == '__main__':
    listener()

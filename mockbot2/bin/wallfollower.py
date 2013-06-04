#!/usr/bin/env python
import random
import roslib; 
import rospy
from geometry_msgs.msg import Vector3, Twist
from sensor_msgs.msg import LaserScan

class wander:

    def __init__(self):
        self.pub = rospy.Publisher('cmd_vel', Twist)
        rospy.init_node('wander')
        self.v = 1.0; self.w = 0.0
        self.safety_limit = 0.90

    def scan_callback(self, scan):
        rospy.loginfo(min(scan.ranges))
        min_ahead = min(scan.ranges)
        if min_ahead < self.safety_limit:
            self.v = 0.0; self.w = 1.0
	    #rospy.loginfo("links")
            tw = Twist(Vector3(self.v,0,0), Vector3(0,0,self.w))
        else:
            self.v = 2.0; self.w = -0.5
        tw = Twist(Vector3(self.v,0,0), Vector3(0,0,self.w))
        self.pub.publish(tw)

    def run(self):
        self.sub = rospy.Subscriber('base_scan', LaserScan, self.scan_callback)
        rospy.spin()

if __name__ == '__main__':
    
    controller = wander()    
    try:        
        controller.run()
    except ROSInterruptException:
        pass

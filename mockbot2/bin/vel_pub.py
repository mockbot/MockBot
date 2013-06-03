#!/usr/bin/env python
from sys import argv
import roslib; #roslib.load_manifest('ros_liv_wander')
import rospy
from geometry_msgs.msg import Vector3, Twist

def publish_velocities(v, w):
    tw = Twist(Vector3(v,0,0), Vector3(0,0,w))
    pub.publish(tw)
    rospy.sleep(1.0)

if __name__ == '__main__':
    
    pub = rospy.Publisher('cmd_vel', Twist)
    rospy.init_node('vel_pub')    
    
    v = 0.5; w = 0.5    
    if len(argv) == 3:
        v = float(argv[1]); w = float(argv[2])

    try:
        while not rospy.is_shutdown():
            publish_velocities(v, w)
    except rospy.ROSInterruptException:
        pass

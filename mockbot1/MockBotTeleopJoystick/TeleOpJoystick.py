
#!/usr/bin/env python
'''
Created February, 2011

@author: Dr. Rainer Hessmer

  teleop.py - simple teleoperation node that translates joystick messages
  to velocity commands (for details see
  http://www.ros.org/wiki/ps3joy/Tutorials/WritingTeleopNode

  Copyright (c) 2011 Dr. Rainer Hessmer.  All right reserved.
  The source code is effectively a port of the ROS WritingTeleopNode tutorial
  code to Python.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the Vanadium Labs LLC nor the names of its
        contributors may be used to endorse or promote products derived
        from this software without specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL VANADIUM LABS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'''

import roslib; roslib.load_manifest('MockBotTeleopJoystick')
import rospy
from geometry_msgs.msg import Twist
from joy.msg import Joy

class Teleop(object):
        '''
        A node that listens to joystick output, scales the values, and publishes
        them as velocity commands.
        '''

        def __init__(self, linearAxisIndex = 3, angularAxisIndex = 2):
                '''
                Initializes the receiver class.
                port: The serial port to listen to.
                baudrate: Baud rate for the serial communication
                '''

                rospy.init_node('teleop')

                self._LinearAxisIndex = rospy.get_param("~linearAxisIndex", linearAxisIndex)
                self._AngularAxisIndex = rospy.get_param("~angularAxisIndex", angularAxisIndex)
                self._LinearScalingFactor = rospy.get_param("~linearScalingFactor", 0)
                self._AngularScalingFactor = rospy.get_param("~angularScalingFactor", 0)

                rospy.loginfo("Starting teleop node with linear axis %d and angular axis %d" % (self._LinearAxisIndex, self._AngularAxisIndex))

                # subscriptions
                rospy.Subscriber("joy", Joy, self._HandleJoystickMessage)
                self._VelocityCommandPublisher = rospy.Publisher("cmd_vel", Twist)

        def _HandleJoystickMessage(self, joyMessage):
                #rospy.logwarn("Handling joystick message: " + str(joyMessage))

                velocityCommand = Twist()
                velocityCommand.linear.x = self._LinearScalingFactor * joyMessage.axes[self._LinearAxisIndex]
                velocityCommand.angular.z = self._AngularScalingFactor * joyMessage.axes[self._AngularAxisIndex]
               
                self._VelocityCommandPublisher.publish(velocityCommand)


if __name__ == '__main__':
        teleop = Teleop()
        rospy.spin()




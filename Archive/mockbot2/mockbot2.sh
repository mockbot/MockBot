#!/bin/bash
/opt/ros/groovy/setup.bash

echo Running MockBot2
/usr/bin/flite -t "running mockbot 2"

#verify connected hardware

# simulator only
# kinect found

roslaunch mockbot2 mockbot2.launch


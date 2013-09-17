#!/bin/bash
export ROS_IP=$1
export ROS_HOSTNAME=$1
export ROS_MASTER_URI=http://$1:11311
echo Using ROS at $1
ping -c 1 $1
rostopic list



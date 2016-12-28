#!/bin/bash
export TURTLEBOT_STAGE_MAP_FILE=/opt/ros/kinetic/share/prog/MockBot/mockbot/simulator/m17-outdoor.yaml
export TURTLEBOT_STAGE_WORLD_FILE=/opt/ros/kinetic/share/prog/MockBot/mockbot/simulator/m17-outdoor.world
roslaunch mockbot m17_mockbot_in_stage.launch

#!/bin/bash
echo Install and setup ROS Groovy for $SUDO_USER 

sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu precise main" > /etc/apt/sources.list.d/ros-latest.list'

wget http://packages.ros.org/ros.key -O - | sudo apt-key add -

sudo apt-get update
sudo apt-get upgrade

echo Setup some usefull system utils
sudo apt-get install ssh htop iptraf bacula-fd flite mosh screen
sudo apt-get install ros-groovy-desktop-full

sudo rosdep init
rosdep update

grep -i "/opt/ros/groovy/setup.bash" $HOME/.bashrc
if [ $? -eq 1 ] ; then 
	echo ROS Env updated
	echo "source /opt/ros/groovy/setup.bash" >> $HOME/.bashrc
else
	echo ROS Env OK
fi

if [ -d "/opt/ros/prog" ] ; then
	echo ROS_PROG OK
else
	echo ROS_PROG added
	sudo mkdir -p /opt/ros/prog
fi

source ~/.bashrc

grep -i "ROS_PACKAGE_PATH=.:/opt/ros/prog:/opt/ros/groovy/share:/opt/ros/groovy/stacks" $HOME/.bashrc
if [ $? -eq 1 ] ; then
	echo ROS_PACKAGE_PATH modified
	echo ROS_PACKAGE_PATH=.:/opt/ros/prog:/opt/ros/groovy/share:/opt/ros/groovy/stacks >> $HOME/.bashrc
	source $HOME/.bashrc
else
	echo ROS_PACKAGE_PATH OK
fi

sudo apt-get install python-rosinstall

echo Adding additional packages
sudo apt-get install ros-groovy-audio-common ros-groovy-openni-launch ros-groovy-openni-tracker ros-groovy-rosserial-arduino ros-groovy-rosserial-python ros-groovy-rosbridge-suite ros-groovy-mjpeg-server ros-groovy-mjpegcanvasjs ros-groovy-tf2-web-republisher

sudo apt-get install apache2 libapache2-mod-php5 php5-curl mysql-server php5-mysql
sudo apt-get install ros-groovy-freiburg-tools ros-groovy-octomap-mapping
sudo apt-get install ros-groovy-hector-slam ros-groovy-hector-models ros-groovy-hector-worldmodel

sudo apt-get install nut python-nut

echo set permissions for user $SUDO_USER
sudo chmod -R 777 $HOME/.ros
sudo chown -R ros:ros $HOME/.ros

echo add $SUDO_USER to groups
sudo usermod -aG dialout $SUDO_USER
sudo usermod -aG audio $SUDO_USER



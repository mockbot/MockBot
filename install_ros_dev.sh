#!/bin/bash

if [ "$1" == "" ] ; then
	echo -e "Parameter distribution (groovy/hydro) missing !!!"
	exit
fi

export DISTRO=$1
echo Install and setup ROS $DISTRO for USER $SUDO_USER 

exit

sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu precise main" > /etc/apt/sources.list.d/ros-latest.list'

wget http://packages.ros.org/ros.key -O - | sudo apt-key add -

sudo apt-get update
sudo apt-get upgrade

echo Setup some usefull system utils
sudo apt-get install ssh htop iptraf bacula-fd flite mosh screen
sudo apt-get install ros-$DISTRO-desktop-full

sudo rosdep init
rosdep update

grep -i "/opt/ros/$DISTRO/setup.bash" $HOME/.bashrc
if [ $? -eq 1 ] ; then 
	echo ROS Env updated
	echo "source /opt/ros/$DISTRO/setup.bash" >> $HOME/.bashrc
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

grep -i "ROS_PACKAGE_PATH=.:/opt/ros/prog:/opt/ros/$DISTRO/share:/opt/ros/$DISTRO/stacks" $HOME/.bashrc
if [ $? -eq 1 ] ; then
	echo ROS_PACKAGE_PATH modified
	echo ROS_PACKAGE_PATH=.:/opt/ros/prog:/opt/ros/$DISTRO/share:/opt/ros/$DISTRO/stacks >> $HOME/.bashrc
	source $HOME/.bashrc
else
	echo ROS_PACKAGE_PATH OK
fi

sudo apt-get install python-rosinstall

echo Adding additional packages
sudo apt-get install ros-$DISTRO-audio-common ros-$DISTRO-openni-launch ros-$DISTRO-openni-tracker ros-$DISTRO-rosserial-arduino ros-$DISTRO-rosserial-python ros-$DISTRO-rosbridge-suite ros-$DISTRO-mjpeg-server ros-$DISTRO-mjpegcanvasjs ros-$DISTRO-tf2-web-republisher

sudo apt-get install apache2 libapache2-mod-php5 php5-curl mysql-server php5-mysql
sudo apt-get install ros-$DISTRO-freiburg-tools ros-$DISTRO-octomap-mapping
sudo apt-get install ros-$DISTRO-hector-slam ros-$DISTRO-hector-models ros-$DISTRO-hector-worldmodel

sudo apt-get install nut python-nut

echo set permissions for user $SUDO_USER
sudo chmod -R 777 $HOME/.ros
sudo chown -R ros:ros $HOME/.ros

echo add $SUDO_USER to groups
sudo usermod -aG dialout $SUDO_USER
sudo usermod -aG audio $SUDO_USER

cd /opt/ros/prog
if [ -e /opt/ros/prog/MockBot ] ; then
	cd MockBot
	git pull
else
	git clone https://github.com/mockbot/MockBot.git
fi


echo "Have fun"

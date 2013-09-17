export ROS_HOSTNAME=`/bin/hostname -I`
export ROS_MASTER_URI="http://$1:11311"
echo Using ROS MASTER at $ROS_MASTER_URI from $ROS_HOSTNAME
ping -c 1 $1
rostopic list
export LIBGL_ALWAYS_SOFTWARE=1



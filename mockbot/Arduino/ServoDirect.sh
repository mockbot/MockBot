echo ServoDirect for Servo \# $1 $2
rostopic pub -v --once /MockBot/servo$1 std_msgs/UInt16 $2


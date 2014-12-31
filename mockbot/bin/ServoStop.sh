echo ServoStop for Servos 
rostopic pub -v --once /MockBot/servo1 std_msgs/UInt16 89
rostopic pub -v --once /MockBot/servo2 std_msgs/UInt16 90


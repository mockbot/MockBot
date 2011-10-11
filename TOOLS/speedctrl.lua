-- Constants
PI=3.14159

-- ROBOT Parameters
ROBOT_WIDTH=0.42 -- distance between wheels in meters
WHEEL_RADIUS=0.20 -- wheelradius in meters
CIRCUMFERENCE=2*PI*WHEEL_RADIUS 

-- SERVO/MOTORCONTROLLER Parameters
SERVO_STOP=90
SERVO_MAX_FORWARD=0
SERVO_MAX_BACKWARDS=179

cmd_vel_linear_x=0 -- DEFAULT vel_linear value at start
cmd_vel_angular_z=0 -- DEFAULT vel_angular at start

-- ahead
for cmd_vel_linear_x=0,1.0,0.1 do
	left_speed_out=cmd_vel_linear_x - cmd_vel_angular_z/ROBOT_WIDTH/2
	right_speed_out=cmd_vel_linear_x + cmd_vel_angular_z/ROBOT_WIDTH/2

	print("LSpeed("..cmd_vel_linear_x..")=>"..left_speed_out.." m/s")
	print("RSpeed("..cmd_vel_linear_x..")=>"..right_speed_out.." m/s")
end

-- left turn
cmd_vel_angular_z=0.9
for cmd_vel_linear_x=0,1.0,0.1 do
	left_speed_out=cmd_vel_linear_x - cmd_vel_angular_z/ROBOT_WIDTH/2
	right_speed_out=cmd_vel_linear_x + cmd_vel_angular_z/ROBOT_WIDTH/2

	print("LSpeed("..cmd_vel_linear_x..")=>"..left_speed_out.." m/s")
	print("RSpeed("..cmd_vel_linear_x..")=>"..right_speed_out.." m/s")
end


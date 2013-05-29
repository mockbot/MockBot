export target="mockbot.urdf"
rosrun xacro xacro.py $target.xacro -o $target
rosrun urdfdom check_urdf $target
rosrun urdfdom urdf_to_graphiz $target



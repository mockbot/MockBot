export target="mockturtlebot.urdf"
rosrun xacro xacro -i -o $target $target.xacro 
check_urdf $target
urdf_to_graphiz $target

sleep 3

cat $target

echo "http://mymodelrobot.appspot.com"

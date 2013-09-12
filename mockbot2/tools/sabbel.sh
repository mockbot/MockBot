export SLEEP=300
while true 
do
rosrun sound_play say.py Cookook
sleep $SLEEP
rosrun sound_play say.py "Hello, I am ROS"
sleep $SLEEP
rosrun sound_play say.py "anybody out there ?"
sleep $SLEEP
rosrun sound_play say.py "come and find me "
sleep $SLEEP
rosrun sound_play say.py "ha ha ha ha ha"
sleep $SLEEP
rosrun sound_play say.py "what a nice day"
sleep $SLEEP
rosrun sound_play say.py "it's `date +%-H` hour and `date +%-M ` minutes"
sleep $SLEEP
done

 

export DIR=/tmp
export MAP=mockbotmap
echo Saving map $MAP to $DIR/$MAP
rosrun map_server map_saver -f $DIR/$MAP


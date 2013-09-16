echo ServoTest for No $1
for i in 0 1 2 3 4 5 6 7 8 9 
do
for j in 0  5  
do
echo Servo$1:$i$j
rostopic pub -v --once /MockBot/servo$1 std_msgs/UInt16 $i$j 
done
done



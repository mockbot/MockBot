for i in 0 1 2 3 4 5 6 7 8 9 
do
for j in 0  5  
do
echo Servo1:$i$j
rostopic pub /servo1 std_msgs/UInt16 $i$j -1 -v 
done
done



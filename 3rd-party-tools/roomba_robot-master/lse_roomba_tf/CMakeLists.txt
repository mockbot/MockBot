cmake_minimum_required(VERSION 2.8.3)
project(lse_roomba_tf)


find_package(catkin REQUIRED COMPONENTS
   roscpp
   tf
  geometry_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mpu_6050
   CATKIN_DEPENDS geometry_msgs 
#  DEPENDS system_lib
)

add_executable(tf_broadcaster_laser src/tf_broadcaster_laser.cpp)
add_executable(tf_broadcaster_sonar src/tf_broadcaster_sonar.cpp)
add_executable(tf_broadcaster_multi src/tf_broadcaster_multi.cpp)
add_executable(tf_broadcaster_nose src/tf_broadcaster_nose.cpp)

add_dependencies(tf_broadcaster_laser lse_roomba_tf_generate_messages_cpp)
add_dependencies(tf_broadcaster_sonar lse_roomba_tf_generate_messages_cpp)
add_dependencies(tf_broadcaster_multi lse_roomba_tf_generate_messages_cpp)
add_dependencies(tf_broadcaster_multi lse_roomba_tf_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(tf_broadcaster_laser   ${catkin_LIBRARIES} )
target_link_libraries(tf_broadcaster_sonar   ${catkin_LIBRARIES} )
target_link_libraries(tf_broadcaster_multi   ${catkin_LIBRARIES} )
target_link_libraries(tf_broadcaster_nose   ${catkin_LIBRARIES} )

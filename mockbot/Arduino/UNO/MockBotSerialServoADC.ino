/*
 * MockBotSerial Arduino  
 * Author: chrimo@moccy.xdsnet.de
 * Changes: 
 * -control of 2 servos (servo1 pin9, servo2 pin10)
 * -reading ADC0-ADC5
 * - adc0 Battery Voltage
 * - adc1 Batter Loader Voltage
 * Todo:
 * -TWI/I2C ACCEL-Sensor
 * -TWI/I2C ULTRASONIC-Sensor
 *
 *
 * Version date: 0.2011.10.08.17.00
 *
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#include <WProgram.h>
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
/*
#include <rosserial_arduino/Adc.h>
*/

Servo servo1, servo2;

void ROS_CALLBACK1( const std_msgs::UInt16& cmd_msg1){ 
  servo1.write(cmd_msg1.data);                       //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));          //toggle led  
}

void ROS_CALLBACK2( const std_msgs::UInt16& cmd_msg2){ 
  servo2.write(cmd_msg2.data);                       //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));          //toggle led  
}

ros::NodeHandle nh;
ros::Subscriber <std_msgs::UInt16> sub1("/MockBot/servo1", ROS_CALLBACK1);
ros::Subscriber <std_msgs::UInt16> sub2("MockBot/servo2", ROS_CALLBACK2);

/*
rosserial_arduino::Adc adc_msg;
ros::Publisher pub("/MockBot/adc", &adc_msg);
*/

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);

/*
  nh.advertise(pub);
*/
  
  servo1.attach(9); //attach it to pin 9
  servo2.attach(10); //attach it to pin 10
}

/*
int averageAnalog(int pin){
  int v=0;
  for(int i=0; i<4; i++) v+= analogRead(pin);
  return v/4;
}

long adc_timer;
*/

void loop(){

/*
  adc_msg.adc0 = averageAnalog(0);
  adc_msg.adc1 = averageAnalog(1);
  adc_msg.adc2 = averageAnalog(2);
  adc_msg.adc3 = averageAnalog(3);
  adc_msg.adc4 = averageAnalog(4);
  adc_msg.adc5 = averageAnalog(5);

  pub.publish(&adc_msg);
*/

  nh.spinOnce();
/*
  delay(1);
*/
}



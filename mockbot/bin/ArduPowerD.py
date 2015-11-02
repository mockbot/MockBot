#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import serial
import json
import re
import os

DEBUG=0

MANU="MockBot"
MODEL="SoftUPS"
CONTACT="chrimo@moccy.xdsnet.de"
LOCATION=MANU+"@HOME"
BATCAP=8000
BATCUR=3000
UPTIME=3600

minBAT=12.0
loadBAT=13.0

DEVICE="/dev/POWER"
UPSLOG="/tmp/ups-dummy"

ser = serial.Serial(DEVICE, 9600, timeout=2, xonxoff=False, rtscts=False, dsrdtr=False)
ser.flushInput()
ser.flushOutput()

count=0  

def powerd():
    pub0 = rospy.Publisher('powerd/A0', String, queue_size=10)
    pub1 = rospy.Publisher('powerd/A1', String, queue_size=10)
    pub2 = rospy.Publisher('powerd/A2', String, queue_size=10)
    pub3 = rospy.Publisher('powerd/A3', String, queue_size=10)
    rospy.init_node('powerd', anonymous=True)
    rate = rospy.Rate(1) # 1hz
    while not rospy.is_shutdown():
	serialString=ser.readline()  
	strippedSerialString=serialString.rstrip()
	if strippedSerialString.startswith('[') and strippedSerialString.endswith(']'):         
		jsonString=re.sub('[\[\]]','',strippedSerialString)
		jsonData=json.loads(jsonString)
		log=open(UPSLOG,'w')
		log.write("device.mfr "+MANU+"\n")  
		log.write("device.model "+MODEL+"\n")
		log.write("device.description "+MANU+" "+MODEL+" Arduino\n")
		log.write("device.contact "+CONTACT+"\n")
		log.write("device.location "+LOCATION+"\n")
		log.write("device.uptime "+str(UPTIME)+"\n")
		a0=float(jsonData['A0'])
		if (a0 > loadBAT):
			STATUS='OL'
		log.write("ups.status "+STATUS+"\n")
		if (a0 < loadBAT):
			STATUS='OB'
		log.write("ups.status "+STATUS+"\n")
		if (a0 < minBAT):  
			STATUS='LB'
		log.write("ups.status "+STATUS+"\n")
		if DEBUG:
			print('A0:'+jsonData['A0']+' A1:'+jsonData['A1']+' A2:'+jsonData['A2']+' A3:'+jsonData['A3']+' STATUS:'+STATUS)
		log.write("ups.mfr "+MANU+"\n")
		log.write("ups.model "+MODEL+"\n")  
		log.write("input.voltage "+jsonData['A0']+"\n")
		log.write("output.voltage "+jsonData['A1']+"\n") 
		log.write("battery.charge 50\n")
		log.write("battery.voltage "+jsonData['A0']+"\n")
		log.write("battery.capacity "+str(BATCAP)+"\n")
		log.write("battery.current "+str(BATCUR)+"\n")
		log.write("battery.temperature 20.0\n")
		log.write("battery.runtime 3600\n")
		log.close()
        	#msg = "MSG: %s%s %s%s" % ('A0:',jsonData['A0'],'A1:',jsonData['A1'])
        	msg0 = jsonData['A0']
        	msg1 = jsonData['A1']
        	msg2 = jsonData['A2']
        	msg3 = jsonData['A3']
        	#rospy.loginfo(msg)
		if DEBUG:
        		rospy.loginfo(msg0)
        		rospy.loginfo(msg1)
        		rospy.loginfo(msg2)
        		rospy.loginfo(msg3)
        	pub0.publish(msg0)
        	pub1.publish(msg1)
        	pub2.publish(msg2)
        	pub3.publish(msg3)
        	rate.sleep()

if __name__ == '__main__':
    try:
        powerd()
    except rospy.ROSInterruptException:
        pass


#!/usr/bin/python

from PyMata.pymata import PyMata

import roslib
import rospy

from std_msgs.msg import String

USB_PORT="/dev/ttyUSB0"
ADC_PIN=0
SERVO_PIN=9
DEBUG=0

def adc_callback(data):
    adc=board.analog_read(ADC_PIN)
    if DEBUG:
        print("PUB:ADC"+str(ADC_PIN)+":"+str(adc))
    pub_adc.publish(str(adc))

def servo_callback(data):
    if DEBUG:
        print("SUB:DATA:"+str(data.data))
    '''write to servo port'''
    pos=int(data.data)
    ''' fake map adc values 0-1024 to 0-180 for servo '''
    pos=int(pos/6)
    if DEBUG:
        print("Set servo to: "+str(pos))
    board.analog_write(SERVO_PIN, pos)

if __name__ == '__main__':
    try:
        ''' init ros node '''
        pub_adc = rospy.Publisher("pymata/adc", String, queue_size=10)
        rospy.init_node("pymata")
        rospy.Subscriber("pymata/adc", String, servo_callback)
        ''' init pymata and ports '''
        board = PyMata(USB_PORT)
        if DEBUG:
            board.refresh_report_firmware()
            print(board.get_firmata_firmware_version())
        board.servo_config(SERVO_PIN)
        board.set_pin_mode(ADC_PIN,board.INPUT,board.ANALOG,adc_callback)
        ''' ros loop '''
        rospy.spin()
    except rospy.ROSInterruptException: pass



/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2010, ISR University of Coimbra.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the ISR University of Coimbra nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author: Gonçalo Cabrita on 19/05/2010
*********************************************************************/

#include "OpenInterface.h"
#include <angles/angles.h>
#include <algorithm>
#include <stdio.h>

// *****************************************************************************
// Constructor
iRobot::OpenInterface::OpenInterface()
{
    packet_size_[OI_PACKET_BUMPS_DROPS] = 1;
    packet_size_[OI_PACKET_WALL] = 1;
    packet_size_[OI_PACKET_CLIFF_LEFT] = 1;
    packet_size_[OI_PACKET_CLIFF_FRONT_LEFT] = 1;
    packet_size_[OI_PACKET_CLIFF_FRONT_RIGHT] = 1;
    packet_size_[OI_PACKET_CLIFF_RIGHT] = 1;
    packet_size_[OI_PACKET_VIRTUAL_WALL] = 1;
    packet_size_[OI_PACKET_WHEEL_OVERCURRENTS] = 1;
    packet_size_[OI_PACKET_DIRT_DETECT] = 1;
    packet_size_[OI_PACKET_UNUSED_16] = 1;
    packet_size_[OI_PACKET_IR_CHAR_OMNI] = 1;
    packet_size_[OI_PACKET_BUTTONS] = 1;
    packet_size_[OI_PACKET_DISTANCE] = 2;
    packet_size_[OI_PACKET_ANGLE] = 2;
    packet_size_[OI_PACKET_CHARGING_STATE] = 1;
    packet_size_[OI_PACKET_VOLTAGE] = 2;
    packet_size_[OI_PACKET_CURRENT] = 2;
    packet_size_[OI_PACKET_TEMPERATURE] = 1;
    packet_size_[OI_PACKET_BATTERY_CHARGE] = 2;
    packet_size_[OI_PACKET_BATTERY_CAPACITY] = 2;
    packet_size_[OI_PACKET_WALL_SIGNAL] = 2;
    packet_size_[OI_PACKET_CLIFF_LEFT_SIGNAL] = 2;
    packet_size_[OI_PACKET_CLIFF_FRONT_LEFT_SIGNAL] = 2;
    packet_size_[OI_PACKET_CLIFF_FRONT_RIGHT_SIGNAL] = 2;
    packet_size_[OI_PACKET_CLIFF_RIGHT_SIGNAL] = 2;
    packet_size_[OI_PACKET_UNUSED_32] = 1;
    packet_size_[OI_PACKET_UNUSED_33] = 2;
    packet_size_[OI_PACKET_CHARGE_SOURCES] = 1;
    packet_size_[OI_PACKET_OI_MODE] = 1;
    packet_size_[OI_PACKET_SONG_NUMBER] = 1;
    packet_size_[OI_PACKET_SONG_PLAYING] = 1;
    packet_size_[OI_PACKET_STREAM_PACKETS] = 1;
    packet_size_[OI_PACKET_REQ_VELOCITY] = 2;
    packet_size_[OI_PACKET_REQ_RADIUS] = 2;
    packet_size_[OI_PACKET_REQ_RIGHT_VELOCITY] = 2;
    packet_size_[OI_PACKET_REQ_LEFT_VELOCITY] = 2;
    packet_size_[OI_PACKET_RIGHT_ENCODER] = 2;
    packet_size_[OI_PACKET_LEFT_ENCODER] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER] = 1;
    packet_size_[OI_PACKET_LIGHT_BUMPER_LEFT] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER_FRONT_LEFT] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER_CENTER_LEFT] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER_CENTER_RIGHT] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER_FRONT_RIGHT] = 2;
    packet_size_[OI_PACKET_LIGHT_BUMPER_RIGHT] = 2;
    packet_size_[OI_PACKET_IR_CHAR_LEFT] = 1;
    packet_size_[OI_PACKET_IR_CHAR_RIGHT] = 1;
    packet_size_[OI_PACKET_LEFT_MOTOR_CURRENT] = 2;
    packet_size_[OI_PACKET_RIGHT_MOTOR_CURRENT] = 2;
    packet_size_[OI_PACKET_BRUSH_MOTOR_CURRENT] = 2;
    packet_size_[OI_PACKET_SIDE_BRUSH_MOTOR_CURRENT] = 2;
    packet_size_[OI_PACKET_STASIS] = 1;

	OImode_ = OI_MODE_OFF;

    clean_color_ = 0;
    clean_brightness_ = 0;

    odometry_yaw_ = 0.0;
    odometry_x_ = 0.0;
    odometry_y_ = 0.0;

    last_encoder_counts_[ROOMBA_LEFT_ENCODER] = -1;
    last_encoder_counts_[ROOMBA_LEFT_ENCODER] = -1;

    unsigned int i;
    for(i=0 ; i<17 ; i++) leds_[i] = false;
    for(i=0 ; i<2 ; i++) brush_direction_[i] = false;
    for(i=0 ; i<3 ; i++)
    {
        brush_[i] = false;
        brush_pwm_[i] = false;
    }
	
	// Default packets
    OIPacketID packets[2] = {OI_PACKET_RIGHT_ENCODER, OI_PACKET_LEFT_ENCODER};
    setSensorPackets(packets, 2);

	serial_port_ = new cereal::CerealPort();
}


// *****************************************************************************
// Destructor
iRobot::OpenInterface::~OpenInterface()
{
	// Clean up!
	delete serial_port_;
}


// *****************************************************************************
// Open the serial port
bool iRobot::OpenInterface::openSerialPort(std::string * serial_port, int baud_rate, bool full_control)
{
    try{ serial_port_->open(serial_port->c_str(), baud_rate); }
    catch(cereal::Exception& e){ return false; }

    startOI(full_control);

    return true;
}


// *****************************************************************************
// Close the serial port
bool iRobot::OpenInterface::closeSerialPort()
{
    drive(0.0, 0.0);
    usleep(OI_DELAY_MODECHANGE_MS * 1e3);

    try{ serial_port_->close(); }
    catch(cereal::Exception& e){ return false; }

    return true;
}


// *****************************************************************************
// Set the mode
bool iRobot::OpenInterface::startOI(bool full_control)
{	
	char buffer[1];

	usleep(OI_DELAY_MODECHANGE_MS * 1e3);
	buffer[0] = (char)OI_OPCODE_START;
	try{ serial_port_->write(buffer, 1); }
    catch(cereal::Exception& e){ return false; }
	OImode_ = OI_MODE_PASSIVE;

	usleep(OI_DELAY_MODECHANGE_MS * 1e3);
	buffer[0] = (char)OI_OPCODE_CONTROL;
	try{ serial_port_->write(buffer, 1); }
    catch(cereal::Exception& e){ return false; }
	OImode_ = OI_MODE_SAFE;
	
	if(full_control)
	{
		usleep(OI_DELAY_MODECHANGE_MS * 1e3);
		buffer[0] = (char)OI_OPCODE_FULL;
		try{ serial_port_->write(buffer, 1); }
        catch(cereal::Exception& e){ return false; }
		OImode_ = OI_MODE_FULL;
	}
    return true;
}


// *****************************************************************************
// Send an OP code to the roomba
bool iRobot::OpenInterface::sendOpcode(OIOpcode code)
{
	char to_send = code;
	try{ serial_port_->write(&to_send, 1); }
    catch(cereal::Exception& e){ return false; }
    return true;
}


// *****************************************************************************
// Power down the roomba
bool iRobot::OpenInterface::powerDown()
{
	return sendOpcode(OI_OPCODE_POWER);
}


// *****************************************************************************
// Set the speeds
bool iRobot::OpenInterface::drive(double linear_speed, double angular_speed)
{
	int left_speed_mm_s = (int)((linear_speed-ROOMBA_AXLE_LENGTH*angular_speed/2)*1e3);		// Left wheel velocity in mm/s
	int right_speed_mm_s = (int)((linear_speed+ROOMBA_AXLE_LENGTH*angular_speed/2)*1e3);	// Right wheel velocity in mm/s
	
    return driveDirect(left_speed_mm_s, right_speed_mm_s);
}


// *****************************************************************************
// Set the motor speeds
bool iRobot::OpenInterface::driveDirect(int left_speed, int right_speed)
{
	// Limit velocity
    int16_t left_speed_mm_s = std::max(left_speed, -ROOMBA_MAX_LIN_VEL_MM_S);
    left_speed_mm_s = std::min(left_speed, ROOMBA_MAX_LIN_VEL_MM_S);
    int16_t right_speed_mm_s = std::max(right_speed, -ROOMBA_MAX_LIN_VEL_MM_S);
    right_speed_mm_s = std::min(right_speed, ROOMBA_MAX_LIN_VEL_MM_S);
	
	// Compose comand
	char cmd_buffer[5];
	cmd_buffer[0] = (char)OI_OPCODE_DRIVE_DIRECT;
	cmd_buffer[1] = (char)(right_speed_mm_s >> 8);
	cmd_buffer[2] = (char)(right_speed_mm_s & 0xFF);
	cmd_buffer[3] = (char)(left_speed_mm_s >> 8);
	cmd_buffer[4] = (char)(left_speed_mm_s & 0xFF);

	try{ serial_port_->write(cmd_buffer, 5); }
    catch(cereal::Exception& e){ return false; }

    return true;
}


// *****************************************************************************
// Set the brushes motors status
bool iRobot::OpenInterface::setBrushes(unsigned char * brushes, bool * states, unsigned char * pwms, unsigned char * directions, unsigned int size)
{
    char cmd_buffer[4];

    bool update_state = false;
    bool update_pwm = false;

    for(unsigned int i=0 ; i<size ; i++)
    {
        if(states[brushes[i]] != brush_[brushes[i]])
        {
            brush_[brushes[i]] = states[brushes[i]];
            update_state = true;
        }
        if(directions[brushes[i]] != brush_direction_[brushes[i]] && brushes[i]!=ROOMBA_VACUUM)
        {
            brush_direction_[brushes[i]] = directions[brushes[i]];
            update_state = true;
        }
        if(pwms[brushes[i]] != brush_pwm_[brushes[i]])
        {
            brush_pwm_[brushes[i]] = pwms[brushes[i]];
            update_pwm = true;
        }
    }

    if(update_state)
    {
        cmd_buffer[0] = OI_OPCODE_MOTORS;
        cmd_buffer[1] = brush_[ROOMBA_SIDE_BRUSH] | brush_[ROOMBA_VACUUM]<<1 | brush_[ROOMBA_MAIN_BRUSH]<<2 |  brush_direction_[ROOMBA_SIDE_BRUSH]<<3 | brush_direction_[ROOMBA_MAIN_BRUSH]<<4;

        try{ serial_port_->write((char*)cmd_buffer, 2); }
        catch(cereal::Exception& e){ return false; }
    }

    if(update_pwm)
    {
        cmd_buffer[0] = OI_OPCODE_PWM_MOTORS;
        cmd_buffer[1] = brush_pwm_[ROOMBA_MAIN_BRUSH];
        cmd_buffer[2] = brush_pwm_[ROOMBA_SIDE_BRUSH];
        cmd_buffer[3] = brush_pwm_[ROOMBA_VACUUM];

        try{ serial_port_->write(cmd_buffer, 4); }
        catch(cereal::Exception& e){ return false; }
    }

    return true;
}


// *****************************************************************************
// Compose a song
bool iRobot::OpenInterface::setSong(unsigned char song_number, unsigned char song_length, unsigned char *notes, unsigned char *note_lengths)
{
    int size = 2*song_length+3;
    unsigned char cmd_buffer[size];
    unsigned char i;

    cmd_buffer[0] = (unsigned char)OI_OPCODE_SONG;
    cmd_buffer[1] = song_number;
    cmd_buffer[2] = song_length;

    for(i=0 ; i < song_length ; i++)
    {
        cmd_buffer[3+(2*i)] = notes[i];
        cmd_buffer[3+(2*i)+1] = note_lengths[i];
    }

    try{ serial_port_->write((char*)cmd_buffer, size); }
    catch(cereal::Exception& e){ return false; }
    return true;
}


// *****************************************************************************
// Play a song from the list
bool iRobot::OpenInterface::playSong(unsigned char song_number)
{
    unsigned char cmd_buffer[2];

    cmd_buffer[0] = (unsigned char)OI_OPCODE_PLAY;
    cmd_buffer[1] = song_number;

    try{ serial_port_->write((char*)cmd_buffer, 2); }
    catch(cereal::Exception& e){ return false; }
    return true;
}


// *****************************************************************************
// Set the LEDs
bool iRobot::OpenInterface::setLeds(unsigned int * leds, bool * states, unsigned int size, int clean_color, int clean_brightness)
{
    if(clean_color >= 0) clean_color_ = clean_color;
    if(clean_brightness >= 0) clean_brightness_ = clean_brightness;

    bool update_leds = false;
    bool update_scheduling_leds = false;

    for(unsigned int i=0 ; i<size ; i++)
    {
        leds_[leds[i]] = states[i];
        if(leds[i] == LED_CLEAN && !states[i]) clean_brightness_ = 0;
        if(leds[i] >= LED_WARNING && leds[i] <= LED_CLEAN) update_leds = true;
        if(leds[i] >= LED_SUNDAY && leds[i] <= LED_SCHEDULE) update_leds = true;
    }

    unsigned char cmd_buffer[4];

    if(update_leds)
    {
        cmd_buffer[0] = (unsigned char)OI_OPCODE_LEDS;
        cmd_buffer[1] = leds_[LED_DIRT] | leds_[LED_SPOT]<<1 | leds_[LED_DOCK]<<2 | leds_[LED_WARNING]<<3;
        cmd_buffer[2] = clean_color_;
        cmd_buffer[3] = clean_brightness_;

        try{ serial_port_->write((char*)cmd_buffer, 4); }
        catch(cereal::Exception& e){ return false; }
    }

    if(update_scheduling_leds)
    {
        cmd_buffer[0] = OI_OPCODE_SCHEDULE_LEDS;
        cmd_buffer[1] = leds_[LED_SUNDAY] | leds_[LED_MONDAY]<<1 | leds_[LED_TUESDAY]<<2 | leds_[LED_WEDNESDAY]<<3 | leds_[LED_THURSDAY]<<4 | leds_[LED_FRIDAY]<<5 | leds_[LED_SATURDAY]<<6;
        cmd_buffer[2] = leds_[LED_COLON] | leds_[LED_PM]<<1 | leds_[LED_AM]<<2 | leds_[LED_CLOCK]<<3 | leds_[LED_SCHEDULE]<<4;

        try{ serial_port_->write((char*)cmd_buffer, 3); }
        catch(cereal::Exception& e){ return false; }
    }

    return true;
}


// *****************************************************************************
// Set the digit LEDs
bool iRobot::OpenInterface::setSevenSegmentDisplay(unsigned char * digits)
{
    unsigned char cmd_buffer[5];
    cmd_buffer[0] = (unsigned char)OI_OPCODE_DIGIT_LEDS_ASCII;
    for(unsigned int i=0 ; i<4 ; i++) cmd_buffer[i+1] = digits[i];

    try{ serial_port_->write((char*)cmd_buffer, 5); }
    catch(cereal::Exception& e){ return false; }
    return true;
}


// *****************************************************************************
// Set Roomba odometry
void iRobot::OpenInterface::setOdometry(double new_x, double new_y, double new_yaw)
{
    odometry_x_ = new_x;
    odometry_y_ = new_y;
    odometry_yaw_ = new_yaw;
}


// *****************************************************************************
// Set the sensors to read
bool iRobot::OpenInterface::setSensorPackets(OIPacketID * packets, unsigned int packets_size)
{
    if(packets_size == 0) return false;

    if(!request_packets_.empty())
	{
        request_packets_.clear();
    }
    if(!reply_packets_.empty())
    {
        reply_packets_.clear();
    }
	
    request_packets_.insert(packets, packets+packets_size);

    std::set<iRobot::OIPacketID>::iterator packet_it;

    for(packet_it = request_packets_.begin() ; packet_it != request_packets_.end() ; packet_it++)
    {
        unsigned int packet_id;
        switch(*packet_it)
        {
            case OI_PACKET_GROUP_0:			//! OI packets 7-26
                for(packet_id=7 ; packet_id<=26 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_1:			//! OI packets 7-16
                for(packet_id=7 ; packet_id<=16 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_2:			//! OI packets 17-20
                for(packet_id=17 ; packet_id<=20 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_3:			//! OI packets 21-26
                for(packet_id=21 ; packet_id<=26 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_4:			//! OI packets 27-34
                for(packet_id=27 ; packet_id<=34 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_5:			//! OI packets 35-42
                for(packet_id=35 ; packet_id<=42 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_6:			//! OI packets 7-42
                for(packet_id=7 ; packet_id<=42 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_100:		//! OI packets 7-58
                for(packet_id=7 ; packet_id<=58 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_101:		//! OI packets 43-58
                for(packet_id=43 ; packet_id<=58 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_106:		//! OI packets 46-51
                for(packet_id=46 ; packet_id<=51 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            case OI_PACKET_GROUP_107:		//! OI packets 54-58
                for(packet_id=54 ; packet_id<=58 ; packet_id++) reply_packets_.insert(OIPacketID(packet_id));
                break;
            default:
                reply_packets_.insert(*packet_it);
        }
    }

    reply_packets_size_ = 0;
    for(packet_it = reply_packets_.begin() ; packet_it != reply_packets_.end() ; packet_it++)
    {
       reply_packets_size_+= packet_size_[*packet_it];
    }

    return true;
}


// *****************************************************************************
// Read the sensors
bool iRobot::OpenInterface::getSensorPackets(int timeout)
{
    char cmd_buffer[request_packets_.size()+2];
    char data_buffer[reply_packets_size_];

	// Fill in the command buffer to send to the robot
	cmd_buffer[0] = (char)OI_OPCODE_QUERY;			// Query
    cmd_buffer[1] = request_packets_.size();        // Number of packets
    unsigned int i;
    std::set<iRobot::OIPacketID>::iterator packet_it;
    for(packet_it = request_packets_.begin(), i = 0 ; packet_it != request_packets_.end() ; packet_it++, i++)
    {
        cmd_buffer[i+2] = *packet_it;               // The packet IDs
	}

    /*printf("[DEBUG] Request buffer: 0x%X ", cmd_buffer[0]);
    for(i=1 ; i<request_packets_.size()+1 ; i++) printf("%d ", cmd_buffer[i]);
    printf("\n");*/

    try{ serial_port_->write(cmd_buffer, request_packets_.size()+2); }
    catch(cereal::Exception& e){ return false; }

    //printf("[DEBUG] Reply buffer size: %d bytes\n", reply_packets_size_);
	
    int bytes;
    try{bytes = serial_port_->readBytes(data_buffer, reply_packets_size_, timeout); }
    catch(cereal::Exception& e){ return false; }

    /*printf("[DEBUG] Reply buffer: ");
    for(i=0 ; i<reply_packets_size_ ; i++) printf("0x%X ", data_buffer[i]);
    printf("\n");*/
	
    return parseSensorPackets((unsigned char*)data_buffer);
}


// *****************************************************************************
// Parse sensor data
bool iRobot::OpenInterface::parseSensorPackets(unsigned char * buffer)
{	
    unsigned int index = 0;
    std::set<iRobot::OIPacketID>::iterator packet_it;
    for(packet_it = reply_packets_.begin() ; packet_it != reply_packets_.end() ; packet_it++)
    {
        switch(*packet_it)
        {
            case OI_PACKET_BUMPS_DROPS:
                bumper_flag_[ROOMBA_TWO_RIGHT] = checkAndSet(bumper_[ROOMBA_TWO_RIGHT], bool(buffer[index] & 0x01));
                bumper_flag_[ROOMBA_TWO_LEFT] = checkAndSet(bumper_[ROOMBA_TWO_LEFT], bool((buffer[index] >> 1) & 0x01));
                wheel_drop_flag_[ROOMBA_TWO_RIGHT] = checkAndSet(wheel_drop_[ROOMBA_TWO_RIGHT], bool((buffer[index] >> 2) & 0x01));
                wheel_drop_flag_[ROOMBA_TWO_LEFT] = checkAndSet(wheel_drop_[ROOMBA_TWO_LEFT], bool((buffer[index] >> 3) & 0x01));
                index++;
                break;

            case OI_PACKET_WALL:
                wall_ = buffer[index] & 0x01;
                index++;
                break;

            case OI_PACKET_CLIFF_LEFT:
            case OI_PACKET_CLIFF_FRONT_LEFT:
            case OI_PACKET_CLIFF_FRONT_RIGHT:
            case OI_PACKET_CLIFF_RIGHT:
            cliff_flag_[*packet_it-OI_PACKET_CLIFF_LEFT] = checkAndSet(cliff_[*packet_it-OI_PACKET_CLIFF_LEFT], bool(buffer[index] & 0x01));
                index++;
                break;

            case OI_PACKET_VIRTUAL_WALL:
                virtual_wall_ = buffer[index] & 0x01;
                index++;
                break;

            case OI_PACKET_WHEEL_OVERCURRENTS:
                overcurrent_[ROOMBA_SIDE_MOTOR] = buffer[index] & 0x01;
                overcurrent_[ROOMBA_MAIN_MOTOR] = (buffer[index] >> 2) & 0x01;
                overcurrent_[ROOMBA_RIGHT_MOTOR] = (buffer[index] >> 3) & 0x01;
                overcurrent_[ROOMBA_LEFT_MOTOR] = (buffer[index] >> 4) & 0x01;
                index++;
                break;

            case OI_PACKET_DIRT_DETECT:
                dirt_detect_ = buffer[index];
                index++;
                break;

            case OI_PACKET_IR_CHAR_OMNI:
                ir_char_[ROOMBA_OMNI] = buffer[index];
                index++;
                break;

            case OI_PACKET_BUTTONS:
            for(unsigned int i=0 ; i<8 ; i++) button_flag_[i] = checkAndSet(button_[i], bool((buffer[index] >> i) & 0x01));
                index++;
                break;

            case OI_PACKET_DISTANCE:
                distance_ = buffer2signed_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_ANGLE:
                angle_ = buffer2signed_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_CHARGING_STATE:
                power_cord_ = buffer[index] & 0x01;
                dock_ = (buffer[index] >> 1) & 0x01;
                index++;
                break;

            case OI_PACKET_VOLTAGE:
                voltage_ = buffer2unsigned_int(buffer, index)/1000.0;
                index+=2;
                break;

            case OI_PACKET_CURRENT:
                current_ = buffer2signed_int(buffer, index)/1000.0;
                index+=2;
                break;

            case OI_PACKET_TEMPERATURE:
                temperature_ = (char)(buffer[index]);
                index++;
                break;

            case OI_PACKET_BATTERY_CHARGE:
                charge_ = buffer2unsigned_int(buffer, index)/1000.0;
                index+=2;
                break;

            case OI_PACKET_BATTERY_CAPACITY:
                capacity_ = buffer2unsigned_int(buffer, index)/1000.0;
                index+=2;
                break;

            case OI_PACKET_WALL_SIGNAL:
                wall_signal_ = buffer2unsigned_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_CLIFF_LEFT_SIGNAL:
            case OI_PACKET_CLIFF_FRONT_LEFT_SIGNAL:
            case OI_PACKET_CLIFF_FRONT_RIGHT_SIGNAL:
            case OI_PACKET_CLIFF_RIGHT_SIGNAL:
                cliff_signal_[*packet_it-OI_PACKET_CLIFF_LEFT_SIGNAL] = buffer2unsigned_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_CHARGE_SOURCES:
                power_cord_ = buffer[index] & 0x01;
                dock_ = (buffer[index] >> 1) & 0x01;
                index++;
                break;

            case OI_PACKET_OI_MODE:
                OImode_ = buffer[index];
                index++;
                break;

            case OI_PACKET_SONG_NUMBER:
                index++;
                break;

            case OI_PACKET_SONG_PLAYING:
                index++;
                break;

            case OI_PACKET_STREAM_PACKETS:
                index++;
                break;

            case OI_PACKET_REQ_VELOCITY:
                index++;
                break;

            case OI_PACKET_REQ_RADIUS:
                index++;
                break;

            case OI_PACKET_RIGHT_ENCODER:
            case OI_PACKET_LEFT_ENCODER:
                //last_encoder_counts_[*packet_it-OI_PACKET_RIGHT_ENCODER] = encoder_counts_[*packet_it-OI_PACKET_RIGHT_ENCODER];
                encoder_counts_[*packet_it-OI_PACKET_RIGHT_ENCODER] = buffer2unsigned_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_LIGHT_BUMPER:
                ir_bumper_flag_[ROOMBA_SIX_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_LEFT], bool(buffer[index] & 0x01));
                ir_bumper_flag_[ROOMBA_SIX_FRONT_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_FRONT_LEFT], bool((buffer[index] >> 1) & 0x01));
                ir_bumper_flag_[ROOMBA_SIX_CENTER_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_CENTER_LEFT], bool((buffer[index] >> 2) & 0x01));
                ir_bumper_flag_[ROOMBA_SIX_CENTER_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_CENTER_RIGHT], bool((buffer[index] >> 3) & 0x01));
                ir_bumper_flag_[ROOMBA_SIX_CENTER_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_FRONT_RIGHT], bool((buffer[index] >> 4) & 0x01));
                ir_bumper_flag_[ROOMBA_SIX_CENTER_LEFT] = checkAndSet(ir_bumper_[ROOMBA_SIX_RIGHT], bool((buffer[index] >> 5) & 0x01));
                index++;
                break;

            case OI_PACKET_LIGHT_BUMPER_LEFT:
            case OI_PACKET_LIGHT_BUMPER_FRONT_LEFT:
            case OI_PACKET_LIGHT_BUMPER_CENTER_LEFT:
            case OI_PACKET_LIGHT_BUMPER_CENTER_RIGHT:
            case OI_PACKET_LIGHT_BUMPER_FRONT_RIGHT:
            case OI_PACKET_LIGHT_BUMPER_RIGHT:
                ir_bumper_signal_[*packet_it-OI_PACKET_LIGHT_BUMPER_LEFT] = buffer2unsigned_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_IR_CHAR_LEFT:
            case OI_PACKET_IR_CHAR_RIGHT:
                ir_char_[*packet_it-OI_PACKET_IR_CHAR_LEFT] = buffer[index];
                index++;
                break;

            case OI_PACKET_LEFT_MOTOR_CURRENT:
            case OI_PACKET_RIGHT_MOTOR_CURRENT:
            case OI_PACKET_BRUSH_MOTOR_CURRENT:
            case OI_PACKET_SIDE_BRUSH_MOTOR_CURRENT:
                motor_current_[*packet_it-OI_PACKET_LEFT_MOTOR_CURRENT] = buffer2signed_int(buffer, index);
                index+=2;
                break;

            case OI_PACKET_STASIS:
                stasis_ = buffer[index] & 0x01;
                index++;
                break;

            default:
                index++;
                break;
        }
    }
    calculateOdometry();

    return true;
}


// *****************************************************************************
// Calculate Roomba odometry
void iRobot::OpenInterface::calculateOdometry()
{	
    if(last_encoder_counts_[ROOMBA_LEFT_ENCODER] > -1 && last_encoder_counts_[ROOMBA_RIGHT_ENCODER] > -1)
    {
        int left_pulses = encoder_counts_[ROOMBA_LEFT_ENCODER] - last_encoder_counts_[ROOMBA_LEFT_ENCODER];
        if(abs(left_pulses) > ROOMBA_ENCODER_OVERFLOW/2) left_pulses += left_pulses < 0 ? ROOMBA_ENCODER_OVERFLOW : -ROOMBA_ENCODER_OVERFLOW;

        int right_pulses = encoder_counts_[ROOMBA_RIGHT_ENCODER] - last_encoder_counts_[ROOMBA_RIGHT_ENCODER];
        if(abs(right_pulses) > ROOMBA_ENCODER_OVERFLOW/2) right_pulses += right_pulses < 0 ? ROOMBA_ENCODER_OVERFLOW : -ROOMBA_ENCODER_OVERFLOW;

        double distance = (right_pulses*ROOMBA_PULSES_TO_M + left_pulses*ROOMBA_PULSES_TO_M) / 2.0;
        double angle = (right_pulses*ROOMBA_PULSES_TO_M - left_pulses*ROOMBA_PULSES_TO_M) / -ROOMBA_AXLE_LENGTH;

        // Update odometry
        odometry_yaw_ = angles::normalize_angle(odometry_yaw_ + angle);
        odometry_x_ = odometry_x_ + distance*cos(odometry_yaw_);
        odometry_y_ = odometry_y_ + distance*sin(odometry_yaw_);
    }
    last_encoder_counts_[ROOMBA_LEFT_ENCODER] = encoder_counts_[ROOMBA_LEFT_ENCODER];
    last_encoder_counts_[ROOMBA_RIGHT_ENCODER] = encoder_counts_[ROOMBA_RIGHT_ENCODER];
}


// EOF

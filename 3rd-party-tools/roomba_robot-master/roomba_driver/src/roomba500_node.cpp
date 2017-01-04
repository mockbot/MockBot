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
* Author: Gonçalo Cabrita on 07/10/2010
*********************************************************************/

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <roomba_msgs/Battery.h>
#include <roomba_msgs/Brush.h>
#include <roomba_msgs/BumperEvent.h>
#include <roomba_msgs/ButtonEvent.h>
#include <roomba_msgs/CliffEvent.h>
#include <roomba_msgs/InfraRedEvent.h>
#include <roomba_msgs/SetLeds.h>
#include <roomba_msgs/PlaySong.h>
#include <roomba_msgs/SaveSong.h>
#include <roomba_msgs/SevenSegmentDisplay.h>
#include <roomba_msgs/WheelDropEvent.h>
#include <sensor_msgs/Range.h>

#include "OpenInterface.h"

std::string wheel_frame_id[2] = {"left_wheel_link", "right_wheel_link"};
std::string cliff_frame_id[4] = {"left_cliff_sensor_link", "front_left_cliff_sensor_link", "front_right_cliff_sensor_link", "right_cliff_sensor_link"};
std::string ir_bumper_frame_id[6] = {"left_ir_sensor_link", "front_left_ir_sensor_link", "center_left_ir_sensor_link", "center_right_ir_sensor_link", "front_right_ir_sensor_link", "right_ir_sensor_link"};
std::string bumper_frame_id[2] = {"left_bumper_link", "right_bumper_link"};

class Roomba
{
public:
    Roomba();

    void update();
    void spin();

    void cmdVelReceived(const geometry_msgs::Twist::ConstPtr& msg);
    void brushReceived(const roomba_msgs::Brush::ConstPtr& msg);
    void ledReceived(const roomba_msgs::SetLeds::ConstPtr& msg);
    void playSong(const roomba_msgs::PlaySong::ConstPtr& msg);
    void saveSong(const roomba_msgs::SaveSong::ConstPtr& msg);
    void ssdReceived(const roomba_msgs::SevenSegmentDisplay::ConstPtr& msg);

private:
    iRobot::OpenInterface oi_;

    ros::NodeHandle n_;
    ros::NodeHandle pn_;

    double rate_;

    tf::TransformBroadcaster tf_broadcaster_;

    ros::Publisher odom_pub_;
    ros::Publisher battery_pub_;
    ros::Publisher * bumper_pub_;
    ros::Publisher * button_pub_;
    ros::Publisher * cliff_pub_;
    ros::Publisher * ir_pub_;
    ros::Publisher * wheel_pub_;
    ros::Publisher * range_pub_;

    ros::Subscriber cmd_sub_;
    ros::Subscriber * brush_sub_;
    ros::Subscriber * led_sub_;
    ros::Subscriber * play_song_sub_;
    ros::Subscriber * save_song_sub_;
    ros::Subscriber * display_sub_;

    std::string base_frame_id_;
    std::string odom_frame_id_;

    double last_x_;
    double last_y_;
    double last_yaw_;
    ros::Time last_update_;
    double last_charge_;

    double ir_sensor_max_range_;
    double ir_sensor_exp_denominator_;
};

Roomba::Roomba() : oi_(), n_(), pn_("~")
{
    bumper_pub_ = NULL;
    button_pub_ = NULL;
    cliff_pub_ = NULL;
    ir_pub_ = NULL;
    wheel_pub_ = NULL;
    range_pub_ = NULL;

    pn_.param<std::string>("base_frame_id", base_frame_id_, "base_footprint");
    pn_.param<std::string>("odom_frame_id", odom_frame_id_, "odom");

    pn_.param("ir_sensor_max_range", ir_sensor_max_range_, 0.25);
    pn_.param("ir_sensor_exp_denominator", ir_sensor_exp_denominator_, 200.0);

    pn_.param("rate", rate_, 10.0);

    std::string port;
    pn_.param<std::string>("port", port, "/dev/ttyUSB0");
    int baudrate;
    pn_.param("baudrate", baudrate, 115200);

    if(!oi_.openSerialPort(&port, baudrate))
    {
        ROS_FATAL("Roomba - %s - Failed to open the serial port %s at %d baud!", __FUNCTION__, port.c_str(), baudrate);
        ROS_BREAK();
    }

    unsigned int led = LED_DIRT;
    bool state = true;
    oi_.setLeds(&led, &state, 1);

    std::vector<iRobot::OIPacketID> packets;

    odom_pub_ = n_.advertise<nav_msgs::Odometry>("/odom", 50);
    packets.push_back(iRobot::OI_PACKET_LEFT_ENCODER);
    packets.push_back(iRobot::OI_PACKET_RIGHT_ENCODER);

    battery_pub_ = n_.advertise<roomba_msgs::Battery>("/battery", 10);
    packets.push_back(iRobot::OI_PACKET_BATTERY_CAPACITY);
    packets.push_back(iRobot::OI_PACKET_BATTERY_CHARGE);
    packets.push_back(iRobot::OI_PACKET_CHARGE_SOURCES);
    packets.push_back(iRobot::OI_PACKET_CHARGING_STATE);

    cmd_sub_  = n_.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, &Roomba::cmdVelReceived, this);

    bool bumpers;
    pn_.param("use_bumpers", bumpers, false);
    if(bumpers)
    {
        bumper_pub_ = new ros::Publisher();
        *bumper_pub_ = n_.advertise<roomba_msgs::BumperEvent>("/bumpers", 10, true);
        packets.push_back(iRobot::OI_PACKET_BUMPS_DROPS);
    }

    bool buttons;
    pn_.param("use_buttons", buttons, false);
    if(buttons)
    {
        button_pub_ = new ros::Publisher();
        *button_pub_ = n_.advertise<roomba_msgs::ButtonEvent>("/buttons", 10, true);
        packets.push_back(iRobot::OI_PACKET_BUTTONS);
    }

    bool cliff_sensors;
    pn_.param("use_cliff_sensors", cliff_sensors, false);
    if(cliff_sensors)
    {
        cliff_pub_ = new ros::Publisher();
        *cliff_pub_ = n_.advertise<roomba_msgs::CliffEvent>("/cliff", 10, true);
        packets.push_back(iRobot::OI_PACKET_CLIFF_LEFT);
        packets.push_back(iRobot::OI_PACKET_CLIFF_FRONT_LEFT);
        packets.push_back(iRobot::OI_PACKET_CLIFF_FRONT_RIGHT);
        packets.push_back(iRobot::OI_PACKET_CLIFF_RIGHT);
    }

    bool ir_receiver;
    pn_.param("use_ir_receiver", ir_receiver, false);
    if(ir_receiver)
    {
        ir_pub_ = new ros::Publisher();
        *ir_pub_ = n_.advertise<roomba_msgs::InfraRedEvent>("/ir_receivers", 10, true);
        packets.push_back(iRobot::OI_PACKET_IR_CHAR_LEFT);
        packets.push_back(iRobot::OI_PACKET_IR_CHAR_OMNI);
        packets.push_back(iRobot::OI_PACKET_IR_CHAR_RIGHT);
    }

    bool wheel_drops;
    pn_.param("use_wheel_drops", wheel_drops, false);
    if(wheel_drops)
    {
        wheel_pub_ = new ros::Publisher();
        *wheel_pub_ = n_.advertise<roomba_msgs::WheelDropEvent>("/wheel_drops", 10, true);
        packets.push_back(iRobot::OI_PACKET_BUMPS_DROPS);
    }

    bool ir_sensors;
    pn_.param("use_ir_sensors", ir_sensors, false);
    if(ir_sensors)
    {
        range_pub_ = new ros::Publisher();
        *range_pub_ = n_.advertise<sensor_msgs::Range>("/range", 10);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_LEFT);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_CENTER_LEFT);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_FRONT_LEFT);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_FRONT_RIGHT);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_CENTER_RIGHT);
        packets.push_back(iRobot::OI_PACKET_LIGHT_BUMPER_RIGHT);
    }

    bool brushes;
    pn_.param("use_brushes", brushes, false);
    if(brushes)
    {
        brush_sub_ = new ros::Subscriber();
        *brush_sub_ = n_.subscribe<roomba_msgs::Brush>("/brushes", 10, &Roomba::brushReceived, this);
    }

    bool leds;
    pn_.param("use_leds", leds, false);
    if(leds)
    {
        led_sub_ = new ros::Subscriber();
        *led_sub_ = n_.subscribe<roomba_msgs::SetLeds>("/leds", 10, &Roomba::ledReceived, this);
    }

    bool songs;
    pn_.param("use_songs", songs, false);
    if(songs)
    {
        play_song_sub_ = new ros::Subscriber();
        *play_song_sub_ = n_.subscribe<roomba_msgs::PlaySong>("/play_song", 10, &Roomba::playSong, this);

        save_song_sub_ = new ros::Subscriber();
        *save_song_sub_ = n_.subscribe<roomba_msgs::SaveSong>("/save_song", 10, &Roomba::saveSong, this);
    }

    bool ssd;
    pn_.param("use_seven_segment_display", ssd, false);
    if(ssd)
    {
        display_sub_ = new ros::Subscriber();
        *display_sub_ = n_.subscribe<roomba_msgs::SevenSegmentDisplay>("/seven_segment_display", 10, &Roomba::ssdReceived, this);
    }

    if(!oi_.setSensorPackets(packets))
    {
        ROS_FATAL("Roomba - %s - Failed to setup the sensor packets!", __FUNCTION__);
        ROS_BREAK();
    }
}

void Roomba::update()
{
    if(!oi_.getSensorPackets(100))
    {
        ROS_ERROR("Roomba - %s - Failed to update sensor data!", __FUNCTION__);
    }

    ros::Time current_time = ros::Time::now();

    double dt = (current_time - last_update_).toSec();
    double vel_x = (oi_.odometry_x_ - last_x_)/dt;
    double vel_y = (oi_.odometry_y_ - last_y_)/dt;
    double vel_yaw = (oi_.odometry_yaw_ - last_yaw_)/dt;

    // since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(oi_.odometry_yaw_);

    // first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_tf;
    odom_tf.header.stamp = current_time;
    odom_tf.header.frame_id = odom_frame_id_;
    odom_tf.child_frame_id = base_frame_id_;

    odom_tf.transform.translation.x = oi_.odometry_x_;
    odom_tf.transform.translation.y = oi_.odometry_y_;
    odom_tf.transform.translation.z = 0.0;
    odom_tf.transform.rotation = odom_quat;

    // send the transform
    tf_broadcaster_.sendTransform(odom_tf);

    // next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = odom_frame_id_;

    // set the position
    odom.pose.pose.position.x = oi_.odometry_x_;
    odom.pose.pose.position.y = oi_.odometry_y_;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    // set the velocity
    odom.child_frame_id = base_frame_id_;
    odom.twist.twist.linear.x = vel_x;
    odom.twist.twist.linear.y = vel_y;
    odom.twist.twist.angular.z = vel_yaw;

    // publish the message
    odom_pub_.publish(odom);

    // publish battery data
    roomba_msgs::Battery bat_msg;
    bat_msg.stamp = current_time;
    if(oi_.dock_ == 0 && oi_.power_cord_ == 0) bat_msg.state = roomba_msgs::Battery::NOT_CHARGING;
    else if(oi_.dock_ == 1) bat_msg.state = roomba_msgs::Battery::DOCK;
    else if(oi_.power_cord_ == 1) bat_msg.state = roomba_msgs::Battery::CORD;
    bat_msg.level = 100.0*(oi_.charge_/oi_.capacity_);
    bat_msg.time_remaining = ros::Duration((bat_msg.level/((last_charge_ - oi_.charge_)/oi_.capacity_)/dt)/60);
    battery_pub_.publish(bat_msg);

    if(bumper_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<2 ; i++)
        {
            if(oi_.bumper_flag_[i])
            {
                roomba_msgs::BumperEvent msg;
                msg.header.stamp = current_time;
                msg.header.frame_id = bumper_frame_id[i];
                msg.state = oi_.bumper_[i];
                oi_.bumper_flag_[i] = false;
                bumper_pub_->publish(msg);
            }
        }
    }

    if(button_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<8 ; i++)
        {
            if(oi_.button_flag_[i])
            {
                roomba_msgs::ButtonEvent msg;
                msg.stamp = current_time;
                msg.button = i;
                msg.state = oi_.button_[i];
                oi_.button_flag_[i] = false;
                button_pub_->publish(msg);
            }
        }
    }

    if(cliff_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<4 ; i++)
        {
            if(oi_.cliff_flag_[i])
            {
                roomba_msgs::CliffEvent msg;
                msg.header.stamp = current_time;
                msg.header.frame_id = cliff_frame_id[i];
                msg.state = oi_.cliff_[i];
                oi_.cliff_flag_[i] = false;
                cliff_pub_->publish(msg);
            }
        }
    }

    if(ir_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<3 ; i++)
        {
            if(oi_.ir_char_flag_[i])
            {
                roomba_msgs::InfraRedEvent msg;
                msg.stamp = current_time;
                msg.sensor = i;
                msg.data = oi_.ir_char_[i];
                oi_.ir_char_flag_[i] = false;
                ir_pub_->publish(msg);
            }
        }
    }

    if(wheel_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<2 ; i++)
        {
            if(oi_.wheel_drop_flag_[i])
            {
                roomba_msgs::WheelDropEvent msg;
                msg.header.stamp = current_time;
                msg.header.frame_id = wheel_frame_id[i];
                msg.state = oi_.wheel_drop_[i];
                oi_.wheel_drop_flag_[i] = false;
                wheel_pub_->publish(msg);
            }
        }
    }

    if(range_pub_ != NULL)
    {
        for(unsigned int i=0 ; i<6 ; i++)
        {
            sensor_msgs::Range msg;
            msg.header.stamp = current_time;
            msg.header.frame_id = ir_bumper_frame_id[i];
            msg.radiation_type = sensor_msgs::Range::INFRARED;
            msg.field_of_view = M_PI/8;
            msg.min_range = 0;
            msg.max_range = ir_sensor_max_range_;
            msg.range = ir_sensor_max_range_*exp((-1*oi_.ir_bumper_signal_[i])/ir_sensor_exp_denominator_);
            range_pub_->publish(msg);
        }
    }

    last_x_ = oi_.odometry_x_;
    last_y_ = oi_.odometry_y_;
    last_yaw_ = oi_.odometry_yaw_;
    last_update_ = current_time;
    last_charge_ = oi_.charge_;
}

void Roomba::spin()
{
    ros::Rate r(rate_);
    while(n_.ok())
    {
        update();

        ros::spinOnce();
        r.sleep();
    }

    oi_.powerDown();
}

void Roomba::cmdVelReceived(const geometry_msgs::Twist::ConstPtr& msg)
{
    oi_.drive(msg->linear.x, msg->angular.z);
}

void Roomba::brushReceived(const roomba_msgs::Brush::ConstPtr& msg)
{
    unsigned char brush = msg->brush;
    bool state = msg->state;
    unsigned char pwm = msg->pwm;
    unsigned char direction = msg->direction;

    oi_.setBrushes(&brush, &state, &pwm, &direction, 1);
}

void Roomba::ledReceived(const roomba_msgs::SetLeds::ConstPtr& msg)
{
    unsigned int leds[msg->led.size()];
    bool states[msg->led.size()];

    int clean_color = -1;
    int clean_brightness = -1;
    for(unsigned int i=0 ; i<msg->led.size() ; i++)
    {
        leds[i] = msg->led[i].button;
        states[i] = msg->led[i].state;

        if(leds[i] == LED_CLEAN)
        {
            clean_color = msg->led[i].color;
            clean_brightness = msg->led[i].brightness;
        }
    }

    oi_.setLeds(leds, states, msg->led.size(), clean_color, clean_brightness);
}

void Roomba::playSong(const roomba_msgs::PlaySong::ConstPtr& msg)
{
    oi_.playSong(msg->song);
}

void Roomba::saveSong(const roomba_msgs::SaveSong::ConstPtr& msg)
{
    unsigned char note[msg->notes.size()];
    unsigned char note_length[msg->notes.size()];

    for(unsigned int i=0 ; i<msg->notes.size() ; i++)
    {
        note[i] = msg->notes[i].note;
        note_length[i] = msg->notes[i].length;
    }

    oi_.setSong(msg->song, msg->notes.size(), note, note_length);
}

void Roomba::ssdReceived(const roomba_msgs::SevenSegmentDisplay::ConstPtr& msg)
{
    oi_.setSevenSegmentDisplay((unsigned char*)(msg->digit.data()));
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "roomba_node");

    ROS_INFO("Roomba for ROS");

    Roomba roomba;
    roomba.spin();

    return(0);
}

// EOF

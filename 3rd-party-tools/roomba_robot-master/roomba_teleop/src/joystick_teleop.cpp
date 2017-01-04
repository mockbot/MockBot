/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2013, ISR University of Coimbra.
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
* Author: Gonçalo Cabrita on 06/06/2013
* Copied from the Squirtle teleop ROS package
*********************************************************************/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include "ros/console.h"

class RoombaTeleop
{
public:
  RoombaTeleop();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void velCallback(const geometry_msgs::Twist::ConstPtr& vel);
  void publish();

  ros::NodeHandle ph_, nh_;

  int linear_, angular_, dead_man_switch_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber vel_sub_;
  ros::Subscriber joy_sub_;

  geometry_msgs::Twist last_published_;
  boost::mutex publish_mutex_;
  bool dead_man_switch_pressed_;
  ros::Timer timer_;

  bool mux_;

};

RoombaTeleop::RoombaTeleop():
  ph_("~"),
  linear_(1),
  angular_(0),
  dead_man_switch_(0),
  l_scale_(0.3),
  a_scale_(0.9)
{
  ph_.param("axis_linear", linear_, linear_);
  ph_.param("axis_angular", angular_, angular_);
  ph_.param("dead_man_switch", dead_man_switch_, dead_man_switch_);
  ph_.param("scale_angular", a_scale_, a_scale_);
  ph_.param("scale_linear", l_scale_, l_scale_);

  ph_.param("multiplex", mux_, false);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("teleop/cmd_vel", 1);
  if(mux_) vel_sub_ = nh_.subscribe<geometry_msgs::Twist>("move_base/cmd_vel", 10, &RoombaTeleop::velCallback, this);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &RoombaTeleop::joyCallback, this);

  timer_ = nh_.createTimer(ros::Duration(0.1), boost::bind(&RoombaTeleop::publish, this));
}

void RoombaTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{ 
  dead_man_switch_pressed_ = joy->buttons[dead_man_switch_];

  geometry_msgs::Twist vel;
  if(dead_man_switch_pressed_)
  {
    vel.angular.z = a_scale_*joy->axes[angular_];
    vel.linear.x = joy->axes[linear_] == 0.0 ? 0.01 : l_scale_*joy->axes[linear_];
  }
  else
  {
    vel.angular.z = 0.0;
    vel.linear.x = 0.0;
  }

  last_published_ = vel;
}

void RoombaTeleop::velCallback(const geometry_msgs::Twist::ConstPtr& vel)
{
    boost::mutex::scoped_lock lock(publish_mutex_);

    if(!dead_man_switch_pressed_)
    {
        vel_pub_.publish(*vel);
    }
}

void RoombaTeleop::publish()
{
  boost::mutex::scoped_lock lock(publish_mutex_);

  if(!dead_man_switch_pressed_ && (last_published_.angular.z != 0.0 || last_published_.linear.x != 0.0))
  {
      last_published_.angular.z = 0.0;
      last_published_.linear.x = 0.0;
      vel_pub_.publish(last_published_);
  }
  else if(dead_man_switch_pressed_)
  {
    vel_pub_.publish(last_published_);
  }

}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "roomba_joystick_teleop");
  RoombaTeleop roomba_teleop;

  puts("Reading from a joystick");
  puts("---------------------------");
  puts("Push the deadman switch to activate cmd_vel publishing.");
  puts("Move the analog stick around to control the velocity.");

  ros::spin();
}

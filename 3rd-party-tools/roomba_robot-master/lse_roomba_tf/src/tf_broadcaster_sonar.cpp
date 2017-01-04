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
* Author: Gonçalo Cabrita
*********************************************************************/
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <math.h>

#define SONAR_RADIUS 0.125

int main(int argc, char** argv)
{
  	ros::init(argc, argv, "roomba_tf_setup");
  	ros::NodeHandle n;

  	ros::Rate r(50);

  	tf::TransformBroadcaster broadcaster;

  	while(n.ok())
	{
    		broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::createQuaternionFromYaw(M_PI/2.0), tf::Vector3(SONAR_RADIUS*cos(M_PI/2.0), SONAR_RADIUS*sin(M_PI/2.0), 0.120)),
        	ros::Time::now(),"base_link", "/base_sonar_0"));

		broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::createQuaternionFromYaw(M_PI/4.0), tf::Vector3(SONAR_RADIUS*cos(M_PI/4.0), SONAR_RADIUS*sin(M_PI/4.0), 0.120)),
        	ros::Time::now(),"base_link", "/base_sonar_1"));

		broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::createQuaternionFromYaw(0.0), tf::Vector3(SONAR_RADIUS, 0.000, 0.120)),
        	ros::Time::now(),"base_link", "/base_sonar_2"));

		broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::createQuaternionFromYaw(-M_PI/4.0), tf::Vector3(SONAR_RADIUS*cos(-M_PI/4.0), SONAR_RADIUS*sin(-M_PI/4.0), 0.120)),
        	ros::Time::now(),"base_link", "/base_sonar_3"));

		broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::createQuaternionFromYaw(-M_PI/2.0), tf::Vector3(SONAR_RADIUS*cos(-M_PI/2.0), SONAR_RADIUS*sin(-M_PI/2.0), 0.120)),
        	ros::Time::now(),"base_link", "/base_sonar_4"));
		
    		r.sleep();
  	}
}

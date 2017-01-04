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
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <string.h>
#include <vector>

int main(int argc, char** argv)
{
  	ros::init(argc, argv, "roomba_tf_setup");
  	ros::NodeHandle n;
	
	tf::TransformListener listener;
	tf::TransformBroadcaster broadcaster;

	std::vector<ros::Time> tf_time;
	std::vector<ros::Time> start_time;

	int numofrobots = 3;
	std::string basename = "robot";

	bool error = false;
	for(int i=1 ; i<numofrobots+1 ; i++)
	{
		char map[128];
		sprintf(map, "/%s%d/map", basename.c_str(), i);
		char odom[128];
		sprintf(odom, "/%s%d/odom", basename.c_str(), i);

		tf::StampedTransform transform;
    		try
		{
			error = false;
      			listener.lookupTransform(map, odom, ros::Time(0), transform);
		}
		catch (tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
			i--;	
			error = true;
		}
		if(!error)
		{
			tf_time.push_back(transform.stamp_);
			start_time.push_back(ros::Time::now());
		}
	}

  	ros::Rate r(10);
  	while(n.ok())
	{
		for(int i=1 ; i<numofrobots+1 ; i++)
		{
			char map[128];
			sprintf(map, "/%s%d/map", basename.c_str(), i);
			
			tf::Transform transform;
  			transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
 			transform.setRotation( tf::Quaternion(0, 0, 0) );
  			broadcaster.sendTransform(tf::StampedTransform(transform, tf_time[i-1]+(ros::Time::now()-start_time[i-1]), "map", map));
		}
    		r.sleep();
  	}
}

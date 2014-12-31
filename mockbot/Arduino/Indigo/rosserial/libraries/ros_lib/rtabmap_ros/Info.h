#ifndef _ROS_rtabmap_ros_Info_h
#define _ROS_rtabmap_ros_Info_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"

namespace rtabmap_ros
{

  class Info : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int32_t refId;
      int32_t loopClosureId;
      int32_t localLoopClosureId;
      geometry_msgs::Transform loopClosureTransform;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_refId;
      u_refId.real = this->refId;
      *(outbuffer + offset + 0) = (u_refId.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_refId.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_refId.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_refId.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->refId);
      union {
        int32_t real;
        uint32_t base;
      } u_loopClosureId;
      u_loopClosureId.real = this->loopClosureId;
      *(outbuffer + offset + 0) = (u_loopClosureId.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_loopClosureId.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_loopClosureId.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_loopClosureId.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->loopClosureId);
      union {
        int32_t real;
        uint32_t base;
      } u_localLoopClosureId;
      u_localLoopClosureId.real = this->localLoopClosureId;
      *(outbuffer + offset + 0) = (u_localLoopClosureId.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_localLoopClosureId.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_localLoopClosureId.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_localLoopClosureId.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->localLoopClosureId);
      offset += this->loopClosureTransform.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_refId;
      u_refId.base = 0;
      u_refId.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_refId.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_refId.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_refId.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->refId = u_refId.real;
      offset += sizeof(this->refId);
      union {
        int32_t real;
        uint32_t base;
      } u_loopClosureId;
      u_loopClosureId.base = 0;
      u_loopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_loopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_loopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_loopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->loopClosureId = u_loopClosureId.real;
      offset += sizeof(this->loopClosureId);
      union {
        int32_t real;
        uint32_t base;
      } u_localLoopClosureId;
      u_localLoopClosureId.base = 0;
      u_localLoopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_localLoopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_localLoopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_localLoopClosureId.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->localLoopClosureId = u_localLoopClosureId.real;
      offset += sizeof(this->localLoopClosureId);
      offset += this->loopClosureTransform.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/Info"; };
    const char * getMD5(){ return "9fd99abb94c54ecc63466e3e281359e1"; };

  };

}
#endif
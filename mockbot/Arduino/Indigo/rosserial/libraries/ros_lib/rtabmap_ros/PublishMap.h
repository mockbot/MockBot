#ifndef _ROS_SERVICE_PublishMap_h
#define _ROS_SERVICE_PublishMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rtabmap_ros
{

static const char PUBLISHMAP[] = "rtabmap_ros/PublishMap";

  class PublishMapRequest : public ros::Msg
  {
    public:
      bool global;
      bool optimized;
      bool graphOnly;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_global;
      u_global.real = this->global;
      *(outbuffer + offset + 0) = (u_global.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->global);
      union {
        bool real;
        uint8_t base;
      } u_optimized;
      u_optimized.real = this->optimized;
      *(outbuffer + offset + 0) = (u_optimized.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->optimized);
      union {
        bool real;
        uint8_t base;
      } u_graphOnly;
      u_graphOnly.real = this->graphOnly;
      *(outbuffer + offset + 0) = (u_graphOnly.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->graphOnly);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_global;
      u_global.base = 0;
      u_global.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->global = u_global.real;
      offset += sizeof(this->global);
      union {
        bool real;
        uint8_t base;
      } u_optimized;
      u_optimized.base = 0;
      u_optimized.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->optimized = u_optimized.real;
      offset += sizeof(this->optimized);
      union {
        bool real;
        uint8_t base;
      } u_graphOnly;
      u_graphOnly.base = 0;
      u_graphOnly.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->graphOnly = u_graphOnly.real;
      offset += sizeof(this->graphOnly);
     return offset;
    }

    const char * getType(){ return PUBLISHMAP; };
    const char * getMD5(){ return "6213f9f13cced23f4d224b22f59d839c"; };

  };

  class PublishMapResponse : public ros::Msg
  {
    public:

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return PUBLISHMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class PublishMap {
    public:
    typedef PublishMapRequest Request;
    typedef PublishMapResponse Response;
  };

}
#endif

#ifndef _ROS_SERVICE_GetMap_h
#define _ROS_SERVICE_GetMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rtabmap_ros/MapData.h"

namespace rtabmap_ros
{

static const char GETMAP[] = "rtabmap_ros/GetMap";

  class GetMapRequest : public ros::Msg
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

    const char * getType(){ return GETMAP; };
    const char * getMD5(){ return "6213f9f13cced23f4d224b22f59d839c"; };

  };

  class GetMapResponse : public ros::Msg
  {
    public:
      rtabmap_ros::MapData data;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->data.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->data.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETMAP; };
    const char * getMD5(){ return "45e45e933a0a62d2bd43f8154ed7b1d0"; };

  };

  class GetMap {
    public:
    typedef GetMapRequest Request;
    typedef GetMapResponse Response;
  };

}
#endif

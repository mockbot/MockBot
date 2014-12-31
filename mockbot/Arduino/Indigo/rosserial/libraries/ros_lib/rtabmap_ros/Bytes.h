#ifndef _ROS_rtabmap_ros_Bytes_h
#define _ROS_rtabmap_ros_Bytes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rtabmap_ros
{

  class Bytes : public ros::Msg
  {
    public:
      uint8_t bytes_length;
      uint8_t st_bytes;
      uint8_t * bytes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = bytes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bytes_length; i++){
      *(outbuffer + offset + 0) = (this->bytes[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bytes[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t bytes_lengthT = *(inbuffer + offset++);
      if(bytes_lengthT > bytes_length)
        this->bytes = (uint8_t*)realloc(this->bytes, bytes_lengthT * sizeof(uint8_t));
      offset += 3;
      bytes_length = bytes_lengthT;
      for( uint8_t i = 0; i < bytes_length; i++){
      this->st_bytes =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_bytes);
        memcpy( &(this->bytes[i]), &(this->st_bytes), sizeof(uint8_t));
      }
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/Bytes"; };
    const char * getMD5(){ return "d159f2bd8169d3b3339e6f1fce045c6d"; };

  };

}
#endif
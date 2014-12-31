#ifndef _ROS_rtabmap_ros_KeyPoint_h
#define _ROS_rtabmap_ros_KeyPoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rtabmap_ros
{

  class KeyPoint : public ros::Msg
  {
    public:
      float ptx;
      float pty;
      float size;
      float angle;
      float response;
      int32_t octave;
      int32_t class_id;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_ptx;
      u_ptx.real = this->ptx;
      *(outbuffer + offset + 0) = (u_ptx.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ptx.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ptx.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ptx.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ptx);
      union {
        float real;
        uint32_t base;
      } u_pty;
      u_pty.real = this->pty;
      *(outbuffer + offset + 0) = (u_pty.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pty.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pty.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pty.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pty);
      union {
        float real;
        uint32_t base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_size.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_size.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        float real;
        uint32_t base;
      } u_response;
      u_response.real = this->response;
      *(outbuffer + offset + 0) = (u_response.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_response.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_response.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_response.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->response);
      union {
        int32_t real;
        uint32_t base;
      } u_octave;
      u_octave.real = this->octave;
      *(outbuffer + offset + 0) = (u_octave.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_octave.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_octave.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_octave.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->octave);
      union {
        int32_t real;
        uint32_t base;
      } u_class_id;
      u_class_id.real = this->class_id;
      *(outbuffer + offset + 0) = (u_class_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_class_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_class_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_class_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->class_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_ptx;
      u_ptx.base = 0;
      u_ptx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ptx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ptx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ptx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ptx = u_ptx.real;
      offset += sizeof(this->ptx);
      union {
        float real;
        uint32_t base;
      } u_pty;
      u_pty.base = 0;
      u_pty.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pty.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pty.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pty.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pty = u_pty.real;
      offset += sizeof(this->pty);
      union {
        float real;
        uint32_t base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size = u_size.real;
      offset += sizeof(this->size);
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      union {
        float real;
        uint32_t base;
      } u_response;
      u_response.base = 0;
      u_response.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_response.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_response.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_response.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->response = u_response.real;
      offset += sizeof(this->response);
      union {
        int32_t real;
        uint32_t base;
      } u_octave;
      u_octave.base = 0;
      u_octave.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_octave.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_octave.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_octave.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->octave = u_octave.real;
      offset += sizeof(this->octave);
      union {
        int32_t real;
        uint32_t base;
      } u_class_id;
      u_class_id.base = 0;
      u_class_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_class_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_class_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_class_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->class_id = u_class_id.real;
      offset += sizeof(this->class_id);
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/KeyPoint"; };
    const char * getMD5(){ return "0ff91e51ebaf0c97a102580aaab50951"; };

  };

}
#endif
#ifndef _ROS_rtabmap_ros_InfoEx_h
#define _ROS_rtabmap_ros_InfoEx_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"

namespace rtabmap_ros
{

  class InfoEx : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int32_t refId;
      int32_t loopClosureId;
      int32_t localLoopClosureId;
      geometry_msgs::Transform loopClosureTransform;
      uint8_t posteriorKeys_length;
      int32_t st_posteriorKeys;
      int32_t * posteriorKeys;
      uint8_t posteriorValues_length;
      float st_posteriorValues;
      float * posteriorValues;
      uint8_t likelihoodKeys_length;
      int32_t st_likelihoodKeys;
      int32_t * likelihoodKeys;
      uint8_t likelihoodValues_length;
      float st_likelihoodValues;
      float * likelihoodValues;
      uint8_t rawLikelihoodKeys_length;
      int32_t st_rawLikelihoodKeys;
      int32_t * rawLikelihoodKeys;
      uint8_t rawLikelihoodValues_length;
      float st_rawLikelihoodValues;
      float * rawLikelihoodValues;
      uint8_t weightsKeys_length;
      int32_t st_weightsKeys;
      int32_t * weightsKeys;
      uint8_t weightsValues_length;
      int32_t st_weightsValues;
      int32_t * weightsValues;
      uint8_t statsKeys_length;
      char* st_statsKeys;
      char* * statsKeys;
      uint8_t statsValues_length;
      float st_statsValues;
      float * statsValues;

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
      *(outbuffer + offset++) = posteriorKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < posteriorKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_posteriorKeysi;
      u_posteriorKeysi.real = this->posteriorKeys[i];
      *(outbuffer + offset + 0) = (u_posteriorKeysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_posteriorKeysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_posteriorKeysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_posteriorKeysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->posteriorKeys[i]);
      }
      *(outbuffer + offset++) = posteriorValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < posteriorValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_posteriorValuesi;
      u_posteriorValuesi.real = this->posteriorValues[i];
      *(outbuffer + offset + 0) = (u_posteriorValuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_posteriorValuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_posteriorValuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_posteriorValuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->posteriorValues[i]);
      }
      *(outbuffer + offset++) = likelihoodKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < likelihoodKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_likelihoodKeysi;
      u_likelihoodKeysi.real = this->likelihoodKeys[i];
      *(outbuffer + offset + 0) = (u_likelihoodKeysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_likelihoodKeysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_likelihoodKeysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_likelihoodKeysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->likelihoodKeys[i]);
      }
      *(outbuffer + offset++) = likelihoodValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < likelihoodValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_likelihoodValuesi;
      u_likelihoodValuesi.real = this->likelihoodValues[i];
      *(outbuffer + offset + 0) = (u_likelihoodValuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_likelihoodValuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_likelihoodValuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_likelihoodValuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->likelihoodValues[i]);
      }
      *(outbuffer + offset++) = rawLikelihoodKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rawLikelihoodKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_rawLikelihoodKeysi;
      u_rawLikelihoodKeysi.real = this->rawLikelihoodKeys[i];
      *(outbuffer + offset + 0) = (u_rawLikelihoodKeysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rawLikelihoodKeysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rawLikelihoodKeysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rawLikelihoodKeysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rawLikelihoodKeys[i]);
      }
      *(outbuffer + offset++) = rawLikelihoodValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rawLikelihoodValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_rawLikelihoodValuesi;
      u_rawLikelihoodValuesi.real = this->rawLikelihoodValues[i];
      *(outbuffer + offset + 0) = (u_rawLikelihoodValuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rawLikelihoodValuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rawLikelihoodValuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rawLikelihoodValuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rawLikelihoodValues[i]);
      }
      *(outbuffer + offset++) = weightsKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < weightsKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_weightsKeysi;
      u_weightsKeysi.real = this->weightsKeys[i];
      *(outbuffer + offset + 0) = (u_weightsKeysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_weightsKeysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_weightsKeysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_weightsKeysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->weightsKeys[i]);
      }
      *(outbuffer + offset++) = weightsValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < weightsValues_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_weightsValuesi;
      u_weightsValuesi.real = this->weightsValues[i];
      *(outbuffer + offset + 0) = (u_weightsValuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_weightsValuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_weightsValuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_weightsValuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->weightsValues[i]);
      }
      *(outbuffer + offset++) = statsKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < statsKeys_length; i++){
      uint32_t length_statsKeysi = strlen(this->statsKeys[i]);
      memcpy(outbuffer + offset, &length_statsKeysi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->statsKeys[i], length_statsKeysi);
      offset += length_statsKeysi;
      }
      *(outbuffer + offset++) = statsValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < statsValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_statsValuesi;
      u_statsValuesi.real = this->statsValues[i];
      *(outbuffer + offset + 0) = (u_statsValuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_statsValuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_statsValuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_statsValuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->statsValues[i]);
      }
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
      uint8_t posteriorKeys_lengthT = *(inbuffer + offset++);
      if(posteriorKeys_lengthT > posteriorKeys_length)
        this->posteriorKeys = (int32_t*)realloc(this->posteriorKeys, posteriorKeys_lengthT * sizeof(int32_t));
      offset += 3;
      posteriorKeys_length = posteriorKeys_lengthT;
      for( uint8_t i = 0; i < posteriorKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_posteriorKeys;
      u_st_posteriorKeys.base = 0;
      u_st_posteriorKeys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_posteriorKeys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_posteriorKeys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_posteriorKeys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_posteriorKeys = u_st_posteriorKeys.real;
      offset += sizeof(this->st_posteriorKeys);
        memcpy( &(this->posteriorKeys[i]), &(this->st_posteriorKeys), sizeof(int32_t));
      }
      uint8_t posteriorValues_lengthT = *(inbuffer + offset++);
      if(posteriorValues_lengthT > posteriorValues_length)
        this->posteriorValues = (float*)realloc(this->posteriorValues, posteriorValues_lengthT * sizeof(float));
      offset += 3;
      posteriorValues_length = posteriorValues_lengthT;
      for( uint8_t i = 0; i < posteriorValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_posteriorValues;
      u_st_posteriorValues.base = 0;
      u_st_posteriorValues.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_posteriorValues.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_posteriorValues.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_posteriorValues.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_posteriorValues = u_st_posteriorValues.real;
      offset += sizeof(this->st_posteriorValues);
        memcpy( &(this->posteriorValues[i]), &(this->st_posteriorValues), sizeof(float));
      }
      uint8_t likelihoodKeys_lengthT = *(inbuffer + offset++);
      if(likelihoodKeys_lengthT > likelihoodKeys_length)
        this->likelihoodKeys = (int32_t*)realloc(this->likelihoodKeys, likelihoodKeys_lengthT * sizeof(int32_t));
      offset += 3;
      likelihoodKeys_length = likelihoodKeys_lengthT;
      for( uint8_t i = 0; i < likelihoodKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_likelihoodKeys;
      u_st_likelihoodKeys.base = 0;
      u_st_likelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_likelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_likelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_likelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_likelihoodKeys = u_st_likelihoodKeys.real;
      offset += sizeof(this->st_likelihoodKeys);
        memcpy( &(this->likelihoodKeys[i]), &(this->st_likelihoodKeys), sizeof(int32_t));
      }
      uint8_t likelihoodValues_lengthT = *(inbuffer + offset++);
      if(likelihoodValues_lengthT > likelihoodValues_length)
        this->likelihoodValues = (float*)realloc(this->likelihoodValues, likelihoodValues_lengthT * sizeof(float));
      offset += 3;
      likelihoodValues_length = likelihoodValues_lengthT;
      for( uint8_t i = 0; i < likelihoodValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_likelihoodValues;
      u_st_likelihoodValues.base = 0;
      u_st_likelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_likelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_likelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_likelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_likelihoodValues = u_st_likelihoodValues.real;
      offset += sizeof(this->st_likelihoodValues);
        memcpy( &(this->likelihoodValues[i]), &(this->st_likelihoodValues), sizeof(float));
      }
      uint8_t rawLikelihoodKeys_lengthT = *(inbuffer + offset++);
      if(rawLikelihoodKeys_lengthT > rawLikelihoodKeys_length)
        this->rawLikelihoodKeys = (int32_t*)realloc(this->rawLikelihoodKeys, rawLikelihoodKeys_lengthT * sizeof(int32_t));
      offset += 3;
      rawLikelihoodKeys_length = rawLikelihoodKeys_lengthT;
      for( uint8_t i = 0; i < rawLikelihoodKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_rawLikelihoodKeys;
      u_st_rawLikelihoodKeys.base = 0;
      u_st_rawLikelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_rawLikelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_rawLikelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_rawLikelihoodKeys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_rawLikelihoodKeys = u_st_rawLikelihoodKeys.real;
      offset += sizeof(this->st_rawLikelihoodKeys);
        memcpy( &(this->rawLikelihoodKeys[i]), &(this->st_rawLikelihoodKeys), sizeof(int32_t));
      }
      uint8_t rawLikelihoodValues_lengthT = *(inbuffer + offset++);
      if(rawLikelihoodValues_lengthT > rawLikelihoodValues_length)
        this->rawLikelihoodValues = (float*)realloc(this->rawLikelihoodValues, rawLikelihoodValues_lengthT * sizeof(float));
      offset += 3;
      rawLikelihoodValues_length = rawLikelihoodValues_lengthT;
      for( uint8_t i = 0; i < rawLikelihoodValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_rawLikelihoodValues;
      u_st_rawLikelihoodValues.base = 0;
      u_st_rawLikelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_rawLikelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_rawLikelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_rawLikelihoodValues.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_rawLikelihoodValues = u_st_rawLikelihoodValues.real;
      offset += sizeof(this->st_rawLikelihoodValues);
        memcpy( &(this->rawLikelihoodValues[i]), &(this->st_rawLikelihoodValues), sizeof(float));
      }
      uint8_t weightsKeys_lengthT = *(inbuffer + offset++);
      if(weightsKeys_lengthT > weightsKeys_length)
        this->weightsKeys = (int32_t*)realloc(this->weightsKeys, weightsKeys_lengthT * sizeof(int32_t));
      offset += 3;
      weightsKeys_length = weightsKeys_lengthT;
      for( uint8_t i = 0; i < weightsKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_weightsKeys;
      u_st_weightsKeys.base = 0;
      u_st_weightsKeys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_weightsKeys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_weightsKeys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_weightsKeys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_weightsKeys = u_st_weightsKeys.real;
      offset += sizeof(this->st_weightsKeys);
        memcpy( &(this->weightsKeys[i]), &(this->st_weightsKeys), sizeof(int32_t));
      }
      uint8_t weightsValues_lengthT = *(inbuffer + offset++);
      if(weightsValues_lengthT > weightsValues_length)
        this->weightsValues = (int32_t*)realloc(this->weightsValues, weightsValues_lengthT * sizeof(int32_t));
      offset += 3;
      weightsValues_length = weightsValues_lengthT;
      for( uint8_t i = 0; i < weightsValues_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_weightsValues;
      u_st_weightsValues.base = 0;
      u_st_weightsValues.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_weightsValues.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_weightsValues.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_weightsValues.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_weightsValues = u_st_weightsValues.real;
      offset += sizeof(this->st_weightsValues);
        memcpy( &(this->weightsValues[i]), &(this->st_weightsValues), sizeof(int32_t));
      }
      uint8_t statsKeys_lengthT = *(inbuffer + offset++);
      if(statsKeys_lengthT > statsKeys_length)
        this->statsKeys = (char**)realloc(this->statsKeys, statsKeys_lengthT * sizeof(char*));
      offset += 3;
      statsKeys_length = statsKeys_lengthT;
      for( uint8_t i = 0; i < statsKeys_length; i++){
      uint32_t length_st_statsKeys;
      memcpy(&length_st_statsKeys, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_statsKeys; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_statsKeys-1]=0;
      this->st_statsKeys = (char *)(inbuffer + offset-1);
      offset += length_st_statsKeys;
        memcpy( &(this->statsKeys[i]), &(this->st_statsKeys), sizeof(char*));
      }
      uint8_t statsValues_lengthT = *(inbuffer + offset++);
      if(statsValues_lengthT > statsValues_length)
        this->statsValues = (float*)realloc(this->statsValues, statsValues_lengthT * sizeof(float));
      offset += 3;
      statsValues_length = statsValues_lengthT;
      for( uint8_t i = 0; i < statsValues_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_statsValues;
      u_st_statsValues.base = 0;
      u_st_statsValues.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_statsValues.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_statsValues.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_statsValues.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_statsValues = u_st_statsValues.real;
      offset += sizeof(this->st_statsValues);
        memcpy( &(this->statsValues[i]), &(this->st_statsValues), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/InfoEx"; };
    const char * getMD5(){ return "ff8eb30fab8e621cb74743ca03f1f9a0"; };

  };

}
#endif
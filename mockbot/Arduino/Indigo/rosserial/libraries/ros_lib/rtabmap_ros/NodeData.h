#ifndef _ROS_rtabmap_ros_NodeData_h
#define _ROS_rtabmap_ros_NodeData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "rtabmap_ros/Bytes.h"
#include "geometry_msgs/Transform.h"
#include "rtabmap_ros/KeyPoint.h"
#include "sensor_msgs/PointCloud2.h"

namespace rtabmap_ros
{

  class NodeData : public ros::Msg
  {
    public:
      int32_t id;
      int32_t mapId;
      geometry_msgs::Pose pose;
      rtabmap_ros::Bytes image;
      rtabmap_ros::Bytes depth;
      float fx;
      float fy;
      float cx;
      float cy;
      rtabmap_ros::Bytes depth2D;
      geometry_msgs::Transform localTransform;
      uint8_t wordsKeys_length;
      int32_t st_wordsKeys;
      int32_t * wordsKeys;
      uint8_t wordsValues_length;
      rtabmap_ros::KeyPoint st_wordsValues;
      rtabmap_ros::KeyPoint * wordsValues;
      sensor_msgs::PointCloud2 words3DValues;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_mapId;
      u_mapId.real = this->mapId;
      *(outbuffer + offset + 0) = (u_mapId.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mapId.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mapId.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mapId.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mapId);
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->image.serialize(outbuffer + offset);
      offset += this->depth.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_fx;
      u_fx.real = this->fx;
      *(outbuffer + offset + 0) = (u_fx.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fx.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fx.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fx.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fx);
      union {
        float real;
        uint32_t base;
      } u_fy;
      u_fy.real = this->fy;
      *(outbuffer + offset + 0) = (u_fy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fy);
      union {
        float real;
        uint32_t base;
      } u_cx;
      u_cx.real = this->cx;
      *(outbuffer + offset + 0) = (u_cx.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cx.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cx.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cx.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cx);
      union {
        float real;
        uint32_t base;
      } u_cy;
      u_cy.real = this->cy;
      *(outbuffer + offset + 0) = (u_cy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cy);
      offset += this->depth2D.serialize(outbuffer + offset);
      offset += this->localTransform.serialize(outbuffer + offset);
      *(outbuffer + offset++) = wordsKeys_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < wordsKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_wordsKeysi;
      u_wordsKeysi.real = this->wordsKeys[i];
      *(outbuffer + offset + 0) = (u_wordsKeysi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wordsKeysi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wordsKeysi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wordsKeysi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wordsKeys[i]);
      }
      *(outbuffer + offset++) = wordsValues_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < wordsValues_length; i++){
      offset += this->wordsValues[i].serialize(outbuffer + offset);
      }
      offset += this->words3DValues.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_mapId;
      u_mapId.base = 0;
      u_mapId.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mapId.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mapId.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mapId.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mapId = u_mapId.real;
      offset += sizeof(this->mapId);
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->image.deserialize(inbuffer + offset);
      offset += this->depth.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_fx;
      u_fx.base = 0;
      u_fx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->fx = u_fx.real;
      offset += sizeof(this->fx);
      union {
        float real;
        uint32_t base;
      } u_fy;
      u_fy.base = 0;
      u_fy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->fy = u_fy.real;
      offset += sizeof(this->fy);
      union {
        float real;
        uint32_t base;
      } u_cx;
      u_cx.base = 0;
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cx = u_cx.real;
      offset += sizeof(this->cx);
      union {
        float real;
        uint32_t base;
      } u_cy;
      u_cy.base = 0;
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cy = u_cy.real;
      offset += sizeof(this->cy);
      offset += this->depth2D.deserialize(inbuffer + offset);
      offset += this->localTransform.deserialize(inbuffer + offset);
      uint8_t wordsKeys_lengthT = *(inbuffer + offset++);
      if(wordsKeys_lengthT > wordsKeys_length)
        this->wordsKeys = (int32_t*)realloc(this->wordsKeys, wordsKeys_lengthT * sizeof(int32_t));
      offset += 3;
      wordsKeys_length = wordsKeys_lengthT;
      for( uint8_t i = 0; i < wordsKeys_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_wordsKeys;
      u_st_wordsKeys.base = 0;
      u_st_wordsKeys.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_wordsKeys.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_wordsKeys.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_wordsKeys.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_wordsKeys = u_st_wordsKeys.real;
      offset += sizeof(this->st_wordsKeys);
        memcpy( &(this->wordsKeys[i]), &(this->st_wordsKeys), sizeof(int32_t));
      }
      uint8_t wordsValues_lengthT = *(inbuffer + offset++);
      if(wordsValues_lengthT > wordsValues_length)
        this->wordsValues = (rtabmap_ros::KeyPoint*)realloc(this->wordsValues, wordsValues_lengthT * sizeof(rtabmap_ros::KeyPoint));
      offset += 3;
      wordsValues_length = wordsValues_lengthT;
      for( uint8_t i = 0; i < wordsValues_length; i++){
      offset += this->st_wordsValues.deserialize(inbuffer + offset);
        memcpy( &(this->wordsValues[i]), &(this->st_wordsValues), sizeof(rtabmap_ros::KeyPoint));
      }
      offset += this->words3DValues.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/NodeData"; };
    const char * getMD5(){ return "498529da8a5a5ab1121f9dd577cf17be"; };

  };

}
#endif
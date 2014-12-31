#ifndef _ROS_rtabmap_ros_MapData_h
#define _ROS_rtabmap_ros_MapData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/Pose.h"
#include "rtabmap_ros/NodeData.h"

namespace rtabmap_ros
{

  class MapData : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Transform mapToOdom;
      uint8_t poseIDs_length;
      int32_t st_poseIDs;
      int32_t * poseIDs;
      uint8_t poses_length;
      geometry_msgs::Pose st_poses;
      geometry_msgs::Pose * poses;
      uint8_t constraintFromIDs_length;
      int32_t st_constraintFromIDs;
      int32_t * constraintFromIDs;
      uint8_t constraintToIDs_length;
      int32_t st_constraintToIDs;
      int32_t * constraintToIDs;
      uint8_t constraintTypes_length;
      int32_t st_constraintTypes;
      int32_t * constraintTypes;
      uint8_t constraints_length;
      geometry_msgs::Transform st_constraints;
      geometry_msgs::Transform * constraints;
      uint8_t mapIDs_length;
      int32_t st_mapIDs;
      int32_t * mapIDs;
      uint8_t maps_length;
      int32_t st_maps;
      int32_t * maps;
      uint8_t nodes_length;
      rtabmap_ros::NodeData st_nodes;
      rtabmap_ros::NodeData * nodes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->mapToOdom.serialize(outbuffer + offset);
      *(outbuffer + offset++) = poseIDs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < poseIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_poseIDsi;
      u_poseIDsi.real = this->poseIDs[i];
      *(outbuffer + offset + 0) = (u_poseIDsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_poseIDsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_poseIDsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_poseIDsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poseIDs[i]);
      }
      *(outbuffer + offset++) = poses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = constraintFromIDs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < constraintFromIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_constraintFromIDsi;
      u_constraintFromIDsi.real = this->constraintFromIDs[i];
      *(outbuffer + offset + 0) = (u_constraintFromIDsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_constraintFromIDsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_constraintFromIDsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_constraintFromIDsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->constraintFromIDs[i]);
      }
      *(outbuffer + offset++) = constraintToIDs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < constraintToIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_constraintToIDsi;
      u_constraintToIDsi.real = this->constraintToIDs[i];
      *(outbuffer + offset + 0) = (u_constraintToIDsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_constraintToIDsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_constraintToIDsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_constraintToIDsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->constraintToIDs[i]);
      }
      *(outbuffer + offset++) = constraintTypes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < constraintTypes_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_constraintTypesi;
      u_constraintTypesi.real = this->constraintTypes[i];
      *(outbuffer + offset + 0) = (u_constraintTypesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_constraintTypesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_constraintTypesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_constraintTypesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->constraintTypes[i]);
      }
      *(outbuffer + offset++) = constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < constraints_length; i++){
      offset += this->constraints[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = mapIDs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < mapIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_mapIDsi;
      u_mapIDsi.real = this->mapIDs[i];
      *(outbuffer + offset + 0) = (u_mapIDsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mapIDsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mapIDsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mapIDsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mapIDs[i]);
      }
      *(outbuffer + offset++) = maps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < maps_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_mapsi;
      u_mapsi.real = this->maps[i];
      *(outbuffer + offset + 0) = (u_mapsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mapsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mapsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mapsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->maps[i]);
      }
      *(outbuffer + offset++) = nodes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < nodes_length; i++){
      offset += this->nodes[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->mapToOdom.deserialize(inbuffer + offset);
      uint8_t poseIDs_lengthT = *(inbuffer + offset++);
      if(poseIDs_lengthT > poseIDs_length)
        this->poseIDs = (int32_t*)realloc(this->poseIDs, poseIDs_lengthT * sizeof(int32_t));
      offset += 3;
      poseIDs_length = poseIDs_lengthT;
      for( uint8_t i = 0; i < poseIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_poseIDs;
      u_st_poseIDs.base = 0;
      u_st_poseIDs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_poseIDs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_poseIDs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_poseIDs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_poseIDs = u_st_poseIDs.real;
      offset += sizeof(this->st_poseIDs);
        memcpy( &(this->poseIDs[i]), &(this->st_poseIDs), sizeof(int32_t));
      }
      uint8_t poses_lengthT = *(inbuffer + offset++);
      if(poses_lengthT > poses_length)
        this->poses = (geometry_msgs::Pose*)realloc(this->poses, poses_lengthT * sizeof(geometry_msgs::Pose));
      offset += 3;
      poses_length = poses_lengthT;
      for( uint8_t i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(geometry_msgs::Pose));
      }
      uint8_t constraintFromIDs_lengthT = *(inbuffer + offset++);
      if(constraintFromIDs_lengthT > constraintFromIDs_length)
        this->constraintFromIDs = (int32_t*)realloc(this->constraintFromIDs, constraintFromIDs_lengthT * sizeof(int32_t));
      offset += 3;
      constraintFromIDs_length = constraintFromIDs_lengthT;
      for( uint8_t i = 0; i < constraintFromIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_constraintFromIDs;
      u_st_constraintFromIDs.base = 0;
      u_st_constraintFromIDs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_constraintFromIDs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_constraintFromIDs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_constraintFromIDs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_constraintFromIDs = u_st_constraintFromIDs.real;
      offset += sizeof(this->st_constraintFromIDs);
        memcpy( &(this->constraintFromIDs[i]), &(this->st_constraintFromIDs), sizeof(int32_t));
      }
      uint8_t constraintToIDs_lengthT = *(inbuffer + offset++);
      if(constraintToIDs_lengthT > constraintToIDs_length)
        this->constraintToIDs = (int32_t*)realloc(this->constraintToIDs, constraintToIDs_lengthT * sizeof(int32_t));
      offset += 3;
      constraintToIDs_length = constraintToIDs_lengthT;
      for( uint8_t i = 0; i < constraintToIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_constraintToIDs;
      u_st_constraintToIDs.base = 0;
      u_st_constraintToIDs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_constraintToIDs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_constraintToIDs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_constraintToIDs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_constraintToIDs = u_st_constraintToIDs.real;
      offset += sizeof(this->st_constraintToIDs);
        memcpy( &(this->constraintToIDs[i]), &(this->st_constraintToIDs), sizeof(int32_t));
      }
      uint8_t constraintTypes_lengthT = *(inbuffer + offset++);
      if(constraintTypes_lengthT > constraintTypes_length)
        this->constraintTypes = (int32_t*)realloc(this->constraintTypes, constraintTypes_lengthT * sizeof(int32_t));
      offset += 3;
      constraintTypes_length = constraintTypes_lengthT;
      for( uint8_t i = 0; i < constraintTypes_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_constraintTypes;
      u_st_constraintTypes.base = 0;
      u_st_constraintTypes.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_constraintTypes.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_constraintTypes.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_constraintTypes.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_constraintTypes = u_st_constraintTypes.real;
      offset += sizeof(this->st_constraintTypes);
        memcpy( &(this->constraintTypes[i]), &(this->st_constraintTypes), sizeof(int32_t));
      }
      uint8_t constraints_lengthT = *(inbuffer + offset++);
      if(constraints_lengthT > constraints_length)
        this->constraints = (geometry_msgs::Transform*)realloc(this->constraints, constraints_lengthT * sizeof(geometry_msgs::Transform));
      offset += 3;
      constraints_length = constraints_lengthT;
      for( uint8_t i = 0; i < constraints_length; i++){
      offset += this->st_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->constraints[i]), &(this->st_constraints), sizeof(geometry_msgs::Transform));
      }
      uint8_t mapIDs_lengthT = *(inbuffer + offset++);
      if(mapIDs_lengthT > mapIDs_length)
        this->mapIDs = (int32_t*)realloc(this->mapIDs, mapIDs_lengthT * sizeof(int32_t));
      offset += 3;
      mapIDs_length = mapIDs_lengthT;
      for( uint8_t i = 0; i < mapIDs_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_mapIDs;
      u_st_mapIDs.base = 0;
      u_st_mapIDs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_mapIDs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_mapIDs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_mapIDs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_mapIDs = u_st_mapIDs.real;
      offset += sizeof(this->st_mapIDs);
        memcpy( &(this->mapIDs[i]), &(this->st_mapIDs), sizeof(int32_t));
      }
      uint8_t maps_lengthT = *(inbuffer + offset++);
      if(maps_lengthT > maps_length)
        this->maps = (int32_t*)realloc(this->maps, maps_lengthT * sizeof(int32_t));
      offset += 3;
      maps_length = maps_lengthT;
      for( uint8_t i = 0; i < maps_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_maps;
      u_st_maps.base = 0;
      u_st_maps.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_maps.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_maps.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_maps.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_maps = u_st_maps.real;
      offset += sizeof(this->st_maps);
        memcpy( &(this->maps[i]), &(this->st_maps), sizeof(int32_t));
      }
      uint8_t nodes_lengthT = *(inbuffer + offset++);
      if(nodes_lengthT > nodes_length)
        this->nodes = (rtabmap_ros::NodeData*)realloc(this->nodes, nodes_lengthT * sizeof(rtabmap_ros::NodeData));
      offset += 3;
      nodes_length = nodes_lengthT;
      for( uint8_t i = 0; i < nodes_length; i++){
      offset += this->st_nodes.deserialize(inbuffer + offset);
        memcpy( &(this->nodes[i]), &(this->st_nodes), sizeof(rtabmap_ros::NodeData));
      }
     return offset;
    }

    const char * getType(){ return "rtabmap_ros/MapData"; };
    const char * getMD5(){ return "ded2f84465e3edec467a22a2cd163a96"; };

  };

}
#endif
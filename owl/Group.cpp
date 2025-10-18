// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "Group.h"
#include "Context.h"

namespace owl {
  
  // ------------------------------------------------------------------
  // Group::DeviceData
  // ------------------------------------------------------------------
  
  /*! constructor - pass-through to parent class */
  Group::DeviceData::DeviceData(const DeviceContext::SP &device)
    : RegisteredObject::DeviceData(device)
  {}

  // ------------------------------------------------------------------
  // Group
  // ------------------------------------------------------------------
  
  /*! constructor, that registers this group in the context's registry */
  Group::Group(Context *const context,
               ObjectRegistry &registry)
    : RegisteredObject(context,registry)
  {}

  /*! creates the device-specific data for this group */
  RegisteredObject::DeviceData::SP Group::createOn(const DeviceContext::SP &device) 
  {
    return std::make_shared<DeviceData>(device);
  }
  
  /*! pretty-printer, for printf-debugging */
  std::string Group::toString() const
  {
    return "Group";
  }

  // ------------------------------------------------------------------
  // GeomGroup
  // ------------------------------------------------------------------

  /*! constructor for given number of chilren, will allocate the SBT
    range for those children (or 1 record if geometry contribution is disabled.)*/
  GeomGroup::GeomGroup(Context *const context,
                       size_t numChildren)
    : Group(context,context->groups),
      geometries(numChildren)      
  {
    if (context->perGeometrySBTRecordsDisabled)
      sbtOffset = context->sbtRangeAllocator->alloc(1);
    else 
      sbtOffset = context->sbtRangeAllocator->alloc(numChildren);
  }
  
  /*! destructor that releases the SBT range used by this group */
  GeomGroup::~GeomGroup()
  {
    if (context->perGeometrySBTRecordsDisabled)
      context->sbtRangeAllocator->release(sbtOffset,1);
    else
      context->sbtRangeAllocator->release(sbtOffset,geometries.size());
  }


  /*! set given child ID to given geometry */
  void GeomGroup::setChild(size_t childID, Geom::SP child)
  {
    assert(childID < geometries.size());
    geometries[childID] = child;
  }
  
  /*! pretty-printer, for printf-debugging */
  std::string GeomGroup::toString() const
  {
    return "GeomGroup";
  }
  
} // ::owl

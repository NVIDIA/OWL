// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Group.h"
#include "SphereGeom.h"

namespace owl {

  /*! a geometry group / BLAS over sphere
      primitives. This Group may only be built over UserGeom's */
  struct SphereGeomGroup : public GeomGroup {

    /*! constructor - passthrough to parent class */
    SphereGeomGroup(Context *const context, size_t numChildren, unsigned int buildFlags);
    
    /*! pretty-printer, for printf-debugging */
    std::string toString() const override;

    void buildAccel(LaunchParams::SP launchParams = nullptr) override;
    void refitAccel(LaunchParams::SP launchParams = nullptr) override;

    /*! (re-)compute the Group::bounds[2] information for motion blur
      - ie, our _parent_ node may need this */
    void updateMotionBounds();

    /*! low-level accel structure builder for given device */
    template<bool FULL_REBUILD>
    void buildAccelOn(const DeviceContext::SP &device);

    constexpr static unsigned int defaultBuildFlags = 
        OPTIX_BUILD_FLAG_PREFER_FAST_TRACE |
        OPTIX_BUILD_FLAG_ALLOW_COMPACTION;

    protected:
    const unsigned int buildFlags;
  };

} // ::owl

// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Group.h"
#include "UserGeom.h"

namespace owl {

  /*! a geometry group / BLAS over user-defined/custom
      primitives. This Group may only be built over UserGeom's */
  struct UserGeomGroup : public GeomGroup {

    UserGeomGroup(Context *const context,
                   size_t numChildren,
                   unsigned int buildFlags);
    virtual std::string toString() const { return "UserGeomGroup"; }

    /*! build() and refit() share most of their code; this functoin
        does all that code, with only minor specialization based on
        build vs refit */
    void buildOrRefit(bool FULL_REBUILD);
    
    void buildAccel(LaunchParams::SP launchParams = nullptr) override;
    void refitAccel(LaunchParams::SP launchParams = nullptr) override;

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

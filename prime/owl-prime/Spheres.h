// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "owl-prime/Context.h"
#include "primer-common/Geom.h"
#include <owl/helper/cuda.h>
#include <owl/owl_host.h>

namespace op {

  using primer::Ray;
  using primer::Hit;

  struct Context;

  /*! a type of geometry that, on the device-end side, will be handled
      by an OWL user geometry type */
  struct UserGeom : public primer::Geom {
    UserGeom(Context *context, uint64_t geomDataValue)
      : primer::Geom(geomDataValue),
        context(context)
    {}
    OWLGeom   geom         = 0;
    Context  *context      = 0;
  };
  
  struct Spheres : public UserGeom {

    struct SBTData {
      uint64_t geomDataValue;
      float4  *spheres;
    };
    
    Spheres(Context *context,
            uint64_t geomDataValue,
            OWLBuffer spheresBuffer, int numSpheres);

    OWLBuffer spheresBuffer = 0;
    int       numSpheres    = 0;

    static OWLVarDecl variables[];
  };
  
} // ::op

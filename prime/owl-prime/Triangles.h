// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Geom.h"
#include <owl/helper/cuda.h>
#include <owl/owl_host.h>

namespace op {

  using primer::Ray;
  using primer::Hit;

  struct Context;
  
  struct Triangles : public primer::Geom {

    struct SBTData {
      uint64_t geomDataValue;
    };
    
    Triangles(Context *context,
              uint64_t geomDataValue,
              OWLBuffer vertexBuffer, int numVertices,
              OWLBuffer indexBuffer, int numIndices);
    
    OWLBuffer vertexBuffer = 0;
    int       numVertices  = 0;
    OWLBuffer indexBuffer  = 0;
    int       numIndices   = 0;
    OWLGeom   geom         = 0;
    Context  *context      = 0;

    static OWLVarDecl variables[];
  };
  
} // ::op

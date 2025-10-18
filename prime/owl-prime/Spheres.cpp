// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "Spheres.h"
#include "Context.h"

namespace op {

  OWLVarDecl Spheres::variables[]
  = {
     { "geomDataValue", OWL_INT, OWL_OFFSETOF(Spheres::SBTData,geomDataValue) },
     { "spheres", OWL_BUFPTR, OWL_OFFSETOF(Spheres::SBTData,spheres) },
     { nullptr }
  };
  
  Spheres::Spheres(Context *context,
                   uint64_t geomDataValue,
                   OWLBuffer spheresBuffer,
                   int numSpheres)
    : UserGeom(context,geomDataValue),
      spheresBuffer(spheresBuffer),
      numSpheres(numSpheres)
  {
    geom = owlGeomCreate(context->owl,
                         context->spheresGeomType);
    owlGeomSetPrimCount(geom,numSpheres);
    owlGeomSet1ul(geom,"geomDataValue",geomDataValue);
    owlGeomSetBuffer(geom,"spheres",spheresBuffer);
  }

} // ::op

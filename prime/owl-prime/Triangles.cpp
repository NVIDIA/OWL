// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "owl-prime/Triangles.h"
#include "owl-prime/Context.h"

namespace op {

  OWLVarDecl Triangles::variables[]
  = {
     { "geomDataValue", OWL_LONG, OWL_OFFSETOF(Triangles::SBTData,geomDataValue) },
     { nullptr }
  };
  
  Triangles::Triangles(Context *context,
                       /*! user provided data value to be stored
                               in the hit */
                       uint64_t geomDataValue,
                       OWLBuffer vertexBuffer,
                       int numVertices,
                       OWLBuffer indexBuffer,
                       int numIndices)
    : primer::Geom(geomDataValue),
      context(context),
      vertexBuffer(vertexBuffer),
      numVertices(numVertices),
      indexBuffer(indexBuffer),
      numIndices(numIndices)
  {
    geom = owlGeomCreate(context->owl,
                         context->meshGeomType);
    owlTrianglesSetVertices(geom,vertexBuffer,
                            numVertices,sizeof(vec3f),0);
    owlTrianglesSetIndices(geom,indexBuffer,
                           numIndices,sizeof(vec3i),0);
    owlGeomSet1l(geom,"geomDataValue",geomDataValue);
  }

} // ::op

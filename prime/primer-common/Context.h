// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Ray.h"

namespace primer {

  struct Model;
  struct Geom;
  struct Group;
  
  struct Context {
    virtual ~Context() {}
    
    /*! create a mesh from vertex array and index array */
    virtual Geom *createTriangles(uint64_t userID,
                                  /* vertex array */
                                  const vec3f *vertices,
                                  size_t numVertices,
                                  size_t sizeOfVertexInBytes,
                                  /* index array */
                                  const vec3i *indices,
                                  size_t numIndices,
                                  size_t sizeOfIndexStructInBytes) = 0;

    virtual Group *createGroup(std::vector<OPGeom> &geoms) = 0;
  

    virtual Model *createModel(const std::vector<OPGroup>  &groups,
                               const std::vector<affine3f> &xfms) = 0;
    
    static Context *createOffloadContext(int gpuID);
    static Context *createEmbreeContext();

    /*! enables logging/debugging messages if true, suppresses them if
      false */
    static bool logging;
  };
  
#define LOG(a) if (Context::logging) std::cout << OWL_TERMINAL_LIGHT_BLUE << a << OWL_TERMINAL_DEFAULT << std::endl;

}

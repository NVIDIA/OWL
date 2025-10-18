// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "../s05-rtow/Materials.h"

using namespace owl;

struct LambertianTriangleMesh {
  /*! for now, let's use a single material for all pyramid triangles
      ... .*/
  Lambertian *material;
  /* the vertex and index arrays for the triangle mesh */
  vec3f *vertex;
  vec3i *index;
};

struct RayGenData
{
  OptixTraversableHandle world;
  uint32_t *fbPtr;
  vec2i     fbSize;
  
  struct {
    vec3f origin;
    vec3f lower_left_corner;
    vec3f horizontal;
    vec3f vertical;
  } camera; 
};

struct MissProgData
{
  /* nothing */
};


// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include <owl/owl.h>
#include <owl/owl_device_buffer.h>
#include <owl/common/math/vec.h>
#include <cuda_runtime.h>

using namespace owl;

const int NUM_TEXTURE_SETS = 4;

/* variables for the triangle mesh geometry */
struct TrianglesGeomData
{
  /*! array/buffer of vertex indices */
  vec4i *index;
  /*! array/buffer of vertex positions */
  vec3f *vertex;
  /*! texture coordinates */
  vec2f *texCoord;
  /* texture object */
  owl::device::Buffer textureSets;
};

struct Globals {
  float time;
  int deviceIndex;
  int deviceCount;
};

/* variables for the ray generation program */
struct RayGenData
{
  uint32_t *fbPtr;
  vec2i  fbSize;
  OptixTraversableHandle world;

  vec3f lightDir;
  
  struct {
    vec3f pos;
    vec3f dir_00;
    vec3f dir_du;
    vec3f dir_dv;
  } camera;
};

/* variables for the miss program */
struct MissProgData
{
  vec3f  color0;
  vec3f  color1;
};


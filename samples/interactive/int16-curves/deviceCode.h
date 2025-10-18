// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include <owl/owl.h>
#include "owl/common/math/LinearSpace.h"
#include <owl/common/math/vec.h>
#include <cuda_runtime.h>

using namespace owl;

#define RADIANCE_RAY_TYPE 0
#define SHADOW_RAY_TYPE   1

#ifdef __CUDA_ARCH__
typedef owl::RayT<0,2> RadianceRay;
typedef owl::RayT<1,2> ShadowRay;
#endif

struct BasicLight
{
  vec3f pos;
  vec3f color;
};

struct Material {
  vec3f Kd, Ks, Ka;
  float phong_exp;
  vec3f reflectivity;
};

struct CurvesGeomData
{
  /*! color at the endpoints, to demonstrate interpolation */
  vec3f color0, color1;
  Material material;
};

/* variables for the ray generation program */
struct RayGenData
{
  uint32_t *fbPtr;
  vec2i  fbSize;
  OptixTraversableHandle world;

  struct {
    vec3f pos;
    vec3f dir_00;
    vec3f dir_du;
    vec3f dir_dv;
    float aperture_radius;
    float focal_scale;
  } camera;
};

struct LaunchParams
{
  int numLights;
  BasicLight *lights;
  vec3f ambient_light_color;
  float scene_epsilon;
  OptixTraversableHandle world;
  float4   *accumBuffer;
  int       accumID;
};

/* variables for the miss program */
struct MissProgData
{
  vec3f  bg_color;
};


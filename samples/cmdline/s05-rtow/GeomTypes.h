// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "Materials.h"

namespace owl {

  // ==================================================================
  /* the raw geometric shape of a sphere, without material - this is
     what goes into intersection and bounds programs */
  // ==================================================================
  struct Sphere {
    vec3f center;
    float radius;
  };

  // ==================================================================
  /* the three actual primitive types created by fusing material data
     and geometry data */
  // ==================================================================

  struct MetalSphere {
    Sphere sphere;
    Metal  material;
  };
  struct DielectricSphere {
    Sphere sphere;
    Dielectric material;
  };
  struct LambertianSphere {
    Sphere sphere;
    Lambertian material;
  };

  // ==================================================================
  /* the three actual "Geoms" that each consist of multiple prims of
     same type (this is what optix6 would have called the "geometry
     instance" */
  // ==================================================================

  struct MetalSpheresGeom {
    MetalSphere *prims;
  };
  struct DielectricSpheresGeom {
    DielectricSphere *prims;
  };
  struct LambertianSpheresGeom {
    LambertianSphere *prims;
  };

  // ==================================================================
  /* and finally, input for raygen and miss programs */
  // ==================================================================
  struct RayGenData
  {
    uint32_t *fbPtr;
    vec2i  fbSize;
    OptixTraversableHandle world;
    int sbtOffset;

    struct {
      vec3f origin;
      vec3f lower_left_corner;
      vec3f horizontal;
      vec3f vertical;
    } camera;
  };

  struct MissProgData
  {
    /* nothing in this example */
  };

}

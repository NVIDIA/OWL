// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Materials.h"
#include "Camera.h"

#define HAVE_SHADING_NORMALS 1

namespace samples {
  namespace device {
    
    struct Triangle {
      vec3f A, B, C;
#if HAVE_SHADING_NORMALS
      vec3f Na,Nb,Nc;
#endif
    };

    struct Scene {
      vec3f *fb;
      vec2i  fbSize;
      int    numSamplesPerPixel;
      int    maxPathLength;
      Triangle *triangles;
      Material *materials;
      affine3f *transforms;
      int      *materialIDs;
      Camera camera;
    };
    
  } // ::device
  
  struct World {
    std::vector<Material> materials;

    int addMaterial(const Material &material);
    
    /*! add given sphere */
    void addSphere(const vec3f center,
                   const float radius,
                   int material);
    static int sphereRecDepth;
    void finalize();

  private:
    /*! do given number of recursive subdivs on given spherical
        triangle, and add resuting triangles to scene */
    void addSphericalTriangle(int recDepth,
                              const vec3f &a,
                              const vec3f &b,
                              const vec3f &c);
    
    /*! add a _tessellated_ sphere, using given number of recursive
      subdivisions of a spherical triangle */ 
    void addSphere(const vec3f center,
                   const float radius,
                   int material,
                   int recDepth);

  public:
    // triangles for the (one) tessellated sphere
    std::vector<device::Triangle> triangles;
    // intance transforms
    std::vector<affine3f> transforms;
    // material ID per instance
    std::vector<int> materialIDs;
    OPModel   model   = nullptr;
    OPContext context = nullptr;
  };

  using device::Camera;
  
  /*! create the RTOW test scene */
  std::shared_ptr<World> createScene(Random &random);

}

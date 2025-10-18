// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include <owl/owl_prime.h>

#include <cuda_runtime.h>
#include <random>
#include <owl/common/math/random.h>
#include <owl/common/math/AffineSpace.h>

namespace samples {
  using namespace owl;
  using namespace owl::common;

  namespace device {
    struct Camera {
      inline Camera() {}
      inline Camera(const vec3f &lookfrom,
                    const vec3f &lookat,
                    const vec3f &vup, 
                    float vfov,
                    float aspect,
                    float aperture,
                    float focus_dist);
      

      inline __both__ Ray generateRay(float s, float t,
                                      Random &random);

      vec3f origin;
      vec3f lower_left_corner;
      vec3f horizontal;
      vec3f vertical;
      vec3f u, v, w;
      float lens_radius;
    };
  
    Camera::Camera(const vec3f &lookfrom,
                   const vec3f &lookat,
                   const vec3f &vup, 
                   float vfov,
                   float aspect,
                   float aperture,
                   float focus_dist) 
    { // vfov is top to bottom in degrees
      lens_radius = aperture / 2.0f;
      float theta = vfov * ((float)M_PI) / 180.0f;
      float half_height = tan(theta / 2.0f);
      float half_width = aspect * half_height;
      origin = lookfrom;
      w = normalize(lookfrom - lookat);
      u = normalize(cross(vup, w));
      v = cross(w, u);
      lower_left_corner = origin - half_width * focus_dist*u - half_height * focus_dist*v - focus_dist * w;
      horizontal = 2.0f*half_width*focus_dist*u;
      vertical = 2.0f*half_height*focus_dist*v;
    }

    inline __both__ Ray Camera::generateRay(float s, float t,
                                            Random &random) 
    {
      const vec3f rd = lens_radius * random_in_unit_disk(random);
      const vec3f lens_offset = u * rd.x + v * rd.y;
      const vec3f origin = this->origin + lens_offset;
      const vec3f direction
        = lower_left_corner
        + s * horizontal
        + t * vertical
        - origin;
      
      Ray ray;
      ray.origin = origin;
      ray.direction = direction;
      ray.tmin = 0.f;
      ray.tmax = INFINITY;
      return ray;
    }
  }

}


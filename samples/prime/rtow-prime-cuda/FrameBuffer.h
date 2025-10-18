// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Materials.h"

namespace samples {
  
  struct FrameBuffer {
    FrameBuffer(const vec2i &size)
      : size(size), pixels(size.x*size.y)
    {}
    
    const vec2i        size;
    std::vector<vec3f> pixels;
  };

  void savePNG(const std::string &fileName,
               FrameBuffer &image);
  
}

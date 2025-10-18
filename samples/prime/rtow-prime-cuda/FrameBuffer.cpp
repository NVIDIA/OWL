// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "FrameBuffer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace samples {
  
  unsigned char to255(float f)
  {
    if (f <= 0.f) return 0;
    if (f >= 1.f) return 255;
    return (unsigned char)(f*255.9f);
  }

  void savePNG(const std::string &fileName,
               FrameBuffer &image)
  {
    std::vector<unsigned char> rgba;
    for (int iy=image.size.y-1;iy>=0;--iy) 
      for (int ix=0;ix<image.size.x;ix++) {
        vec3f pixel = image.pixels[ix+image.size.x*iy];
        rgba.push_back(to255(pixel.x));
        rgba.push_back(to255(pixel.y));
        rgba.push_back(to255(pixel.z));
        rgba.push_back(255);
      }
    std::cout << "#owl-prime.rtWeekend: writing image " << fileName << std::endl;
    stbi_write_png(fileName.c_str(),image.size.x,image.size.y,4,
                   rgba.data(),image.size.x*sizeof(uint32_t));
  }

}

// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include <owl/common/math/vec.h>

namespace owl {
  namespace common {
    namespace array2D {
    
      inline int linear(const vec2i &ID, const vec2i &dims)
      { return ID.x + dims.x*ID.y; }

      template<typename Lambda>
      inline void for_each(const vec2i &dims, const Lambda &lambda)
      {
        for (int iy=0;iy<dims.y;iy++)
          for (int ix=0;ix<dims.x;ix++)
            lambda(vec2i(ix,iy));
      }

      template<typename Lambda>
      inline void for_each(const vec2i &begin,
                           const vec2i &end,
                           const Lambda &lambda)
      {
        for (int iy=begin.y;iy<end.y;iy++)
          for (int ix=begin.x;ix<end.x;ix++)
            lambda(vec2i(ix,iy));
      }

      template<typename Lambda>
      inline void parallel_for(const vec2i &dims, const Lambda &lambda)
      {
        owl::common::parallel_for(dims.x*dims.y,[&](int index){
            lambda(vec2i(index%dims.x,index/dims.x));
          });
      }
      
      template<typename Lambda>
      inline void serial_for(const vec2i &dims, const Lambda &lambda)
      {
        owl::common::serial_for(dims.x*dims.y,[&](int index){
            lambda(vec2i(index%dims.x,index/dims.x));
          });
      }
    
      template<typename Lambda>
      inline void parallel_for_blocked(const vec2i &dims,
                                       const vec2i &blockSize,
                                       const Lambda &lambda)
      {
        const vec2i numBlocks = divRoundUp(dims,blockSize);
        array2D::parallel_for
          (numBlocks,[&](const vec2i &block){
                       const vec2i begin = block*blockSize;
                       const vec2i end   = min(begin+blockSize,dims);
                       lambda(begin,end);
                     });
      }
    } // owl::common::array2D
  } // owl::common
} // owl

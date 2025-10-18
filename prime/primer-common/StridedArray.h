// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

namespace primer {
  
  /*! helper class to allow c-style array access to strided arrays
      (primarily used for on-the-fly SoA<->AoS conversions */
  template<typename T>
  struct StridedArray {
    StridedArray(T *base, size_t stride) : base(base), stride(stride) {}
    inline operator bool() const { return base != nullptr; }
    
    inline T &operator[](size_t idx)
    {
      uint8_t *ptr = (uint8_t*)base;
      ptr += stride*idx;
      return *(T*)ptr;
    }
    
    T *base;
    size_t stride;
  };
}

  

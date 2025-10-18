// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



/*! \file optix/common.h Creates a common set of includes, #defines,
  and helpers that will be visible across _all_ files, both host _and_
  device */

#pragma once

#include <owl/common/math/vec.h>
#include <owl/common/math/box.h>
#include <owl/common/math/AffineSpace.h>

#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <typeinfo>
#include <mutex>
#include <atomic>
#include <sstream>

namespace owl {
  
  using owl::common::vec2uc;
  using owl::common::vec3uc;
  using owl::common::vec4uc;
  
  using owl::common::vec2f;
  using owl::common::vec3f;
  using owl::common::vec4f;
  
  using owl::common::vec2i;
  using owl::common::vec3i;
  using owl::common::vec4i;
  
  using owl::common::vec2ui;
  using owl::common::vec3ui;
  using owl::common::vec4ui;
  
  using owl::common::vec2l;
  using owl::common::vec3l;
  using owl::common::vec4l;
  
  using owl::common::vec2ul;
  using owl::common::vec3ul;
  using owl::common::vec4ul;
  
  using owl::common::box3f;
  using owl::common::linear3f;
  using owl::common::affine3f;

  using owl::common::prettyNumber;
  using owl::common::prettyDouble;
  
  template<size_t alignment>
  inline size_t smallestMultipleOf(size_t unalignedSize)
  {
    const size_t numBlocks = (unalignedSize+alignment-1)/alignment;
    return numBlocks*alignment;
  }
  
  inline void *addPointerOffset(void *ptr, size_t offset)
  {
    if (ptr == nullptr) return nullptr;
    return (void*)((unsigned char *)ptr + offset);
  }
    
}

#define IGNORING_THIS() std::cout << OWL_TERMINAL_YELLOW << "## ignoring " << __PRETTY_FUNCTION__ << OWL_TERMINAL_DEFAULT << std::endl;
  

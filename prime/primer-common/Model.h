// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Ray.h"
#include "primer-common/Context.h"
#include "primer-common/StridedArray.h"

namespace primer {
  using namespace owl::common;
  
  struct Model {

    virtual void trace(Ray *rays,
                       Hit *hits,
                       int  numRaysAndHits,
                       int *activeRayIndices,
                       int  numActice,
                       OPTraceFlags flags) = 0;

    virtual void build() {}

    Context *context;
  };
  
}

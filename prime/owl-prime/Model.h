// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Model.h"
#include <owl/owl.h>
               
namespace op {
  using namespace owl::common;
  
  using primer::Ray;
  using primer::Hit;
  
  struct Context;
  
  struct Model : public primer::Model {

    Model(Context *context,
          const std::vector<OPGroup>  &groups,
          const std::vector<affine3f> &xfms);

    void trace(Ray *rays,
               Hit *hits,
               int  numRaysAndHits,
               int *activeRayIndices,
               int  numActiveIndices,
               OPTraceFlags flags) override;
    
    void build() override;
    
    Context  *context      = 0;
    OWLGroup  handle       = 0;
  };

} // ::op

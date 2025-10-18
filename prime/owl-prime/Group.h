// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Group.h"
#include <owl/helper/cuda.h>
#include <owl/owl_host.h>

namespace op {

  struct Context;
  
  struct Group : public primer::Group {
    
    Group(Context *context,
          std::vector<OPGeom> &geoms);
    ~Group();
    
    /*! pretty-printer (mostly for debugging) */
    std::string toString() const override
    { return "op::Group{numGeoms="+std::to_string(geoms.size())+"}"; }
    
    Context *context = 0;
    OWLGroup trianglesGroup = 0;
    OWLGroup userGroup= 0;
  };
  
} // ::op

// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Ray.h"
#include "primer-common/Object.h"
#include "primer-common/Context.h"

namespace primer {

  /*! abstraction for a geometry (triangle mesh, set of spheres,
      etc). this is the primer-common version that backends will
      likely override */
  struct Geom : public Object {
    Geom(uint64_t geomDataValue) : geomDataValue(geomDataValue) {}

    /*! pretty-printer (mostly for debugging) */
    std::string toString() const override { return "primer::Geom (abstract)"; }
    
    uint64_t const geomDataValue;
  };

}

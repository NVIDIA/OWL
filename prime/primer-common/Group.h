// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Geom.h"

namespace primer {

  /*! a group is nothing but a list of geoms (that can be
      instantiated).if a logical groups on the primer level contains
      geometries of multiple different types it _may_ require multiple
      different groups and instances on the actual implementation
      level, but that'll be implementation speicific. this version is
      (intentionally) still abstract, so devices have to implement
      this on their own */
  struct Group : Object {
    Group(std::vector<OPGeom> &geoms)
      : geoms(geoms)
    {}

    std::vector<OPGeom> geoms;
  };
  
}

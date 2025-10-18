// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "primer-common/Ray.h"

namespace primer {

  /*! base class for any kind of primer object that the user may
      create; be it a mesh, a user geometry, or a group */
  struct Object {
    
    /*! pretty-printer (mostly for debugging) */
    virtual std::string toString() const = 0;
  };
  
}

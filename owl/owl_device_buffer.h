// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "owl/owl_host.h"

namespace owl {
  namespace device {
    /*! a *device*-side buffer; ie, this is the type that OWL will
        fill in on the devise side if a paramter (or buffer of) type
        buffers is created on the host */
    struct Buffer {
      OWLDataType type;
      size_t      count;
      void       *data;
    };
    
  }
}

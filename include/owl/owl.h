// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

/* since CUDA can actually understand full C++ we'll have the
   host-side API included on both host and device side; this allows the
  user's device programs to include shared haeders that use host-side
  OWL types like OWLContext etc */
#include "owl_host.h"

/* since the device API contains CUDA types such as float4 etc we'll
   include this only for files compiles with nvcc */
#ifdef __CUDACC__
# include "owl_device.h"
#endif


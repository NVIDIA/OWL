// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include <owl/owl.h>
#include <owl/common/math/vec.h>

using namespace owl;

struct RayGenData
{
  uint32_t *fbPtr;
  vec2i  fbSize;
  vec3f  color0;
  vec3f  color1;
};


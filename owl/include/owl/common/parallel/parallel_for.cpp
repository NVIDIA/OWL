// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "gdt/parallel/parallel_for.h"

namespace owl {
  namespace common {

    tbb::task_scheduler_init tbb_init(tbb::task_scheduler_init::automatic);
  
  } // ::owl::common
} // ::owl

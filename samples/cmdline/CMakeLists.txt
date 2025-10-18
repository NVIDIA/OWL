# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# ---------------------------------------------------------------------------
# the default "tutorial-style" samples that intoduce, step by step,
# individual capabililies like creating a raygen (s00), creating a
# triangle mesh (s01), ... instancing (s08), etc.
# ---------------------------------------------------------------------------
file(GLOB samples RELATIVE ${CMAKE_CURRENT_LIST_DIR} "s??-*")

foreach(sample ${samples})
  add_subdirectory(${sample})
endforeach()

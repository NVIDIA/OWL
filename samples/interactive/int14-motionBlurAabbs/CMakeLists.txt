# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int14-motionBlurAabbs-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int14-motionBlurAabbs hostCode.cpp)
target_link_libraries(int14-motionBlurAabbs
  PRIVATE
    int14-motionBlurAabbs-ptx
    owl_viewer
)

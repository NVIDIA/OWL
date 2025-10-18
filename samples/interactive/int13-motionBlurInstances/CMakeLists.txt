# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int13-motionBlurBoxes-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int13-motionBlurBoxes hostCode.cpp)
target_link_libraries(int13-motionBlurBoxes
  PRIVATE
    int13-motionBlurBoxes-ptx
    owl_viewer
)

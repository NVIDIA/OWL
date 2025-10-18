# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int11-rotatingBoxes-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int11-rotatingBoxes hostCode.cpp)
target_link_libraries(int11-rotatingBoxes
  PRIVATE
    int11-rotatingBoxes-ptx
    owl_viewer
)

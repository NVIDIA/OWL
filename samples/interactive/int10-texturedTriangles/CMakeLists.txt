# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int10-texturedTriangles-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int10-texturedTriangles hostCode.cpp)
target_link_libraries(int10-texturedTriangles
  PRIVATE
    int10-texturedTriangles-ptx
    owl_viewer
)

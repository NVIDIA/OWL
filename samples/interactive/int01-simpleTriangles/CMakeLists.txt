# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int01-simpleTriangles-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int01-simpleTriangles hostCode.cpp)
target_link_libraries(int01-simpleTriangles
  PRIVATE
    int01-simpleTriangles-ptx
    owl_viewer
)

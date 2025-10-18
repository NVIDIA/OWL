# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int06-rtow-mixedGeometries-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int06-rtow-mixedGeometries hostCode.cpp)
target_link_libraries(int06-rtow-mixedGeometries
  PRIVATE
    int06-rtow-mixedGeometries-ptx
    owl_viewer
)

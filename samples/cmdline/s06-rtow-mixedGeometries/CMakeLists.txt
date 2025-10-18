# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample06-rtow-mixedGeometries-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample06-rtow-mixedGeometries hostCode.cpp)
target_link_libraries(sample06-rtow-mixedGeometries
  PRIVATE
    sample06-rtow-mixedGeometries-ptx
    owl::owl
    stb_image
)
add_test(sample06-rtow-mixedGeometries
  ${CMAKE_BINARY_DIR}/sample06-rtow-mixedGeometries)

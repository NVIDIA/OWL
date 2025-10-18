# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample11-textures-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample11-textures hostCode.cpp)
target_link_libraries(sample11-textures
  PRIVATE
    sample11-textures-ptx
    owl::owl
    stb_image
)
add_test(sample11-textures ${CMAKE_BINARY_DIR}/sample11-textures)

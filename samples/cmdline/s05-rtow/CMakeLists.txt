# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample05-rtow-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample05-rtow hostCode.cpp)
target_link_libraries(sample05-rtow
  PRIVATE
    sample05-rtow-ptx
    owl::owl
    stb_image
)
add_test(sample05-rtow
  ${CMAKE_BINARY_DIR}/sample05-rtow)

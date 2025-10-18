# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample09-motionBlurSimpleTriangles-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample09-motionBlurSimpleTriangles hostCode.cpp)
target_link_libraries(sample09-motionBlurSimpleTriangles
  PRIVATE
    sample09-motionBlurSimpleTriangles-ptx
    owl::owl
    stb_image
)
add_test(sample09-motionBlurSimpleTriangles
  ${CMAKE_BINARY_DIR}/sample09-motionBlurSimpleTriangles)

# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample01-simpleTriangles-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample01-simpleTriangles hostCode.cpp)
target_link_libraries(sample01-simpleTriangles
  PRIVATE
    sample01-simpleTriangles-ptx
    owl::owl
    stb_image
)
add_test(sample01-simpleTriangles ${CMAKE_BINARY_DIR}/sample01-simpleTriangles)

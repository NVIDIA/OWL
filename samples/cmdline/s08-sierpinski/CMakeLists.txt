# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample08-sierpinski-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample08-sierpinski hostCode.cpp)
target_link_libraries(sample08-sierpinski
  PRIVATE
    sample08-sierpinski-ptx
    owl::owl
    stb_image
)
add_test(sample08-sierpinski ${CMAKE_BINARY_DIR}/sample08-sierpinski)

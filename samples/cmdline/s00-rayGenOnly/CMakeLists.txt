# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample00-rayGenOnly-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample00-rayGenOnly hostCode.cpp)
target_link_libraries(sample00-rayGenOnly
  PRIVATE
    sample00-rayGenOnly-ptx
    owl::owl
    stb_image
)
add_test(sample00-rayGenOnly ${CMAKE_BINARY_DIR}/sample00-rayGenOnly)

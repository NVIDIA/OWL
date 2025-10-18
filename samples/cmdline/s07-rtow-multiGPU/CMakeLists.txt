# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    sample07-rtow-multiGPU-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(sample07-rtow-multiGPU hostCode.cpp)
target_link_libraries(sample07-rtow-multiGPU
  PRIVATE
    sample07-rtow-multiGPU-ptx
    owl::owl
    stb_image
)
add_test(sample07-rtow-multiGPU ${CMAKE_BINARY_DIR}/sample07-rtow-multiGPU)

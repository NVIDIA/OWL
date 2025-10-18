# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
  sample10-launch3D-ptx
  
  PTX_LINK_LIBRARIES
  owl::owl
  
  SOURCES
  deviceCode.cu)

add_executable(sample10-launch3D
  hostCode.cu
  )
set_property(TARGET sample10-launch3D PROPERTY CUDA_ARCHITECTURES OFF) 

target_link_libraries(sample10-launch3D
  PRIVATE
  sample10-launch3D-ptx
  owl
  stb_image
  )

add_test(sample10-launch3D
  ${CMAKE_BINARY_DIR}/sample10-launch3D)

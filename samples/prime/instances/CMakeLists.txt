# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(opSampleInstances
  instances.cu
  )

target_link_libraries(opSampleInstances
  owl::owl_prime
  stb_image
  )
  
add_test(opSampleInstances ${CMAKE_BINARY_DIR}/opSampleInstances)


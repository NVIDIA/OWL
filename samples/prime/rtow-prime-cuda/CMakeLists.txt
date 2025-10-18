# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(opWeekendCuda
  rtow-render-cuda.cu
  FrameBuffer.cpp
  World.cpp
  )

target_link_libraries(opWeekendCuda
  owl::owl_prime
  stb_image
  )
  
add_test(opWeekendCuda ${CMAKE_BINARY_DIR}/opWeekendCuda)


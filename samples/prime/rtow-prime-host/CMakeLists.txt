# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_executable(opWeekendHost
  rtow-render-host.cpp
  )

target_link_libraries(opWeekendHost
  stb_image
  owl::owl_prime
  )

add_test(opWeekendHost ${CMAKE_BINARY_DIR}/opWeekendHost)




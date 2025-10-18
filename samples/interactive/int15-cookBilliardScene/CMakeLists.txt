# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int15-cookBilliardScene-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int15-cookBilliardScene hostCode.cpp)
target_link_libraries(int15-cookBilliardScene
  PRIVATE
    int15-cookBilliardScene-ptx
    owl_viewer
)
target_compile_definitions(int15-cookBilliardScene
  PRIVATE
    DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data"
)

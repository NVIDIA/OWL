# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int17-curveMaterials-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int17-curveMaterials hostCode.cpp)
target_link_libraries(int17-curveMaterials
  PRIVATE
    int17-curveMaterials-ptx
    owl_viewer
)

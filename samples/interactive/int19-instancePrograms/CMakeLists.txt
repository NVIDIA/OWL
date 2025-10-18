# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    int19-instancePrograms-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int19-instancePrograms hostCode.cpp)
target_link_libraries(int19-instancePrograms
  PRIVATE
    int19-instancePrograms-ptx
    owl_viewer
)

# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

embed_ptx(
  OUTPUT_TARGET
    adv_optix7course-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    devicePrograms.cu
)

add_executable(adv_optix7course
  # the file with embedded PTX string for the device programs:
  SampleRenderer.h
  SampleRenderer.cpp
  Model.h
  Model.cpp
  LaunchParams.h
  main.cpp
)

target_link_libraries(adv_optix7course PRIVATE adv_optix7course-ptx owl_viewer)

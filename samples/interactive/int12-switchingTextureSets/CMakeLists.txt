# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# main purpose of this example is to showcase and test the sitation of
# having buffers of buffers of textures: Though primarily built upon
# the previous int11-rotatoinBoxes sample, in this sample we no longer
# have one randomly created texture per box, but instead, have N sets
# of 6 textures (one per face) of each box, using the current frame
# time to cycle through those texture sets. Ie, each box stores one
# one buffer of N buffers of 6 textures each

embed_ptx(
  OUTPUT_TARGET
    int12-switchingTextureSets-ptx
  PTX_LINK_LIBRARIES
    owl::owl
  SOURCES
    deviceCode.cu
)

add_executable(int12-switchingTextureSets hostCode.cpp)
target_link_libraries(int12-switchingTextureSets
  PRIVATE
    int12-switchingTextureSets-ptx
    owl_viewer
)

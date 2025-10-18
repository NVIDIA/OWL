# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

foreach(sample IN ITEMS
    int01-simpleTriangles
    int06-mixedGeometries
    int07-whitted
    int10-texturedTriangles
    int11-rotatingBoxes
    int12-switchingTextureSets
    int13-motionBlurInstances
    int14-motionBlurAabbs
    int15-cookBilliardScene
    int16-curves
    int17-curveMaterials
    int18-spherePrimitives
    int19-instancePrograms
    )
  add_subdirectory(${sample})
endforeach()



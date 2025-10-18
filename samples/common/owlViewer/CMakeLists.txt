# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)

add_library(owl_viewer STATIC)

target_sources(owl_viewer PRIVATE
  # add header files, so visual studio will properly show them as part of the solution
  OWLViewer.h
  Camera.h
  InspectMode.h
  FlyMode.h

  # the actual source files
  OWLViewer.cpp
  Camera.cpp
  InspectMode.cpp
  FlyMode.cpp
)

if(TARGET OpenGL::OpenGL)
  target_link_libraries(owl_viewer PUBLIC OpenGL::OpenGL)
else()
  target_link_libraries(owl_viewer PUBLIC OpenGL::GL)
endif()

target_link_libraries(owl_viewer
  PUBLIC
    owl::owl
    glfw
    stb_image
)

target_include_directories(owl_viewer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)

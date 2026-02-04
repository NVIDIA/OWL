# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0


set(OWL_VERSION_MAJOR 1)
set(OWL_VERSION_MINOR 2)
set(OWL_VERSION_PATCH 3)

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CUDA_USE_STATIC_CUDA_RUNTIME ON)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.18)
  cmake_policy(SET CMP0104 NEW)
endif()
cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0063 NEW)



if (NOT (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR}))
  set(OWL_IS_SUBPROJECT ON)
else()
  set(OWL_IS_SUBPROJECT OFF)
endif()

set(CMAKE_BUILD_TYPE_INIT "Release")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)




# project command is required to come after cmake_minimum_required command.
set(OWL_VERSION ${OWL_VERSION_MAJOR}.${OWL_VERSION_MINOR}.${OWL_VERSION_PATCH})
project(OWL VERSION ${OWL_VERSION} LANGUAGES C CXX CUDA)
include(GNUInstallDirs)

if (NOT CMAKE_CUDA_ARCHITECTURES)
  # 'all-major', since cmake-3.24
  if (${CMAKE_VERSION} VERSION_LESS 3.24)
    # cmake < 3.24 doesnt' know 'native', so simply leave it off, and
    # specify no arch flags at all - which for most cuda versions
    # should default to whatever the underlying host has, anyway
  else()
    set(CMAKE_CUDA_ARCHITECTURES "native")
  endif()
endif()

if (NOT OWL_IS_SUBPROJECT)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
  endif()
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# ------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/owl/cmake/")
if (OWL_IS_SUBPROJECT)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
  set(OWL_BUILD_SAMPLES OFF)
else()
  # if we're NOT a submodule, we _probably_ want to build the samples,
  # but give the user a way of turning that off, too:
  option(OWL_BUILD_SAMPLES "Build the Samples?" ON)
endif()
#include(configure_tbb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(embed_ptx)
include(embed_optixir)

option(OWL_BUILD_SHARED "Build OWL as a shared library? (otherwise static)" OFF)
set(BUILD_SHARED_LIBS ${OWL_BUILD_SHARED}) # use 'OWL_' naming convention


include(owl/cmake/configure_tbb.cmake)


# ------------------------------------------------------------------
# owl library itself, including owl-common
# ------------------------------------------------------------------

add_subdirectory(owl)

add_subdirectory(3rdParty)

# ------------------------------------------------------------------
# "owl prime" interface
# ------------------------------------------------------------------
add_subdirectory(prime)

# ------------------------------------------------------------------
# tutorial/samples
# ------------------------------------------------------------------
if (OWL_IS_SUBPROJECT)
  # if we ARE a subproject, we ONLY include the samples/common subdir,
  # and ONLY with exclude from all. 
  return()
endif()

if (OWL_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

include(CTest)
if (BUILD_TESTING)
  enable_testing()
endif()



# ------------------------------------------------------------------
# cmake install stuff
# ------------------------------------------------------------------

set(OWL_CMAKE_INSTALL_DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/owl-${OWL_VERSION}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/owl/cmake/owlConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/owlConfig.cmake"
  INSTALL_DESTINATION
  ${OWL_CMAKE_INSTALL_DESTINATION}
)

write_basic_package_version_file(
    "owlConfigVersion.cmake"
    VERSION ${OWL_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/owlConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/owlConfigVersion.cmake
  ${PROJECT_SOURCE_DIR}/owl/cmake/embed_ptx.cmake
  ${PROJECT_SOURCE_DIR}/owl/cmake/run_bin2c.cmake
  DESTINATION
  ${OWL_CMAKE_INSTALL_DESTINATION}
  )

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  DESTINATION
    ${OWL_CMAKE_INSTALL_DESTINATION}
  FILES_MATCHING
    PATTERN *.cmake
    PATTERN Findowl.cmake EXCLUDE
)

set(OWL_INSTALL_TARGETS owl owl_static)

install(
  TARGETS
  ${OWL_INSTALL_TARGETS}
  EXPORT owl-config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  NAMELINK_SKIP
  # on Windows put the dlls into bin
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  # ... and the import lib into the devel package
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(EXPORT owl-config
  DESTINATION ${OWL_CMAKE_INSTALL_DESTINATION}
  NAMESPACE owl::
  )

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/owl
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}
  )
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/optix/include
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/owl/optix
  )



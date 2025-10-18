// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "owl/helper/cuda.h"

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

#include <optix.h>
#include <optix_function_table.h>
#include <optix_stubs.h>

#ifdef _WIN32
#pragma warning( push )
#endif

#define OPTIX_CHECK( call )                                             \
  {                                                                     \
    OptixResult res = call;                                             \
    if( res != OPTIX_SUCCESS )                                          \
      {                                                                 \
        fprintf( stderr, "Optix call (%s) failed with code %d (line %d)\n", #call, res, __LINE__ ); \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define OPTIX_CHECK_LOG( call )                                         \
  {                                                                     \
    OptixResult res = call;                                             \
    if( res != OPTIX_SUCCESS )                                          \
      {                                                                 \
        fprintf( stderr, "Optix call (%s) failed with code %d (line %d)\n", #call, res, __LINE__ ); \
        fprintf( stderr, "Log:\n%s\n", log );                           \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define OPTIX_CALL( call ) OPTIX_CHECK(optix##call)


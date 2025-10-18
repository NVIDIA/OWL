// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "owl/common.h"
#include <cuda_runtime.h>

#define OWL_CUDA_CHECK( call )                                          \
  {                                                                     \
    cudaError_t rc = call;                                              \
    if (rc != cudaSuccess) {                                            \
      fprintf(stderr,                                                   \
              "CUDA call (%s) failed with code %d (line %d): %s\n",     \
              #call, rc, __LINE__, cudaGetErrorString(rc));             \
      OWL_RAISE("fatal cuda error");                                    \
    }                                                                   \
  }

#define OWL_CUDA_CALL(call) OWL_CUDA_CHECK(cuda##call)

#define OWL_CUDA_CHECK2( where, call )                                  \
  {                                                                     \
    cudaError_t rc = call;                                              \
    if(rc != cudaSuccess) {                                             \
      if (where)                                                        \
        fprintf(stderr, "at %s: CUDA call (%s) "                        \
                "failed with code %d (line %d): %s\n",                  \
                where,#call, rc, __LINE__, cudaGetErrorString(rc));     \
      fprintf(stderr,                                                   \
              "CUDA call (%s) failed with code %d (line %d): %s\n",     \
              #call, rc, __LINE__, cudaGetErrorString(rc));             \
      OWL_RAISE("fatal cuda error");                                    \
    }                                                                   \
  }

#define OWL_CUDA_SYNC_CHECK()                                           \
  {                                                                     \
    cudaDeviceSynchronize();                                            \
    cudaError_t rc = cudaGetLastError();                                \
    if (rc != cudaSuccess) {                                            \
      fprintf(stderr, "error (%s: line %d): %s\n",                      \
              __FILE__, __LINE__, cudaGetErrorString(rc));              \
      OWL_RAISE("fatal cuda error");                                    \
    }                                                                   \
  }

#define OWL_CUDA_SYNC_CHECK_STREAM(s)                                   \
  {                                                                     \
    cudaStreamSynchronize(s);                                           \
    cudaError_t rc = cudaGetLastError();                                \
    if (rc != cudaSuccess) {                                            \
      fprintf(stderr, "error (%s: line %d): %s\n",                      \
              __FILE__, __LINE__, cudaGetErrorString(rc));              \
      OWL_RAISE("fatal cuda error");                                    \
    }                                                                   \
  }



#define OWL_CUDA_CHECK_NOTHROW( call )                                  \
  {                                                                     \
    cudaError_t rc = call;                                              \
    if (rc != cudaSuccess) {                                            \
      fprintf(stderr,                                                   \
              "CUDA call (%s) failed with code %d (line %d): %s\n",     \
              #call, rc, __LINE__, cudaGetErrorString(rc));             \
      exit(2);                                                          \
    }                                                                   \
  }

#define OWL_CUDA_CALL_NOTHROW(call) OWL_CUDA_CHECK_NOTHROW(cuda##call)

#define OWL_CUDA_CHECK2_NOTHROW( where, call )                          \
  {                                                                     \
    cudaError_t rc = call;                                              \
    if(rc != cudaSuccess) {                                             \
      if (where)                                                        \
        fprintf(stderr, "at %s: CUDA call (%s) "                        \
                "failed with code %d (line %d): %s\n",                  \
                where,#call, rc, __LINE__, cudaGetErrorString(rc));     \
      fprintf(stderr,                                                   \
              "CUDA call (%s) failed with code %d (line %d): %s\n",     \
              #call, rc, __LINE__, cudaGetErrorString(rc));             \
      exit(2);                                                          \
    }                                                                   \
  }


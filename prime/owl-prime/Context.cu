// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "owl-prime/Context.h"
#include "owl-prime/Triangles.h"
#include "owl-prime/Spheres.h"
#include "owl-prime/Group.h"

primer::Context *primer::Context::createOffloadContext(int gpuID)
{ return new op::Context(gpuID); }

extern "C" char deviceCode_ptx[];

namespace op {
  
  OWLVarDecl Context::lpVariables[]
  = {
     { "rays",      OWL_RAW_POINTER, OWL_OFFSETOF(Context::LPData,rays) },
     { "hits",      OWL_RAW_POINTER, OWL_OFFSETOF(Context::LPData,hits) },
     { "activeIDs", OWL_RAW_POINTER, OWL_OFFSETOF(Context::LPData,activeIDs) },
     { "model",     OWL_GROUP,       OWL_OFFSETOF(Context::LPData,model) },
     { "numRays",   OWL_INT,         OWL_OFFSETOF(Context::LPData,numRays) },
     { "flags",     OWL_ULONG,       OWL_OFFSETOF(Context::LPData,flags) },
     { nullptr /* end of list sentinel */ }
  };

  Context::Context(int gpuID)
  {
    if (gpuID < 0) gpuID = 0;
    
    owl = owlContextCreate(&gpuID,1);
    module = owlModuleCreate(owl,deviceCode_ptx);
    rayGen = owlRayGenCreate(owl,module,"traceRays",sizeof(int),nullptr,0);
    launchParams = owlParamsCreate(owl,sizeof(LPData),lpVariables,-1);
    
    meshGeomType = owlGeomTypeCreate(owl,OWL_TRIANGLES,
                                     sizeof(Triangles::SBTData),
                                     Triangles::variables,-1);
    owlGeomTypeSetClosestHit(meshGeomType,0,module,"TrianglesCH");
    owlGeomTypeSetAnyHit(meshGeomType,0,module,"TrianglesAH");

#if 0
    // disabled right now, not hooked up to API, yet
    spheresGeomType = owlGeomTypeCreate(owl,OWL_GEOM_USER,
                                        sizeof(Spheres::SBTData),
                                        Spheres::variables,-1);
    owlGeomTypeSetBoundsProg(spheresGeomType,module,"Spheres");
    owlGeomTypeSetIntersectProg(spheresGeomType,0,module,"Spheres");
    owlGeomTypeSetClosestHit(spheresGeomType,0,module,"Spheres");
#endif
    owlBuildPrograms(owl);
    owlBuildPipeline(owl);
  }
  
  void Context::checkSBT()
  {
    if (!sbtDirty) return;

    owlBuildSBT(owl);
    owlBuildPipeline(owl);
    sbtDirty = false;
  }

  template<typename T>
  inline __both__
  const T &getWithOffset(const T *base, int idx, size_t strideInBytes)
  {
    unsigned char *ptr = (unsigned char *)base;
    ptr += idx * strideInBytes;
    return *(T*)ptr;
  }

  __global__ void copySpheres(float4 *spheres,
                              int numSpheres,
                              const float *x,
                              const float *y,
                              const float *z,
                              int centerStride,
                              const float *r,
                              int rStride)
  {
    int tid = threadIdx.x+blockIdx.x*blockDim.x;
    if (tid >= numSpheres) return;
    spheres[tid]
      = {
         getWithOffset(x,tid,centerStride),
         getWithOffset(y,tid,centerStride),
         getWithOffset(z,tid,centerStride),
         getWithOffset(r,tid,rStride)
    };
  }

  /*! create a mesh from vertex array and index array */
  primer::Geom *Context::createTriangles(uint64_t userID,
                                         /* vertex array */
                                         const vec3f *vertices,
                                         size_t numVertices,
                                         size_t vertexStrideInBytes,
                                         /* index array */
                                         const vec3i *indices,
                                         size_t numIndices,
                                         size_t indexStrideInBytes)
  {
    // TODO: do all this without copies if these are already device pointers
    OWLBuffer vertexBuffer
      = owlManagedMemoryBufferCreate(owl,OWL_FLOAT3,numVertices,0);
    vec3f *d_vertices = (vec3f*)owlBufferGetPointer(vertexBuffer,0);
    
    OWLBuffer indexBuffer
      = owlManagedMemoryBufferCreate(owl,OWL_INT3,numIndices,0);
    vec3i *d_indices = (vec3i*)owlBufferGetPointer(indexBuffer,0);

    for (int i=0;i<numVertices;i++) 
      d_vertices[i] = getWithOffset(vertices,i,vertexStrideInBytes);
    for (int i=0;i<numIndices;i++) 
      d_indices[i] = getWithOffset(indices,i,indexStrideInBytes);
    
    assert(size_t(int(numIndices)) == numIndices);
    assert(size_t(int(numVertices)) == numVertices);
    return new Triangles(this,userID,
                         vertexBuffer,(int)numVertices,
                         indexBuffer,(int)numIndices);
  }

  primer::Group *Context::createGroup(std::vector<OPGeom> &geoms) 
  {
    return new op::Group(this,geoms);
  }

  primer::Model *Context::createModel(const std::vector<OPGroup>  &groups,
                                      const std::vector<affine3f> &xfms)
  {
    return new op::Model(this,groups,xfms);
  }
  
} // ::op

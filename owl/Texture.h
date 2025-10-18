// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "RegisteredObject.h"

namespace owl {

  struct Texture : public RegisteredObject
  {
    typedef std::shared_ptr<Texture> SP;
    
    Texture(Context *const context,
            vec2i                size,
            uint32_t             linePitchInBytes,
            OWLTexelFormat       texelFormat,
            OWLTextureFilterMode filterMode,
            OWLTextureAddressMode addressMode_x,
            OWLTextureAddressMode addressMode_y,
            OWLTextureColorSpace colorSpace,
            const void          *texels
            );
    
    /*! destructor - free device data, de-regsiter, and destruct */
    virtual ~Texture();
    
    std::string toString() const override { return "Texture"; }

    /* return the cuda texture object corresponding to the specified 
       device ID*/
    cudaTextureObject_t getObject(int deviceID);

    
    /*! destroy whatever resources this texture's ll-layer handle this
        may refer to; this will not destruct the current object
        itself, but should already release all its references */
    void destroy();

    /*! one entry per device */
    std::vector<cudaTextureObject_t> textureObjects;
    std::vector<cudaArray_t>         textureArrays;
    
    vec2i                size;
    uint32_t             linePitchInBytes;
    OWLTexelFormat       texelFormat;
    OWLTextureFilterMode filterMode;
  };

} // ::owl

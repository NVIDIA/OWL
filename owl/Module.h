// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "RegisteredObject.h"

namespace owl {
  
  /*! captures the concept of a module that contains one or more
    programs. */
  struct Module : public RegisteredObject {
    typedef std::shared_ptr<Module> SP;

    /*! any device-specific data, such as optix handles, cuda device
      pointers, etc */
    struct DeviceData : public RegisteredObject::DeviceData {
      
      /*! constructor */
      DeviceData(Module *parent, DeviceContext::SP device);
      
      /*! destructor */
      virtual ~DeviceData();

      /*! build the optix side of this module on this device */
      void build();

      /*! destroy the optix data for this module; the owl data for the
        module itself remains valid */
      void destroy();

      /*! pointer to the non-device specific part of this module */
      Module *const parent;
      
      /*! optix-compiled module for the optix programs. for all
       *optix* programs we can directly build the PTX code into a
       module using optixbuildmodule - this is the result of that
       operation */
      OptixModule module = 0;
      
      /*! for the *bounds* function we have to build a *separate*
        module because this one is built outside of optix, and thus
        does not have the internal _optix_xyz() symbols in it */
      CUmodule    computeModule = 0;
    };

    /*! constructor - ptxCode contains the prec-ompiled ptx code with
      the compiled functions */
    Module(Context *context, const std::string &ptxCode);

    /*! constructor - IR contains the pre-compiled optix IR */
    Module(Context *context, const std::vector<uint8_t> &IR);

    /*! destructor, to release data if required */
    virtual ~Module();
    
    /*! pretty-printer, for printf-debugging */
    std::string toString() const override;
    
    /*! get reference to given device-specific data for this object */
    inline DeviceData &getDD(const DeviceContext::SP &device) const;

    /*! create this object's device-specific data for the device */
    RegisteredObject::DeviceData::SP createOn(const DeviceContext::SP &device) override;

    /*! a flag tracking if we're using OptiX IR or PTX. For now, assuming PTX as default. */
    bool useIR = false;

    /*! the precompiled PTX code supplied by the user */
    const std::string ptxCode;

    /*! the precompiled OptiX IR supplied by the user */
    const std::vector<uint8_t> optixIRCode;
  };
  
  // ------------------------------------------------------------------
  // implementation section
  // ------------------------------------------------------------------
  
  /*! get reference to given device-specific data for this object */
  inline Module::DeviceData &Module::getDD(const DeviceContext::SP &device) const
  {
    assert(device && device->ID >= 0 && device->ID < (int)deviceData.size());
    return deviceData[device->ID]->as<Module::DeviceData>();
  }
  
} // ::owl

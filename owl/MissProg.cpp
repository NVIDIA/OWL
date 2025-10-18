// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "MissProg.h"
#include "Context.h"

namespace owl {

  // ------------------------------------------------------------------
  // MissProgType::DeviceData
  // ------------------------------------------------------------------

  /*! constructor, only pass-through to parent class */
  MissProgType::DeviceData::DeviceData(const DeviceContext::SP &device)
    : RegisteredObject::DeviceData(device)
  {}

  // ------------------------------------------------------------------
  // MissProgType
  // ------------------------------------------------------------------

  MissProgType::MissProgType(Context *const context,
                             Module::SP module,
                             const std::string &progName,
                             size_t varStructSize,
                             const std::vector<OWLVarDecl> &varDecls)
    : SBTObjectType(context,context->missProgTypes,varStructSize,varDecls),
      module(module),
      progName(progName),
      annotatedProgName("__miss__"+progName)
  {}
  
  /*! pretty-printer, for printf-debugging */
  std::string MissProgType::toString() const
  {
    return "MissProgType";
  }

  /*! creates the device-specific data for this group */
  RegisteredObject::DeviceData::SP
  MissProgType::createOn(const DeviceContext::SP &device) 
  {
    return std::make_shared<DeviceData>(device);
  }
  
  // ------------------------------------------------------------------
  // MissProg
  // ------------------------------------------------------------------
  
  MissProg::MissProg(Context *const context,
                     MissProgType::SP type) 
    : SBTObject(context,context->missProgs,type)
  {}
  
  /*! pretty-printer, for printf-debugging */
  std::string MissProg::toString() const
  {
    return "MissProg";
  }

  /*! write the given SBT record, using the given device's
  corresponding device-side data represenataion */
  void MissProg::writeSBTRecord(uint8_t *const sbtRecord,
                                const DeviceContext::SP &device)
  {
    auto &dd = type->getDD(device);
    
    // first, compute pointer to record:
    uint8_t *const sbtRecordHeader = sbtRecord;
    uint8_t *const sbtRecordData   = sbtRecord+OPTIX_SBT_RECORD_HEADER_SIZE;

    // ------------------------------------------------------------------
    // pack record header with the corresponding hit group:
    // ------------------------------------------------------------------
    OPTIX_CALL(SbtRecordPackHeader(dd.pg,sbtRecordHeader));
    
    // ------------------------------------------------------------------
    // then, write the data for that record
    // ------------------------------------------------------------------
    writeVariables(sbtRecordData,device);
  }  
  
} // ::owl


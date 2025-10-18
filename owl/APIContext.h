// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "owl/Context.h"
#include <mutex>

namespace owl {

  struct APIHandle;
  
  struct APIContext : public Context {
    typedef std::shared_ptr<APIContext> SP;

    APIContext(int32_t *requestedDeviceIDs,
               int      numRequestedDevices)
      : Context(requestedDeviceIDs,
                numRequestedDevices)
    {}
    
    /*! pretty-printer, for printf-debugging */
    virtual std::string toString() const override { return "owl::APIContext"; }

    APIHandle *createHandle(Object::SP object);

    void track(APIHandle *object);
    
    void forget(APIHandle *object);

    /*! delete - and thereby, release - all handles that we still
      own. */
    void releaseAll();

    std::set<APIHandle *> activeHandles;    
    std::mutex monitor;
  };
  
} // ::owl  

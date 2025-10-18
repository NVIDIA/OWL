// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "RegisteredObject.h"
#include "ObjectRegistry.h"

namespace owl {

  RegisteredObject::RegisteredObject(Context *const context,
                                     ObjectRegistry &registry)
    : ContextObject(context),
      ID(registry.allocID()),
      registry(registry)
  {
    assert(this);
    registry.track(this);
  }
  
  RegisteredObject::~RegisteredObject()
  {
    assert(this);
    registry.forget(this);
  }
    
} // ::owl


// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Object.h"

namespace owl {

  struct ObjectRegistry;

  /*! a object that is managed/kept track of in a registry that
      assigns linear IDs (so that, for example, the SBT builder can
      easily iterate over all geometries, all geometry types, etc. The
      sole job of this class is to properly register and unregister
      itself in the given registry when it gets created/destroyed */
  struct RegisteredObject : public ContextObject {

    RegisteredObject(Context *const context,
                     ObjectRegistry &registry);
    virtual ~RegisteredObject();

    /*! the ID we're registered by - should only ever get set to any
        useful value in the constructor, and get set to -1 when the
        object is removed from this registry */
    int ID;
    
    /*! the registry (int he context) that we're registered in */
    ObjectRegistry &registry;
  };

} // ::owl


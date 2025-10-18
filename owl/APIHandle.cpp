// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "APIContext.h"
#include "APIHandle.h"

namespace owl {

  APIHandle::APIHandle(Object::SP object, APIContext *_context)
  {
    assert(object);
    assert(_context);
    this->object  = object;
    this->context = std::dynamic_pointer_cast<APIContext>
      (_context->shared_from_this());
    assert(this->object);
    assert(this->context);
  }

  APIHandle::~APIHandle()
  {
    // iw: every active handle _should_ have a context, but if context
    // itself is killing off remaining handles this pointer may
    // already be null.
    if (context) context->forget(this);
    object  = nullptr;
    context = nullptr;
  }

} // ::owl  

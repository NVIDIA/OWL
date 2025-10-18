// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "APIContext.h"
#include "APIHandle.h"

#define LOG(message)                            \
  if (Context::logging())                       \
    std::cout                                   \
      << OWL_TERMINAL_LIGHT_BLUE                \
      << "#owl: "                               \
      << message                                \
      << OWL_TERMINAL_DEFAULT << std::endl

#define LOG_OK(message)                         \
  if (Context::logging())                       \
    std::cout                                   \
      << OWL_TERMINAL_BLUE                      \
      << "#owl: "                               \
      << message                                \
      << OWL_TERMINAL_DEFAULT << std::endl
  
namespace owl {
  
  void APIContext::forget(APIHandle *object)
  {
    std::lock_guard<std::mutex> lock(monitor);
    assert(object);
    auto it = activeHandles.find(object);
    assert(it != activeHandles.end());
    activeHandles.erase(it);
  }

  void APIContext::releaseAll()
  {
    LOG("#owl: context is dying; number of API handles (other than context itself) "
        << "that have not yet been released (incl this context): "
        << (activeHandles.size()));
    
    // create one reference that won't get removed when removing all
    // API handles (caller should actually have one, but just in case)
    std::shared_ptr<APIContext> self = shared_from_this()->as<APIContext>();
    std::vector<APIHandle*> handlesToFree;
    for (auto &it : activeHandles) {
        if (it && it->object
            ) {
          // PRINT(it->object->toString());
            it->object = {};
            it->context = {};
            handlesToFree.push_back(it);
        }
    }
    activeHandles.clear();
    for (auto handle : handlesToFree)
      delete handle;
  }
  
  void APIContext::track(APIHandle *object)
  {
    assert(object);

    std::lock_guard<std::mutex> lock(monitor);
    
    auto it = activeHandles.find(object);
    assert(it == activeHandles.end());
    activeHandles.insert(object);
  }

  APIHandle *APIContext::createHandle(Object::SP object)
  {
    assert(object);
    APIHandle *handle = new APIHandle(object,this);
    track(handle);
    return handle;
  }

} // ::owl  

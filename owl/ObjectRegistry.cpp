// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "ObjectRegistry.h"
#include "RegisteredObject.h"
#include "Context.h"

#include "Buffer.h"
#include "Group.h"
#include "RayGen.h"
#include "MissProg.h"

namespace owl {

  void ObjectRegistry::forget(RegisteredObject *object)
  {
    assert(object);
    if (object->ID == -1)
      // object is already de-registered (eg, with an explicit
      // bufferdestroy, even if owl::buffer object still has a
      // reference count and thus hasn't been deleted yet.
      return;
    
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    assert(object->ID >= 0);
    assert(object->ID < (int)objects.size());
    assert(objects[object->ID] == object);
    objects[object->ID] = nullptr;
      
    previouslyReleasedIDs.push(object->ID);

    object->ID = -1;
  }
    
  void ObjectRegistry::track(RegisteredObject *object)
  {
    assert(object);
    std::lock_guard<std::recursive_mutex> lock(this->mutex);
    assert(object->ID >= 0);
    assert(object->ID < (int)objects.size());
    assert(objects[object->ID] == nullptr);
    objects[object->ID] = object;
  }
    
  int ObjectRegistry::allocID()
  {
    try {
      std::lock_guard<std::recursive_mutex> lock(this->mutex);
      if (previouslyReleasedIDs.empty()) {
        objects.push_back(nullptr);
        const int newID = int(objects.size()-1);
        if (newID >= numIDsAllocedInContext) {
          while (newID >= numIDsAllocedInContext)
            numIDsAllocedInContext = std::max(1,numIDsAllocedInContext*2);
        }
        return newID;
      } else {
        int reusedID = previouslyReleasedIDs.top();
        previouslyReleasedIDs.pop();
        return reusedID;
      }
    } catch (const std::exception &e) {
      std::cout << "Error in allocating ID " << e.what() << std::endl;;
      throw;
    }
  }
  
  RegisteredObject *ObjectRegistry::getPtr(size_t ID)
  {
    assert(ID < objects.size());
    std::lock_guard<std::recursive_mutex> lock(mutex);
    return objects[ID];
  }

} // ::owl


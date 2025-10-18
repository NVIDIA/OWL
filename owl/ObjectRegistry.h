// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#pragma once

#include "Object.h"

namespace owl {

  struct RegisteredObject;
  struct Context;
  struct ObjectRegistry;

  /*! registry that tracks mapping between buffers and buffer
    IDs. Every buffer should have a valid ID, and should be tracked
    in this registry under this ID */
  struct ObjectRegistry {
    ObjectRegistry() = default;
    virtual ~ObjectRegistry() = default;
    
    // ReallocContextIDsCB reallocContextIDs,
    // const char *typeDescription);
    inline size_t size()  const { return objects.size(); }
    inline bool   empty() const { return objects.empty(); }

    // virtual void reallocContextIDs(int newMaxIDs) = 0;
    
    void forget(RegisteredObject *object);
    void track(RegisteredObject *object);
    int allocID();
    RegisteredObject *getPtr(size_t ID);
  private:
    /*! list of all tracked objects. note this are *NOT* shared-ptr's,
      else we'd never released objects because each object would
      always be owned by the registry */
    std::vector<RegisteredObject *> objects;

    /*! number of IDs of given type allocated in the LL context; if we
     *  ever give out an ID that is greater or equal than this side,
     *  we first have to tell the LL context to generate more IDs */
    int numIDsAllocedInContext = 0;
    
    /*! list of IDs that have already been allocated before, and have
      since gotten freed, so can be re-used */
    std::stack<int> previouslyReleasedIDs;
    std::recursive_mutex mutex;
  };


  /*! registry that tracks mapping between buffers and buffer
    IDs. Every buffer should have a valid ID, and should be tracked
    in this registry under this ID */
  template<typename T>
  struct ObjectRegistryT : public ObjectRegistry {
    ObjectRegistryT(Context *context)
      : context(context)
    {}
    virtual ~ObjectRegistryT() = default;
    
    inline T* getPtr(size_t ID)
    {
      return (T*)ObjectRegistry::getPtr(ID);
    }

    inline typename T::SP getSP(size_t ID)
    {
      T *ptr = getPtr(ID);
      if (!ptr) return {};
      Object::SP object = ptr->shared_from_this();
      assert(object);
      return object->as<T>();
    }
    
    Context *const context;
  };
    
} // ::owl


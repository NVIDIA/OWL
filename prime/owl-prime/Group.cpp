// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0



#include "owl-prime/Group.h"
#include "owl-prime/Triangles.h"
#include "owl-prime/Spheres.h"

namespace op {

  Group::Group(Context *context,
               std::vector<OPGeom> &geoms)
    : primer::Group(geoms)
  {
    std::vector<OWLGeom> triangleGeoms;
    std::vector<OWLGeom> userGeoms;
    for (auto _geom : geoms) {
      primer::Geom *geom = (primer::Geom *)_geom;
      if (!geom)
        throw std::runtime_error("invalid null geometry handle!?");
      op::Triangles *triangles
        = dynamic_cast<op::Triangles *>(geom);
      op::UserGeom *user
        = dynamic_cast<op::UserGeom *>(geom);
      if (triangles) {
        assert(triangles->geom);
        triangleGeoms.push_back(triangles->geom);
      } else if (user) {
        assert(user->geom);
        userGeoms.push_back(user->geom);
      } else
        throw std::runtime_error("un-recognized geometry handle!?");
    }
    if (!triangleGeoms.empty()) {
      trianglesGroup = owlTrianglesGeomGroupCreate(context->owl,
                                                   triangleGeoms.size(),
                                                   triangleGeoms.data());
      owlGroupBuildAccel(trianglesGroup);
    }
    if (!userGeoms.empty()) {
      userGroup = owlUserGeomGroupCreate(context->owl,
                                         userGeoms.size(),
                                         userGeoms.data());
      assert(userGroup);
      owlGroupBuildAccel(userGroup);
    }
  }
  
  Group::~Group()
  {
    if (trianglesGroup) owlGroupRelease(trianglesGroup);
    if (userGroup) owlGroupRelease(userGroup);
  }
  
} // ::op

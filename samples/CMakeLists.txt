# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# support libraries
add_subdirectory(common)

# ------------------------------------------------------------------
# cmdline-only samples, also used for 'make test'
# ------------------------------------------------------------------
add_subdirectory(cmdline)

# "owl prime" samples
add_subdirectory(prime)

if (TARGET owl_viewer)

  # interactive tutorial-style samples (these will try to open windows)
  add_subdirectory(interactive)

  # advanced samples (these will try to open windows)
  add_subdirectory(advanced)

else()
  message(WARNING "#owl.cmake: could not build owl_viewer library; skipping advanced samples")
endif()

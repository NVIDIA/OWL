# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# ------------------------------------------------------------------
# cmdline-only samples, also used for 'make test'
# ------------------------------------------------------------------
add_subdirectory(cmdline)

# "owl prime" samples
add_subdirectory(prime)

# ------------------------------------------------------------------
# interactive, viewer based samples
# ------------------------------------------------------------------
# --> all interactive samples got removed from this repo so this repo
# could remain free of windowing, glfw, etcpp; former interactive
# samples will be provided in another repo.

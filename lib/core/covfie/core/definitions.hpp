/*
 * This file is part of covfie, a part of the ACTS project
 *
 * Copyright (c) 2022 CERN
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#if __cpp_concepts >= 201907L
#define CONSTRAINT(x) x
#else
#pragma message                                                                \
    "C++20 concepts are not supported by the current compiler. "               \
    "covfie will compile as normal, but compile-time guarantees will be "      \
    "weaker. Consider upgrading to C++20."
#define CONSTRAINT(x) typename
#endif
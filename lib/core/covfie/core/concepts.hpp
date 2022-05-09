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

#include <covfie/core/definitions.hpp>

#if __cpp_concepts >= 201907L
namespace covfie::concepts {
template <typename T>
concept field_backend = true;

template <typename T>
concept output_scalar = true;

template <typename T>
concept input_scalar = true;

template <typename T>
concept integral_input_scalar = true;

template <typename T>
concept floating_point_input_scalar = true;

template <typename T>
concept layout = true;

template <typename T>
concept datatype = true;
}
#endif
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

#include <covfie/benchmark/test_field.hpp>
#include <covfie/core/backend/primitive/constant.hpp>
#include <covfie/core/backend/transformer/linear.hpp>
#include <covfie/core/backend/transformer/morton.hpp>
#include <covfie/core/backend/transformer/nearest_neighbour.hpp>
#include <covfie/core/field.hpp>
#include <covfie/core/vector.hpp>
#include <covfie/cuda/backend/primitive/cuda_device_array.hpp>
#include <covfie/cuda/backend/primitive/cuda_texture.hpp>

struct FieldConstant {
    using backend_t = covfie::backend::constant<
        covfie::vector::vector_d<float, 3>,
        covfie::vector::vector_d<float, 3>>;

    static covfie::field<backend_t> get_field()
    {
        return covfie::field<backend_t>(typename backend_t::configuration_t{
            0.f, 0.f, 2.f});
    }
};

struct TexInterpolateNN {
    static constexpr covfie::backend::cuda_texture_interpolation value =
        covfie::backend::cuda_texture_interpolation::NEAREST_NEIGHBOUR;
};

struct TexInterpolateLin {
    static constexpr covfie::backend::cuda_texture_interpolation value =
        covfie::backend::cuda_texture_interpolation::LINEAR;
};

struct InterpolateNN {
    template <typename T>
    using apply = covfie::backend::nearest_neighbour<T>;
};

struct InterpolateLin {
    template <typename T>
    using apply = covfie::backend::linear<T>;
};

struct LayoutStride {
    template <typename T>
    using apply = covfie::backend::strided<covfie::vector::ulong3, T>;
};

struct LayoutMortonNaive {
    template <typename T>
    using apply = covfie::backend::morton<covfie::vector::ulong3, T, false>;
};

template <typename Interpolator, typename Layout>
struct Field {
    using backend_t = covfie::backend::affine<
        typename Interpolator::template apply<typename Layout::template apply<

            covfie::backend::cuda_device_array<covfie::vector::float3>>>>;

    static covfie::field<backend_t> get_field()
    {
        return covfie::field<backend_t>(get_test_field());
    }
};

template <typename Interpolator>
struct FieldTex {
    using backend_t = covfie::backend::affine<covfie::backend::cuda_texture<
        covfie::vector::float3,
        covfie::vector::float3,
        Interpolator::value>>;

    static covfie::field<backend_t> get_field()
    {
        return covfie::field<backend_t>(
            get_test_field().backend().get_configuration(),
            get_test_field().backend().get_backend().get_backend()
        );
    }
};
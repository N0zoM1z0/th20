#pragma once

#include "Timer.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// Scalar animation and Wonder Stone interpolation values. Padding is implicit.
template<class T> struct Interpolation {
    T start, end, tangent_start, tangent_end, current;
    Timer timer;
    std::int32_t duration, mode;

    Interpolation();
    void set_duration(std::int32_t value);
    std::int32_t set_mode(std::int32_t value);
    void set_start(const T& value);
    void set_end(const T& value);
    void begin(std::int32_t duration, std::int32_t mode,
               const T& from, const T& to);
};

using ByteInterpolation = Interpolation<std::uint8_t>;
using FloatInterpolation = Interpolation<float>;
static_assert(sizeof(ByteInterpolation) == 32);
static_assert(offsetof(ByteInterpolation, timer) == 8);
static_assert(sizeof(FloatInterpolation) == 44);
static_assert(offsetof(FloatInterpolation, timer) == 20);

extern template struct Interpolation<std::uint8_t>;
extern template struct Interpolation<float>;

} // namespace th20

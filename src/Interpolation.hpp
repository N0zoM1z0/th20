#pragma once

#include "Timer.hpp"
#include "Angle.hpp"
#include "IntegerTriple.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// Shared scalar, angle and component interpolation values. Padding is implicit.
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
using IntegerInterpolation = Interpolation<std::int32_t>;
using IntegerTripleInterpolation = Interpolation<IntegerTriple>;
using AngleInterpolation = Interpolation<Angle>;
using Vector2Interpolation = Interpolation<Vector2>;
using VectorInterpolation = Interpolation<Vector3>;
static_assert(sizeof(ByteInterpolation) == 32);
static_assert(offsetof(ByteInterpolation, timer) == 8);
static_assert(sizeof(FloatInterpolation) == 44);
static_assert(sizeof(IntegerInterpolation) == 44);
static_assert(offsetof(IntegerInterpolation, timer) == 20);
static_assert(sizeof(IntegerTripleInterpolation) == 84);
static_assert(offsetof(IntegerTripleInterpolation, timer) == 60);
static_assert(sizeof(AngleInterpolation) == 44);
static_assert(offsetof(AngleInterpolation, timer) == 20);
static_assert(offsetof(FloatInterpolation, timer) == 20);
static_assert(sizeof(Vector2Interpolation) == 64);
static_assert(offsetof(Vector2Interpolation, timer) == 40);
static_assert(offsetof(Vector2Interpolation, duration) == 56);
static_assert(offsetof(Vector2Interpolation, mode) == 60);
static_assert(sizeof(VectorInterpolation) == 84);
static_assert(offsetof(VectorInterpolation, timer) == 60);
static_assert(offsetof(VectorInterpolation, duration) == 76);
static_assert(offsetof(VectorInterpolation, mode) == 80);

extern template struct Interpolation<std::uint8_t>;
extern template struct Interpolation<float>;
extern template struct Interpolation<std::int32_t>;
extern template struct Interpolation<IntegerTriple>;
extern template struct Interpolation<Angle>;
extern template struct Interpolation<Vector2>;
extern template struct Interpolation<Vector3>;

} // namespace th20

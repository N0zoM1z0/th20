#include "Angle.hpp"
#include "Interpolation.hpp"
#include "Motion.hpp"
#include "Rectangle.hpp"
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <new>

void check_motion_values() {
    constexpr float pi = 3.1415927410125732f;
    for (std::uint32_t bits : {0u, 0x80000000u, 1u, 0x80000001u,
                              0x7fc00001u, 0xffc12345u}) {
        const float input = std::bit_cast<float>(bits);
        assert(std::bit_cast<std::uint32_t>(th20::normalize_angle(input)) == bits);
        assert(std::bit_cast<std::uint32_t>(th20::Angle(input).value) == bits);
    }
    for (float sign : {-1.0f, 1.0f}) {
        assert(th20::normalize_angle(sign * pi) == sign * pi);
        assert(th20::normalize_angle(sign * 2.0f * pi) == 0);
        const float input = sign * std::nextafter(pi, std::numeric_limits<float>::infinity());
        assert(std::signbit(th20::normalize_angle(input)) != std::signbit(input));
        assert(th20::normalize_angle(sign * std::numeric_limits<float>::infinity()) ==
               sign * std::numeric_limits<float>::infinity());
        // The cap leaves large angles outside the principal interval.
        const float bounded = th20::normalize_angle(sign * 1024.0f);
        assert(std::fabs(bounded) > pi);
        assert(std::fabs(std::fabs(bounded) - (1024.0f - 68.0f * pi)) < 0.002f);
    }
    for (int i = -8000; i <= 8000; ++i) {
        const float input = i / 40.0f, result = th20::normalize_angle(input);
        assert(result >= -pi && result <= pi);
        const double turns = (double(input) - result) / (2.0 * double(pi));
        assert(std::fabs(turns - std::round(turns)) < 0.0001);
        assert(th20::normalize_angle(result) == result);
    }
    for (unsigned pattern : {0u, 0x55u, 0xa5u, 0xffu}) {
        alignas(th20::Motion) unsigned char motion[sizeof(th20::Motion)];
        std::memset(motion, pattern, sizeof(motion));
        ::new(motion) th20::Motion;
        for (unsigned char byte : motion) assert(byte == 0);
        alignas(th20::VectorInterpolation) unsigned char interpolation[84];
        std::memset(interpolation, pattern, sizeof(interpolation));
        ::new(interpolation) th20::VectorInterpolation;
        for (unsigned char byte : interpolation) assert(byte == 0);
        alignas(th20::IntPoint) unsigned char point[8];
        std::memset(point, pattern, sizeof(point));
        ::new(point) th20::IntPoint;
        for (unsigned char byte : point) assert(byte == 0);
    }
    for (std::uint32_t a : {0u, 1u, 0x7fffffffu, 0x80000000u, 0xffffffffu}) {
        for (std::uint32_t b : {0u, 1u, 0x7fffffffu, 0x80000000u, 0xffffffffu}) {
            const th20::IntPoint left(std::bit_cast<std::int32_t>(a), std::bit_cast<std::int32_t>(b));
            const th20::IntPoint right(std::bit_cast<std::int32_t>(b), std::bit_cast<std::int32_t>(a));
            const auto sum = left + right;
            const auto expected = std::uint32_t(std::uint64_t(a) + b);
            assert(std::bit_cast<std::uint32_t>(sum.x) == expected);
            assert(std::bit_cast<std::uint32_t>(sum.y) == expected);
            assert(std::bit_cast<std::uint32_t>(left.x) == a);
            assert(std::bit_cast<std::uint32_t>(right.x) == b);
        }
    }
}

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

namespace {
th20::Motion* observed_motion;
int motion_stage;
}

// Observations at the two undefined native update boundaries.
namespace th20 {
void Motion::update_velocity() {
    assert(this == observed_motion && motion_stage == 0);
    velocity = Vector3(2.0f, -3.0f, 5.0f);
    motion_stage = 1;
}
void Motion::update_position() {
    assert(this == observed_motion && motion_stage == 1);
    position += velocity;
    motion_stage = 2;
}
}

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
    th20::Motion motion;
    observed_motion = &motion;
    motion_stage = 0;
    motion.position = th20::Vector3(10.0f, 20.0f, 30.0f);
    motion.flags.bits = 0xffffffffu;
    motion.update();
    assert(motion_stage == 2);
    assert(motion.position.x == 12.0f && motion.position.y == 17.0f &&
           motion.position.z == 35.0f && motion.flags.bits == 0xffffffffu);

    // Membership of an inclusive rectangle is an independent finite-domain oracle.
    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            motion.position = th20::Vector3(float(x), float(y), 999.0f);
            const bool inside = x >= -2 && x <= 6 && y >= -4 && y <= 8;
            unsigned char before[sizeof motion];
            std::memcpy(before, &motion, sizeof motion);
            assert(motion.outside_bounds(2, 2, 8, 12) == (inside ? 0 : 1));
            assert(std::memcmp(before, &motion, sizeof motion) == 0);
        }
    }
    const float inf = std::numeric_limits<float>::infinity();
    const float nan = std::numeric_limits<float>::quiet_NaN();
    motion.position = th20::Vector3(6, 8, inf);
    assert(motion.outside_bounds(2, 2, 8, 12) == 0);
    motion.position.x = std::nextafter(6.0f, inf);
    assert(motion.outside_bounds(2, 2, 8, 12) == 1);
    motion.position = th20::Vector3(nan, nan, 0);
    assert(motion.outside_bounds(0, 0, 8, 12) == 0);
    motion.position.y = inf;
    assert(motion.outside_bounds(0, 0, 8, 12) == 1);
    motion.position = th20::Vector3(inf, -inf, 0);
    assert(motion.outside_bounds(nan, nan, 8, 12) == 0);
    assert(motion.outside_bounds(0, 0, inf, inf) == 0);
    motion.position = th20::Vector3(-0.0f, 0.0f, 0);
    assert(motion.outside_bounds(0, -0.0f, 0, 0) == 0);
    assert(motion.outside_bounds(0, 0, -2, 2) == 1);
}

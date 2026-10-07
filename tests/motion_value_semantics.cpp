#include "Angle.hpp"
#include "Interpolation.hpp"
#include "Motion.hpp"
#include "MotionMath.hpp"
#include "ClockScalar.hpp"
#include "Rectangle.hpp"
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <new>

namespace {
bool near(float first, double second) {
    return std::fabs(double(first) - second) < 0.00002;
}

void check_motion_protocol() {
    constexpr double pi = 3.1415927410125732;
    const float saved_clock = th20::default_timer_clock.value;
    // Frozen updates preserve the entire receiver for every mode and spin bit.
    for (unsigned mode = 0; mode != 16; ++mode) {
        for (unsigned spin : {0u, 16u}) {
            th20::Motion frozen;
            frozen.position = th20::Vector3(-2.345f, 8.456f, 7);
            frozen.vector_38 = th20::Vector3(3, -4, 5);
            frozen.flags.bits = 0xa5a50020u | spin | mode;
            const th20::Motion before = frozen;
            frozen.update();
            assert(std::memcmp(&before, &frozen, sizeof frozen) == 0);
        }
    }
    for (float clock : {0.0f, 0.25f, 1.0f, 2.0f}) {
        th20::default_timer_clock.value = clock;
        for (float damping : {0.0f, 0.25f, 1.0f}) {
            for (unsigned mode = 0; mode != 16; ++mode) {
                for (unsigned spin : {0u, 16u}) {
                    struct Guarded { unsigned first; th20::Motion motion; unsigned last; };
                    Guarded guarded{0x12345678u, {}, 0xabcdef01u};
                    auto& motion = guarded.motion;
                    motion.position = th20::Vector3(4.567f, -2.345f, 9);
                    motion.velocity = th20::Vector3(2, 3, 4);
                    motion.vector_38 = th20::Vector3(1, 2, 7);
                    motion.value_18 = 3;
                    motion.angle_1c = 0.4f;
                    motion.value_20 = 5;
                    motion.value_24 = 0.3f;
                    motion.angle_28 = -0.2f;
                    motion.value_2c = 0.6f;
                    motion.angle_30 = 0.7f;
                    motion.value_34 = damping;
                    motion.flags.bits = 0xa5a50000u | mode | spin;
                    const th20::Motion before = motion;
                    th20::Motion separate = motion;
                    separate.update_velocity();
                    separate.update_position();
                    motion.update();
                    assert(std::memcmp(&motion, &separate, sizeof motion) == 0);
                    assert(guarded.first == 0x12345678u && guarded.last == 0xabcdef01u);
                    assert(motion.flags.bits == before.flags.bits);
                    double x = before.position.x, y = before.position.y;
                    if (mode == 0) {
                        const double length = 3.0 * clock * (1.0 - damping);
                        assert(near(motion.vector_38.x, length * std::cos(0.4f)));
                        assert(near(motion.vector_38.y, length * std::sin(0.4f)));
                        assert(near(motion.vector_38.z, 7.0 * (1.0 - damping)));
                        assert(near(motion.angle_1c.value, 0.4f +
                                    (spin ? 0.3f * clock * (1.0 - damping) : 0)));
                        x += motion.vector_38.x; y += motion.vector_38.y;
                        assert(near(motion.position.z, 9 + motion.vector_38.z));
                    } else if (mode == 2 || mode == 3) {
                        const double radius = 5 + 0.3f * clock * (1.0 - damping);
                        const double angle = th20::normalize_angle(0.4f + 3 * clock * (1 - damping));
                        assert(near(motion.value_20, radius));
                        assert(near(motion.angle_1c.value, angle));
                        const double local_angle = mode == 2 ? angle : angle + 0.2f;
                        double local_x = radius * std::cos(local_angle);
                        const double local_y = radius * std::sin(local_angle);
                        if (mode == 3) {
                            local_x *= 0.6f;
                            x = 1 + local_x * std::cos(-0.2f) - local_y * std::sin(-0.2f);
                            y = 2 + local_y * std::cos(-0.2f) + local_x * std::sin(-0.2f);
                        } else { x = 1 + local_x; y = 2 + local_y; }
                        assert(motion.position.z == 7);
                        assert(std::memcmp(&motion.vector_38, &before.vector_38,
                                           sizeof motion.vector_38) == 0);
                    } else if (mode == 4) {
                        assert(motion.vector_38.z == 0 && motion.velocity.z == 4);
                        assert(near(motion.vector_38.x, 3 * clock * std::cos(-0.2f)));
                        assert(near(motion.vector_38.y, 3 * clock * std::sin(-0.2f)));
                        const double phase = 0.7f + 0.3f * clock * (1 - damping);
                        assert(near(motion.angle_30.value, phase));
                        const double amplitude = std::sin(phase) * 5 * clock;
                        x = motion.velocity.x + amplitude * std::cos(-0.2f + pi / 2);
                        y = motion.velocity.y + amplitude * std::sin(-0.2f + pi / 2);
                        assert(near(motion.angle_1c.value,
                                    std::atan2(y - before.position.y, x - before.position.x)));
                        assert(motion.position.z == 4);
                    } else {
                        th20::Motion unchanged = before;
                        unchanged.update_velocity();
                        assert(std::memcmp(&unchanged, &before, sizeof before) == 0);
                        assert(motion.position.z == 9);
                    }
                    // Rounding follows the actual float intermediate, with one grid cell
                    // allowed at double/float boundaries. It always rounds downward.
                    assert(std::fabs(motion.position.x - std::floor(x * 100) / 100) < 0.01002);
                    assert(std::fabs(motion.position.y - std::floor(y * 100) / 100) < 0.01002);
                }
            }
        }
    }
    for (float angle : {-2.5f, -0.2f, 0.0f, 0.8f, 2.5f}) {
        const th20::Vector3 input(2, -3, 17);
        th20::Vector3 distinct(0, 0, 23), alias = input;
        th20::rotate_xy(distinct, input, angle);
        th20::rotate_xy(alias, alias, angle);
        assert(alias.x == distinct.x && alias.y == distinct.y);
        assert(alias.z == 17 && distinct.z == 23);
        assert(near(alias.x * alias.x + alias.y * alias.y, 13));
        th20::polar(distinct, angle, 4);
        assert(distinct.z == 23 && near(distinct.x * distinct.x + distinct.y * distinct.y, 16));
    }
    for (float value : {-3.456f, -1.0f, -0.0f, 0.0f, 0.009f, 3.456f}) {
        th20::Motion motion;
        motion.position = th20::Vector3(value, value, 17);
        motion.snap_position();
        const float expected = float(std::floor(double(value * 100.0f))) / 100.0f;
        assert(std::bit_cast<unsigned>(motion.position.x) == std::bit_cast<unsigned>(expected));
        assert(motion.position.y == expected && motion.position.z == 17);
    }
    th20::default_timer_clock.value = saved_clock;
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
    check_motion_protocol();

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

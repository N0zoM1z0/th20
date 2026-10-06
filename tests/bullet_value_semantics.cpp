#include "BulletValues.hpp"
#include "BulletStyle.hpp"
#include "CollisionGeometry.hpp"
#include "Vector2.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <new>

namespace th20 {
// Independent synthetic table; does not provide original startup data.
BulletStyle bullet_styles[50];
}

namespace {
template<class T> void dirty_zero_value() {
    alignas(T) std::array<unsigned char, sizeof(T)> bytes;
    for (unsigned pattern : {0u, 0xa5u, 0xffu}) {
        bytes.fill(static_cast<unsigned char>(pattern));
        auto* value = ::new (bytes.data()) T;
        std::array<unsigned char, sizeof(T)> observed;
        std::memcpy(observed.data(), value, sizeof(T));
        for (auto byte : observed) assert(byte == 0);
        value->~T();
    }
}
}

void check_bullet_values() {
    for (std::uint32_t word : {0u, 0x80000000u, 1u, 0x80000001u, 0x3f800000u,
                              0xbf800000u, 0x7f800000u, 0xff800000u,
                              0x7fc12345u, 0xffc12345u}) {
        std::memset(th20::bullet_styles, 0xa5, sizeof(th20::bullet_styles));
        for (auto& style : th20::bullet_styles) style.radius = std::bit_cast<float>(word);
        std::array<unsigned char, sizeof(th20::bullet_styles)> before;
        std::memcpy(before.data(), th20::bullet_styles, before.size());
        for (int type = 0; type < 50; ++type)
            assert(std::bit_cast<std::uint32_t>(th20::bullet_radius(type)) == word);
        assert(std::memcmp(before.data(), th20::bullet_styles, before.size()) == 0);
    }
    std::memset(th20::bullet_styles, 0x5a, sizeof(th20::bullet_styles));
    for (int type = 0; type < 50; ++type) {
        const auto word = 0x3f000000u + std::uint32_t(type) * 0x1234u;
        th20::bullet_styles[type].radius = std::bit_cast<float>(word);
    }
    std::array<unsigned char, sizeof(th20::bullet_styles)> table_before;
    std::memcpy(table_before.data(), th20::bullet_styles, table_before.size());
    for (int type = 0; type < 50; ++type)
        assert(std::bit_cast<std::uint32_t>(th20::bullet_radius(type)) ==
               0x3f000000u + std::uint32_t(type) * 0x1234u);
    assert(std::memcmp(table_before.data(), th20::bullet_styles, table_before.size()) == 0);
    dirty_zero_value<th20::Vector2>();
    dirty_zero_value<th20::ExtendedCommand>();
    dirty_zero_value<th20::ShotParameters>();
    alignas(th20::BulletCommand) std::array<unsigned char, sizeof(th20::BulletCommand)> command_bytes;
    command_bytes.fill(0xa5);
    auto* command = ::new (command_bytes.data()) th20::BulletCommand;
    // Retain natural host pointer width and any implicit alignment padding.
    for (std::size_t i = 0; i < 0x28; ++i) assert(command_bytes[i] == 0);
    for (std::size_t i = 0x28; i < offsetof(th20::BulletCommand, script); ++i)
        assert(command_bytes[i] == 0xa5);
    assert(command->script == nullptr);
    assert(command->operand_00 == 0 && command->operand_1c == 0);
    command->~BulletCommand();

    namespace g = th20::geometry;
    // Check representation-sensitive behavior with an independent bit oracle.
    for (std::uint32_t word : {0u, 0x80000000u, 1u, 0x80000001u, 0x3f800000u,
                              0xbf800000u, 0x7f800000u, 0xff800000u,
                              0x7fc12345u, 0xffc12345u}) {
        const float value = std::bit_cast<float>(word);
        const bool negative_nonzero = (word >> 31) && (word & 0x7fffffffu) &&
                                     (word & 0x7fffffffu) <= 0x7f800000u;
        const auto expected = negative_nonzero ? word & 0x7fffffffu : word;
        assert(std::bit_cast<std::uint32_t>(g::absolute(value)) == expected);
    }
    // Integer lattice has exactly represented squared distances and dimensions.
    for (int x = -16; x <= 16; ++x) for (int y = -16; y <= 16; ++y) {
        for (int radius = -10; radius <= 10; ++radius) {
            const bool inside = x*x + y*y <= radius*radius;
            assert(g::circle_point(float(x)+3, float(y)-5, 3, -5, float(radius)) == inside);
        }
        for (int width = -4; width <= 20; width += 2) {
            const bool inside = width > 0 && std::abs(x)*2 < width && std::abs(y) < 6;
            assert(g::rectangle_point(float(x)+3, float(y)-5, 3, -5, float(width), 12) == inside);
        }
    }
    assert(g::circle_point(3, 4, 0, 0, 5));
    assert(!g::circle_point(std::nextafter(3.0f, 4.0f), 4, 0, 0, 5));
    assert(g::rectangle_point(std::nextafter(1.0f, 0.0f), 0, 0, 0, 2, 2));
    assert(!g::rectangle_point(1, 0, 0, 0, 2, 2));
    assert(!g::rectangle_point(0, 0, 0, 0, -2, 2));
    assert(g::circle_point(-0.0f, 0, 0, 0, -0.0f));
    const auto nan = std::numeric_limits<float>::quiet_NaN();
    const auto inf = std::numeric_limits<float>::infinity();
    assert(!g::circle_point(nan, 0, 0, 0, 1));
    assert(!g::circle_point(0, 0, 0, 0, nan));
    assert(g::circle_point(inf, 0, 0, 0, inf));
    assert(!g::rectangle_point(nan, 0, 0, 0, inf, inf));
    assert(!g::rectangle_point(inf, 0, 0, 0, inf, inf));
    assert(g::rectangle_point(0, 0, 0, 0, inf, inf));
}

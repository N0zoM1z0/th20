#pragma once

#include "Timer.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-032: two native arrays of eighteen 68-byte records at 0x0050FDD0.
// The roles of the two float values at 0x30 and 0x34 remain unknown.
struct ScoreEntry {
    std::uint8_t digits[12];
    Vector3 position;
    float speed;
    std::uint32_t color;
    Timer age;
    float value_30;
    float value_34;
    std::uint8_t active;
    std::uint8_t length;
    std::int32_t bonus;
    float multiplier;

    ScoreEntry();
};

static_assert(sizeof(ScoreEntry) == 68);
static_assert(offsetof(ScoreEntry, position) == 0x0c);
static_assert(offsetof(ScoreEntry, speed) == 0x18);
static_assert(offsetof(ScoreEntry, color) == 0x1c);
static_assert(offsetof(ScoreEntry, age) == 0x20);
static_assert(offsetof(ScoreEntry, value_30) == 0x30);
static_assert(offsetof(ScoreEntry, value_34) == 0x34);
static_assert(offsetof(ScoreEntry, active) == 0x38);
static_assert(offsetof(ScoreEntry, length) == 0x39);
static_assert(offsetof(ScoreEntry, bonus) == 0x3c);
static_assert(offsetof(ScoreEntry, multiplier) == 0x40);

} // namespace th20

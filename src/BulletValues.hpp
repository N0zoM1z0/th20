#pragma once

#include "Timer.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// Shared 64-byte state: fourteen entries in Bullet, twenty-four in Laser.
// Slots have opcode-dependent meanings; neutral names preserve that uncertainty.
struct ExtendedCommand {
    Timer timer;
    float scalar_10;
    float scalar_14;
    Vector3 vector_18;
    Vector3 vector_24;
    std::uint32_t word_30;
    std::uint32_t word_34;
    std::uint32_t word_38;
    std::uint32_t word_3c;

    ExtendedCommand();
};

struct ShotParameters {
    std::uint32_t type;
    std::uint32_t color;
    Vector3 position;
    float angle;
    float angle_step;
    float speed;
    float speed_step;
    std::int16_t count;
    std::int16_t rows;

    ShotParameters();
};

// ECL command operands. Original type spelling and opcode-dependent aliases
// remain open. The final slot is consumed as a script-name pointer by opcode24.
struct BulletCommand {
    float operand_00;
    float operand_04;
    float operand_08;
    float operand_0c;
    std::int32_t operand_10;
    std::int32_t operand_14;
    std::int32_t operand_18;
    std::int32_t operand_1c;
    std::uint32_t opcode;
    std::uint32_t flags;
    const char* script;

    BulletCommand();
};

static_assert(sizeof(ExtendedCommand) == 64);
static_assert(offsetof(ExtendedCommand, scalar_10) == 0x10);
static_assert(offsetof(ExtendedCommand, vector_18) == 0x18);
static_assert(offsetof(ExtendedCommand, vector_24) == 0x24);
static_assert(offsetof(ExtendedCommand, word_30) == 0x30);
static_assert(sizeof(ShotParameters) == 40);
static_assert(offsetof(ShotParameters, position) == 8);
static_assert(offsetof(ShotParameters, angle_step) == 0x18);
static_assert(offsetof(ShotParameters, speed) == 0x1c);
static_assert(offsetof(ShotParameters, count) == 0x24);
static_assert(offsetof(ShotParameters, rows) == 0x26);
static_assert(offsetof(BulletCommand, opcode) == 0x20);
static_assert(offsetof(BulletCommand, script) == 0x28);
#if defined(_M_IX86)
static_assert(sizeof(BulletCommand) == 44);
#endif

} // namespace th20

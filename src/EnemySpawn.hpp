#pragma once

#include "EnemyCounters.hpp"
#include "Identifier32.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// Bit zero of the second spawn mask controls viewport-relative movement.
struct SpawnFlags { std::uint32_t bits; };

struct EnemySpawn {
    Vector3 position;
    std::int32_t field_0c, field_10, health;
    std::uint32_t flags_18;
    SpawnFlags flags_1c;
    EnemyCounters variables;
    Identifier32 field_50;

    EnemySpawn();
};

static_assert(sizeof(Identifier32) == 4);
static_assert(sizeof(SpawnFlags) == 4);
static_assert(sizeof(EnemySpawn) == 84);
static_assert(offsetof(EnemySpawn, field_0c) == 0x0c);
static_assert(offsetof(EnemySpawn, health) == 0x14);
static_assert(offsetof(EnemySpawn, flags_1c) == 0x1c);
static_assert(offsetof(EnemySpawn, variables) == 0x20);
static_assert(offsetof(EnemySpawn, field_50) == 0x50);

} // namespace th20

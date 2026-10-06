#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Typed 48-byte value at the beginning of native EnemyData. Field roles remain
// unnamed; constructors and reset establish four integers and eight floats.
struct EnemyCounters {
    std::uint32_t field_00, field_04, field_08, field_0c;
    float field_10, field_14, field_18, field_1c;
    float field_20, field_24, field_28, field_2c;

    EnemyCounters();
    void reset();
};

static_assert(sizeof(EnemyCounters) == 48);
static_assert(offsetof(EnemyCounters, field_10) == 16);
static_assert(offsetof(EnemyCounters, field_2c) == 44);

} // namespace th20

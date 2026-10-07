#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Actual mixed integer/float ANM value at AnimationBase+444.
// Offset labels retain unresolved field roles and original names.
struct AnmVariables {
    std::int32_t field_00, field_04, field_08, field_0c;
    float field_10, field_14, field_18, field_1c, field_20, field_24, field_28;
    std::int32_t field_2c, field_30;
    float field_34, field_38;
    std::int32_t field_3c;
    AnmVariables();
};

static_assert(sizeof(AnmVariables) == 64);
static_assert(offsetof(AnmVariables, field_10) == 16);
static_assert(offsetof(AnmVariables, field_2c) == 44);
static_assert(offsetof(AnmVariables, field_3c) == 60);

} // namespace th20

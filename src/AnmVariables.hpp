#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Actual mixed integer/float ANM value at AnimationBase+444.
// Offset labels retain unresolved field roles and original names.
struct AnmVariables {
    // Variable slot 10000 is a script-owned word whose role depends on the
    // consuming animation path. These aliases name observed count uses; they
    // are one storage word, not additional state or a universal fixed meaning.
    union {
        std::int32_t field_00;
        std::int32_t geometry_vertex_count;
        std::int32_t draw_shape_count;
        std::int32_t particle_grid_count;
    };
    std::int32_t field_04, field_08, field_0c;
    float field_10, field_14, field_18, field_1c, field_20, field_24;
    union {
        float field_28;
        float particle_grid_angle_offset;
    };
    std::int32_t field_2c, field_30;
    float field_34, field_38;
    std::int32_t field_3c;
    AnmVariables();
};

static_assert(sizeof(AnmVariables) == 64);
static_assert(offsetof(AnmVariables, field_00) == 0);
static_assert(offsetof(AnmVariables, geometry_vertex_count) == 0);
static_assert(offsetof(AnmVariables, draw_shape_count) == 0);
static_assert(offsetof(AnmVariables, particle_grid_count) == 0);
static_assert(offsetof(AnmVariables, field_10) == 16);
static_assert(offsetof(AnmVariables, field_28) == 0x28);
static_assert(offsetof(AnmVariables, particle_grid_angle_offset) == 0x28);
static_assert(offsetof(AnmVariables, field_2c) == 44);
static_assert(offsetof(AnmVariables, field_3c) == 60);

} // namespace th20

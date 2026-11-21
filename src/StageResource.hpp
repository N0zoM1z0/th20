#pragma once
#include "Interpolation.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
class AnimationFile;

// The process Stage/Background owner at 0x005C069C. Its original class tag
// remains unresolved; these are only independently observed member regions.
struct StageBackgroundFogOwner {
    std::byte unknown_000[0x134];
    FogInterpolation fog_interpolation;
    std::byte unknown_1d8[0x17c];
    FogValue current_fog;

    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};

struct StageResourceOwner {
    std::byte unknown_000[0x10];
    StageBackgroundFogOwner background;
    std::byte unknown_380[0x2fb4];
    AnimationFile* animation_file_value;

    AnimationFile* animation_file();
    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};

extern StageResourceOwner* process_stage_resource;

static_assert(offsetof(StageBackgroundFogOwner, fog_interpolation) == 0x134);
static_assert(offsetof(StageBackgroundFogOwner, current_fog) == 0x354);
static_assert(sizeof(StageBackgroundFogOwner) == 0x370);
static_assert(offsetof(StageResourceOwner, background) == 0x10);
#if defined(_M_IX86)
// The process owner contains a native 32-bit pointer at this x86 offset.
static_assert(offsetof(StageResourceOwner, animation_file_value) == 0x3334);
#endif
}

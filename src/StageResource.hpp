#pragma once
#include "Interpolation.hpp"
#include "Timer.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
class AnimationFile;

// The first twelve bytes of a variable-length StageResource record. The
// signed stride is consumed even for records whose kind does not match.
struct StageResourceRecordHeader {
    std::int32_t timer_value;
    std::int16_t kind;
    std::int16_t stride;
    std::int32_t identifier[1];
};
static_assert(sizeof(StageResourceRecordHeader) == 12);
static_assert(offsetof(StageResourceRecordHeader, timer_value) == 0x0);
static_assert(offsetof(StageResourceRecordHeader, kind) == 0x4);
static_assert(offsetof(StageResourceRecordHeader, stride) == 0x6);
static_assert(offsetof(StageResourceRecordHeader, identifier) == 0x8);

// The process Stage/Background owner at 0x005C069C. Its original class tag
// remains unresolved; these are only independently observed member regions.
struct StageBackgroundFogOwner {
    Timer selection_timer;
    std::uint32_t selected_record_offset;
    std::byte unknown_014[0x120];
    FogInterpolation fog_interpolation;
    std::byte unknown_1d8[0x17c];
    FogValue current_fog;

    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};

struct StageResourceOwner {
    std::byte unknown_000[0x10];
    StageBackgroundFogOwner background;
    std::byte unknown_380[0x2fb0];
    const std::byte* record_data;
    AnimationFile* animation_file_value;

    AnimationFile* animation_file();
    void select_record(std::int32_t identifier);
    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};

extern StageResourceOwner* process_stage_resource;

static_assert(offsetof(StageBackgroundFogOwner, selection_timer) == 0x000);
static_assert(offsetof(StageBackgroundFogOwner, selected_record_offset) == 0x010);
static_assert(offsetof(StageBackgroundFogOwner, fog_interpolation) == 0x134);
static_assert(offsetof(StageBackgroundFogOwner, current_fog) == 0x354);
static_assert(sizeof(StageBackgroundFogOwner) == 0x370);
static_assert(offsetof(StageResourceOwner, background) == 0x10);
#if defined(_M_IX86)
// These two adjacent process-owner pointers are independently observed.
static_assert(offsetof(StageResourceOwner, record_data) == 0x3330);
static_assert(offsetof(StageResourceOwner, animation_file_value) == 0x3334);
#endif
}

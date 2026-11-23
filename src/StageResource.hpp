#pragma once
#include "Animation.hpp"
#include "Interpolation.hpp"
#include "Timer.hpp"
#include "Viewport.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
class AnimationFile;
struct StageResourceOwner;

// The instruction stream is variable length: time/opcode/size form the
// native eight-byte instruction header and argument zero follows at +0x08.
// The selector and the 8.5KB VM both consume the same signed size field.
struct StageResourceInstructionHeader {
    std::int32_t time;
    std::int16_t opcode;
    std::int16_t size;
    std::int32_t arguments[1];
};
static_assert(sizeof(StageResourceInstructionHeader) == 12);
static_assert(offsetof(StageResourceInstructionHeader, time) == 0x0);
static_assert(offsetof(StageResourceInstructionHeader, opcode) == 0x4);
static_assert(offsetof(StageResourceInstructionHeader, size) == 0x6);
static_assert(offsetof(StageResourceInstructionHeader, arguments) == 0x8);

// Native ScriptState is the 0x3310-byte subobject at Background+0x10.
// Its historical class/type spelling is still unresolved; this view names
// only fields independently anchored by the original VM and Fog routines.
struct StageBackgroundFogOwner {
    Timer timer;
    std::uint32_t instruction_offset;
    std::uint8_t camera_motion;
    std::byte unknown_015[3];
    Timer motion_timer;
    Timer secondary_motion_timer;
    VectorInterpolation direction_interpolation;
    VectorInterpolation position_interpolation;
    VectorInterpolation up_interpolation;
    FogInterpolation fog_interpolation;
    FloatInterpolation fov_interpolation;
    ViewportState camera;
    StageResourceOwner* owner;
    Animation animations[8];
    std::uint32_t fields_3294[17];
    Timer mesh_timers[2];
    float mesh_phase_x[2];
    float mesh_phase_y[2];
    std::uint32_t mesh_mode;
    std::uint32_t overlay_color;

    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};
using StageBackgroundScriptState = StageBackgroundFogOwner;

// Process Background owner at 0x005C069C. The first subobject is the complete
// VM state; the trailing fields are anchored by native resource/animation,
// update, fade and frame-count consumers. Original class name remains open.
struct StageResourceOwner {
    std::byte unknown_000[0x10];
    StageBackgroundScriptState script_state;
    Animation* primitive_animations;
    void* file;
    void* objects;
    void* instances;
    const StageResourceInstructionHeader* instructions;
    AnimationFile* animation_file_value;
    std::uint32_t rendered[3];
    std::uint32_t state_flags;
    Timer fade_timer;
    std::int32_t stage_id;
    std::uint32_t frame_count;
    const std::byte* original_data;
    std::uint32_t data_size;
    void* additional_draw;

    AnimationFile* animation_file();
    void select_record(std::int32_t identifier);
    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
};

extern StageResourceOwner* process_stage_resource;

static_assert(offsetof(StageBackgroundScriptState, timer) == 0x000);
static_assert(offsetof(StageBackgroundScriptState, instruction_offset) == 0x010);
static_assert(offsetof(StageBackgroundScriptState, camera_motion) == 0x014);
static_assert(offsetof(StageBackgroundScriptState, motion_timer) == 0x018);
static_assert(offsetof(StageBackgroundScriptState, secondary_motion_timer) == 0x028);
static_assert(offsetof(StageBackgroundScriptState, direction_interpolation) == 0x038);
static_assert(offsetof(StageBackgroundScriptState, position_interpolation) == 0x08c);
static_assert(offsetof(StageBackgroundScriptState, up_interpolation) == 0x0e0);
static_assert(offsetof(StageBackgroundScriptState, fog_interpolation) == 0x134);
static_assert(offsetof(StageBackgroundScriptState, fov_interpolation) == 0x1d8);
static_assert(offsetof(StageBackgroundScriptState, camera) == 0x204);
static_assert(offsetof(StageBackgroundScriptState, owner) == 0x370);
#if defined(_M_IX86)
static_assert(offsetof(StageBackgroundScriptState, animations) == 0x374);
static_assert(offsetof(StageBackgroundScriptState, fields_3294) == 0x3294);
static_assert(offsetof(StageBackgroundScriptState, mesh_timers) == 0x32d8);
static_assert(offsetof(StageBackgroundScriptState, mesh_phase_x) == 0x32f8);
static_assert(offsetof(StageBackgroundScriptState, mesh_phase_y) == 0x3300);
static_assert(offsetof(StageBackgroundScriptState, mesh_mode) == 0x3308);
static_assert(offsetof(StageBackgroundScriptState, overlay_color) == 0x330c);
static_assert(sizeof(StageBackgroundScriptState) == 0x3310);
static_assert(offsetof(StageResourceOwner, script_state) == 0x010);
static_assert(offsetof(StageResourceOwner, primitive_animations) == 0x3320);
static_assert(offsetof(StageResourceOwner, file) == 0x3324);
static_assert(offsetof(StageResourceOwner, objects) == 0x3328);
static_assert(offsetof(StageResourceOwner, instances) == 0x332c);
static_assert(offsetof(StageResourceOwner, instructions) == 0x3330);
static_assert(offsetof(StageResourceOwner, animation_file_value) == 0x3334);
static_assert(offsetof(StageResourceOwner, rendered) == 0x3338);
static_assert(offsetof(StageResourceOwner, state_flags) == 0x3344);
static_assert(offsetof(StageResourceOwner, fade_timer) == 0x3348);
static_assert(offsetof(StageResourceOwner, stage_id) == 0x3358);
static_assert(offsetof(StageResourceOwner, frame_count) == 0x335c);
static_assert(offsetof(StageResourceOwner, original_data) == 0x3360);
static_assert(offsetof(StageResourceOwner, data_size) == 0x3364);
static_assert(offsetof(StageResourceOwner, additional_draw) == 0x3368);
static_assert(sizeof(StageResourceOwner) == 0x336c);
#endif
}

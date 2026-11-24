#pragma once
#include "Animation.hpp"
#include "Interpolation.hpp"
#include "Timer.hpp"
#include "Viewport.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
class AnimationFile;
struct Graphics;
struct StageResourceOwner;

// The instruction stream is variable length: time/opcode/size form the
// native eight-byte instruction header and argument zero follows at +0x08.
// The selector and the 8.5KB VM both consume the same signed size field.
struct StageResourceFileHeader {
    std::int16_t object_count;
    std::int16_t animation_count;
    std::uint32_t instance_offset;
    std::uint32_t script_offset;
    std::uint32_t field_0c;
    char animation_name[128];
};
static_assert(sizeof(StageResourceFileHeader) == 0x90);
static_assert(offsetof(StageResourceFileHeader, animation_count) == 0x02);
static_assert(offsetof(StageResourceFileHeader, instance_offset) == 0x04);
static_assert(offsetof(StageResourceFileHeader, animation_name) == 0x10);

// Typed view of the native object parameter block. The update path advances
// rotation_y by rotation_y_velocity; the culler consumes the center and full
// extent vectors at object offsets +0x18 and +0x24 respectively.
struct StageResourceObjectParameters {
    std::uint32_t projected_bounds_bypass;
    float rotation_y_velocity;
    float rotation_y;
    float field_0c;
    float field_10;
    Vector3 bounds_center;
    Vector3 bounds_extent;
};
static_assert(sizeof(Vector3) == 0x0c);
static_assert(sizeof(StageResourceObjectParameters) == 0x2c);
static_assert(offsetof(StageResourceObjectParameters, projected_bounds_bypass) == 0x00);
static_assert(offsetof(StageResourceObjectParameters, rotation_y_velocity) == 0x04);
static_assert(offsetof(StageResourceObjectParameters, rotation_y) == 0x08);
static_assert(offsetof(StageResourceObjectParameters, bounds_center) == 0x14);
static_assert(offsetof(StageResourceObjectParameters, bounds_extent) == 0x20);

// Native resource object and its variable-length primitive table. Object
// records are 0x30 bytes; primitive records begin immediately after the object
// and advance by their signed byte-size field until a negative type sentinel.
struct StageResourceObjectRecord {
    static constexpr std::int8_t has_active_animations_mask = 0x01;
    static constexpr std::int8_t passed_viewport_cull_mask = 0x02;

    std::uint16_t identifier;
    union {
        std::uint8_t layer;
        std::int8_t signed_layer;
    };
    std::int8_t flags;
    StageResourceObjectParameters parameters;

    // Original 0x473B20 object-space distance and projected-bounds culler.
    std::int32_t is_outside_viewport(const Vector3& instance_offset,
                                     float max_distance_squared,
                                     const ViewportState& viewport) const;
};
static_assert(sizeof(StageResourceObjectRecord) == 0x30);
static_assert(offsetof(StageResourceObjectRecord, signed_layer) == 0x02);
static_assert(offsetof(StageResourceObjectRecord, flags) == 0x03);
static_assert(offsetof(StageResourceObjectRecord, parameters) == 0x04);

// The instance visibility bit shares its native short with retained flags.
struct StageResourceInstanceFlagBits {
    std::uint16_t visible : 1;
    std::uint16_t retained : 15;
};
static_assert(sizeof(StageResourceInstanceFlagBits) == 2);

// Per-instance object placement list. The signed object index is the
// terminating sentinel; each record is exactly two shorts plus a Vector3.
struct StageResourceInstanceRecord {
    std::int16_t object_index;
    union {
        std::int16_t flags;
        StageResourceInstanceFlagBits flag_bits;
    };
    Vector3 position;
};
static_assert(sizeof(StageResourceInstanceRecord) == 0x10);
static_assert(offsetof(StageResourceInstanceRecord, position) == 0x04);

enum class StageResourcePrimitiveKind : std::int16_t {
    animation_transform = 0,
};
static_assert(sizeof(StageResourcePrimitiveKind) == 2);

struct StageResourcePrimitiveHeader {
    std::int16_t type;
    std::int16_t size;
    std::int16_t script_index;
    std::int16_t animation_index;
    StageResourcePrimitiveHeader* advance(std::int32_t size);
};
static_assert(sizeof(StageResourcePrimitiveHeader) == 8);
static_assert(offsetof(StageResourcePrimitiveHeader, type) == 0x00);
static_assert(offsetof(StageResourcePrimitiveHeader, size) == 0x02);
static_assert(offsetof(StageResourcePrimitiveHeader, script_index) == 0x04);
static_assert(offsetof(StageResourcePrimitiveHeader, animation_index) == 0x06);

struct StageResourcePrimitiveTransform {
    StageResourcePrimitiveHeader header;
    Vector3 position;
    float scale_x;
    float scale_y;
};
static_assert(sizeof(StageResourcePrimitiveTransform) == 0x1c);
static_assert(offsetof(StageResourcePrimitiveTransform, position) == 0x08);
static_assert(offsetof(StageResourcePrimitiveTransform, scale_x) == 0x14);
static_assert(offsetof(StageResourcePrimitiveTransform, scale_y) == 0x18);

// A resource object is immediately followed by its variable-length primitive
// stream. This view names the first record without changing the 0x30-byte
// standalone object record used by the object table and update routines.
struct StageResourceObjectPrimitiveStream {
    StageResourceObjectRecord object;
    StageResourcePrimitiveTransform primitives[1];
};
static_assert(offsetof(StageResourceObjectPrimitiveStream, primitives) == 0x30);
static_assert(sizeof(StageResourceObjectPrimitiveStream) == 0x4c);

struct StageResourceRenderCounts {
    std::uint32_t visible_objects;
    std::uint32_t culled_objects;
    std::uint32_t primitive_draws;
};
static_assert(sizeof(StageResourceRenderCounts) == 0x0c);
static_assert(offsetof(StageResourceRenderCounts, visible_objects) == 0x00);
static_assert(offsetof(StageResourceRenderCounts, culled_objects) == 0x04);
static_assert(offsetof(StageResourceRenderCounts, primitive_draws) == 0x08);

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

// Typed overlay for the script-state scalar slots. The cull radius squared
// is independently consumed as a float by the native object-layer draw path.
struct StageBackgroundScriptScalars {
    std::uint32_t fields_before_cull_distance[8];
    float cull_distance_squared;
    std::uint32_t fields_after_cull_distance[8];
};
static_assert(sizeof(StageBackgroundScriptScalars) == 0x44);
static_assert(offsetof(StageBackgroundScriptScalars, cull_distance_squared) == 0x20);

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
    union {
        std::uint32_t fields_3294[17];
        StageBackgroundScriptScalars scalars;
    };
    Timer mesh_timers[2];
    float mesh_phase_x[2];
    float mesh_phase_y[2];
    std::uint32_t mesh_mode;
    std::uint32_t overlay_color;

    void set_fog(std::int32_t duration, std::int32_t mode,
                 const FogValue& target);
    void __fastcall execute_script();
    void update_camera_motion(const float* rate);
    void __fastcall update_meshes();
    void draw_inline_animations_for_layer(std::int32_t layer);
};
using StageBackgroundScriptState = StageBackgroundFogOwner;

// Process Background owner at 0x005C069C. The first subobject is the complete
// VM state; the trailing fields are anchored by native resource/animation,
// update, fade and frame-count consumers. Original class name remains open.
struct StageResourceOwner {
    std::byte unknown_000[0x10];
    StageBackgroundScriptState script_state;
    Animation* primitive_animations;
    const StageResourceFileHeader* file;
    StageResourceObjectRecord** objects;
    StageResourceInstanceRecord* instances;
    const StageResourceInstructionHeader* instructions;
    AnimationFile* animation_file_value;
    union {
        std::uint32_t rendered[3];
        StageResourceRenderCounts render_counts;
    };
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
    void interrupt_animations(std::int32_t event);
    void set_primary_rotation_flag(std::uint32_t value);
    std::int32_t __fastcall update_objects();
    std::int32_t __fastcall update();
    std::int32_t draw_objects_for_layer(std::int32_t layer);
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
static_assert(offsetof(StageBackgroundScriptState, scalars) +
              offsetof(StageBackgroundScriptScalars, cull_distance_squared) ==
              0x32b4);
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
static_assert(offsetof(StageResourceOwner, render_counts) == 0x3338);
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

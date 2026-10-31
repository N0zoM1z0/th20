#pragma once
// Borrowed game AnimationFile: no independent Renderer or AnimationFile
// instance. The physical 0x70B owner is already defined by AnimationFile.
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
struct NativeAnmGroupHeader {
    std::uint32_t signature;
    std::uint16_t sprite_count;
    std::uint16_t script_count;
    std::uint32_t field_08, field_0c;
    std::uint32_t embedded_name_offset;
    std::uint32_t field_14,field_18,field_1c;
    // Original per-group parser makes a BYTE read at header+0x20.
    // The earlier uint32 field was a decompiler-induced width mistake.
    std::uint8_t flag_20, reserved_21, reserved_22, reserved_23;
    std::uint32_t next_header_offset;
};
static_assert(sizeof(NativeAnmGroupHeader)==0x28);
static_assert(offsetof(NativeAnmGroupHeader,sprite_count)==4);
static_assert(offsetof(NativeAnmGroupHeader,script_count)==6);
static_assert(offsetof(NativeAnmGroupHeader,flag_20)==0x20);
static_assert(offsetof(NativeAnmGroupHeader,next_header_offset)==0x24);
struct NativeAnimationFileLoadView : AnimationFile {
    std::int32_t load_resource_44a700(const char* path);
};
// The original game global 0x005C0028 is the Renderer manager, not
// an extra member in AnimationFile. Original 1022B parent has
// a genuine PE HIGHLOW +0x32E to this manager before 336B group parse.
struct NativeRendererAnmGroupView : AnimationPoolOwner {
    std::int32_t parse_group_44ebf0(NativeAnimationFileLoadView* file,
        std::int32_t index,const NativeAnmGroupHeader* header);
};
}

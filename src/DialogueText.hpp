#pragma once

#include <cstdint>
#include "AnimationHandle.hpp"
#include "Cursor.hpp"
#include "DialogueFlags.hpp"
#include "Timer.hpp"
#include "Vector3.hpp"
#include <array>

namespace th20::dialogue_text {

// Original shared storage starts at 0x005c4a20; its allocation remains external.
extern char decoded_text[];

// Native ABI takes one byte and returns a full int, not a bool.
int is_lead(std::uint8_t value);

// Input includes its encoded NUL. Both passes must stay within result storage;
// a lead byte must have a non-NUL trail byte. Each call overwrites the shared
// result, so callers must consume or copy it before another call.
const char* decode(const char* input);

} // namespace th20::dialogue_text

namespace th20 {

// Complete nonvirtual message owner. Cursor owns its three containers.
struct Dialogue {
    std::int32_t state;
    Timer timer_04, timer_14, timer_24;
    std::array<AnimationHandle, 4> portraits, portrait_overlays;
    AnimationHandle handle_54, handle_58, handle_5c, handle_60;
    AnimationHandle handle_64, handle_68, handle_6c, handle_70;
    std::uint32_t field_74, field_78;
    Cursor cursor;
    std::int32_t field_c8;
    std::uint8_t* script;
    Vector3 positions[4];
    std::int32_t ready_state;
    DialogueFlags flags;
    std::int32_t field_108, field_10c, field_110, field_114;
    std::int32_t fields_118[4];
    Vector3 text_position;
    float text_width;
    std::int32_t field_138, field_13c;

    explicit Dialogue(std::uint8_t* input);
    ~Dialogue();
    std::int32_t ready();
    void follow_box(Animation* animation);
};

#if defined(_M_IX86)
static_assert(sizeof(Dialogue) == 0x140);
static_assert(offsetof(Dialogue, portraits) == 0x34);
static_assert(offsetof(Dialogue, portrait_overlays) == 0x44);
static_assert(offsetof(Dialogue, cursor) == 0x7C);
static_assert(offsetof(Dialogue, script) == 0xCC);
static_assert(offsetof(Dialogue, positions) == 0xD0);
static_assert(offsetof(Dialogue, ready_state) == 0x100);
static_assert(offsetof(Dialogue, flags) == 0x104);
static_assert(offsetof(Dialogue, text_position) == 0x128);
#endif

} // namespace th20

#pragma once
#include "AnimationHandle.hpp"
#include "Context.hpp"
#include "Timer.hpp"
#include "Vector3.hpp"

namespace th20 {
// Native construction clears this aggregate; bit 0 denotes an active spell.
// Other bit meanings and the complete start/finish protocol remain open.
struct CardFlags { std::uint32_t bits; };

// Actual CardInf owner: five typed handles, Timer, name, scalar state, two
// aligned double clocks and a real Vector3. Alignment supplies the gaps.
struct Card final : TaskInfo {
    AnimationHandle background_handle;
    AnimationHandle info_handles[3];
    AnimationHandle effect_handle;
    Timer age;
    char name[64];
    std::int32_t spell_index;
    CardFlags spell_flags;
    std::int32_t bonus, initial_bonus, duration;
    std::uint32_t capture_index, frames, last_frames;
    double start_time, elapsed;
    std::int32_t encoded_time;
    Vector3 position;
    std::uint32_t field_b8;
    std::int32_t player_index;
    Context* context;
    Card() noexcept;
    // Native cleanup is declared separately; construction is not disposal.
    ~Card() override;
    void encode_time(std::int32_t seconds, std::int32_t hundredths);
    std::int32_t invalid_encoded_time();
    bool active();
    // Valid index is 0 or 1. Binding does not publish or register callbacks.
    void bind_context(std::int32_t index);
};
Card* card(std::int32_t index);

#if defined(_M_IX86)
static_assert(sizeof(Card)==0xc8);
static_assert(offsetof(Card,background_handle)==0x10);
static_assert(offsetof(Card,info_handles)==0x14);
static_assert(offsetof(Card,effect_handle)==0x20);
static_assert(offsetof(Card,age)==0x24);
static_assert(offsetof(Card,name)==0x34);
static_assert(offsetof(Card,spell_flags)==0x78);
static_assert(offsetof(Card,start_time)==0x98);
static_assert(offsetof(Card,elapsed)==0xa0);
static_assert(offsetof(Card,encoded_time)==0xa8);
static_assert(offsetof(Card,position)==0xac);
static_assert(offsetof(Card,context)==0xc0);
#endif
}

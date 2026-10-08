#pragma once
#include "TaskInfo.hpp"
#include "Timer.hpp"
#include "Configuration.hpp"
namespace th20 {
// EXACT-077: native GameInf storage, independently allocated at size 0x110.
// Field-offset names preserve unknown roles. No source-only Services suffix.

// Full aggregate zeroing is distinct from the inherited Task flag word.
struct GameFlagWord { std::uint32_t bits; };
struct GameController final : TaskInfo {
    Timer frame_timer, secondary_timer;
    std::uint32_t load_stage, field_34;
    Configuration configuration;
    GameFlagWord game_flags;
    std::uint32_t field_ec,field_f0,field_f4;
    double field_f8,field_100;
    std::int32_t restart_mode;
    std::uint32_t field_10c;
    GameController() noexcept;
    // Native destruction/cleanup is a separate, still open protocol.
    ~GameController() override;
    int update_suppressed() const;
    int animation_frozen() const;
    std::int32_t restart() const;
    void clear_flag_6();
};
#if defined(_M_IX86)
static_assert(sizeof(GameController)==0x110);
static_assert(offsetof(GameController,frame_timer)==0x10);
static_assert(offsetof(GameController,configuration)==0x38);
static_assert(offsetof(GameController,game_flags)==0xe8);
static_assert(offsetof(GameController,field_f8)==0xf8);
static_assert(offsetof(GameController,restart_mode)==0x108);
#endif
}

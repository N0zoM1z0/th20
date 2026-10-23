#pragma once

#include <cstddef>
#include <cstdint>
#include <array>
#include "AnimationHandle.hpp"
#include "TaskInfo.hpp"
#include "Timer.hpp"

namespace th20 {

// REF-032: four 8-byte markers per boss panel. Native 0x004B3BB0 reads
// fraction as a float. The second word's role and signedness are unresolved.
struct HudGauge {
    float fraction;
    std::uint32_t value_04;

    HudGauge();
};

static_assert(sizeof(HudGauge) == 8);
static_assert(offsetof(HudGauge, fraction) == 0);
static_assert(offsetof(HudGauge, value_04) == 4);

struct FrontBossPanel {
    float field_00, field_04;
    std::int32_t field_08, field_0c;
    HudGauge gauges[4];
    AnimationHandle handles[7];
    std::int32_t field_4c, field_50;
    FrontBossPanel() noexcept;
};

struct FrontFlags {
    union {
        std::uint32_t bits;
        struct {
            std::uint32_t bit_0:1, field_1:2, bit_3:1, bit_4:1, field_5:3;
            std::uint32_t bit_8:1, field_9:2, field_11:2, bit_13:1, upper:18;
        } fields;
    };
    FrontFlags() noexcept;
};

class AnimationFile;
struct Dialogue;

// Complete native FrontInf storage. Resource startup and destruction remain
// separate protocols; construction retains the as-yet-unloaded front_file.
class FrontInf : public TaskInfo {
public:
    std::array<AnimationHandle, 7> handles_10, handles_2c;
    std::array<AnimationHandle, 2> handles_48;
    std::int32_t field_50;
    std::array<std::int32_t, 6> fields_54;
    std::int32_t field_6c;
    std::array<std::int32_t, 6> fields_70;
    std::int32_t field_88;
    std::array<std::int32_t, 1> fields_8c;
    AnimationHandle handle_90;
    std::array<AnimationHandle, 10> handles_94;
    std::array<AnimationHandle, 3> handles_bc;
    AnimationHandle handle_c8, handle_cc;
    std::array<AnimationHandle, 10> handles_d0;
    AnimationHandle handle_f8, handle_fc, handle_100, handle_104, handle_108;
    AnimationHandle handle_10c, handle_110, handle_114, handle_118;
    std::int32_t field_11c;
    float field_120, field_124;
    std::int32_t field_128, field_12c, field_130, field_134, field_138;
    AnimationHandle handle_13c;
    Timer timer_140;
    FunctionChainNode* field_150;
    std::uint64_t field_158, field_160, field_168;
    AnimationFile* message_file;
    float field_174, field_178;
    std::int32_t field_17c, field_180;
    HudGauge gauges_184[4];
    FrontFlags front_flags;
    Timer timer_1a8;
    std::int32_t field_1b8;
    Dialogue* dialogue;
    std::uint8_t* message_bytes;
    std::int32_t field_1c4, field_1c8, field_1cc;
    FrontBossPanel boss_panels[3];
    AnimationFile* front_file;
    std::int32_t field_2d0;

    FrontInf();
    ~FrontInf() override;
    void enable() override;
    std::int32_t has_dialogue();
    std::int32_t dialogue_ready();
    Dialogue* dialogue_value();
    void set_field_180(std::int32_t value);
    void set_boss_gauge(std::int32_t boss, std::int32_t marker, float fraction,
                        std::int32_t value);
};

extern FrontInf* current_front;

static_assert(sizeof(FrontBossPanel) == 0x54);
static_assert(sizeof(FrontFlags) == 4);
#if defined(_M_IX86)
static_assert(sizeof(FrontInf) == 0x2d8);
static_assert(alignof(FrontInf) == 8);
static_assert(offsetof(FrontInf, field_158) == 0x158);
static_assert(offsetof(FrontInf, dialogue) == 0x1bc);
static_assert(offsetof(FrontInf, boss_panels) == 0x1d0);
static_assert(offsetof(FrontInf, front_file) == 0x2cc);
static_assert(offsetof(FrontInf, field_2d0) == 0x2d0);
#endif

} // namespace th20

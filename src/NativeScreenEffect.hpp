#pragma once
// ScreenInf uses an actual TaskInfo base and a Timer at original +0x30.
#include "TaskInfo.hpp"
#include "Timer.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativeScreenInf : TaskInfo {
    NativeScreenInf() noexcept;
    std::int32_t mode_10;
    std::uint32_t field_14;
    std::uint32_t alpha_18;
    std::uint32_t field_1c,field_20,field_24,field_28,field_2c;
    Timer timer_30;
    std::uint32_t view_40;
    void initialize_423bf0(std::int32_t mode,std::uint32_t p1,std::uint32_t p2,
                           std::uint32_t p3,std::uint32_t p4,std::int32_t draw_priority);
};
#if defined(_M_IX86)
static_assert(sizeof(NativeScreenInf)==0x44);
static_assert(offsetof(NativeScreenInf,timer_30)==0x30);
static_assert(offsetof(NativeScreenInf,view_40)==0x40);
#endif
NativeScreenInf* __cdecl screen_factory_4250f0(std::int32_t mode,std::uint32_t p1,
    std::uint32_t p2,std::uint32_t p3,std::uint32_t p4,std::int32_t priority,std::uint32_t view);
// Native 37B default-priority wrapper, selected by Bomb/Screen callers.
NativeScreenInf* __cdecl screen_effect_default_425090(std::int32_t mode,std::uint32_t p1,
    std::uint32_t p2,std::uint32_t p3,std::uint32_t p4);
}

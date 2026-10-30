#pragma once
// Independently native-observed vtable 0x0056ED1C: 64 two-float points,
// 64 four-byte color records, angle, Timer and final four-byte pointer.
#include "AnimationCallback.hpp"
#include "AnimationHandle.hpp"
#include "Vector2.hpp"
#include "Timer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
class Animation;
class NativeRibbonTrailGroup : public AnimationCallback {
public:
    std::array<Vector2,64> vertices_08;
    std::array<AnimationHandle,64> colors_208;
    float angle_308;
    Timer timer_30c;
    void* token_31c;
    explicit NativeRibbonTrailGroup(Animation* owner);
    std::int32_t update() override;
    std::int32_t draw() override;
};
static_assert(offsetof(NativeRibbonTrailGroup,vertices_08)==0x08);
static_assert(offsetof(NativeRibbonTrailGroup,colors_208)==0x208);
static_assert(offsetof(NativeRibbonTrailGroup,angle_308)==0x308);
static_assert(offsetof(NativeRibbonTrailGroup,timer_30c)==0x30C);
static_assert(offsetof(NativeRibbonTrailGroup,token_31c)==0x31C);
static_assert(sizeof(NativeRibbonTrailGroup)==0x320);
}

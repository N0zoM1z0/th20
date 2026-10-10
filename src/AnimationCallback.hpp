#pragma once
#include <cstdint>
namespace th20 {
struct Animation;
// Native SprtFuncBaseInf: vptr followed by its Animation receiver.
struct AnimationCallback {
    Animation* animation;
    explicit AnimationCallback(Animation* receiver);
    virtual ~AnimationCallback();
    virtual std::int32_t update();
    virtual std::int32_t draw();
    virtual std::int32_t slot_0c();
    virtual std::int32_t interrupt(std::int32_t event);
};
#if defined(_M_IX86)
static_assert(sizeof(AnimationCallback) == 8);
#endif
std::int32_t bullet_animation_script(Animation* animation, std::int32_t script);
}

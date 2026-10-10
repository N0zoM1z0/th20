#pragma once
#include "Animation.hpp"
#include "AnimationCallback.hpp"
#include <cassert>

namespace th20_test {

// Observe real owned callback destruction, including the resource-release order.
// A null callback has no destructor and contributes no observation.
class AnimationReleaseObserver final : public th20::AnimationCallback {
    unsigned& releases_;
public:
    AnimationReleaseObserver(th20::Animation* receiver, unsigned& releases)
        : AnimationCallback(receiver), releases_(releases) {}
    ~AnimationReleaseObserver() override {
        assert(animation->geometry == nullptr && animation->geometry_bytes == 0);
        assert(animation->callback == this);
        ++releases_;
    }
};

} // namespace th20_test

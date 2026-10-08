#include "Enemy.hpp"
#include "Animation.hpp"
#include "ClockScalar.hpp"

namespace th20 {
int Enemy::tick() {
    if (state.field_3c <= 0.0f) {
        if ((state.flags.word_04 >> 16) & 1u) {
            for (auto& link : state.animations) {
                auto* animation = link.handle.resolve();
                if (animation) animation->set_slowdown(0.0f);
            }
        }
        return state.tick();
    } else {
        float clock = default_timer_clock;
        float reduced_clock = clock - clock * state.field_3c;
        if (reduced_clock > 1.0f) reduced_clock = 1.0f;
        else if (reduced_clock < 0.0f) reduced_clock = 0.0f;
        default_timer_clock.set(reduced_clock);
        for (auto& link : state.animations) {
            auto* animation = link.handle.resolve();
            if (animation) animation->set_slowdown(state.field_3c);
        }
        int result = state.tick();
        default_timer_clock.set(clock);
        state.flags.word_04 |= 0x10000u;
        return result;
    }
}
}

#pragma once

namespace th20 {

// REF-002: the shared float view used by Timer's clock operations.
// This does not describe an enclosing interpolation or clock-controller owner.
struct ClockScalar {
    float value;

    operator float() const;
    float operator*(float delta) const;
};
static_assert(sizeof(ClockScalar) == 4);

// The observed default slot points at a float initialized to 1.0f. Timer's
// add/tick methods clear nonzero modes before selecting this slot.
extern ClockScalar default_timer_clock;
extern ClockScalar* timer_clock_sources[1];

} // namespace th20

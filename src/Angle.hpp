#pragma once

namespace th20 {

// Native reduction is bounded to 34 steps, including for infinite input.
float normalize_angle(float value);

struct Angle {
    float value;

    Angle();
    explicit Angle(float input);
};

static_assert(sizeof(Angle) == 4);

} // namespace th20

#include "EnemyMovement.hpp"
#include "Easing.hpp"

namespace th20 {

EnemyMotionInterpolation::EnemyMotionInterpolation()
    : duration(0), axis_modes{}, mode(0), flags{} {}
EnemyMovement::EnemyMovement() {}
void EnemyMotionInterpolation::stop() { duration = 0; }
float EnemyMotionInterpolation::factor() const {
    return easing(mode, timer.fraction(), static_cast<float>(duration));
}
float EnemyMotionInterpolation::factor(std::int32_t axis) const {
    return easing(axis_modes.values[axis], timer.fraction(), static_cast<float>(duration));
}
Vector3 EnemyMotionInterpolation::sample() {
    if (duration > 0) {
        ++timer;
        if (timer.at_least(duration)) {
            timer = duration;
            stop();
            if (mode != 7 && mode != 17) return end;
            else return start;
        }
    } else if (duration == 0) {
        if (mode != 7 && mode != 17) return end;
        else return start;
    }
    if ((flags.bits & 1) == 0) {
        if (mode == 7) {
            start = Vector3(start) + end;
            current = start;
        } else if (mode == 17) {
            start = Vector3(start) + tangent_end;
            tangent_end = tangent_end + end;
            current = start;
        } else if (mode == 8) {
            const float t = timer.fraction() / static_cast<float>(duration);
            const float from_weight = (t-1.0f)*(t-1.0f)*(2.0f*t+1.0f);
            const float to_weight = t*t*(3.0f-2.0f*t);
            const float from_tangent_weight = (1.0f-t)*(1.0f-t)*t;
            const float to_tangent_weight = (t-1.0f)*t*t;
            current = start * from_weight + end * to_weight
                + tangent_start * from_tangent_weight + tangent_end * to_tangent_weight;
        } else {
            const float amount = factor();
            current = (end - start) * amount + start;
        }
        return current;
    } else {
        for (int axis = 0; axis < 3; ++axis) {
            if (axis_modes.values[axis] == 7) {
                start[axis] = start[axis] + end[axis];
                current[axis] = start[axis];
            } else if (axis_modes.values[axis] == 17) {
                start[axis] = start[axis] + tangent_end[axis];
                tangent_end[axis] = tangent_end[axis] + end[axis];
                current[axis] = start[axis];
            } else if (axis_modes.values[axis] == 8) {
                const float t = timer.fraction() / static_cast<float>(duration);
                const float from_weight = (t-1.0f)*(t-1.0f)*(2.0f*t+1.0f);
                const float to_weight = t*t*(3.0f-2.0f*t);
                const float from_tangent_weight = (1.0f-t)*(1.0f-t)*t;
                const float to_tangent_weight = (t-1.0f)*t*t;
                current[axis] = start[axis] * from_weight + end[axis] * to_weight
                    + tangent_start[axis] * from_tangent_weight + tangent_end[axis] * to_tangent_weight;
            } else {
                const float amount = factor(axis);
                current[axis] = (end[axis] - start[axis]) * amount + start[axis];
            }
        }
        return current;
    }
}
std::int32_t EnemyMotionInterpolation::duration_value() const { return duration; }

} // namespace th20

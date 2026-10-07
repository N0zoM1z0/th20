#include "Motion.hpp"
#include "MotionMath.hpp"
#include "ClockScalar.hpp"
#include "ScalarMath.hpp"

namespace th20 {

void Motion::update_velocity() {
    if (flags.fields.frozen) return;
    float delta;
    switch (flags.fields.mode) {
    case 0:
        polar(motion_vector(), angle_1c, value_18 * static_cast<float>(default_timer_clock));
        if (value_34 > 0.0f) vector_38 -= vector_38 * value_34;
        if (flags.fields.spin) {
            delta = value_24 * static_cast<float>(default_timer_clock);
            angle_1c = (delta - delta * value_34) + static_cast<float>(angle_1c);
        }
        break;
    case 1:
        break;
    case 2:
    case 3:
        delta = value_24 * static_cast<float>(default_timer_clock);
        value_20 += delta - delta * value_34;
        delta = value_18 * static_cast<float>(default_timer_clock);
        angle_1c = (delta - delta * value_34) + static_cast<float>(angle_1c);
        break;
    case 4:
        delta = value_24 * static_cast<float>(default_timer_clock);
        angle_30 += delta - delta * value_34;
        polar(motion_vector(), angle_28, value_18 * static_cast<float>(default_timer_clock));
        set_motion_z(0.0f);
        break;
    }
}

#ifdef _MSC_VER
// Preserve the native cookie around addressable local vector lifetimes.
#pragma strict_gs_check(push, on)
#endif
void Motion::update_position() {
    if (flags.fields.frozen) return;
    Vector3 step;
    switch (flags.fields.mode) {
    case 0:
        step = motion_vector();
        position += step;
        break;
    case 2:
        polar(step, angle_1c, value_20);
        step.z = 0.0f;
        position = motion_vector() + step;
        break;
    case 3:
        polar(step, normalize_angle(angle_1c - angle_28), value_20);
        step.x *= value_2c;
        rotate_xy(step, step, angle_28);
        step.z = 0.0f;
        position = motion_vector() + step;
        break;
    case 4: {
        Vector3 displacement;
        Vector3 previous;
        previous = position;
        velocity += motion_vector();
        const float heading = normalize_angle(angle_28 + 3.1415927410125732f / 2.0f);
        polar(displacement, heading,
              scalar_math::sine(angle_30) * value_20 * static_cast<float>(default_timer_clock));
        displacement.z = 0.0f;
        position = displacement + velocity;
        displacement = position - previous;
        angle_1c = vector_direction(displacement);
        break;
    }
    }
    snap_position();
}

#ifdef _MSC_VER
#pragma strict_gs_check(pop)
#endif
void Motion::snap_position() {
    position.x = floor_scalar(position.x * 100.0f) / 100.0f;
    position.y = floor_scalar(position.y * 100.0f) / 100.0f;
}

Vector3& Motion::motion_vector() { return vector_38; }

void Motion::set_motion_z(float value) { vector_38.z = value; }

} // namespace th20

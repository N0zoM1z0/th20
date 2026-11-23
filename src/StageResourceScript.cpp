#include "StageResource.hpp"
#include "StageResourceScriptAdapters.hpp"
#include "ClockScalar.hpp"
#include "ScalarMath.hpp"

#include <bit>
#include <cstdint>
#include <immintrin.h>

namespace th20 {
namespace {
constexpr float pi = 3.1415927410125732421875f;

float add32(float a, float b) noexcept {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
float sub32(float a, float b) noexcept {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
float mul32(float a, float b) noexcept {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
float div32(float a, float b) noexcept {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
float negate(float value) noexcept {
    return std::bit_cast<float>(std::bit_cast<std::uint32_t>(value) ^ 0x80000000u);
}
float int_float(std::int32_t value) noexcept {
    return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), value));
}
std::int32_t truncate32(float value) noexcept {
    return _mm_cvttss_si32(_mm_set_ss(value));
}

float power32(float value, unsigned exponent) noexcept {
    float result = value;
    for (unsigned index = 1; index < exponent; ++index)
        result = mul32(result, value);
    return result;
}

float shifted_quadratic(float t, float shift) noexcept {
    const float denominator = mul32(sub32(1.0f, shift), sub32(1.0f, shift));
    const float offset = div32(mul32(shift, shift), denominator);
    return div32(sub32(div32(mul32(sub32(t, shift), sub32(t, shift)),
                              denominator), offset), sub32(1.0f, offset));
}

// Stage VM interpolation uses the ECL easing protocol, not the separately
// instantiated Animation easing helper. Keep the original SSE operation order.
float ecl_easing(std::int32_t mode, float time, float duration) noexcept {
    if (duration == 0.0f) return 1.0f;
    float t = div32(time, duration);
    if (mode >= 1 && mode <= 3)
        return power32(t, static_cast<unsigned>(mode + 1));
    if (mode >= 4 && mode <= 6)
        return sub32(1.0f, power32(sub32(1.0f, t), static_cast<unsigned>(mode - 2)));
    if (mode >= 9 && mode <= 11) {
        t = mul32(t, 2.0f);
        const auto exponent = static_cast<unsigned>(mode - 7);
        t = t >= 1.0f ? sub32(2.0f, power32(sub32(2.0f, t), exponent)) :
                        power32(t, exponent);
        return div32(t, 2.0f);
    }
    if (mode >= 12 && mode <= 14) {
        t = mul32(t, 2.0f);
        const auto exponent = static_cast<unsigned>(mode - 10);
        return t >= 1.0f ?
            add32(div32(power32(sub32(t, 1.0f), exponent), 2.0f), 0.5f) :
            sub32(0.5f, div32(power32(sub32(1.0f, t), exponent), 2.0f));
    }
    switch (mode) {
    case 15: return 0.0f;
    case 16: return 1.0f;
    case 18: return scalar_math::sine(div32(mul32(t, pi), 2.0f));
    case 19:
        return sub32(1.0f, scalar_math::sine(
            add32(div32(mul32(t, pi), 2.0f), div32(pi, 2.0f))));
    case 20:
        t = mul32(t, 2.0f);
        return t >= 1.0f ?
            add32(div32(sub32(1.0f, scalar_math::sine(div32(mul32(t, pi), 2.0f))),
                        2.0f), 0.5f) :
            div32(scalar_math::sine(div32(mul32(t, pi), 2.0f)), 2.0f);
    case 21:
        t = mul32(t, 2.0f);
        return t >= 1.0f ?
            add32(div32(scalar_math::sine(
                div32(mul32(sub32(t, 1.0f), pi), 2.0f)), 2.0f), 0.5f) :
            div32(sub32(1.0f, scalar_math::sine(
                add32(div32(mul32(t, pi), 2.0f), div32(pi, 2.0f)))), 2.0f);
    default: break;
    }
    constexpr float shifts[] = {0.25f, 0.30f, 0.35f, 0.38f, 0.40f};
    if (mode >= 22 && mode <= 26)
        return shifted_quadratic(t, shifts[mode - 22]);
    if (mode >= 27 && mode <= 31)
        return sub32(1.0f, shifted_quadratic(sub32(1.0f, t), shifts[mode - 27]));
    return t;
}

void timer_set(Timer& timer, std::int32_t value) {
    timer.set(value);
}

// The interpreter's clock is an explicit pointer. A null pointer advances by
// one frame and does not consult the process-wide default clock.
void timer_tick(Timer& timer, const float* rate) noexcept {
    if (!(timer.flags & 1u)) {
        timer.reset();
        timer.set_mode(0);
        timer.flags |= 1u;
    }
    timer.flags &= ~6u;
    timer.previous = timer.current;
    if (!rate || (*rate > 0.99f && *rate < 1.01f)) {
        timer.current = std::bit_cast<std::int32_t>(
            static_cast<std::uint32_t>(timer.current) + 1u);
        timer.current_fraction = add32(timer.current_fraction, 1.0f);
    } else {
        timer.current_fraction = add32(timer.current_fraction, *rate);
        timer.current = truncate32(timer.current_fraction);
    }
}

Vector3 add_vector(const Vector3& a, const Vector3& b) noexcept {
    return {add32(a.x, b.x), add32(a.y, b.y), add32(a.z, b.z)};
}
Vector3 subtract_vector(const Vector3& a, const Vector3& b) noexcept {
    return {sub32(a.x, b.x), sub32(a.y, b.y), sub32(a.z, b.z)};
}
Vector3 scale_vector(const Vector3& value, float factor) noexcept {
    return {mul32(value.x, factor), mul32(value.y, factor), mul32(value.z, factor)};
}

FogValue make_fog(float near_distance, float far_distance,
                  float blue, float green, float red, float alpha) {
    return FogValue(near_distance, far_distance, blue, green, red, alpha);
}
FogValue scale_fog(const FogValue& value, float factor) {
    return make_fog(mul32(value.near_distance, factor),
                    mul32(value.far_distance, factor),
                    mul32(value.channels[0], factor),
                    mul32(value.channels[1], factor),
                    mul32(value.channels[2], factor),
                    mul32(value.channels[3], factor));
}
FogValue subtract_fog(const FogValue& a, const FogValue& b) {
    return make_fog(sub32(a.near_distance, b.near_distance),
                    sub32(a.far_distance, b.far_distance),
                    sub32(a.channels[0], b.channels[0]),
                    sub32(a.channels[1], b.channels[1]),
                    sub32(a.channels[2], b.channels[2]),
                    sub32(a.channels[3], b.channels[3]));
}
FogValue add_fog(const FogValue& a, const FogValue& b) {
    return make_fog(add32(a.near_distance, b.near_distance),
                    add32(a.far_distance, b.far_distance),
                    add32(a.channels[0], b.channels[0]),
                    add32(a.channels[1], b.channels[1]),
                    add32(a.channels[2], b.channels[2]),
                    add32(a.channels[3], b.channels[3]));
}

// Return an endpoint after the native timer clamp. Negative durations remain
// active and flow through the original easing expression without clamping.
template<class T>
bool interpolation_endpoint(Timer& timer, std::int32_t& duration,
                             std::int32_t mode, const T& start,
                             const T& end, const float* rate, T& result) {
    if (duration > 0) {
        timer_tick(timer, rate);
        if (timer.current >= duration) {
            timer_set(timer, duration);
            duration = 0;
            result = mode == 7 || mode == 17 ? start : end;
            return true;
        }
    } else if (duration == 0) {
        result = mode == 7 || mode == 17 ? start : end;
        return true;
    }
    return false;
}

Vector3 sample_vector_interpolation(VectorInterpolation& value,
                                    const float* rate) {
    Vector3 result{};
    if (interpolation_endpoint(value.timer, value.duration, value.mode,
                               value.start, value.end, rate, result))
        return result;
    if (value.mode == 7) {
        value.start = add_vector(value.start, value.end);
        value.current = value.start;
    } else if (value.mode == 17) {
        value.start = add_vector(value.start, value.tangent_end);
        value.tangent_end = add_vector(value.tangent_end, value.end);
        value.current = value.start;
    } else if (value.mode == 8) {
        const float t = div32(value.timer.current_fraction,
                              int_float(value.duration));
        const float from_weight = mul32(
            mul32(sub32(t, 1.0f), sub32(t, 1.0f)),
            add32(mul32(2.0f, t), 1.0f));
        const float to_weight = mul32(mul32(t, t), sub32(3.0f, mul32(2.0f, t)));
        const float from_tangent_weight =
            mul32(mul32(sub32(1.0f, t), sub32(1.0f, t)), t);
        const float to_tangent_weight = mul32(mul32(sub32(t, 1.0f), t), t);
        value.current = add_vector(
            add_vector(add_vector(scale_vector(value.start, from_weight),
                                  scale_vector(value.end, to_weight)),
                       scale_vector(value.tangent_start, from_tangent_weight)),
            scale_vector(value.tangent_end, to_tangent_weight));
    } else {
        const float amount = ecl_easing(value.mode, value.timer.current_fraction,
                                            int_float(value.duration));
        value.current = add_vector(
            scale_vector(subtract_vector(value.end, value.start), amount),
            value.start);
    }
    return value.current;
}

float sample_float_interpolation(FloatInterpolation& value,
                                  const float* rate) {
    float result = 0.0f;
    if (interpolation_endpoint(value.timer, value.duration, value.mode,
                               value.start, value.end, rate, result))
        return result;
    if (value.mode == 7) {
        value.start = add32(value.start, value.end);
        value.current = value.start;
    } else if (value.mode == 17) {
        value.start = add32(value.start, value.tangent_end);
        value.tangent_end = add32(value.tangent_end, value.end);
        value.current = value.start;
    } else if (value.mode == 8) {
        const float t = div32(value.timer.current_fraction,
                              int_float(value.duration));
        const float from_weight = mul32(
            mul32(sub32(t, 1.0f), sub32(t, 1.0f)),
            add32(mul32(2.0f, t), 1.0f));
        const float to_weight = mul32(mul32(t, t), sub32(3.0f, mul32(2.0f, t)));
        const float from_tangent_weight =
            mul32(mul32(sub32(1.0f, t), sub32(1.0f, t)), t);
        const float to_tangent_weight = mul32(mul32(sub32(t, 1.0f), t), t);
        value.current = add32(
            add32(add32(mul32(value.start, from_weight),
                        mul32(value.end, to_weight)),
                  mul32(value.tangent_start, from_tangent_weight)),
            mul32(value.tangent_end, to_tangent_weight));
    } else {
        const float amount = ecl_easing(value.mode, value.timer.current_fraction,
                                            int_float(value.duration));
        value.current = add32(
            mul32(sub32(value.end, value.start), amount), value.start);
    }
    return value.current;
}

FogValue sample_fog_interpolation(FogInterpolation& value,
                                  const float* rate) {
    FogValue result{};
    if (interpolation_endpoint(value.timer, value.duration, value.mode,
                               value.start, value.end, rate, result))
        return result;
    if (value.mode == 7) {
        value.start = add_fog(value.start, value.end);
        value.current = value.start;
    } else if (value.mode == 17) {
        value.start = add_fog(value.start, value.tangent_end);
        value.tangent_end = add_fog(value.tangent_end, value.end);
        value.current = value.start;
    } else if (value.mode == 8) {
        const float t = div32(value.timer.current_fraction,
                              int_float(value.duration));
        const float from_weight = mul32(
            mul32(sub32(t, 1.0f), sub32(t, 1.0f)),
            add32(mul32(2.0f, t), 1.0f));
        const float to_weight = mul32(mul32(t, t), sub32(3.0f, mul32(2.0f, t)));
        const float from_tangent_weight =
            mul32(mul32(sub32(1.0f, t), sub32(1.0f, t)), t);
        const float to_tangent_weight = mul32(mul32(sub32(t, 1.0f), t), t);
        value.current = add_fog(
            add_fog(add_fog(scale_fog(value.start, from_weight),
                            scale_fog(value.end, to_weight)),
                    scale_fog(value.tangent_start, from_tangent_weight)),
            scale_fog(value.tangent_end, to_tangent_weight));
    } else {
        const float amount = ecl_easing(value.mode, value.timer.current_fraction,
                                            int_float(value.duration));
        value.current = add_fog(
            scale_fog(subtract_fog(value.end, value.start), amount), value.start);
    }
    return value.current;
}

template<class T>
void configure(Interpolation<T>& value, std::int32_t duration,
               std::int32_t mode, const T& start, const T& end) {
    value.set_duration(duration);
    (void)value.set_mode(mode);
    value.set_start(start);
    value.set_end(end);
    value.reset_timer();
}

void interpolate_camera(StageBackgroundScriptState& state, const float* rate) {
    if (state.direction_interpolation.duration != 0)
        state.camera.vector_0c = sample_vector_interpolation(
            state.direction_interpolation, rate);
    if (state.position_interpolation.duration != 0)
        state.camera.vector_00 = sample_vector_interpolation(
            state.position_interpolation, rate);
    if (state.fog_interpolation.duration != 0)
        state.camera.fog = sample_fog_interpolation(state.fog_interpolation, rate);
    if (state.up_interpolation.duration != 0)
        state.camera.vector_18 = sample_vector_interpolation(
            state.up_interpolation, rate);
    if (state.fov_interpolation.duration != 0)
        state.camera.field_of_view = sample_float_interpolation(
            state.fov_interpolation, rate);
    state.update_camera_motion(rate);
}

float camera_angle(float time, float period) noexcept {
    return div32(mul32(mul32(time, pi), 2.0f), period);
}
}

void StageBackgroundScriptState::update_camera_motion(const float* rate) {
    auto& timer = motion_timer;
    auto& secondary = secondary_motion_timer;
    auto& offset = camera.vector_3c;
    auto& target = camera.vector_48;
    auto& up = camera.vector_18;
    const auto tick = [&](std::int32_t limit, std::int32_t reset) {
        timer_tick(timer, rate);
        if (timer.current >= limit) timer_set(timer, reset);
    };

    switch (camera_motion) {
    case 1: {
        const float amplitude = timer.current >= 512 ? 1.0f :
            div32(timer.current_fraction, 512.0f);
        const float angle = normalize_angle(camera_angle(timer.current_fraction, 1024.0f));
        offset.x = mul32(mul32(scalar_math::sine(angle), -10.0f), amplitude);
        offset.z = mul32(mul32(scalar_math::sine(
            normalize_angle(mul32(angle, 2.0f))), -10.0f), amplitude);
        up.x = mul32(mul32(negate(scalar_math::sine(angle)), 0.01f), amplitude);
        target.x = div32(negate(offset.x), 2.0f);
        target.z = div32(negate(offset.z), 2.0f);
        tick(2048, 1024);
        break;
    }
    case 2:
    case 4: {
        const float angle = normalize_angle(camera_angle(timer.current_fraction,
                                                          mul32(512.0f, 6.0f)));
        up.x = mul32(negate(scalar_math::sine(angle)), 1.0f);
        up.z = mul32(camera_motion == 4 ? negate(scalar_math::cosine(angle)) :
                                          scalar_math::cosine(angle), 1.0f);
        tick(3072, 0);
        break;
    }
    case 3:
    case 6: {
        const float angle = normalize_angle(camera_angle(
            int_float(timer.current % 1024), 1024.0f));
        const float amplitude = camera_motion == 3 ?
            (timer.current >= 1024 ? 80.0f :
             div32(mul32(timer.current_fraction, 80.0f), 1024.0f)) :
            (secondary.current >= 512 ? 0.0f :
             mul32(sub32(1.0f, div32(secondary.current_fraction, 512.0f)), 80.0f));
        offset.x = mul32(scalar_math::sine(angle), amplitude);
        offset.y = 0.0f;
        offset.z = 0.0f;
        target.x = div32(negate(offset.x), 10.0f);
        timer_tick(timer, rate);
        if (camera_motion == 6) timer_tick(secondary, rate);
        if (timer.current >= 2048) timer_set(timer, 1024);
        break;
    }
    case 5: {
        const float angle = normalize_angle(camera_angle(
            int_float(timer.current % 1024), 1024.0f));
        const float amplitude = timer.current < 512 ?
            div32(timer.current_fraction, 512.0f) : 1.0f;
        offset.z = mul32(mul32(scalar_math::sine(angle), -50.0f), amplitude);
        tick(2048, 1024);
        break;
    }
    case 7: {
        const float angle = normalize_angle(camera_angle(timer.current_fraction, 4800.0f));
        offset.x = mul32(scalar_math::sine(angle), 1200.0f);
        offset.y = mul32(negate(scalar_math::cosine(angle)), 1200.0f);
        offset.z = mul32(scalar_math::cosine(angle), -40.0f);
        target.x = mul32(scalar_math::sine(angle), -512.0f);
        target.y = mul32(negate(scalar_math::cosine(angle)), -512.0f);
        target.z = add32(mul32(scalar_math::cosine(
            normalize_angle(mul32(angle, 2.0f))), 110.0f), 100.0f);
        tick(4800, 0);
        break;
    }
    case 8: {
        const float angle = normalize_angle(sub32(
            camera_angle(timer.current_fraction, 800.0f), pi));
        offset.x = mul32(scalar_math::sine(angle), -30.0f);
        offset.y = mul32(scalar_math::sine(angle), -15.0f);
        offset.z = mul32(scalar_math::sine(angle), -20.0f);
        up.x = mul32(negate(scalar_math::sine(angle)), 0.1f);
        tick(800, 0);
        break;
    }
    case 9: {
        float angle = normalize_angle(camera_angle(timer.current_fraction, 2000.0f));
        if (angle >= pi) angle = normalize_angle(sub32(angle, mul32(pi, 2.0f)));
        offset.x = mul32(scalar_math::sine(angle), 5.0f);
        offset.y = mul32(scalar_math::sine(angle), -15.0f);
        up.x = mul32(negate(scalar_math::sine(angle)), 1.0f);
        up.y = mul32(scalar_math::cosine(angle), 1.0f);
        tick(2000, 0);
        break;
    }
    case 11: {
        const float angle = sub32(camera_angle(timer.current_fraction, 2048.0f), pi);
        offset.x = mul32(scalar_math::sine(angle), 70.0f);
        offset.z = mul32(scalar_math::sine(
            normalize_angle(mul32(angle, 2.0f))), 200.0f);
        up.x = mul32(negate(scalar_math::sine(angle)), 0.1f);
        tick(2048, 0);
        break;
    }
    case 12:
    case 13: {
        const bool last = camera_motion == 13;
        const float angle = sub32(camera_angle(timer.current_fraction,
                                               last ? 512.0f : 1024.0f), pi);
        offset.x = mul32(scalar_math::sine(angle), last ? -15.0f : -50.0f);
        up.x = mul32(negate(scalar_math::sine(angle)), last ? 0.01f : 0.1f);
        tick(last ? 512 : 1024, 0);
        break;
    }
    // Mode 10, zero and unrecognized values preserve all camera/timer fields.
    }
}

void __fastcall StageBackgroundScriptState::execute_script() {
    const float* const rate = timer_clock_sources[0] != nullptr ?
        &timer_clock_sources[0]->value : nullptr;
    for (;;) {
        const auto& instruction = *reinterpret_cast<const StageResourceInstructionHeader*>(
            reinterpret_cast<const std::byte*>(owner->instructions) + instruction_offset);
        if (timer.current < instruction.time) {
            timer_tick(timer, rate);
            interpolate_camera(*this, rate);
            return;
        }

        const auto* arguments = instruction.arguments;
        const auto integer = [&](unsigned index) {
            return std::bit_cast<std::int32_t>(arguments[index]);
        };
        const auto real = [&](unsigned index) {
            return std::bit_cast<float>(static_cast<std::uint32_t>(arguments[index]));
        };
        const auto vector = [&](unsigned index) {
            return Vector3{real(index), real(index + 1), real(index + 2)};
        };

        switch (instruction.opcode) {
        case 0:
            interpolate_camera(*this, rate);
            return;
        case 1:
            timer_set(timer, integer(1));
            instruction_offset = arguments[0];
            continue;
        case 2:
            camera.final_vector.x = sub32(real(0), camera.vector_00.x);
            camera.vector_00.x = real(0);
            camera.final_vector.y = sub32(real(1), camera.vector_00.y);
            camera.vector_00.y = real(1);
            camera.final_vector.z = sub32(real(2), camera.vector_00.z);
            camera.vector_00.z = real(2);
            break;
        case 3:
            configure(position_interpolation, integer(0), integer(1),
                      camera.vector_00, vector(2));
            break;
        case 4:
            camera.vector_0c = vector(0);
            break;
        case 5:
            configure(direction_interpolation, integer(0), integer(1),
                      camera.vector_0c, vector(2));
            break;
        case 6:
            camera.vector_18 = vector(0);
            break;
        case 7:
            camera.field_of_view = real(0);
            break;
        case 8: {
            const std::uint32_t color = arguments[0];
            camera.fog = make_fog(real(1), real(2),
                static_cast<float>(color & 0xffu),
                static_cast<float>((color >> 8) & 0xffu),
                static_cast<float>((color >> 16) & 0xffu),
                static_cast<float>(color >> 24));
            break;
        }
        case 9: {
            const std::uint32_t color = arguments[2];
            set_fog(integer(0), integer(1),
                make_fog(real(3), real(4),
                    static_cast<float>(color & 0xffu),
                    static_cast<float>((color >> 8) & 0xffu),
                    static_cast<float>((color >> 16) & 0xffu),
                    static_cast<float>(color >> 24)));
            break;
        }
        case 10:
        case 11: {
            auto& interpolation = instruction.opcode == 10 ?
                position_interpolation : direction_interpolation;
            interpolation.set_duration(integer(0));
            (void)interpolation.set_mode(8);
            interpolation.set_start(instruction.opcode == 10 ?
                camera.vector_00 : camera.vector_0c);
            interpolation.tangent_start = vector(2);
            interpolation.set_end(vector(5));
            interpolation.tangent_end = vector(8);
            interpolation.reset_timer();
            break;
        }
        case 12:
            camera_motion = static_cast<std::uint8_t>(arguments[0]);
            if (camera_motion == 0) camera.vector_3c = Vector3{};
            timer_set(camera_motion == 6 ? secondary_motion_timer : motion_timer, 0);
            if (camera_motion == 2) timer_set(motion_timer, 512);
            break;
        case 13:
            stage_vm_set_clear_color(arguments[0]);
            break;
        case 14: {
            const std::int32_t index = integer(0);
            Animation& animation = animations[index];
            const std::int32_t script = integer(1);
            if (script >= 0) {
                stage_vm_assign_animation(*this, index, script);
            } else if (script == -2) {
                animation.base.flags.byte_02 &= 0xfeu;
            } else if (script == -1) {
                stage_vm_stop_animation(animation);
            }
            fields_3294[index] = arguments[2];
            break;
        }
        case 17:
            mesh_mode = arguments[0];
            stage_vm_reset_meshes(*this);
            break;
        case 18:
            configure(up_interpolation, integer(0), integer(1),
                      camera.vector_18, vector(2));
            break;
        case 19:
            stage_vm_interrupt_animations(*owner, arguments[0] + 7u);
            break;
        case 20:
            fields_3294[8] = std::bit_cast<std::uint32_t>(
                mul32(real(0), real(0)));
            break;
        case 21:
            configure(fov_interpolation, integer(0), integer(1),
                      camera.field_of_view, real(2));
            break;
        case 22:
            stage_vm_set_primary_rotation_flag(arguments[0]);
            break;
        }
        instruction_offset += static_cast<std::uint32_t>(
            static_cast<std::int32_t>(instruction.size));
    }
}

} // namespace th20

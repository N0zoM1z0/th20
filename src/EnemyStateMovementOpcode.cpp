#include "EnemyStateMovementOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "Player.hpp"
#include "EclRuntime.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "Angle.hpp"

namespace th20 {
namespace {
constexpr float missing = -999999.0f;
constexpr float pi = 3.1415927410125732f;
EnemyMovement& movement(EnemyState& state, std::uint32_t index) {
    if (state.movements.size() <= index) state.movements.resize(index + 1);
    return state.movements[index];
}
float reflected(float value) {
    return normalize_angle(-normalize_angle(value - pi / 2.0f) + pi / 2.0f);
}
template<class T> void configure(Interpolation<T>& value, std::int32_t duration,
    std::int32_t mode, const T& from, const T& to) {
    value.set_duration(duration);
    value.tangent_start = {};
    value.tangent_end = {};
    value.set_mode(mode);
    value.set_start(from);
    value.set_end(to);
    value.timer = 0;
}

} // namespace

bool execute_enemy_movement_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 400: case 402: {
        auto& motion = movement(state, opcode == 400 ? state.field_44 : 1).motion;
        const float x = state.float_argument(0);
        const float y = state.float_argument(1);
        if (missing < x) motion.set_position_x(x);
        if (missing < y) motion.set_position_y(y);
        motion.select_linear();
        state.combine_movements();
        break;
    }
    case 401: case 403: case 436: case 437: {
        auto& record = movement(state, opcode == 401 || opcode == 436 ? state.field_44 : 1);
        auto& motion = record.motion;
        auto& position = record.position;
        float x = state.float_argument(2);
        float y = state.float_argument(3);
        if (state.integer_argument(0) < 1) {
            position.stop();
            break;
        }
        if (opcode == 436 || opcode == 437) {
            x = state.flags.word_04 & 8u ? motion.position_x() - x : motion.position_x() + x;
            y = motion.position_y() + y;
        }
        position.duration = state.integer_argument(0);
        position.tangent_start = {};
        position.tangent_end = {};
        position.flags.bits &= ~1u;
        position.mode = state.integer_argument(1);
        position.start = motion.position_ref();
        position.end = {missing < x ? x : motion.position_x(), missing < y ? y : motion.position_y(), 0};
        position.timer = 0;
        motion.select_linear();
        break;
    }
    case 434: case 435: case 438: case 439: {
        auto& record = movement(state, opcode == 434 || opcode == 438 ? state.field_44 : 1);
        auto& motion = record.motion;
        auto& position = record.position;
        float x = state.float_argument(3);
        float y = state.float_argument(4);
        if (state.integer_argument(0) < 1) {
            position.stop();
            break;
        }
        if (opcode == 438 || opcode == 439) {
            x = state.flags.word_04 & 8u ? motion.position_x() - x : motion.position_x() + x;
            y = motion.position_y() + y;
        }
        position.duration = state.integer_argument(0);
        position.tangent_start = {};
        position.tangent_end = {};
        position.flags.bits |= 1u;
        position.axis_modes.values[0] = state.integer_argument(1);
        position.axis_modes.values[1] = state.integer_argument(2);
        position.start = motion.position_ref();
        position.end = {missing < x ? x : motion.position_x(), missing < y ? y : motion.position_y(), 0};
        position.timer = 0;
        motion.select_linear();
        break;
    }
    case 425: case 426: {
        auto& record = movement(state, opcode == 425 ? state.field_44 : 1);
        auto& motion = record.motion;
        auto& position = record.position;
        const float x = state.float_argument(3);
        const float y = state.float_argument(4);
        Vector3 from_tangent, to_tangent;
        from_tangent.x = state.float_argument(1);
        from_tangent.y = state.float_argument(2);
        from_tangent.z = 0;
        to_tangent.x = state.float_argument(5);
        to_tangent.y = state.float_argument(6);
        to_tangent.z = 0;
        position.duration = state.integer_argument(0);
        position.tangent_start = from_tangent;
        position.tangent_end = to_tangent;
        position.flags.bits &= ~1u;
        position.mode = 8;
        position.start = motion.position_ref();
        position.end = {missing < x ? x : motion.position_x(), missing < y ? y : motion.position_y(), 0};
        position.timer = 0;
        motion.select_linear();
        break;
    }
    case 404: case 406: case 428: case 430: {
        auto& motion = movement(state, opcode == 404 || opcode == 428 ? state.field_44 : 1).motion;
        float angle = state.float_argument(0);
        const float speed = state.float_argument(1);
        if (missing < angle) {
            if ((state.flags.word_04 & 8u) && (opcode == 404 || opcode == 406)) angle = reflected(angle);
            motion.set_angle(angle);
        }
        if (missing < speed) motion.set_speed(speed);
        motion.select_linear();
        break;
    }
    case 405: case 407: case 429: case 431: {
        auto& record = movement(state, opcode == 405 || opcode == 429 ? state.field_44 : 1);
        auto& motion = record.motion;
        const float angle = state.float_argument(2);
        const float speed = state.float_argument(3);
        Vector2 target;
        if (state.integer_argument(0) < 1) {
            record.scalar_ac.stop();
            record.scalar_d8.stop();
            break;
        }
        const int mode = state.integer_argument(1);
        if (mode == 7) {
            target.x = missing < angle ? ((state.flags.word_04 & 8u) && (opcode == 405 || opcode == 407) ? -angle : angle) : 0;
            target.y = missing < speed ? speed : 0;
        } else {
            target.x = missing < angle ? ((state.flags.word_04 & 8u) && (opcode == 405 || opcode == 407) ? reflected(angle) : angle) : static_cast<float>(motion.angle_1c);
            target.y = missing < speed ? speed : motion.value_18;
        }
        Vector2 from(static_cast<float>(motion.angle_1c), motion.value_18);
        if (pi <= scalar_math::absolute(from.x - target.x)) {
            if (target.x <= from.x) target.x = pi * 2.0f + target.x;
            else from.x = pi * 2.0f + from.x;
        }
        const int duration = state.integer_argument(0);
        record.scalar_ac.begin(duration, mode, from.x, target.x);
        record.scalar_d8.begin(duration, mode, from.y, target.y);
        motion.select_linear();
        break;
    }
    case 440: case 442: {
        auto& motion = movement(state, opcode == 440 ? state.field_44 : 1).motion;
        float angle = state.float_argument(0);
        if (state.flags.word_04 & 8u) angle = reflected(angle);
        motion.set_angle(angle);
        motion.select_linear();
        break;
    }
    case 441: case 443: {
        auto& record = movement(state, opcode == 441 ? state.field_44 : 1);
        auto& motion = record.motion;
        const float angle = state.float_argument(2);
        if (state.integer_argument(0) < 1) {
            record.scalar_ac.stop();
            break;
        }
        const int mode = state.integer_argument(1);
        float target;
        if (mode == 7) target = missing < angle ? (state.flags.word_04 & 8u ? -angle : angle) : 0;
        else target = missing < angle ? (state.flags.word_04 & 8u ? reflected(angle) : angle) : static_cast<float>(motion.angle_1c);
        target = angle_difference(target, motion.angle_1c) + static_cast<float>(motion.angle_1c);
        record.scalar_ac.begin(state.integer_argument(0), mode, static_cast<float>(motion.angle_1c), target);
        motion.select_linear();
        break;
    }
    case 444: case 446: {
        auto& motion = movement(state, opcode == 444 ? state.field_44 : 1).motion;
        const float speed = state.float_argument(0);
        if (missing < speed) motion.set_speed(speed);
        motion.select_linear();
        break;
    }
    case 445: case 447: {
        auto& record = movement(state, opcode == 445 ? state.field_44 : 1);
        auto& motion = record.motion;
        const float speed = state.float_argument(2);
        const float from = motion.value_18;
        if (state.integer_argument(0) < 1) {
            record.scalar_d8.stop();
            break;
        }
        const int mode = state.integer_argument(1);
        const float target = missing < speed ? speed : mode == 7 ? 0 : motion.value_18;
        record.scalar_d8.begin(state.integer_argument(0), mode, from, target);
        motion.select_linear();
        break;
    }
    case 408: case 410: case 420: case 422: {
        auto& motion = movement(state, opcode == 408 || opcode == 420 ? state.field_44 : 1).motion;
        const float angle = state.float_argument(0);
        const float speed = state.float_argument(1);
        const float x = state.float_argument(2);
        const float y = state.float_argument(3);
        float second_angle = 0, second_speed = 0;
        if (opcode == 420 || opcode == 422) {
            second_angle = state.float_argument(4);
            second_speed = state.float_argument(5);
        }
        if (!motion.is_orbit()) motion.set_motion_vector(motion.position_ref());
        if (missing < angle) motion.set_angle(angle);
        if (missing < speed) motion.set_speed(speed);
        if (missing < x) motion.set_parameter_20(x);
        if (missing < y) motion.set_parameter_24(y);
        if (opcode == 420 || opcode == 422) {
            if (missing < second_angle) motion.angle_28 = normalize_angle(second_angle);
            if (missing < second_speed) motion.value_2c = second_speed;
        }
        motion.select_orbit();
        if (opcode == 420 || opcode == 422) motion.select_elliptic();
        motion.update_position();
        state.combine_movements();
        break;
    }
    case 409: case 411: case 421: case 423: {
        auto& record = movement(state, opcode == 409 || opcode == 421 ? state.field_44 : 1);
        auto& motion = record.motion;
        const float speed = state.float_argument(2);
        const float x = state.float_argument(3);
        const float y = state.float_argument(4);
        float second_angle = 0, second_speed = 0;
        if (opcode == 421 || opcode == 423) {
            second_angle = state.float_argument(5);
            second_speed = state.float_argument(6);
        }
        const float end_speed = missing < speed ? speed : motion.value_18;
        const Vector2 to(missing < x ? x : motion.value_20, missing < y ? y : motion.value_24);
        const Vector2 from(motion.value_20, motion.value_24);
        Vector2 from_second, to_second;
        if (opcode == 421 || opcode == 423) {
            to_second.x = missing < second_angle ? second_angle : static_cast<float>(motion.angle_28);
            to_second.y = missing < second_speed ? second_speed : motion.value_2c;
            from_second = {static_cast<float>(motion.angle_28), motion.value_2c};
        }
        const int duration = state.integer_argument(0);
        const int mode = state.integer_argument(1);
        if (duration < 1) {
            record.scalar_d8.stop();
            record.vector_104.stop();
            if (opcode == 421 || opcode == 423) record.vector_144.stop();
            break;
        }
        configure(record.scalar_d8, duration, mode, motion.value_18, end_speed);
        configure(record.vector_104, duration, mode, from, to);
        if (opcode == 421 || opcode == 423) {
            configure(record.vector_144, duration, mode, from_second, to_second);
            motion.set_motion_vector(motion.position_ref());
        }
        motion.select_orbit();
        if (opcode == 421 || opcode == 423) motion.select_elliptic();
        motion.update_position();
        state.combine_movements();
        break;
    }
    case 412: case 413: {
        auto& record = movement(state, opcode == 412 ? state.field_44 : 1);
        auto& motion = record.motion;
        float angle;
        if (state.position_ref().x < state.bounds_178.x - state.bounds_178.width / 4.0f) {
            angle = script_random.radians() / 3.0f;
        } else if (state.bounds_178.width / 4.0f + state.bounds_178.x < state.position_ref().x) {
            angle = normalize_angle(script_random.radians() / 3.0f + pi);
        } else if (state.position_ref().x < state.context->player()->position.x) {
            angle = script_random.radians() / 4.0f;
            if (script_random.next_word() % 3u == 0) angle = angle + pi;
        } else {
            angle = script_random.radians() / 4.0f;
            if (script_random.next_word() % 3u != 0) angle = angle + pi;
        }
        if (state.position_ref().y < state.bounds_178.y - state.bounds_178.height / 4.0f) angle = scalar_math::absolute(angle);
        else if (state.bounds_178.height / 4.0f + state.bounds_178.y < state.position_ref().y) angle = -scalar_math::absolute(angle);
        if (scalar_math::absolute(pi / 2.0f + angle) < 0.05f) {
            angle = -pi / 2.0f <= angle ? -pi / 2.0f + 0.05f : -pi / 2.0f - 0.05f;
        } else if (static_cast<double>(scalar_math::absolute(angle - pi / 2.0f)) < 0.05) {
            angle = pi / 2.0f <= angle ? pi / 2.0f + 0.05f : pi / 2.0f - 0.05f;
        }
        const int mode = state.integer_argument(1);
        const float speed = state.float_argument(2);
        const int duration = state.integer_argument(0);
        configure(record.scalar_ac, duration, mode, angle, angle);
        record.scalar_d8.set_duration(state.integer_argument(0));
        // The second native mode call still addresses the angular interpolator.
        record.scalar_ac.set_mode(mode);
        record.scalar_d8.tangent_start = 0;
        record.scalar_d8.tangent_end = 0;
        record.scalar_d8.set_start(speed);
        record.scalar_d8.set_end(0);
        record.scalar_d8.timer = 0;
        motion.select_linear();
        break;
    }
    case 414: case 415: case 432: case 433: {
        auto& motion = movement(state, opcode == 414 || opcode == 432 ? 0 : 1).motion;
        auto* controller = state.context->enemy_controller();
        auto* target = opcode == 414 || opcode == 415 ? controller->selected(0) : controller->find(state.integer_argument(0));
        motion.set_position(target->position_ref());
        break;
    }
    case 416: case 417: {
        auto& motion = movement(state, opcode == 416 ? state.field_44 : 1).motion;
        motion.position_ref().x += state.float_argument(0);
        motion.position_ref().y += state.float_argument(1);
        motion.position_ref().z += state.float_argument(2);
        state.combine_movements();
        break;
    }
    case 418: case 419: {
        auto& motion = movement(state, opcode == 418 ? 0 : 1).motion;
        const float x = state.float_argument(0);
        const float y = state.float_argument(1);
        if (missing < x) motion.vector_38.x = x;
        if (missing < y) motion.vector_38.y = y;
        if (motion.flags.fields.mode == 4) motion.velocity = motion.position;
        motion.update_position();
        state.combine_movements();
        break;
    }
    case 424:
        state.flags.word_04 = (state.flags.word_04 & ~8u) | ((static_cast<std::uint32_t>(state.integer_argument(0)) & 1u) << 3);
        break;
    case 427:
        for (std::int32_t i = 0; i < static_cast<std::int32_t>(state.movements.size()) - 1; ++i) {
            state.position_ref() += state.movements[i + 1].motion.position_copy();
        }
        state.movements.resize(1);
        state.movements[0].motion.set_position({});
        state.movements[0].motion.set_motion_vector({});
        state.movements[0].motion.select_linear();
        break;
    case 448:
        state.field_44 = state.integer_argument(0);
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20

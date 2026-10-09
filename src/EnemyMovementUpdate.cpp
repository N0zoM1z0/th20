#include "EnemyController.hpp"
#include "Animation.hpp"
#include "Graphics.hpp"
#include "ScalarMath.hpp"
#include "Context.hpp"
namespace th20 {
int EnemyState::update_movements() {
    motion_c8 = motion_110;
    if ((flags.word_08 >> 3) & 1u)
        movements[0].motion = entity->parent()->position_ref();
    for (EnemyMovement& movement : movements) {
        if (movement.scalar_ac.duration_value() &&
            !movement.motion.is_orbit() && !movement.motion.is_elliptic())
            movement.motion.set_angle(normalize_angle(movement.scalar_ac.sample()));
        if (movement.scalar_d8.duration_value())
            movement.motion.set_speed(movement.scalar_d8.sample());
        if (movement.vector_104.duration_value()) {
            Vector2 parameters = movement.vector_104.sample();
            movement.motion.set_parameter_20(parameters.x);
            movement.motion.set_parameter_24(parameters.y);
        }
        if (movement.position.duration_value()) {
            Vector3 delta = movement.position.sample() - movement.motion.position_ref();
            movement.motion.set_motion_vector(delta);
        } else {
            movement.motion.update_velocity();
        }
        movement.motion.update_position();
        if ((flags.word_04 >> 10) & 1u)
            movement.motion.position_ref() += process_graphics.viewports[0].final_vector;
    }
    combine_movements();
    if ((flags.word_04 >> 4) & 1u) {
        int direction = 0;
        if (motion_110.motion_vector().x < -0.03f) direction = -1;
        else if (motion_110.motion_vector().x > 0.03f) direction = 1;
        else direction = 0;
        if (field_2c != direction) {
            int transition = 0;
            switch (field_2c) {
            case -1: transition = direction == 0 ? 3 : 2; break;
            case 0: transition = direction == -1 ? 1 : 2; break;
            case 1: transition = direction == 0 ? 4 : 1; break;
            }
            Animation* previous = animations[0].handle.resolve();
            Vector3 position(0.0f, 0.0f, 0.0f);
            AnimationFile* file = context->enemy_controller()->animation_file(field_20);
            if (previous) {
                position = previous->position_ref();
                animations[0].handle.retire();
            }
            animations[0].handle = file->spawn_flag8(nullptr, field_28 + transition, position,
                                                0.0f, field_34 + 7, 0);
            field_2c = direction;
        }
    }
    Animation* current = animations[0].handle.resolve();
    if (current) {
        vector_170.x = scalar_math::absolute(current->height());
        vector_170.y = scalar_math::absolute(current->width());
    }
    if (motion_110.position_x() + vector_170.x / 2.0f < -384.0f / 2.0f ||
        motion_110.position_x() - vector_170.x / 2.0f > 384.0f / 2.0f) {
        flags.word_08 &= ~0x40u;
        if ((flags.word_04 & 1u) && !((flags.word_00 >> 2) & 1u)) return -1;
    } else if (motion_110.position_y() + vector_170.y / 2.0f < 0.0f ||
               motion_110.position_y() - vector_170.y / 2.0f > 448.0f) {
        flags.word_08 &= ~0x40u;
        if ((flags.word_04 & 1u) && !((flags.word_00 >> 3) & 1u)) return -1;
    } else {
        flags.word_04 |= 1u;
        flags.word_08 |= 0x40u;
    }
    return 0;
}
}

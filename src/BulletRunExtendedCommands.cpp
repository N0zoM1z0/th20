// Partial natural-C++ restoration of the original 12,140-byte Bullet
// command interpreter. The whole parent remains NONEXACT: the animation,
// ECL, interpolation, enemy and laser command families are still being
// restored. Unsupported native opcodes deliberately remain pending rather
// than being silently consumed as no-ops.
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationCallback.hpp"
#include "EnemyController.hpp"
#include "EnemySpawn.hpp"
#include "Bullet.hpp"
#include "DebugAllocator.hpp"
#include "ShotMetadata.hpp"
#include <memory>
#include <utility>
#include "BulletAimSelector.hpp"
#include "BulletStyle.hpp"
#include "Player.hpp"
#include "GameRandom.hpp"
#include "LaserParameters.hpp"
#include "MotionMath.hpp"
#include "SoundInf.hpp"
#include <cstdint>

namespace th20 {
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_screen_height_448_56d7c0;
extern const float native_selector_min;
extern const float native_selector_player_hi;
extern const float native_selector_wobble_lo;
extern GameRandom script_random;
extern const Vector3 native_zero_position;
extern std::int32_t bullet_cancel_scripts_by_color[8];
void __fastcall interrupt_animation_mode2(Animation* animation);
void __fastcall set_animation_flag_byte_01_zero(Animation* animation);
void __fastcall set_animation_flag_byte_01_one(Animation* animation);
void __fastcall set_animation_flag_byte_01_two(Animation* animation);
void Bullet::run_extended_commands() {
    for (;;) {
        if (field_38 >= 24)
            return;
        if (field_38 >= metadata->commands.size())
            return;

        const BulletCommand& command = metadata->commands[field_38];
        if (command.opcode == 0)
            return;

        if (command.flags == 0) {
            const std::uint64_t opcode_bit = command.opcode < 64
                ? (std::uint64_t{1} << command.opcode) : 0;
            if ((command_flags.bits & ~(opcode_bit | 0x200000100ull)) != 0)
                return;
        }

        if (command.opcode > 33) {
            ++field_38;
            continue;
        }

        switch (command.opcode) {
        case 0:
            command_flags.words.low |= 1;
            commands.at(0).timer = 0;
            commands.at(0).vector_24.z = 0.0f;
            break;
        case 1:
            animation->interrupt(static_cast<std::int16_t>(command.operand_10) + 7);
            state = 2;
            position -= velocity * 4.0f;
            ++field_38;
            continue;
        case 2: {
            command_flags.words.low |= 4;
            commands.at(1).scalar_10 = command.operand_00;
            const float current_angle = static_cast<float>(angle);
            const float target_angle = select_bullet_aim(
                view_index, current_angle, position,
                command.operand_04, command.operand_08);
            commands.at(1).scalar_14 = target_angle;
            commands.at(1).timer = 0;
            commands.at(1).word_30 = command.operand_10_word;
            const float polar_angle = commands.at(1).scalar_14;
            const float polar_length = commands.at(1).scalar_10;
            polar(commands.at(1).vector_24, polar_angle, polar_length);
            if (field_38 != 0 && static_cast<std::int32_t>(field_40) >= 0)
                process_sound.request_effect(static_cast<std::int32_t>(field_40), 0);
            break;
        }
        case 3:
            command_flags.words.low |= 8;
            commands.at(2).scalar_10 = command.operand_00;
            commands.at(2).scalar_14 = command.operand_04;
            commands.at(2).timer = 0;
            commands.at(2).word_30 = command.operand_10_word;
            if (field_38 != 0 && static_cast<std::int32_t>(field_40) >= 0)
                process_sound.request_effect(static_cast<std::int32_t>(field_40), 0);
            break;
        case 4: {
            command_flags.words.low |= 0x10;
            commands.at(3).scalar_10 = command.operand_04 <= native_selector_min
                ? field_24 : command.operand_04;
            const float current_angle = static_cast<float>(angle);
            const float target_angle = select_bullet_aim(
                view_index, current_angle, position,
                command.operand_00, command.operand_08);
            commands.at(3).scalar_14 = target_angle;

            switch (command.operand_18) {
            case 0:
            case 1:
            case 4:
                commands.at(3).scalar_14 = target_angle;
                break;
            case 2: {
                const float player_angle = context->player()->direction_to(
                    commands.at(12).vector_18);
                commands.at(3).scalar_14 = normalize_angle(target_angle + player_angle);
                break;
            }
            case 3:
                commands.at(3).scalar_14 = normalize_angle(
                    target_angle + commands.at(12).scalar_14);
                break;
            case 5:
            case 6:
                commands.at(3).scalar_14 =
                    script_random.signed_unit() * command.operand_00;
                break;
            case 7: {
                float selected_angle;
                if (command.operand_00 > native_selector_min) {
                    if (command.operand_00 < 990.0f)
                        selected_angle = command.operand_00;
                    else
                        selected_angle = context->player()->direction_to(position);
                } else {
                    selected_angle = current_angle;
                }
                commands.at(3).scalar_14 = selected_angle;
                commands.at(3).scalar_10 =
                    script_random.signed_unit() * command.operand_04 + field_24;
                break;
            }
            }

            commands.at(3).timer = 0;
            commands.at(3).word_30 = command.operand_10_word;
            commands.at(3).word_34 = command.operand_14_word;
            commands.at(3).word_38 = 0;
            commands.at(3).word_3c = command.operand_18_word;
            break;
        }
        case 5:
            ++field_38;
            continue;
        case 6: {
            command_flags.words.low |= 0x40;
            commands.at(4).scalar_10 = command.operand_00;
            if ((command.operand_14_word & 0x20u) == 0) {
                commands.at(4).vector_18.x = native_screen_rect_inner_width_384_56cda4;
                commands.at(4).vector_18.y = native_screen_height_448_56d7c0;
            } else {
                commands.at(4).vector_18.x = command.operand_04;
                commands.at(4).vector_18.y = command.operand_08;
            }
            commands.at(4).word_34 = command.operand_10_word;
            commands.at(4).word_30 = 0;
            commands.at(4).word_3c = command.operand_14_word;
            break;
        }
        case 7:
            field_18 = static_cast<std::int32_t>(command.operand_10_word);
            break;
        case 8:
            command_flags.words.low |= 0x100;
            commands.at(11).timer =
                static_cast<std::int32_t>(command.operand_10_real);
            commands.at(11).word_30 = command.operand_14_word;
            ++field_38;
            continue;
        case 9: {
            if ((command.operand_10_word & 0x8000u) == 0) {
                field_4c = static_cast<std::int16_t>(command.operand_10_word);
                field_4e = static_cast<std::int16_t>(command.operand_14_word & 0x7fffu);
                const std::int32_t type = static_cast<std::int32_t>(command.operand_10_word);
                const std::int32_t color = field_4e;
                const float radius = bullet_radius(type);
                size.y = radius;
                size.x = radius;
                draw_group = bullet_styles[field_4c].draw_group;

                animation->reset();
                animation->set_field_5e0(bullet_animation_script);
                animation->user_data = this;
                context->bullet_controller()->file->load_script(
                    animation, type_to_script(type));
                flags.bits |= 0x10;
                animation->base.flags.bits_0b.viewport_placement_mode = 1;
                animation_handle.retire();
                const std::uint32_t child_script = bullet_styles[field_4c].child_script;
                if (child_script != 0) {
                    animation_handle = context->bullet_controller()->file->spawn(
                        nullptr, static_cast<std::int32_t>(child_script), position,
                        0.0f, -1, nullptr);
                }

                switch (bullet_styles[field_4c].cancel_type) {
                case 0:
                    cancel_script = static_cast<std::int32_t>(field_4e) * 2 + 6;
                    break;
                case 1:
                    cancel_script = color < 8 ? bullet_cancel_scripts_by_color[color] : 0;
                    break;
                case 2:
                    cancel_script = -1;
                    flags.bits |= 0x10;
                    break;
                case 3:
                    cancel_script = 0x12;
                    break;
                case 4:
                    cancel_script = 8;
                    break;
                case 5:
                    cancel_script = 0x0e;
                    break;
                case 6:
                    cancel_script = color < 16
                        ? static_cast<std::int32_t>(bullet_styles[field_4c].colors[color].words[3])
                        : 0;
                    flags.bits |= 0x10;
                    break;
                case 7:
                    cancel_script = 0x107;
                    flags.bits |= 0x10;
                    break;
                case 8:
                    cancel_script = 0x10a;
                    flags.bits |= 0x10;
                    break;
                case 9:
                    cancel_script = 0x10d;
                    flags.bits |= 0x10;
                    break;
                case 10:
                    cancel_script = 0x116;
                    flags.bits |= 0x10;
                    break;
                }
                if ((command.operand_14_word & 0x8000u) != 0)
                    interrupt_animation_mode2(animation);
            } else {
                animation->reset();
                const std::int32_t enemy_type =
                    static_cast<std::int32_t>(command.operand_10_word & 0x7fffu);
                const std::int32_t enemy_script =
                    static_cast<std::int32_t>(command.operand_14_word & 0x7fffu);
                context->enemy_controller()->animation_file(enemy_type)->load_script(
                    animation, enemy_script);
                animation->base.flags.bits_0b.viewport_placement_mode = 1;
            }
            ++field_38;
            continue;
        }
        case 13: {
            auto spawned_metadata =
                std::allocate_shared<ShotMetadata>(DebugAllocator<ShotMetadata>{});
            ShotParameters parameters;
            spawned_metadata->field_38 =
                static_cast<std::int16_t>(command.operand_10_word);
            spawned_metadata->field_44 = command.operand_14_real;

            parameters.position = position;
            parameters.count = static_cast<std::int16_t>(command.operand_18_word);
            parameters.rows = static_cast<std::int16_t>(command.operand_1c_word);
            const BulletCommand& following = metadata->commands[field_38 + 1];
            parameters.angle = select_bullet_aim(
                view_index, static_cast<float>(angle), position,
                command.operand_00, following.operand_0c);
            parameters.angle_step = command.operand_04;
            parameters.speed = command.operand_08 > native_selector_min
                ? command.operand_08 : speed;
            parameters.speed_step = command.operand_0c;

            ++field_38;
            parameters.type = following.operand_10_word;
            parameters.color = following.operand_14_word;
            const bool cancel_after_fire = following.operand_18_real != 0.0f;
            spawned_metadata->commands = metadata->commands;
            context->bullet_controller()->fire(
                parameters, std::move(spawned_metadata));
            ++field_38;
            if (cancel_after_fire)
                cancel(0);
            continue;
        }
        case 17: {
            command_flags.words.low |= 0x20000;
            commands.at(8).vector_24.x = command.operand_00;
            commands.at(8).vector_24.y = command.operand_04;
            if ((command.operand_14_word & 0x100u) != 0)
                commands.at(8).vector_24 += position;
            commands.at(8).scalar_10 = field_24;
            commands.at(8).vector_24.z = 0.0f;
            commands.at(8).word_30 = command.operand_10_word;
            commands.at(8).word_34 = command.operand_14_word & 0xffu;
            commands.at(8).timer = 0;
            interpolation_420.set_start(position);
            interpolation_420.set_end(commands.at(8).vector_24);
            interpolation_420.set_tangent_start(native_zero_position);
            interpolation_420.set_tangent_end(native_zero_position);
            interpolation_420.set_duration(
                static_cast<std::int32_t>(command.operand_10_word));
            interpolation_420.set_mode(
                static_cast<std::int32_t>(command.operand_14_word & 0xffu));
            interpolation_420.reset_timer();
            break;
        }
        case 18: {
            if (command.operand_00 < 990.0f) {
                if (command.operand_00 >= -998.0f) {
                    float next_angle = command.operand_00;
                    if (next_angle <= -990.0f) {
                        if (next_angle < -999.0f)
                            next_angle += 360.0f;
                    } else if (next_angle > 999.0f) {
                        next_angle -= 360.0f;
                    }
                    angle.value = next_angle;
                }
            } else {
                float next_angle = context->player()->direction_to(position) +
                                   (command.operand_00 - 999.0f);
                if (next_angle <= -990.0f) {
                    if (next_angle < -999.0f)
                        next_angle += 360.0f;
                } else if (next_angle > 999.0f) {
                    next_angle -= 360.0f;
                }
                angle.value = next_angle;
            }
            if (command.operand_04 >= -998.0f)
                field_24 = command.operand_04;
            polar(velocity, static_cast<float>(angle), field_24);
            ++field_38;
            continue;
        }
        case 19:
            command_flags.words.low &= ~0x80000u;
            polar(commands.at(9).vector_24, command.operand_00, command.operand_04);
            commands.at(9).vector_24.z = 0.0f;
            commands.at(9).scalar_14 = command.operand_00;
            commands.at(9).scalar_10 = command.operand_04;
            commands.at(9).word_30 = command.operand_10_word;
            commands.at(9).timer = 0;
            break;
        case 20:
            if (command.operand_10_word == 2)
                set_animation_flag_byte_01_two(animation);
            else if (command.operand_10_word == 1)
                set_animation_flag_byte_01_one(animation);
            else
                set_animation_flag_byte_01_zero(animation);
            ++field_38;
            continue;
        case 22:
            command_flags.words.low &= ~0x400000u;
            interpolation_474.set_start(command.operand_00);
            interpolation_474.set_end(command.operand_04);
            interpolation_474.set_tangent_start(0.0f);
            interpolation_474.set_tangent_end(0.0f);
            interpolation_474.set_duration(
                static_cast<std::int32_t>(command.operand_10_word));
            interpolation_474.set_mode(
                static_cast<std::int32_t>(command.operand_14_word));
            interpolation_474.reset_timer();
            flags.bits |= 0x40;
            ++field_38;
            continue;
        case 23: {
            auto& slot = commands.at(12);
            slot.vector_18.x = position.x;
            slot.vector_18.y = position.y;
            slot.vector_18.z = position.z;
            commands.at(12).scalar_14 = static_cast<float>(angle);
            commands.at(12).scalar_10 = field_24;
            ++field_38;
            continue;
        }
        case 24: {
            EnemySpawn parameters;
            parameters.position = position;
            parameters.health = 10000;
            parameters.variables.field_00 = command.operand_10_word;
            parameters.variables.field_04 = command.operand_14_word;
            parameters.variables.field_08 = command.operand_18_word;
            parameters.variables.field_0c = command.operand_1c_word;
            parameters.variables.field_10 = command.operand_00;
            parameters.variables.field_14 = command.operand_04;
            parameters.variables.field_18 = command.operand_08;
            parameters.variables.field_1c = command.operand_0c;
            context->enemy_controller()->create(command.script, parameters, nullptr);
            break;
        }
        case 27: {
            if (command.operand_10_real == 0.0f) {
                LaserType0Parameters parameters;
                parameters.commands = metadata->commands;
                const BulletCommand& following = *(&command + 1);
                parameters.position = position;
                parameters.angle = select_bullet_aim(
                    view_index, static_cast<float>(angle), position,
                    command.operand_00, following.operand_0c);
                parameters.length = command.operand_0c;
                parameters.field_14 = command.operand_08;
                parameters.length_limit = following.operand_00;
                parameters.width = following.operand_04;
                parameters.speed = command.operand_04 > native_selector_min
                    ? command.operand_04 : field_24;
                parameters.type = command.operand_14_word;
                parameters.color = command.operand_18_word;
                parameters.radial_offset = following.operand_08;
                parameters.command_index = following.operand_18_word;
                parameters.flags |= 1;
                parameters.field_48 = static_cast<std::int32_t>(following.operand_10_word);
                parameters.field_4c = static_cast<std::int32_t>(following.operand_14_word);

                ++field_38;
                context->laser_controller()->create_laser(0, &parameters);
                ++field_38;
                if (command.operand_1c_real != 0.0f)
                    cancel(0);
                continue;
            }
            if (command.operand_10_real == 1.0f) {
                LaserType1Parameters parameters;
                parameters.commands = metadata->commands;
                const BulletCommand& following = *(&command + 1);
                parameters.position = position;
                if (command.operand_00 > native_selector_min) {
                    if (command.operand_00 < native_selector_player_hi ||
                        command.operand_00 >= native_selector_wobble_lo)
                        parameters.angle = command.operand_00;
                    else
                        parameters.angle = context->player()->direction_to(position);
                } else {
                    parameters.angle = static_cast<float>(angle);
                }
                parameters.length_limit = command.operand_0c;
                parameters.length = command.operand_08;
                parameters.width = following.operand_00;
                parameters.growth_speed = command.operand_04 > native_selector_min
                    ? command.operand_04 : field_24;
                parameters.delay = static_cast<std::int32_t>(following.operand_10_word);
                parameters.grow_time = static_cast<std::int32_t>(following.operand_14_word);
                parameters.sustain_time = static_cast<std::int32_t>(following.operand_18_word);
                parameters.shrink_time = static_cast<std::int32_t>(following.operand_1c_word);
                parameters.sound = 0x12;
                parameters.field_44 = -1;
                parameters.radial_offset = following.operand_04;
                parameters.command_index = (command.operand_1c_word & 0xff00u) >> 8;
                parameters.type = command.operand_14_word;
                parameters.color = command.operand_18_word;
                parameters.flags = (command.operand_1c_word & 0xffu) | 2u;

                ++field_38;
                context->laser_controller()->create_laser(1, &parameters);
                ++field_38;
                if ((command.operand_1c_word & 0x10000u) != 0)
                    cancel(0);
                continue;
            }
            return;
        }
        case 10:
            cancel(0);
            break;
        case 11:
            process_sound.request_effect_at(
                static_cast<std::int32_t>(command.operand_10_real), position.x);
            ++field_38;
            continue;
        case 12:
            command_flags.words.low |= 0x1000;
            commands.at(6).word_34 = command.operand_10_word;
            commands.at(6).word_30 = 0;
            commands.at(6).word_38 = command.operand_14_word;
            break;
        case 14:
            ++field_38;
            continue;
        case 15:
            field_2c = command.operand_10_word;
            ++field_38;
            continue;
        case 16: {
            const std::int32_t repeat_count =
                static_cast<std::int32_t>(command.operand_14_real);
            if (repeat_count < 1) {
                field_38 = command.operand_10_word;
                continue;
            }
            if (field_3c == 0) {
                field_3c = command.operand_14_word;
                field_38 = command.operand_10_word;
                continue;
            }
            if (field_3c != 1) {
                --field_3c;
                field_38 = command.operand_10_word;
                continue;
            }
            field_3c = 0;
            break;
        }
        case 21: {
            command_flags.words.low |= 4;
            const float step = (command.operand_00 - field_24) /
                static_cast<float>(static_cast<std::int32_t>(command.operand_10_real));
            commands.at(10).scalar_10 = step;
            const float current_angle = static_cast<float>(angle);
            const float target_angle = select_bullet_aim(
                view_index, current_angle, position,
                command.operand_04, command.operand_08);
            commands.at(10).scalar_14 = target_angle;
            commands.at(10).timer = 0;
            commands.at(10).word_30 = command.operand_10_word;
            const float polar_angle = commands.at(10).scalar_14;
            const float polar_length = commands.at(10).scalar_10;
            polar(commands.at(10).vector_24, polar_angle, polar_length);
            if (field_38 != 0 && static_cast<std::int32_t>(field_40) >= 0)
                process_sound.request_effect(static_cast<std::int32_t>(field_40), 0);
            break;
        }
        case 25:
            draw_group = command.operand_10_word;
            ++field_38;
            continue;
        case 26:
            if (command.operand_10_real < 1.0f) {
                ++field_38;
                continue;
            }
            command_flags.words.low |= 0x04000000;
            commands.at(13).timer = static_cast<std::int32_t>(command.operand_10_real);
            break;
        case 28:
            ++field_38;
            continue;
        case 29: {
            const float radius = command.operand_00 >= 0.0f
                ? command.operand_00 : bullet_radius(field_4c);
            size.y = radius;
            size.x = size.y;
            break;
        }
        case 30:
            if (command.operand_10_real < 1.0f) {
                ++field_38;
                continue;
            }
            command_flags.words.low |= 0x40000000;
            commands.at(5).timer = static_cast<std::int32_t>(command.operand_10_real);
            break;
        case 31:
            command_flags.words.low |= 0x80000000;
            commands.at(7).scalar_10 = command.operand_00;
            commands.at(7).scalar_14 = command.operand_04;
            commands.at(7).vector_24.x = command.operand_08;
            commands.at(7).timer = 0;
            commands.at(7).word_30 = command.operand_10_word;
            break;
        case 32: {
            command_flags.words.low |= 4;
            const float step = (command.operand_00 * field_24 - field_24) /
                static_cast<float>(static_cast<std::int32_t>(command.operand_10_real));
            commands.at(1).scalar_10 = step;
            const float current_angle = static_cast<float>(angle);
            const float target_angle = select_bullet_aim(
                view_index, current_angle, position,
                command.operand_04, command.operand_08);
            commands.at(1).scalar_14 = target_angle;
            commands.at(1).timer = 0;
            commands.at(1).word_30 = command.operand_10_word;
            const float polar_angle = commands.at(1).scalar_14;
            const float polar_length = commands.at(1).scalar_10;
            polar(commands.at(1).vector_24, polar_angle, polar_length);
            if (field_38 != 0 && static_cast<std::int32_t>(field_40) >= 0)
                process_sound.request_effect(static_cast<std::int32_t>(field_40), 0);
            break;
        }
        case 33:
            command_flags.words.high = (command_flags.words.high & ~2u) |
                                       ((command.operand_10_word & 1u) << 1);
            break;
        default:
            return;
        }
        ++field_38;
    }
}
} // namespace th20

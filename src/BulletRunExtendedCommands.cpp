// Partial natural-C++ restoration of the original 12,140-byte Bullet
// command interpreter. The whole parent remains NONEXACT: the animation,
// ECL, interpolation, enemy and laser command families are still being
// restored. Unsupported native opcodes deliberately remain pending rather
// than being silently consumed as no-ops.
#include "Animation.hpp"
#include "Bullet.hpp"
#include "BulletAimSelector.hpp"
#include "BulletStyle.hpp"
#include "MotionMath.hpp"
#include "SoundInf.hpp"
#include <cstdint>

namespace th20 {
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_screen_height_448_56d7c0;
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
        case 4:
            return; // Native command-4 has a separate eight-way subtype switch.
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
        case 9:
        case 13:
        case 17:
        case 18:
        case 19:
        case 20:
        case 22:
        case 23:
        case 24:
        case 27:
            return; // Animation, ECL, interpolation, enemy and laser branches remain open.
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

#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "ClockScalar.hpp"
namespace th20 {
void AnimationFile::bind_animation(Animation* animation, std::int32_t script, Animation* parent) {
    apply_template(animation, script);
    if (parent) {
        animation->base.flags.bits_04.bit_24 = parent->base.flags.bits_04.bit_24;
        animation->update_layer();
        animation->parent_55c = parent;
        if (parent->parent_558) parent = parent->parent_558;
        animation->field_4e8 = parent->field_4e8;
        animation->parent_558 = parent;
    } else {
        animation->parent_55c = nullptr;
        animation->parent_558 = nullptr;
    }
    animation->update();
}
float Animation::slowdown() {
    if (parent_558 && !((base.flags.word_04 >> 12) & 1u)) return parent_558->slowdown();
    else return field_560;
}
void Animation::update_motion() {
    if (base.vector_44.x != 0.0f) {
        base.vector_38.x = add_angles(base.vector_38.x, base.vector_44.x * float(default_timer_clock));
        base.flags.word_04 |= 2u;
    }
    if (base.vector_44.y != 0.0f) {
        base.vector_38.y = add_angles(base.vector_38.y, base.vector_44.y * float(default_timer_clock));
        base.flags.word_04 |= 2u;
    }
    if (base.vector_44.z != 0.0f) {
        base.vector_38.z = add_angles(base.vector_38.z, base.vector_44.z * float(default_timer_clock));
        base.flags.word_04 |= 2u;
    }
    if (base.vector_60.y != 0.0f) {
        base.vector_50.y += base.vector_60.y * float(default_timer_clock);
        base.flags.word_04 |= 4u;
    }
    if (base.vector_60.x != 0.0f) {
        base.vector_50.x += base.vector_60.x * float(default_timer_clock);
        base.flags.word_04 |= 4u;
    }
    if (base.field_3a0 != 0.0f) {
        base.field_78 += base.field_3a0 * float(default_timer_clock);
        if (base.field_78 >= 2.0f) base.field_78 -= 2.0f;
        else if (base.field_78 < 0.0f) base.field_78 += 2.0f;
    }
    if (base.field_3a4 != 0.0f) {
        base.field_7c += base.field_3a4 * float(default_timer_clock);
        if (base.field_7c >= 2.0f) base.field_7c -= 2.0f;
        else if (base.field_7c < 0.0f) base.field_7c += 2.0f;
    }
}
void Animation::update_interpolations() {
    if (base.interpolation_8c.duration_value()) {
        if (!((base.flags.word_04 >> 6) & 1u)) base.vector_2c = base.interpolation_8c.sample();
        else base.vector_484 = base.interpolation_8c.sample();
    }
    if (base.interpolation_e0.duration_value()) {
        base.interpolation_e0.sample();
        base.channels_490.red = static_cast<std::uint8_t>(base.interpolation_e0.current_value().third);
        base.channels_490.green = static_cast<std::uint8_t>(base.interpolation_e0.current_value().second);
        base.channels_490.blue = static_cast<std::uint8_t>(base.interpolation_e0.current_value().first);
    }
    if (base.interpolation_134.duration_value()) base.channels_490.alpha = static_cast<std::uint8_t>(base.interpolation_134.sample());
    if (base.interpolation_1e0.duration_value()) {
        base.vector_50 = base.interpolation_1e0.sample(); base.flags.word_04 |= 4u;
    }
    if (base.interpolation_220.duration_value()) {
        base.vector_58 = base.interpolation_220.sample(); base.flags.word_04 |= 4u;
    }
    if (base.interpolation_260.duration_value()) {
        base.vector_68 = base.interpolation_260.sample(); base.flags.word_04 |= 8u;
    }
    if (base.interpolation_160.duration_value()) {
        base.vector_38 = base.interpolation_160.sample(); base.flags.word_04 |= 2u;
    }
    if (base.interpolation_1b4.duration_value()) {
        base.vector_38.z = float(base.interpolation_1b4.sample()); base.flags.word_04 |= 2u;
    }
    if (base.interpolation_2a0.duration_value()) {
        base.interpolation_2a0.sample();
        base.channels_494.red = static_cast<std::uint8_t>(base.interpolation_2a0.current_value().third);
        base.channels_494.green = static_cast<std::uint8_t>(base.interpolation_2a0.current_value().second);
        base.channels_494.blue = static_cast<std::uint8_t>(base.interpolation_2a0.current_value().first);
    }
    if (base.interpolation_2f4.duration_value()) base.channels_494.alpha = static_cast<std::uint8_t>(base.interpolation_2f4.sample());
    if (base.interpolation_320.duration_value()) base.field_3a0 = base.interpolation_320.sample();
    if (base.interpolation_34c.duration_value()) base.field_3a4 = base.interpolation_34c.sample();
}
}

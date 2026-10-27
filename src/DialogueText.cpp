#include "DialogueText.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "EnemyController.hpp"
#include "HudGauge.hpp"
#include "LaserParameters.hpp"
#include "TextLine.hpp"
#include "WindowState.hpp"

#if defined(_M_IX86)
static_assert(offsetof(th20::WindowState, scale) == 0x20C0);
#endif

namespace th20::dialogue_text {

int is_lead(std::uint8_t value) {
    if ((value >= 0x81 && value <= 0x9f) ||
        (value >= 0xe0 && value <= 0xfc)) {
        return 1;
    } else {
        return 0;
    }
}

const char* decode(const char* input) {
    unsigned offset = 0;
    std::uint8_t key = 0x77;
    std::uint8_t step = 7;
    std::uint8_t value;
    do {
        value = static_cast<std::uint8_t>(*input ^ key);
        decoded_text[offset] = static_cast<char>(value);
        ++offset;
        ++input;
        key = static_cast<std::uint8_t>(key + step);
        step = static_cast<std::uint8_t>(step + 0x10);
    } while (value);

    unsigned index = 0;
    while (static_cast<unsigned char>(decoded_text[index])) {
        if (is_lead(static_cast<unsigned char>(decoded_text[index]))) {
            ++index;
        } else if (static_cast<unsigned char>(decoded_text[index]) == '_') {
            decoded_text[index] = ' ';
        }
        ++index;
    }
    return decoded_text;
}

} // namespace th20::dialogue_text

namespace th20 {

Dialogue::Dialogue(std::uint8_t* input)
    : state(0), field_74(0), field_78(0), field_c8(0), script(nullptr),
      ready_state(0), field_108(0), field_10c(0), field_110(0), field_114(0),
      fields_118{}, text_width(0.0f), field_138(0), field_13c(0) {
    timer_04 = 0;
    timer_14 = 0;
    field_c8 = 0;
    timer_24 = 0;
    script = input;
    handle_58 = current_ascii->text_animation_file()->spawn("text", 20, -1, nullptr);
    handle_5c = current_ascii->text_animation_file()->spawn("text", 20, -1, nullptr);
    handle_5c.interrupt_offset_7(0);
    handle_58.resolve()->field_578 = 0x15;
    handle_58.resolve()->field_579 = 0x15;
    handle_5c.resolve()->field_578 = 0x15;
    handle_5c.resolve()->field_579 = 0x15;
    handle_60 = current_ascii->text_animation_file()->spawn("text", 21, -1, nullptr);
    handle_64 = current_ascii->text_animation_file()->spawn("text", 21, -1, nullptr);
    handle_64.interrupt_offset_7(0);
    handle_60.resolve()->field_578 = 0x15;
    handle_60.resolve()->field_579 = 0x15;
    handle_64.resolve()->field_578 = 0x15;
    handle_64.resolve()->field_579 = 0x15;
    handle_58.resolve()->base.flags.word_04 &= ~0x400u;
    handle_5c.resolve()->base.flags.word_04 &= ~0x400u;
    handle_60.resolve()->base.flags.word_04 &= ~0x400u;
    handle_64.resolve()->base.flags.word_04 &= ~0x400u;
    AnimationEntryCallback follow = [](Animation* animation) {
        current_front->dialogue_value()->follow_box(animation);
        return 0;
    };
    handle_58.resolve()->set_field_5dc(follow);
    handle_5c.resolve()->set_field_5dc(follow);
    handle_60.resolve()->set_field_5dc(follow);
    handle_64.resolve()->set_field_5dc(follow);
    field_108 = 0;
    field_10c = 0;
    fields_118[0] = 0;
    fields_118[1] = 0;
    fields_118[2] = 0;
    fields_118[3] = 0;
    field_114 = 0;
    positions[0] = Vector3(16.0f, 0.0f, 0.0f);
    positions[1] = Vector3(16.0f, 0.0f, 0.0f);
    positions[2] = Vector3(16.0f, 0.0f, 0.0f);
    positions[3] = Vector3(16.0f, 0.0f, 0.0f);
    bullet_controller(0)->cancel_all(0);
    laser_controller(0)->cancel_all(0, 0);
    enemy_controller(0)->clear();
    text_position.x = 384.0f;
    text_position.y = 640.0f;
    text_position.z = 0.0f;
    text_width = 320.0f;
    flags.flag_6 = 0;
    field_110 = 0;
}

Dialogue::~Dialogue() {
    for (std::int32_t index = 0; index < 4; ++index) {
        portraits[index].retire();
        portrait_overlays[index].retire();
    }
    handle_54.retire();
    handle_58.retire();
    handle_5c.retire();
    handle_60.retire();
    handle_64.retire();
    handle_68.retire();
    handle_6c.retire();
}

void Dialogue::follow_box(Animation* animation) {
    Animation* child = handle_6c.find_child(field_13c + 166, 0);
    if (child) {
        Vector3 position;
        child->position(position);
        position.x = (2.0f / window_state.scale) * position.x;
        position.y = (2.0f / window_state.scale) * position.y;
        if (field_114 == 1) {
            if (child->scale_x_value() < 1.0f) {
                position.x += (child->scale_x_value() + 0.125f) * 32.0f - 8.0f;
            } else {
                position.x += 1.0f * 32.0f - 8.0f;
            }
        } else if (field_114 == 0) {
            position.x -= 36.0f;
        } else if (field_114 == 2) {
            position.x += (child->scale_x_value() + 0.125f) * 16.0f - 8.0f;
        }
        animation->set_position(position);
    }
}

std::int32_t Dialogue::ready() { return ready_state; }

} // namespace th20

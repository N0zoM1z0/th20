#include "Animation.hpp"
namespace th20 {
void Animation::set_rotation(float angle) { set_rotation_z(angle); }
void Animation::set_rotation_z(float angle) {
    base.vector_38.z = angle;
    base.flags.word_04 |= 2u;
}
void Animation::set_scale(float x, float y) {
    base.vector_50.x = x;
    base.vector_50.y = y;
    base.flags.word_04 |= 4u;
}
void Animation::set_scale_58(float x, float y) {
    base.vector_58.x = x;
    base.vector_58.y = y;
    base.flags.word_04 |= 4u;
}
void Animation::interpolate_scale(std::int32_t duration, std::int32_t mode, float x, float y) {
    Vector2 target;
    target.x = x;
    target.y = y;
    auto& interpolation = base.interpolation_1e0;
    interpolation.begin(duration, mode, scale_ref(), target);
}
Vector2& Animation::scale_ref() { return base.vector_50; }
Vector3& Animation::vector_5bc_ref() { return vector_5bc; }
void Animation::interpolate_position(std::int32_t duration, std::int32_t mode,
                                     const Vector3& from, const Vector3& to) {
    auto& interpolation = base.interpolation_8c;
    interpolation.begin(duration, mode, from, to);
}
void Animation::set_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    base.channels_490.red = red;
    base.channels_490.green = green;
    base.channels_490.blue = blue;
}
void Animation::interpolate_color(std::int32_t duration, std::int32_t mode, const Color3& color) {
    IntegerTriple from(static_cast<std::uint8_t>((base.color_490 >> 16) & 255u),
                       static_cast<std::uint8_t>((base.color_490 >> 8) & 255u),
                       static_cast<std::uint8_t>(base.color_490 & 255u));
    IntegerTriple to(color);
    auto& interpolation = base.interpolation_e0;
    interpolation.begin(duration, mode, from, to);
}
void Animation::set_alpha(std::uint8_t alpha) {
    base.channels_490.alpha = alpha;
}
void Animation::set_alpha_494(std::uint8_t alpha) {
    base.channels_494.alpha = alpha;
}
void Animation::interpolate_alpha(std::int32_t duration, std::int32_t mode, std::uint8_t alpha) {
    const std::int32_t from = base.channels_490.alpha;
    const std::int32_t to = alpha;
    auto& interpolation = base.interpolation_134;
    interpolation.begin(duration, mode, from, to);
}
void Animation::interpolate_alpha_494(std::int32_t duration, std::int32_t mode, std::uint8_t alpha) {
    const std::int32_t from = base.channels_494.alpha;
    const std::int32_t to = alpha;
    auto& interpolation = base.interpolation_2f4;
    interpolation.begin(duration, mode, from, to);
    if (!base.flags.color_mode) base.flags.color_mode = 1;
}
void Animation::set_flag_byte_01(std::uint8_t value) {
    base.flags.bytes_00.field_01 = value;
}
}
namespace th20 {
void Animation::update_layer() {}
void Animation::set_layer(std::int32_t layer) {
    base.field_14 = layer;
    update_layer();
    if (base.field_14 >= 3 && base.field_14 <= 19) base.flags.layer_mode = 1;
    else if (base.field_14 >= 20 && base.field_14 <= 23) base.flags.layer_mode = 2;
    else base.flags.layer_mode = 0;
    if (((base.field_14 >= 20 && base.field_14 <= 36) ||
         (base.field_14 >= 45 && base.field_14 <= 53)) &&
        !((base.flags.word_04 >> 23) & 1u)) base.flags.field_0c = 1;
}
}

namespace th20 {
void Animation::set_slowdown(float value) { field_560 = value; }
}

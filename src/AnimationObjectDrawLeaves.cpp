#include "Animation.hpp"

namespace th20 {

float Animation::rotation_y_value() const {
    return base.vector_38.y;
}

void Animation::set_rotation_y(float angle) {
    base.vector_38.y = angle;
    base.flags.word_04 |= 2u;
}

void Animation::set_rotation_y_forward(float angle) {
    set_rotation_y(angle);
}

void Animation::set_scale_x(float x) {
    base.vector_50.x = x;
    base.flags.word_04 |= 4u;
}

void Animation::set_scale_y(float y) {
    base.vector_50.y = y;
    base.flags.word_04 |= 4u;
}

} // namespace th20

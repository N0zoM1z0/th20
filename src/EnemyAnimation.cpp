#include "Enemy.hpp"
#include "Animation.hpp"
namespace th20 {
void EnemyState::change_animation() {
    auto* instruction = entity->current_instruction();
    const auto index = integer_argument(0);
    if (animations.size() < static_cast<std::size_t>(index + 1)) {
        auto& links = animations;
        links.resize(index + 1);
    }
    auto& links = animations;
    auto* animation = links[index].handle.resolve();
    if (!animation) return;
    switch (instruction->opcode) {
    case 319: animation->set_rotation(float_argument(1)); break;
    case 329: animation->set_scale(float_argument(1), float_argument(2)); break;
    case 335: animation->set_scale_58(float_argument(1), float_argument(2)); break;
    case 330:
        animation->interpolate_scale(integer_argument(1), integer_argument(2),
                                     float_argument(3), float_argument(4)); break;
    case 325:
        animation->set_color(integer_argument(1), integer_argument(2), integer_argument(3)); break;
    case 326: {
        Color3 color;
        color.red = integer_argument(3);
        color.green = integer_argument(4);
        color.blue = integer_argument(5);
        animation->interpolate_color(integer_argument(1), integer_argument(2), color);
        break;
    }
    case 327: animation->set_alpha(integer_argument(1)); break;
    case 328: animation->interpolate_alpha(integer_argument(1), integer_argument(2), integer_argument(3)); break;
    case 331: animation->set_alpha_494(integer_argument(1)); break;
    case 332: animation->interpolate_alpha_494(integer_argument(1), integer_argument(2), integer_argument(3)); break;
    case 333:
        animation->interpolate_position(integer_argument(1), integer_argument(2),
                                        animation->vector_5bc_ref(),
                                        {float_argument(3), float_argument(4), 0.0f});
        break;
    case 336: animation->set_layer(integer_argument(1)); break;
    case 337: animation->set_flag_byte_01(integer_argument(1)); break;
    }
}
}

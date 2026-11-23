#include "EnemyStateBulletClearOpcode.hpp"
#include "EnemyState.hpp"
#include "Animation.hpp"
#include "Bullet.hpp"
#include "CollisionGeometry.hpp"
#include "Player.hpp"
#include "Session.hpp"

namespace th20 {

extern const float native_one_56c8cc;
extern const float native_six_56f00c;
extern const float native_ten_56e734;

int EnemyState::clear_bullets_in_animation_rectangle() {
    Animation* const animation = animations[0].handle.resolve();
    const float width = animation->scale_x_value();
    const float height = animation->scale_y_value();
    const float direction = animation->rotation_z_value();
    auto& active = context->bullet_controller()->active_list();
    {
        auto iterator = active.begin();
        auto* const end = active.end();
        for (; iterator.differs(end); iterator.advance()) {
            auto* const link = iterator.get();
            Bullet* const bullet = link->node_value();
            const float bullet_y = bullet->position_ref().y;
            const float bullet_x = bullet->position_ref().x;
            const float center_y = position_ref().y;
            const float center_x = position_ref().x;
            if (geometry::rectangle_circle(center_x, center_y, width, height, direction,
                                           bullet_x, bullet_y, native_six_56f00c)) {
                bullet->set_timer_4d8(counters.field_10);
                bullet->animation_ref()->set_packed_color(0xffa05000u);
                bullet->set_field_18_to_ten();
            }
        }
    }

    const float player_y = context->player()->position_ref().y;
    const float player_x = context->player()->position_ref().x;
    const float center_y = position_ref().y;
    const float center_x = position_ref().x;
    if (geometry::rectangle_circle(center_x, center_y, width, height, direction,
                                   player_x, player_y, native_ten_56e734)) {
        player(0)->set_field_20ec(counters.field_10);
    }
    return 0;
}

int EnemyState::clear_all_bullets_for_enemy_clear() {
    auto& active = context->bullet_controller()->active_list();
    {
        auto iterator = active.begin();
        auto* const end = active.end();
        for (; iterator.differs(end); iterator.advance()) {
            auto* const link = iterator.get();
            Bullet* const bullet = link->node_value();
            bullet->set_timer_4d8(native_one_56c8cc);
            bullet->animation_ref()->set_packed_color(0xffffffffu);
            bullet->clear_field_18();
        }
    }

    Player* const target_player = player(0);
    target_player->set_field_20ec(native_one_56c8cc);
    return 0;
}

bool execute_enemy_bullet_clear_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 629)
        return false;

    using Callback = int (EnemyState::*)();
    static const Callback callbacks[] = {
        nullptr,
        &EnemyState::clear_bullets_in_animation_rectangle,
        &EnemyState::clear_all_bullets_for_enemy_clear,
    };
    const std::int32_t index = state.integer_argument(0);
    (state.*callbacks[index])();
    return true;
}

} // namespace th20

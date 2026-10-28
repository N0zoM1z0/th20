// Complete original 863-byte active Bullet iteration and six draw-group
// publication boss. Iterator lifetime, true reference-return node access,
// live GameController pause flag and shared draw-path jumps are preserved.
#include "Bullet.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "GameController.hpp"

namespace th20 {
extern GameController* current_game_controller;

std::int32_t BulletController::rebuild_active_bullets() {
    current_animation_pool->select_view(view_index);
    bullet_count=0;
    draw_heads[0]=draw_heads[1]=draw_heads[2]=draw_heads[3]=draw_heads[4]=draw_heads[5]=nullptr;
    draw_tails[0]=draw_tails[1]=draw_tails[2]=draw_tails[3]=draw_tails[4]=draw_tails[5]=nullptr;
    {
    auto& active_list=active;
    auto iterator=active_list.begin();
    auto* end=active_list.end();
    for (; iterator.differs(end); iterator.advance()) {
        IntrusiveLink<Bullet>* link=iterator.get();
        // The actual paused-game path skips physics but still queues drawing.
        if (current_game_controller && ((current_game_controller->game_flags.bits >> 11) & 1u))
            goto publish_draw;
            if (((link->node_access()->flags.bits >> 8) & 1u) &&
                 ((link->node_access()->state == 2 && link->node_access()->timer_4f8.at_least(8)) ||
                   link->node_access()->state == 1)) {
                link->node_access()->process_collision(1);
            } else if (link->node_access()->step_update() != 0) {
                continue;
            }
    publish_draw:
        if (!((link->node_access()->flags.bits >> 9) & 1u)) {
            if (draw_heads[link->node_access()->draw_group] != nullptr) {
                if (draw_tails[link->node_access()->draw_group] != nullptr)
                    draw_tails[link->node_access()->draw_group]->draw_next = link->node_value();
            } else {
                draw_heads[link->node_access()->draw_group] = link->node_access();
            }
            draw_tails[link->node_access()->draw_group] = link->node_access();
            link->node_access()->draw_next = nullptr;
        }
        ++bullet_count;
        link->node_access()->timer_4f8++;
    }
    }
    return 1;
}
}

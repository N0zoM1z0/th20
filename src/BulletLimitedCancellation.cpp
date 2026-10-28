// Native entire capped radial Bullet cancellation, with the actual
// two-bit Bullet effect-mode field, native iterator and early EH return.
#include "Bullet.hpp"
#include "BulletDistance.hpp"
namespace th20 {
extern const float native_two;
std::int32_t BulletController::cancel_near_limited(const Vector3& center, float radius,
    std::int32_t mode, std::int32_t limit, std::uint32_t effects) {
    std::int32_t cancelled=0;
    {
        auto& list=active_list();
        auto it=list.begin();
        auto* last=list.end();
        for(;it.differs(last);it.advance()) {
            auto* entry=it.get();
            auto* bullet=entry->node_value();
            if (bullet->state!=2 && bullet->state!=1) continue;
            if (bullet->field_18!=0) continue;
            if (bullet_distance_within(bullet->position,center,bullet->size.x/native_two+radius)) {
                bullet->flags.fields.effect_mode = effects;
                bullet->cancel(mode);
                --limit;
                ++cancel_counter;
                ++cancelled;
                if (limit <= 0) return cancelled;
            }
        }
    }
    return cancelled;
}
}

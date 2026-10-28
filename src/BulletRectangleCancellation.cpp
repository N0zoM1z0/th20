// Original 707-byte native Bullet rectangle/radial cancellation boss.
// The two compound geometry filters, full iterator lifetime, and effect
// mode publication are all game-owned code, not an isolated branch.
#include "Bullet.hpp"
#include "CollisionGeometry.hpp"
namespace th20 {
extern const float native_two;
extern const float native_448;
extern const float native_gameplay_width;
std::int32_t BulletController::cancel_in_rectangle(const Vector3& center,
    const Vector3& dimensions, float direction, std::int32_t mode, std::uint32_t effects) {
    Vector3 start;
    Vector3 half;
    std::int32_t count=0;
    half=dimensions/native_two;
    start=center-half;
    half=center+half;
    {
        auto& list=active_list();
        auto it=list.begin();
        auto* last=list.end();
        for (;it.differs(last);it.advance()) {
            auto* entry=it.get();
            auto* bullet=entry->node_value();
            if (bullet->state!=2 && bullet->state!=1) continue;
            if (bullet->field_18!=0) continue;
            if (!(geometry::rectangle_circle(center.x, center.y, dimensions.x,
                                               dimensions.y, direction,
                                               bullet->position.x, bullet->position.y,
                                               bullet->size.x * bullet->scale) &&
                  geometry::rectangle_circle(0.0f, native_448 / native_two,
                                               native_gameplay_width, native_448,
                                               0.0f, bullet->position.x,
                                               bullet->position.y,
                                               bullet->size.x * bullet->scale))) continue;
            ++count;
            ++cancel_counter;
            bullet->flags.fields.effect_mode = effects;
            bullet->cancel(mode);
        }
    }
    return count;
}
}

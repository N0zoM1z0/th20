// Complete original std::function-filtered Bullet cancellation, including
// the ABI-correct by-value 40-byte callback owner, real EH teardown, full
// intrusive-list traversal and native cancellation calls.
#include "Bullet.hpp"
#include "BulletDistance.hpp"
#include <functional>
namespace th20 {
extern const float native_two;
std::int32_t BulletController::cancel_near_if(const Vector3& center,float radius,
    std::function<std::int32_t(const Vector3&)> predicate) {
    std::int32_t count=0;
    {
        auto& list=active_list();
        auto it=list.begin();
        auto* last=list.end();
        for (;it.differs(last);it.advance()) {
            auto* entry=it.get();
            auto* bullet=entry->node_value();
            if (bullet->state!=2 && bullet->state!=1) continue;
            if (bullet->field_18!=0) continue;
            if (bullet_distance_within(bullet->position,center,bullet->size.x/native_two+radius) &&
                predicate(bullet->position)) {
                bullet->flags.bits &= ~0x1800u;
                bullet->cancel(0);
                ++cancel_counter;
                ++count;
            }
        }
    }
    return count;
}
}

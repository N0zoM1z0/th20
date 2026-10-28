// Entire original BulletController radial cancellation gameplay method.
// Uses the native IntrusiveList<Bullet> lifetime; the separate native radius
// predicate and 662B individual cancellation routine remain external ABI.
#include "Bullet.hpp"
#include "BulletDistance.hpp"
namespace th20 {
extern const float native_two;
std::int32_t BulletController::cancel_near(const Vector3& center,float radius,std::int32_t mode) {
    std::int32_t cancelled=0;
    {
        auto& list=active;
        auto it=list.begin();
        auto* last=list.end();
        for(;it.differs(last);it.advance()) {
            auto* entry=it.get();
            auto* bullet=entry->node_value();
            if (bullet->state!=2 && bullet->state!=1) continue;
            if (bullet_distance_within(bullet->position,center,bullet->size.x/native_two+radius)) {
                bullet->cancel(mode);
                ++cancel_counter;
                ++cancelled;
            }
        }
    }
    return cancelled;
}
}

// Full original BulletController cancellation traversal, including complete
// observed list-iterator lifetime, state filtering, and native cancellation ABI.
#include "Bullet.hpp"
namespace th20 {
std::int32_t BulletController::cancel_all(std::int32_t mode) {
    std::int32_t cancelled=0;
    {
        auto& list=active_list();
        auto it=list.begin();
        auto* last=list.end();
        for(;it.differs(last);it.advance()) {
            auto* entry=it.get();
            auto* bullet=entry->node_value();
            if (bullet->state==0 || bullet->state==3) continue;
            bullet->cancel(mode);
            ++cancelled;
        }
    }
    return cancelled;
}
}

namespace th20 {
IntrusiveList<Bullet>& BulletController::active_list() { return active; }
}

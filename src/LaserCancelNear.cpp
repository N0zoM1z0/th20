#include "LaserParameters.hpp"

namespace th20 {

std::int32_t LaserController::cancel_near(const Vector3& center, float radius,
                                          std::int32_t mode, std::int32_t argument) {
    cancel_position=center;

    std::int32_t cancelled=0;
    {
        auto& list=active;
        auto it=list.begin();
        auto* last=list.end();
        for (;it.differs(last);it.advance()) {
            auto* link=it.get();
            auto* laser=link->node_value();
            if (laser->state==1) continue;
            cancelled+=laser->cancel_circle(center,radius,mode,argument);
        }
    }
    return cancelled;
}

}

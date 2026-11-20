#include "LaserParameters.hpp"

namespace th20 {

std::int32_t LaserController::cancel_near(const Vector3& center, float radius,
                                          std::int32_t mode, std::int32_t argument) {
    std::int32_t cancelled=0;
    cancel_position=center;
    {
        auto& list=active;
        auto it=list.begin();
        auto* last=list.end();
        for (;it.differs(last);it.advance()) {
            auto* link=it.get();
            if (link->node_access()->state!=1) {
                cancelled+=link->node_access()->cancel_circle(center,radius,mode,argument);
            }
        }
    }
    return cancelled;
}

}

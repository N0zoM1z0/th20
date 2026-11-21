#include "LaserParameters.hpp"

namespace th20 {

std::int32_t LaserController::cancel_all(std::int32_t mode, std::int32_t argument) {
    {
        auto& list = active;
        auto it = list.begin();
        auto* last = list.end();
        for (; it.differs(last); it.advance()) {
            auto* link = it.get();
            if (link->node_access()->state != 1) {
                link->node_access()->erase(mode, argument);
            }
        }
    }
    return 1;
}

} // namespace th20

#include "GameController.hpp"

namespace th20 {

std::int32_t GameController::update_node_enabled() const {
    std::int32_t result;
    if (update_node!=nullptr && update_node->enabled()) result=1;
    else result=0;
    return result;
}

}

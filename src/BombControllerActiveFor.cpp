#include "Bomb.hpp"
namespace th20 {
bool BombController::active_for(std::int32_t duration) const {
    if (active_state==1 && age.less_than(duration)) return true;
    return false;
}
}

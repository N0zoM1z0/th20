#include "Bomb.hpp"
namespace th20 {
std::uint8_t BombController::active_for(std::int32_t duration) const {
    std::int32_t result;
    if (active_state==1 && age.less_than(duration)) result=1;
    else result=0;
    return static_cast<std::uint8_t>(result);
}
}

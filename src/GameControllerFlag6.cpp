#include "GameController.hpp"

namespace th20 {

std::uint32_t GameController::flag_6_set() const {
    return (game_flags.bits>>6)&1u;
}

}

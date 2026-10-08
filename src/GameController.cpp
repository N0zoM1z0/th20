#include "GameController.hpp"
#include "EclDiagnostic.hpp"
namespace th20 {
GameController::GameController() noexcept
    :load_stage(0),field_34(0),game_flags{},field_ec(0),field_f0(0),field_f4(0),
     field_f8(0.0),field_100(0.0),restart_mode(0),field_10c(0) {
    ecl_diagnostic_hint("initialize GameTaskInf\n");
}
int GameController::update_suppressed() const {
    return (game_flags.bits&1u)|((game_flags.bits>>2)&1u);
}
int GameController::animation_frozen() const {return (game_flags.bits>>1)&1u;}
std::int32_t GameController::restart() const {return restart_mode;}
void GameController::clear_flag_6() {game_flags.bits&=~0x40u;}
}

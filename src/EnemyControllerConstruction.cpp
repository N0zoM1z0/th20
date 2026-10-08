#include "EnemyController.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {
EnemyController::EnemyController() noexcept
    : field_c4(0), field_c8(0), field_cc(0), field_e0(0),
      animation_files{}, loader(nullptr), field_120(0), field_124(0),
      player_index(0), context(nullptr) {
    ecl_diagnostic_hint("initialize EnemyCtrlInf\n");
    advance_generation();
}
}

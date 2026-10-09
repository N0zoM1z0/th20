#include "Player.hpp"
#include "EclDiagnostic.hpp"
namespace th20 {
Player::Player() noexcept
    : state(0),entity_flags{},animation_file(nullptr),field_20(0),field_24(0),
      field_674(0),field_678(0),field_67c(0),field_680(0),focused(0),
      speed_20b4(0),speed_20b8(0),speed_20bc(0),speed_20c0(0),
      field_20e4(0),field_20e8(0),field_20ec(0),field_2204(0),shot_data(nullptr),
      collision_expansion(0),clock_scale(0),field_2240(0),animation_scripts{},
      view_index(0),context(nullptr) {
    ecl_diagnostic_hint("initialize PlayerInf\n");
}
}

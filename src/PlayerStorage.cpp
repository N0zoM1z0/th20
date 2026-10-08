#include "PlayerStorage.hpp"
namespace th20 {
DamageHandle::DamageHandle(std::uint32_t initial):value(initial) {}
PlayerOption::PlayerOption() noexcept
    : state(0),field_d8(0),field_f4(0),field_f8(0),field_fc(0),state_100{},
      field_108(0),field_10c(0),field_110(0),field_118(0),field_11c(0),field_120(0),
      player_index(0),context(nullptr) {}
PlayerFeedback::PlayerFeedback()
    : field_30(0),field_34(0),field_38(0),field_3c(0),enabled(0),player_index(0),context(nullptr) {}
PlayerCollisionBounds::PlayerCollisionBounds():normal_radius(0),focus_radius(0) {}
PlayerMotionParameters::PlayerMotionParameters() noexcept
    :field_00(0),field_04(0),field_08(0),field_0c(0),field_10(0) {}
PlayerShot::PlayerShot()
    :state_14(0),flags_3c{},field_40(0),field_44(0),field_48(0),field_4c(0),
     field_9c(0),field_a4(1),field_a8(0),field_ac(0),words_b8{},record_index(0),
     words_e0{},field_10c(0),field_110(0),byte_114(0),player_index(0),owner(nullptr),context(nullptr) {}
PlayerShotPool::PlayerShotPool() noexcept {}
PlayerShotController::PlayerShotController()
    :field_12460(0),field_12464(0),counters_12468{},counters_124e0{},field_12558(0),
     flags_1255c{},field_12564(0),field_12578(0),byte_1257c(0),player_index(0),context(nullptr) {}
}

#include "EnemyController.hpp"

namespace th20 {
EnemyHandle::EnemyHandle() noexcept : value(0) {}
void EnemyHandle::operator=(std::uint32_t input) { value = input; }
EnemyData::EnemyData() : field_30(0), field_34(0), field_38(0), field_3c(0), field_40(0), field_84{}, field_88(0), field_9c(0), field_a0(0) {}
void EnemyController::set_selected(std::uint32_t index, Enemy* enemy) {
    data.handles.at(index) = enemy ? enemy->identifier_value().get() : 0u;
}
void EnemyController::set_field_84_bit_0(std::uint32_t input) {
    data.field_84.bits.bit_0 = input;
}
void EnemyController::set_field_88(std::uint32_t value) {
    data.field_88 = value;
}
} // namespace th20

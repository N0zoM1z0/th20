#include "EnemyHealth.hpp"

namespace th20 {

EnemyHealth::EnemyHealth()
    : health(0), field_04(0), phase_health(0), scaled_health(0),
      threshold(0), damage(0), flags{} {}

void EnemyHealth::reset() {
    health = 0;
    field_04 = 0;
    phase_health = 0;
    flags.bits &= ~2u;
    damage = 0;
}

std::int32_t EnemyHealth::apply(std::int32_t amount) {
    damage += static_cast<std::uint32_t>(amount);
    if (flags.bits & 1u) {
        scaled_health -= static_cast<std::uint32_t>(amount);
        health = static_cast<std::uint32_t>(
            static_cast<std::int32_t>(scaled_health - threshold * 7u) / 7)
            + threshold;
        return static_cast<std::int32_t>(health);
    } else {
        return static_cast<std::int32_t>(health -= static_cast<std::uint32_t>(amount));
    }
}

void EnemyHealth::record(std::int32_t amount) {
    damage += static_cast<std::uint32_t>(amount);
}

int EnemyHealth::positive() const {
    return static_cast<std::int32_t>(health) > 0 ? 1 : 0;
}

std::uint32_t EnemyHealth::forced_end() const {
    return (flags.bits >> 1) & 1u;
}

} // namespace th20

namespace th20 {
void EnemyHealth::set_health(std::uint32_t value) { health = value; }
void EnemyHealth::set_initial(std::uint32_t value) { field_04 = value; }
void EnemyHealth::set_phase(std::uint32_t value) { phase_health = value; }
}

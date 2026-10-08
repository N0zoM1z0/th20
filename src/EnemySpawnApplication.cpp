#include "Enemy.hpp"
#include "Session.hpp"

namespace th20 {
int Enemy::apply_spawn(const EnemySpawn& parameters) {
    spawn_parameters = parameters;
    auto& movements = state.movements;
    movements.resize(1);
    auto& active_movements = state.movements;
    active_movements[0].motion.set_position(parameters.position);
    auto& identifier = state.identifier_188;
    identifier = parameters.field_0c;
    auto& health = state.health;
    health.set_health(parameters.health);
    auto& initial_health = state.health;
    initial_health.set_initial(parameters.health);
    auto& phase_health = state.health;
    phase_health.set_phase(parameters.health);
    auto& pattern = state.pattern;
    pattern.set_base_kind(parameters.field_10);
    state.flags.fields_04.spawn_mirrored = parameters.flags_18;
    state.field_50 = session.mode();
    if (state.field_50 < 4)
        main.rank = static_cast<std::uint8_t>(1u << state.field_50);
    else main.rank = 2;
    state.counters = parameters.variables;
    state.timer_288 = 2;
    state.flags.fields_04.viewport_relative = parameters.flags_1c.bits & 1u;
    state.field_30 = 0;
    state.identifier_04 = parameters.field_50;
    if (parameters.health >= 1000) state.flags.word_04 |= 0x4000u;
    state.field_280 = session.clamped_field_1fc();
    tick();
    if ((state.flags.word_04 >> 7) & 1u) {
        auto value = state.pattern.base_kind_value();
        auto& updated_pattern = state.pattern;
        updated_pattern.set_base_kind(value);
    }
    state.field_250 = (state.identifier.get() & 1u) + 3;
    if (state.field_254 == 0) {
        state.field_254 = 37;
        if (state.field_20 == 2) switch (state.field_24) {
        case 0: case 20: case 59: case 62: case 104: state.field_254 = 37; break;
        case 5: case 25: case 53: case 94: state.field_254 = 33; break;
        case 15: case 109: state.field_254 = 45; break;
        case 10: case 56: case 99: state.field_254 = 41; break;
        case 30: state.field_254 = 51; break;
        case 35: state.field_254 = 50; break;
        case 40: state.field_254 = 49; break;
        }
        state.field_258 = 1;
    }
    return 0;
}
}

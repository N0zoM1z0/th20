#include "Enemy.hpp"
#include "Session.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "ItemResourceOwners.hpp"
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "SoundInf.hpp"
#include "WeaponStoneInfo.hpp"
#include "CollisionGeometry.hpp"

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

std::int32_t Enemy::defeat() {
    {
        auto& list = children;
        for (auto it = list.begin(), *finish = list.end(); it.differs(finish); it.advance()) {
            auto* link = it.get();
            link->node_value()->defeat();
            auto& child_flags = link->node_value()->state.flags.word_04;
            child_flags |= 0x200u;
        }
    }
    parent_link.detach();
    if (state.field_250 >= 0) {
        const float x = state.motion_110.position_x();
        const auto sound = state.field_250;
        process_sound.request_effect_at(sound, x);
    }
    const auto distance = geometry::squared_distance_xy(state.vector_6c, position_ref());
    float direction;
    if (0.2f * 0.2f > distance) direction = -3.1415927410125732f / 2.0f;
    else direction = geometry::direction_xy(state.vector_6c, position_ref());
    if (state.field_254 >= 0) {
        auto* effects = context->effect_info();
        auto* file = animation_file(state.field_258);
        auto& origin = position_ref();
        const auto script = state.field_254;
        const auto handle = file->spawn(nullptr, script, origin, direction, -1, nullptr).value;
        effects->publish_handle(handle);
    }
    auto* controller = context->enemy_controller();
    controller->set_angle_128(direction);
    auto& drops = state.pattern;
    const auto mark = bomb_drop_disabled();
    auto& origin = position_ref();
    drops.drop(origin, mark);
    if (damage_marked()) {
        auto* feedback = player(0)->feedback_value();
        const auto update = state.field_26c;
        feedback->record_hit(update);
        const std::int32_t multipliers[10]{100,150,200,250,300,400,500,600,700,800};
        const auto multiplier = multipliers[player(0)->feedback_value()->count_value() >= 10
            ? 9 : player(0)->feedback_value()->count_value()];
        const auto reward = static_cast<std::int32_t>(static_cast<std::uint32_t>(state.field_278)
            * static_cast<std::uint32_t>(multiplier)) / 100;
        auto* record = player_record(0);
        record->add_field_44(reward);
        if (!stone_enemy_controller()->byte_b0_value()) {
            auto* extra = player_record(0);
            extra->add_field_5c(reward);
        }
        auto kind = static_cast<std::int32_t>(script_random.next() % 5u);
        auto* stone = weapon_stone_info(0);
        auto& position = position_ref();
        stone->record_damage(&position, 2000, kind + 9);
        if (!stone_enemy_controller()->byte_b0_value()) {
            if (kind != 4) {
                auto* target = player_record(0);
                auto* selected = player_record(0);
                const auto configuration = selected->starting_configuration(kind);
                target->add_reward(configuration, reward);
            } else {
                kind = static_cast<std::int32_t>(script_random.next() % 8u);
                auto* target = player_record(0);
                target->add_reward(kind, reward);
            }
        }
    }
    if (state.field_27c != -1) {
        terminate_async();
        reset();
        select_subroutine_index(state.field_27c);
        EclManager::tick(0.0f);
        state.field_27c = -1;
        if ((state.flags.word_04 >> 27) & 1u) return 0;
    }
    if (callback) {
        auto& invoke = callback;
        invoke(this);
    }
    return 1;
}
}

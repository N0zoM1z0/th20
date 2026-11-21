#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "LockRegistry.hpp"
#include "EnemyStateMovementOpcode.hpp"
#include "EnemyStatePatternOpcode.hpp"
#include "EnemyStateControlOpcode.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"
#include "EnemyStateAnimationSpawnOpcode.hpp"
#include "EnemyStateCardStartOpcode.hpp"
#include "EnemyStateControllerSetterOpcode.hpp"
#include "EnemyStateFogOpcode.hpp"
#include "EnemyStateLaserOpcode.hpp"
#include "EnemyStateMembershipOpcode.hpp"
#include "EnemyStateMeshOpcode.hpp"
#include "EnemyStatePhaseOpcode.hpp"
#include "EnemyStateQueueCopyOpcode.hpp"
#include "EnemyStateQueuedParametersOpcode.hpp"
#include "EnemyStateScriptPointerOpcode.hpp"
#include "EnemyStateSharedQueuedParametersOpcode.hpp"
#include "EnemyStateShotCommandOpcode.hpp"
#include "EnemyStateShotFireOpcode.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

namespace th20 {
GameRandom script_random(1);
DiagnosticAllocator* process_allocator = nullptr;
LockRegistry process_locks;
std::int32_t defeat_result = 0;
std::uint32_t current_enemy_generation = 1, previous_enemy_generation = 0;
bool pattern_drop_called = false;
bool pattern_drop_bomb_mark = false;
Vector3 pattern_drop_origin{};
std::int32_t enemy_script_globals[4]{};
Enemy::~Enemy() = default;
EnemyController::~EnemyController() = default;
std::int32_t Enemy::defeat() { return defeat_result; }
void EnemyPattern::drop(const Vector3& origin, bool bomb_mark) {
    pattern_drop_called = true;
    pattern_drop_bomb_mark = bomb_mark;
    pattern_drop_origin = origin;
}
std::int32_t Enemy::read_integer(std::int32_t) { return 0; }
float Enemy::read_float(std::int32_t) { return 0.0f; }
Player* Context::player() { return nullptr; }
Enemy* EnemyController::find(std::uint32_t) { return nullptr; }
bool execute_enemy_phase_opcode(EnemyState&, const EclInstruction&, std::int32_t) { return false; }
bool execute_enemy_card_start_opcode(EnemyState&, const EclInstruction&, std::int32_t) { return false; }
bool execute_enemy_script_pointer_opcode(EnemyState&, const EclInstruction&, std::int32_t) { return false; }
bool execute_enemy_animation_spawn_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_controller_setter_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_fog_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_membership_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_mesh_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_queue_copy_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_shot_fire_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_shared_queued_parameters_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_shot_command_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_queued_parameters_opcode(EnemyState&, std::int32_t) { return false; }
bool execute_enemy_laser_opcode(EnemyState&, std::int32_t) { return false; }
}

int main() {
    using namespace th20;
    Enemy enemy;
    Context context;
    PlayerRecord player_record;
    EnemyController controller;
    context.current_player = &player_record;
    context.enemies = &controller;
    enemy.state.context = &context;
    enemy.state.identifier = 0x12345678u;
    EclLoader loader;
    alignas(16) std::array<std::uint8_t, 16 + 16 + 8 * 4> packet{};
    loader.records.push_back({"root-test", packet.data()});
    enemy.loader = &loader;
    enemy.main.manager = &enemy;
    enemy.main.position.subroutine = 0;
    enemy.main.position.offset = 0;
    enemy.current_runtime = &enemy.main;
    enemy.state.entity = &enemy;
    enemy.state.movements.resize(1);

    auto set_packet = [&](std::int16_t opcode, const std::array<std::uint32_t,8>& args) {
        auto* ins = reinterpret_cast<EclInstruction*>(packet.data() + 16);
        std::memset(ins, 0, sizeof(EclInstruction) + args.size() * sizeof(std::uint32_t));
        ins->opcode = opcode;
        ins->length = static_cast<std::uint16_t>(sizeof(EclInstruction) + args.size() * sizeof(std::uint32_t));
        ins->references = 0;
        std::memcpy(ins + 1, args.data(), args.size() * sizeof(std::uint32_t));
    };
    auto bits = [](float value) { std::uint32_t out; std::memcpy(&out,&value,4); return out; };

    enemy.state.flags.word_04 = 0xa5000000u;
    set_packet(424, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0xa5000008u);

    enemy.state.field_44 = 0;
    set_packet(448, {7,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.field_44 == 7);

    enemy.state.field_44 = 0;
    enemy.state.movements[0].motion.position = {1.0f,2.0f,0.0f};
    enemy.state.motion_110.position = {0.0f,0.0f,0.0f};
    set_packet(400, {bits(12.5f),bits(-7.25f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.movements[0].motion.position.x == 12.5f);
    assert(enemy.state.movements[0].motion.position.y == -7.25f);

    enemy.state.flags.word_04 = 0;
    set_packet(404, {bits(0.5f),bits(12.5f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(static_cast<float>(enemy.state.movements[0].motion.angle_1c) == 0.5f);
    assert(enemy.state.movements[0].motion.value_18 == 12.5f);

    defeat_result = 1;
    set_packet(560, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 1);
    defeat_result = 0;

    enemy.state.pattern.counts.fill(9);
    enemy.state.pattern.extra_counts.fill(7);
    enemy.state.pattern.duration = 99;
    set_packet(506, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    for (const auto value : enemy.state.pattern.counts) assert(value == 0);
    assert(enemy.state.pattern.duration == 0);

    set_packet(507, {1,17,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.counts[0] == 17);
    set_packet(567, {2,23,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.extra_counts[1] == 23);
    set_packet(568, {77,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.duration == 77);
    set_packet(572, {4,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.bomb_kind == 4);
    set_packet(508, {bits(-3.5f),bits(9.25f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.radius_x == -3.5f);
    assert(enemy.state.pattern.radius_y == 9.25f);
    set_packet(510, {6,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.base_kind == 6);

    session.field_70 = 2;
    enemy.state.pattern.counts[0] = 123;
    pattern_drop_called = false;
    set_packet(509, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.pattern.counts[0] == 123);
    assert(!pattern_drop_called);

    session.field_70 = 1;
    enemy.state.flags.word_08 = 1u << 5;
    enemy.state.motion_110.position = {3.0f,4.0f,5.0f};
    pattern_drop_called = false;
    set_packet(509, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(pattern_drop_called && pattern_drop_bomb_mark);
    assert(pattern_drop_origin.x == 3.0f && pattern_drop_origin.y == 4.0f && pattern_drop_origin.z == 5.0f);

    session.field_70 = 2;
    enemy.state.flags.word_08 = 0;
    pattern_drop_called = false;
    set_packet(556, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(pattern_drop_called && !pattern_drop_bomb_mark);

    enemy.state.field_284 = 0;
    player_record.field_dc = 0;
    set_packet(500, {bits(1.25f),bits(2.5f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.bounds_5c.x == 1.25f && enemy.state.bounds_5c.y == 2.5f);
    assert(enemy.state.field_284 == 1 && player_record.field_dc == 1);
    set_packet(501, {bits(-4.0f),bits(8.0f),0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.bounds_64.x == -4.0f && enemy.state.bounds_64.y == 8.0f);

    enemy.state.flags.word_04 = 0x8000u;
    set_packet(504, {bits(10.0f),bits(20.0f),bits(30.0f),bits(40.0f),0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0x8002u);
    assert(enemy.state.bounds_178.x == 10.0f && enemy.state.bounds_178.y == 20.0f);
    assert(enemy.state.bounds_178.width == 30.0f && enemy.state.bounds_178.height == 40.0f);
    set_packet(505, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.flags.word_04 == 0x8000u);

    enemy.state.flags.word_04 = 0x80u;
    set_packet(511, {123,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.health == 123 && enemy.state.health.field_04 == 123);
    assert(enemy.state.health.phase_health == 123 && enemy.state.health.scaled_health == 861);
    assert((enemy.state.flags.word_04 & 0x4080u) == 0x4080u);
    set_packet(566, {11,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(enemy.state.health.health == 11 && enemy.state.health.scaled_health == 77);
    assert(enemy.state.health.field_04 == 123 && enemy.state.health.phase_health == 123);

    controller.data.field_84.value = 0xabcd0001u;
    enemy.state.flags.word_04 = 0x8000u;
    set_packet(512, {3,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.field_84.value == 0xabcd0000u);
    assert(controller.data.handles[3].value == 0x12345678u);
    assert(enemy.state.field_270 == 3 && (enemy.state.flags.word_04 & 0x80u));
    set_packet(512, {0xffffffffu,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0);
    assert(controller.data.handles[3].value == 0);
    assert((enemy.state.flags.word_04 & 0x80u) == 0);

    enemy.state.timer_a8 = 8;
    set_packet(513, {0,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_a8) == 0);
    set_packet(515, {55,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_288) == 55);
    set_packet(535, {66,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && static_cast<std::int32_t>(enemy.state.timer_298) == 66);
    set_packet(526, {bits(-2.5f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_274 == 6.25f);
    set_packet(557, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && (enemy.state.flags.word_00 & 0x1000u));
    set_packet(558, {bits(7.25f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_38 == 7.25f);
    set_packet(559, {bits(-1.5f),0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_4c == -1.5f);
    set_packet(543, {1,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && (enemy.state.flags.word_04 & 0x8000u));
    set_packet(544, {9,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_30 == 9);
    set_packet(546, {10,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_34 == 10);
    set_packet(547, {11,0,0,0,0,0,0,0});
    assert(enemy.state.execute_opcode() == 0 && enemy.state.field_264 == 11);

    std::cout << "PASS root dispatch: movement 400/404/424/448, pattern 506-510/556/567/568/572, bounds/health/controller/state 500-559 and special 560 return\n";
}

#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "LockRegistry.hpp"
#include "EnemyStateMovementOpcode.hpp"
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
std::int32_t enemy_script_globals[4]{};
EnemyController* enemy_controller(std::int32_t) { return nullptr; }
Enemy::~Enemy() = default;
std::int32_t Enemy::defeat() { return defeat_result; }
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

    std::cout << "PASS whole-root dispatch for movement opcodes 400/404/424/448 and special opcode 560 return\n";
}

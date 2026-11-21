#pragma once

namespace th20 {

struct EnemyState;

// Native opcode 517 creates a mode-1 ScreenInf using three integer operands.
int execute_enemy_screen_effect_spawn_opcode(EnemyState& state);

} // namespace th20

#include "EnemyStateFogOpcode.hpp"
#include "EnemyState.hpp"
#include "EffectParameters.hpp"
#include "FogValue.hpp"
#include "StageResource.hpp"

namespace th20 {

bool execute_enemy_fog_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 551)
        return false;

    // Native construction and VM reads are deliberately interleaved in this
    // order. In particular, float operands are read 4 then 3, not 3 then 4.
    PackedColor color;
    const auto first = state.integer_argument(0);
    const auto second = state.integer_argument(1);
    color = static_cast<std::uint32_t>(state.integer_argument(2));
    const float far_distance = state.float_argument(4);
    const float near_distance = state.float_argument(3);

    const auto packed = color.value;
    FogValue value(near_distance, far_distance,
        static_cast<float>(packed & 0xffu),
        static_cast<float>((packed >> 8) & 0xffu),
        static_cast<float>((packed >> 16) & 0xffu),
        static_cast<float>((packed >> 24) & 0xffu));

    // The original reads 0x005C069C only after all five operand reads and the
    // real FogValue construction. The global is now a typed production owner.
    process_stage_resource->set_fog(first, second, value);
    return true;
}

} // namespace th20

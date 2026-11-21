#include "ItemResourceOwners.hpp"
#include "EffectParameters.hpp"

namespace th20 {

std::uint32_t EffectInfo::spawn_effect_at_position(
    std::int32_t kind, const Vector3& position, Animation* existing_animation) {
    const std::int32_t slot = select_handle_slot();
    if (slot == -1 || slot >= 1024)
        return 0;

    const std::uint32_t handle_value = spawn_effect(
        kind, *reinterpret_cast<const EffectParameters*>(&position), existing_animation).value;
    auto* handle_slots = &handles;
    (*handle_slots)[static_cast<std::uint32_t>(slot)].handle.value = handle_value;
    return static_cast<std::uint32_t>(slot) | 0x80000000u;
}

} // namespace th20

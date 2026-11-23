#include "EnemyStateQueuedShotPropertyOpcode.hpp"
#include "EnemyState.hpp"
#include <cstdint>
#include <utility>

namespace th20 {

#if defined(_M_IX86)
static_assert(offsetof(EnemyQueuedRecord, parameters) == 0x08);
static_assert(offsetof(ShotParameters, speed) == 0x1c);
static_assert(offsetof(ShotParameters, speed_step) == 0x20);
static_assert(offsetof(ShotParameters, count) == 0x24);
static_assert(offsetof(ShotParameters, rows) == 0x26);
static_assert(offsetof(ShotMetadata, field_38) == 0x38);
static_assert(offsetof(ShotMetadata, sound) == 0x3c);
static_assert(offsetof(ShotMetadata, alternate_sound) == 0x40);
#endif

// Native Enemy jump-table cases 605-608 operate on the same real queued-shot
// record as 602-604/618/620. The first two are ensure-only shared accesses;
// the latter two are writable accesses and must perform the native metadata
// copy-on-write before reading their value operands. Their narrow/wide stores
// target ShotMetadata::field_38/sound/alternate_sound, not the queued record's
// adjacent Vector3 fields.
bool execute_enemy_queued_shot_property_opcode(EnemyState& state,
                                               std::int32_t opcode) {
    switch (opcode) {
    case 605: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)metadata;
        record->parameters.speed = state.float_argument(1);
        record->parameters.speed_step = state.float_argument(2);
        return true;
    }
    case 606: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)metadata;
        record->parameters.count = static_cast<std::int16_t>(state.integer_argument(1));
        record->parameters.rows = static_cast<std::int16_t>(state.integer_argument(2));
        return true;
    }
    case 607: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)record;
        metadata->field_38 = static_cast<std::int16_t>(state.integer_argument(1));
        return true;
    }
    case 608: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)record;
        metadata->sound = state.integer_argument(1);
        metadata->alternate_sound = state.integer_argument(2);
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20

#pragma once

#include "AnimationHandle.hpp"
#include "EnemyHandle.hpp"
#include "IntrusiveLink.hpp"
#include "Timer.hpp"

#include <cstddef>
#include <cstdint>

namespace th20 {

extern const char stone_enemy_record_diagnostic_label[];

// One intrusive record owned by StoneEnemyController::records. Its EnemyHandle,
// AnimationHandle and Timer are anchored by the original constructor calls;
// the trailing words are initialized by the allocation path, not this ctor.
class StoneEnemyRecord {
public:
    IntrusiveLink<StoneEnemyRecord> link;
    EnemyHandle enemy_14;
    AnimationHandle handle_18;
    Timer timer_1c;
    std::int32_t field_2c;
    std::int32_t field_30;

    StoneEnemyRecord();
    void initialize(std::int32_t enemy_handle, std::int32_t player_index);
};

#if defined(_M_IX86)
static_assert(sizeof(StoneEnemyRecord) == 0x34);
static_assert(offsetof(StoneEnemyRecord, link) == 0x00);
static_assert(offsetof(StoneEnemyRecord, enemy_14) == 0x14);
static_assert(offsetof(StoneEnemyRecord, handle_18) == 0x18);
static_assert(offsetof(StoneEnemyRecord, timer_1c) == 0x1c);
static_assert(offsetof(StoneEnemyRecord, field_2c) == 0x2c);
static_assert(offsetof(StoneEnemyRecord, field_30) == 0x30);
#endif

} // namespace th20

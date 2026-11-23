#pragma once

#include "AnimationHandle.hpp"
#include "IntrusiveLink.hpp"
#include "Timer.hpp"

#include <cstddef>
#include <cstdint>

namespace th20 {

// One intrusive record owned by StoneEnemyController::records. The two
// AnimationHandles and Timer are anchored by the original constructor calls;
// the trailing words are initialized by the allocation path, not this ctor.
struct StoneEnemyRecord {
    IntrusiveLink<StoneEnemyRecord> link;
    AnimationHandle handle_14;
    AnimationHandle handle_18;
    Timer timer_1c;
    std::int32_t field_2c;
    std::int32_t field_30;

    StoneEnemyRecord() noexcept;
};

#if defined(_M_IX86)
static_assert(sizeof(StoneEnemyRecord) == 0x34);
static_assert(offsetof(StoneEnemyRecord, link) == 0x00);
static_assert(offsetof(StoneEnemyRecord, handle_14) == 0x14);
static_assert(offsetof(StoneEnemyRecord, handle_18) == 0x18);
static_assert(offsetof(StoneEnemyRecord, timer_1c) == 0x1c);
static_assert(offsetof(StoneEnemyRecord, field_2c) == 0x2c);
static_assert(offsetof(StoneEnemyRecord, field_30) == 0x30);
#endif

} // namespace th20

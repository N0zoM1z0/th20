#pragma once
#include <cstdint>

namespace th20 {
struct Enemy;
// Four-byte Enemy identifier, distinct from an animation handle. Resolution
// uses player 0's Controller and leaves stale identifiers intact.
struct EnemyHandle {
    std::uint32_t value;
    EnemyHandle() noexcept;
    Enemy* resolve();
};
static_assert(sizeof(EnemyHandle) == 4);
} // namespace th20

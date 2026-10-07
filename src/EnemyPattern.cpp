#include "EnemyPattern.hpp"
#include <cstring>

namespace th20 {

EnemyPattern::EnemyPattern()
    : player(0), base_kind(0), bomb_kind(0), counts{}, extra_counts{},
      duration(0), timer(), radius_x(0.0f), radius_y(0.0f) {}

void EnemyPattern::reset() {
    // Native reset clears the complete trivially copyable value before applying
    // the two radii and Timer assignment protocol; this differs from construction.
    std::memset(static_cast<void*>(this), 0, sizeof(*this));
    radius_y = 32.0f;
    radius_x = 32.0f;
    base_kind = 0;
    duration = 0;
    timer = 0;
}

void EnemyPattern::clear_counts() {
    counts.fill(0);
    duration = 0;
    timer = 0;
}

} // namespace th20

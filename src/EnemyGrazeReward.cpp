// Complete native 123-byte EnemyController graze-reward predicate.
// Actual 16 EnemyHandle values are scanned by std::any_of. The explicit
// branch preserves original bool normalization without any fake padding.
#include "EnemyController.hpp"
#include <algorithm>
namespace th20 {
bool EnemyController::graze_reward_active() {
    if (std::any_of(data.handles.begin(),data.handles.end(),[](EnemyHandle handle) { return handle.value != 0; })) return true; return false;
}
}

#include "StoneEnemyRecord.hpp"

namespace th20 {

StoneEnemyRecord::StoneEnemyRecord() noexcept
    : link(), handle_14(), handle_18(), timer_1c() {
    // The original constructor first default-constructs the five-pointer link,
    // then publishes this record as its node. Keep the separate initialize call.
    link.initialize(this);
}

} // namespace th20

#include "EnemyState.hpp"

namespace th20 {
// Native complete 119-byte ordinary copy assignment of a 76-byte queue
// record. MSVC emits the real shared_ptr copy, 40-byte ShotParameters copy,
// scalar field and two Vector3 copies; no manual byte copying is necessary.
EnemyQueuedRecord& EnemyQueuedRecord::operator=(const EnemyQueuedRecord&) = default;
}

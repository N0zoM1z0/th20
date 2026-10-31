// Original 153-byte ASCII task enqueue: lock scope, queue publication and
// by-value std::function destruction retain the genuine native EH behavior.
#include "TextLine.hpp"
#include "NativeCardAsciiTaskQueueView.hpp"
#include "LockRegistry.hpp"
#include <functional>
#include <mutex>
#include <utility>
namespace th20 {
void NativeCardAsciiTaskQueueView::enqueue_470180(std::function<void()> task) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(18));
    reinterpret_cast<AsciiInf*>(this)->pending_tasks.push_back(std::move(task));
}
#if defined(_M_IX86)
static_assert(sizeof(std::function<void()>)==0x28);
#endif
}

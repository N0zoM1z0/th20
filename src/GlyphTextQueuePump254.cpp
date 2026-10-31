// Whole original 254B/74-i386 TH20 glyph-render task queue dispatcher.
// The source deliberately preserves the native *count* test (not a bool
// std::list::_Empty call), two game-owned recursive lock slots 0x12/0x13,
// an owned 40-byte std::function copy, erase(begin()) and invocation while
// both original locks remain held. These are live game task operations.
#include "NativeGlyphTaskQueue.hpp"
#include "LockRegistry.hpp"
#include <mutex>
namespace th20 {
void glyph_task_pump_416140() {
    if (native_glyph_task_queue_5b66e0.size()!=0) {
        std::lock_guard<std::recursive_mutex> lock_writer(process_locks.slot(0x12));
        std::lock_guard<std::recursive_mutex> lock_reader(process_locks.slot(0x13));
        std::function<void()> task;
        task=native_glyph_task_queue_5b66e0.front();
        native_glyph_task_queue_5b66e0.erase(native_glyph_task_queue_5b66e0.begin());
        task();
    }
}
}

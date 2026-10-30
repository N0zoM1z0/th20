// Complete original 103B file-object pointer retirement and 16B
// scalar-destructor forwarding, including native lock-slot 1 lifetime.
#include "NativeFileClearAllocatorView.hpp"
#include "LockRegistry.hpp"
#include <mutex>
#include <memory>
namespace th20 {
void NativeDiagnosticFileAllocator::release_file_entry_447330(AnimationFile** entry) {
    // The native /Od branch has an explicit empty null-entry arm.
    if(*entry == nullptr) { } else {
        std::destroy_at(*entry);
        std::lock_guard<std::recursive_mutex> guard(process_locks.slot(1));
        ::operator delete(*entry);
    }
}
}

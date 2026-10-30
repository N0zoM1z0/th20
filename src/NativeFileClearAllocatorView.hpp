#pragma once
// Non-owning allocator/file destruction ABI for native 103B/16B pair.
// Original library/compiler provenance remains under review.
#include "AnimationFile.hpp"
#include "DiagnosticAllocator.hpp"
#include <cstdint>
namespace th20 {
struct NativeDiagnosticFileAllocator : DiagnosticAllocator {
    void release_file_entry_447330(AnimationFile** entry);
};
}

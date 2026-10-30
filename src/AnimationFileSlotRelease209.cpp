// Original complete 209B RendererPool file-slot retirement of one
// std::array<AnimationFile*,42> at native pool offset +0x06000730.
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "NativeFileClearPoolView.hpp"
#include "DiagnosticAllocator.hpp"
#include "NativeFileClearAllocatorView.hpp"
#include <array>
#include <cstdint>
namespace th20 {
void NativeFileClearPoolView::release_file_slot_44c430(std::int32_t index) {
    // The genuine original /Od lexical guard emits a short JL and JB plus
    // one unconditional JMP. Combining both branches into one expression
    // instead emits two 6-byte near conditional jumps (212B nonexact).
    if (index<0 || static_cast<std::uint32_t>(index)>=reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730)->size()) { } else {
      if (reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730)->at(index)!=nullptr) {
        (*reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730))[index]->clear();
        reinterpret_cast<NativeDiagnosticFileAllocator*>(process_allocator)->release_file_entry_447330(&(*reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730))[index]);
        (*reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730))[index]=nullptr;
        (*reinterpret_cast<std::array<AnimationFile*,42>*>(reinterpret_cast<std::uint8_t*>(this)+0x6000730))[index]=nullptr;
      }
    }
}
}

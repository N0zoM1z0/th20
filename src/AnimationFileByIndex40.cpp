// Complete original 40B game Renderer animation-file lookup.
// Native owner has a genuine 42-entry pointer array at +0x06000730;
// compiler generates the original folded 22B std::array::operator[] E8.
// The one receiver is the existing AnimationPoolOwner, not a new instance.
#include "AnimationRuntimeOwner.hpp"
#include "AnimationFile.hpp"
#include <array>
#include <cstdint>
namespace th20 {
AnimationFile* AnimationPoolOwner::file_by_index(std::int32_t index) {
    auto& loaded=*reinterpret_cast<std::array<AnimationFile*,42>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x06000730);
    return loaded[index];
}
}

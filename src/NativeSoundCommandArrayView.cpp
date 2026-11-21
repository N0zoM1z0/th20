#include "NativeSoundCommandArrayView.hpp"
#include "SoundEffects.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

SoundCommand& NativeSoundCommandArrayView::operator[](std::uint32_t index) {
    return *reinterpret_cast<SoundCommand*>(reinterpret_cast<std::uint8_t*>(this) +
        static_cast<std::size_t>(index) * sizeof(SoundCommand));
}

static_assert(sizeof(SoundCommand) == 0x10c);

} // namespace th20

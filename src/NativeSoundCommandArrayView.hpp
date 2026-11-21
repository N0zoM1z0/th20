#pragma once
#include <cstdint>

namespace th20 {

struct SoundCommand;

// Borrowed view of the native SoundInf command ring's 32-element array.
struct NativeSoundCommandArrayView {
    SoundCommand& operator[](std::uint32_t index);
};

} // namespace th20

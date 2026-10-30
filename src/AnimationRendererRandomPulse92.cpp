// Complete original 92B/30-i386 game-owned Renderer random state update.
// Original uses guard10 and a real native RandomState::next; original
// compiler profile has /GS, but NO C++ exception unwind frame (/EHsc off).
#include "NativeRendererRandomPulse.hpp"
#include "LockRegistry.hpp"
#include <mutex>
namespace th20 {
std::uint8_t NativeRendererRandomPulse::random_byte_449d20() {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(10));
    last_14=random_04.next();
    return static_cast<std::uint8_t>(last_14);
}
}

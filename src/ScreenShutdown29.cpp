// Native ScreenInf scheduler shutdown bridge 0x00425070.
#include "NativeScreenFactoryViews.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
std::int32_t __cdecl screen_shutdown_425070(void* screen) {
    reinterpret_cast<NativeScreenFactoryAllocatorView*>(process_allocator)
        ->release_screen_41f7c0(reinterpret_cast<NativeScreenInf*>(screen));
    // The original release protocol explicitly invalidates its local argument.
    screen=nullptr;
    return 0;
}
}

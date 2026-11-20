// Original 81B ScreenInf factory at 0x004250F0. This allocates a real
// 0x44B task owner via the separately recovered screen-specific allocator.
#include "NativeScreenEffect.hpp"
#include "DiagnosticAllocator.hpp"
namespace th20 {
// A non-allocating view onto the real global DiagnosticAllocator. Its
// specialized C++ ScreenInf factory at 0x00422D40 remains a separate body.
struct NativeScreenAllocatorView {
    NativeScreenInf* allocate_screen_422d40(const char* source_label);
};
NativeScreenInf* __cdecl screen_factory_4250f0(std::int32_t mode,
    std::uint32_t p1,std::uint32_t p2,std::uint32_t p3,std::uint32_t p4,
    std::int32_t priority,std::uint32_t view) {
    NativeScreenInf* effect=
        reinterpret_cast<NativeScreenAllocatorView*>(process_allocator)->allocate_screen_422d40(
            "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\screen.cpp:580 ScreenInf");
    if (!effect) return nullptr;
    effect->view_40=view;
    effect->initialize_423bf0(mode,p1,p2,p3,p4,priority);
    return effect;
}
}

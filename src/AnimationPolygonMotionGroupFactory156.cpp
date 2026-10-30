// Original 156B polygon group diagnostic allocation factory, C++17 profile.
// The real pointer-bearing class tag naturally triggers MSVC /sdl auto-clear,
// while std::forward on the handle retains the original native E8 helper.
#include "NativePolygonMotionGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template NativePolygonMotionGroup* DiagnosticAllocator::allocate_object<
    NativePolygonMotionGroup, std::uint32_t>(const char*, std::uint32_t);
} // namespace th20

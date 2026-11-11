// Original complete 113B frame device timestamp assembly at 0x004AC0E0.
// The actual frame pair, uint64 clock and breakdown fields occupy
// member offsets +0xD0, +0xD8 and +0xE0 respectively. The original
// has NO GS security-cookie code; its natural MSVC profile excludes /sdl
// and uses /GS- instead of fabricating NOPs or hand-coding the body.
#include "NativeWindowFrameClockView.hpp"
#include <cstdint>
namespace th20 {
struct NativeFrameTimePair {
    std::uint32_t low;
    std::uint32_t high;
};
static_assert(sizeof(NativeFrameTimePair)==8);
NativeFrameTimePair* __cdecl read_frame_pair_4ac170(NativeFrameTimePair* temp);
std::uint64_t __cdecl frame_time_u64_4ac200(NativeFrameTimePair* pair);
void __cdecl frame_time_breakdown_4ac270(std::uint8_t* out, std::uint64_t* value);
NativeFrameTimePair* NativeFrameDeviceClockView::frame_pipeline_4ac0e0() {
    NativeFrameTimePair local;
    *reinterpret_cast<NativeFrameTimePair*>(reinterpret_cast<std::uint8_t*>(this)+0xD0) =
        *read_frame_pair_4ac170(&local);
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this)+0xD8) =
        frame_time_u64_4ac200(
            reinterpret_cast<NativeFrameTimePair*>(reinterpret_cast<std::uint8_t*>(this)+0xD0));
    frame_time_breakdown_4ac270(
        reinterpret_cast<std::uint8_t*>(this)+0xE0,
        reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(this)+0xD8));
    return reinterpret_cast<NativeFrameTimePair*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
}
}

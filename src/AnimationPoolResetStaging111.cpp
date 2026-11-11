// Whole native 111-byte Animation pool draw-staging reset at 0x00445A40.
// The original three frame-recovery callers pass the real process pool.
// Its ~130 MiB layout is not allocated here: fields are addressed on the
// borrowed AnimationPoolOwner, with only native-observed offsets modeled.
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
// Borrowed subclass changes no ABI layout and is never instantiated.
struct NativeAnimationPoolStagingView : AnimationPoolOwner {
    void reset_staging_buffers_445a40();
};

void NativeAnimationPoolStagingView::reset_staging_buffers_445a40() {
 *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000e70)=0;
 void* first=reinterpret_cast<std::uint8_t*>(this)+0x6000e74;
 *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x7c00e74)=first;
 *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x7c00e78)=first;
 *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7c00e7c)=0;
 void* second=reinterpret_cast<std::uint8_t*>(this)+0x7c00e80;
 *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x7d40e80)=second;
 *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x7d40e84)=second;
}
}

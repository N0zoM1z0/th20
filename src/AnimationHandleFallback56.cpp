// Physical original 56B Handle resolution with resident pool Animation fallback.
#include "AnimationHandle.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include <cstdint>
namespace th20 {
Animation* AnimationHandle::resolve_or_resident_44cf10() {
    Animation* resolved=resolve();
    Animation* out;
    if(resolved) out=resolved;
    else out=reinterpret_cast<Animation*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xDC);
    return out;
}
}

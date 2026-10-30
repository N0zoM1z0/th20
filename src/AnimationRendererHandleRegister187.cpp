// Original complete 187B game-owned AnimationHandle registration.
// The native large pool offset, increment/mask/match/high-word generation
// and hidden AnimationHandle return are PE-attested. All storage is borrowed.
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "NativeRendererPoolRegister.hpp"
#include "AnimationHandle.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
AnimationHandle NativeRendererPoolRegister::register_44c8f0(Animation* anim) {
    reinterpret_cast<NativeGenerationPool*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E88)->operator++(0);
    generation_7d40e88 &= 0xFFFFu;
    if (reinterpret_cast<NativeGenerationPool*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E88)->slot_matches_449430(0)) {
        reinterpret_cast<NativeGenerationPool*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E88)->operator++(0);
    }
    std::uint32_t generation=reinterpret_cast<NativeGenerationPool*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E88)->generation_bits_4493e0(16);
    std::uint32_t index=anim->index & 0xFFFFu;
    anim->handle=generation | index;
    return anim->handle;
}
}

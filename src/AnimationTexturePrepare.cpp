// Whole 26-byte original renderer texture-state wrapper, native 0x00445BA0.
// Shared receiver with the exact 352B quad append and the separately
// WHOLE STRICT EXACT 3,159B quad submit Boss; no new owner or storage.
#include "AnimationQuadSubmitOwner.hpp"
namespace th20 {
void AnimationQuadSubmitOwner::prepare_texture_states(Animation* animation) {
    bind_native_texture_state(animation);
}
} // namespace th20

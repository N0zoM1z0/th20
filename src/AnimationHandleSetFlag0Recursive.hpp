#pragma once

namespace th20 {

struct AnimationHandle;

// Resolve a borrowed handle and restore flag zero on its Animation subtree.
// The fastcall ABI keeps the original one-register handle-view entry point.
void __fastcall set_animation_handle_flag0_recursively(AnimationHandle* handle);

} // namespace th20

#pragma once

#if defined(_MSC_VER)
#define TH20_FASTCALL __fastcall
#else
#define TH20_FASTCALL
#endif

namespace th20 {

struct AnimationHandle;

// Resolve a borrowed handle and restore flag zero on its Animation subtree.
// The fastcall ABI keeps the original one-register handle-view entry point.
void TH20_FASTCALL set_animation_handle_flag0_recursively(AnimationHandle* handle);

} // namespace th20

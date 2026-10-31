// Original 118B Animation handle rebind; native 29B alternate file-slot owner.
// The original reads AnimationBase+0x18, distinct from already exact 29B
// Animation::animation_file() which reads the OTHER original slot +0x1C.
// Local derived views add NO storage or synthetic member fields.
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Identifier32.hpp"
#include <cstdint>
namespace th20 {
struct NativeAnimationLegacyFileView : Animation {
    AnimationFile* previous_file_437470();
};
AnimationFile* NativeAnimationLegacyFileView::previous_file_437470() {
    return current_animation_pool->file_by_index(base.field_18);
}
struct NativeAnimationHandleRefreshView {
    AnimationHandle handle;
    void rebind_animation_44bcd0(std::int32_t script);
};
#if defined(_M_IX86)
static_assert(sizeof(NativeAnimationHandleRefreshView)==4);
#endif
void NativeAnimationHandleRefreshView::rebind_animation_44bcd0(std::int32_t script) {
    Animation* previous=current_animation_pool->resolve_handle(handle.value);
    if (previous!=nullptr) {
        AnimationFile* file=static_cast<NativeAnimationLegacyFileView*>(previous)->previous_file_437470();
        previous->stop();
        handle=file->spawn(nullptr,script,-1,nullptr);
        previous->base.field_18=reinterpret_cast<const Identifier32*>(file)->get();
        previous->base.field_1c=reinterpret_cast<const Identifier32*>(file)->get();
    }
}
}

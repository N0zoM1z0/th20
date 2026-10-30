// CORE/RECON-958: complete original 922B AnimationFile spawn Boss.
// The original EH RAII, return-object ABI, mode-bit writes and unreachable
// source-level zero-position branch are all intentionally retained.
// Renderer/stem helper receiver names remain provisional physical ABIs;
// strict exactness is established against the original PE call targets.
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "LockRegistry.hpp"
#include "EclDiagnostic.hpp"
#include <mutex>
#include <cstdint>
namespace th20 {
extern const float native_spawn_width_640, native_spawn_width_384;
extern const float native_spawn_divisor_2, native_spawn_shift_16;
extern const char native_spawn_bad_name_hint[];
// Unknown native resource name predicate, real original 17B callee.
bool __cdecl native_spawn_stem_equals_446de0(const std::pmr::string* stem,
                                              const char* requested);
struct NativeSpawnAnimationPoolView : AnimationPoolOwner {
    void* choose_renderer_44c8c0(int view);
    int prefer_alternate_44c8a0();
};
struct NativeSpawnRendererView {
    AnimationHandle spawn_normal_44b7f0(Animation* anim);
    AnimationHandle spawn_flag2_44b840(Animation* anim);
    AnimationHandle spawn_flag4_44b8e0(Animation* anim);
    AnimationHandle spawn_flag6_44b890(Animation* anim);
};
AnimationHandle AnimationFile::spawn(const char* expected_stem,std::int32_t script,
    const Vector3* position,float rotation,std::int32_t layer,
    std::uint32_t flags,Animation** output) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    ++field_68;
    Animation* anim=current_animation_pool->allocate_animation();
    if (output) *output=anim;
    if (expected_stem && !native_spawn_stem_equals_446de0(&stem,expected_stem))
        ecl_diagnostic_hint(native_spawn_bad_name_hint);
    auto* renderer=reinterpret_cast<NativeSpawnRendererView*>(
        reinterpret_cast<NativeSpawnAnimationPoolView*>(current_animation_pool)->choose_renderer_44c8c0(0));
    int secondary=0;
    if ((flags&16u) || reinterpret_cast<NativeSpawnAnimationPoolView*>(current_animation_pool)->prefer_alternate_44c8a0()) {
        secondary=1;
        renderer=reinterpret_cast<NativeSpawnRendererView*>(
            reinterpret_cast<NativeSpawnAnimationPoolView*>(current_animation_pool)->choose_renderer_44c8c0(1));
    }
    apply_template(anim,script);
    anim->field_4e8=reinterpret_cast<std::uintptr_t>(renderer);
    anim->base.flags.word_04 |= 0x200u;
    if (layer>=0) {
        anim->base.field_14=layer;
        if (layer<=23) anim->base.flags.layer_mode=1;
    }
    if (position != nullptr || (flags&8u)!=0) {
        if ((flags&1u)!=0) {
            if (position) {
                anim->vector_5bc.x=(native_spawn_width_640-native_spawn_width_384)/native_spawn_divisor_2
                                    +native_spawn_width_384/native_spawn_divisor_2+position->x;
                anim->vector_5bc.y=position->y+native_spawn_shift_16;
                anim->vector_5bc.z=position->z;
            }
        } else {
            if (position) anim->vector_5bc=*position;
        }
    } else {
        anim->vector_5bc=Vector3(0.0f,0.0f,0.0f);
        if (position) anim->base.vector_2c=*position;
    }
    anim->base.vector_38.z=rotation;
    if ((flags&4u)!=0) anim->base.flags.word_04 |= 0x40000u;
    else anim->base.flags.word_04 &= ~0x40000u;
    anim->update();
    Vector3 world;
    anim->position(world);
    AnimationHandle result;
    anim->field_574=flags;
    if ((flags&4u)!=0 && (flags&2u)!=0) {
        result=renderer->spawn_flag6_44b890(anim);
        anim->base.flags.bits_08.mode = 0;
    } else if ((flags&4u)!=0) {
        result=renderer->spawn_flag4_44b8e0(anim);
        anim->base.flags.bits_08.mode = 0;
    } else if ((flags&2u)!=0) {
        result=renderer->spawn_flag2_44b840(anim);
    } else {
        result=renderer->spawn_normal_44b7f0(anim);
    }
    return result;
}
}

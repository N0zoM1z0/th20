// CORE/RECON-991: entire native 138B RendererPool destructor, with the
// real 5 following PE/COFF INT3 alignment bytes (compare extent 143B).
// Non-owning structural overlay ONLY, not an allocation site: the observed
// +4 Worker, +0xDC Animation, +0x6C8 Renderer triple list, +0x710 real
// 65536x0x600 AnimationPool and +0x6000818 Animation are all typed.
// Unknown gaps stay opaque and are not assigned speculative member roles.
#include "AnimationRuntimeOwner.hpp"
#include "NativeSpawnAnimationPoolView.hpp"
#include "NativeRendererClassificationView.hpp"
#include "NativeSpawnRendererView.hpp"
#include "Animation.hpp"
#include <cstdint>
#include <cstddef>
#include "Worker.hpp"
namespace th20 {
void __fastcall retire_all_renderer_44a3a0(NativeSpawnRendererView* renderer);
struct NativeAnimationPoolDestructorLayout : AnimationPoolOwner {
    std::uint8_t pad_0[4];
    Worker worker_4;
    std::uint8_t opaque_14_to_dc[0xDC - 0x14];
    Animation resident_dc;
    std::uint32_t original_state_6c0;
    std::uint32_t unknown_6c4;
    NativeRendererClassificationView renderer_6c8;
    AnimationPool records_710;
    std::uint8_t opaque_6000710_to_6000818[0x108];
    Animation final_6000818;
    ~NativeAnimationPoolDestructorLayout();
};
static_assert(offsetof(NativeAnimationPoolDestructorLayout,worker_4)==0x4);
static_assert(offsetof(NativeAnimationPoolDestructorLayout,resident_dc)==0xDC);
static_assert(offsetof(NativeAnimationPoolDestructorLayout,renderer_6c8)==0x6C8);
static_assert(offsetof(NativeAnimationPoolDestructorLayout,records_710)==0x710);
static_assert(offsetof(NativeAnimationPoolDestructorLayout,final_6000818)==0x6000818);
NativeAnimationPoolDestructorLayout::~NativeAnimationPoolDestructorLayout() {
    retire_all_renderer_44a3a0(reinterpret_cast<NativeSpawnRendererView*>(
        reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(0)));
}
}

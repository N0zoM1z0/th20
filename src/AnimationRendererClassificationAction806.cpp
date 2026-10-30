// CORE/RECON-985: original complete 806B Renderer classification/action Boss.
// Real 22 E8 /28 PE HIGHLOW original physical roles and genuine category
// transitions. Source uses actual Graphics/AnimationPoolOwner globals and
// reads the owner's +0x6C0 state member independently on each native access.
// The larger Graphics lifetime and the distinct Graphics child routines
// remain separate original code, not inferred exact by this match.
#include "NativeRendererClassificationOwner.hpp"
#include "Graphics.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
struct NativeGraphicsModeAction : Graphics {
    void set_mode_44f720(int mode,int variant);
    void set_mode_44f700(int mode,int variant);
    void set_clip_41dce0(int value);
    void reset_stage_4dda60();
    void reset_view_4ddf80();
    void set_render_state_4d9db0(int mode,int value);
};
static_assert(sizeof(NativeGraphicsModeAction)==sizeof(Graphics));

void NativeRendererClassificationOwner::perform_classification_44f3d0(int identifier,int view_index) {
    if(identifier==0x29) {
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f720(3,view_index);
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_stage_4dda60();
        (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=view_index+1;
    } else if(identifier==0x2b || identifier==0x2c) {
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_clip_41dce0(3);
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_stage_4dda60();
        (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=13;
    } else if(identifier<=2 || (identifier>=0x27 && identifier<=0x2a)) {
        (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=0;
    } else if(identifier<=5) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=view_index+1) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f720(0,view_index);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_stage_4dda60();
            (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=view_index+1;
        }
    } else if(identifier<=0xb) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=view_index+3) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f720(0,view_index);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_stage_4dda60();
            (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=view_index+3;
        }
    } else if(identifier<=0x13) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=view_index+5) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f720(0,view_index);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_stage_4dda60();
            (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=view_index+5;
        }
    } else if(identifier<=0x17) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=view_index+7) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f700(1,view_index);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_view_4ddf80();
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_render_state_4d9db0(0x17,8);
        }
    } else if(identifier<=0x19) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=9) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_clip_41dce0(4);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_view_4ddf80();
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_render_state_4d9db0(0x17,8);
            *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xc8)=0.0f;
            *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xcc)=0.0f;
            (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=9;
        }
    } else if(identifier<=0x1f || (identifier>=0x22 && identifier<=0x24) ||
              (identifier>=0x2d && identifier<=0x30) || (identifier>=0x33 && identifier<=0x35)) {
        if((*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=10) {
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_clip_41dce0(2);
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_view_4ddf80();
            reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_render_state_4d9db0(0x17,8);
            *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xc8)=0.0f;
            *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xcc)=0.0f;
            (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=10;
        }
    } else if(((identifier>=0x20 && identifier<=0x21) || (identifier>=0x31 && identifier<=0x32)) && (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))!=view_index+11) {
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_mode_44f700(5,view_index);
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).reset_view_4ddf80();
        reinterpret_cast<NativeGraphicsModeAction&>(process_graphics).set_render_state_4d9db0(0x17,8);
        *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xc8)=0.0f;
        *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xcc)=0.0f;
        (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6c0))=view_index+11;
    }
}
}

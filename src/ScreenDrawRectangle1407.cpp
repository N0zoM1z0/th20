// Original 1407B Graphics rectangle submission routine at 0x00423650.
// Four genuine ColoredVertex records are built and submitted as a D3D9
// triangle strip. The Graphics and AnimationPoolOwner objects are the real
// process globals; no replacement device/cache storage is introduced.
#include "NativeArrayConstruct.hpp"
#include "NativeAnimationResetHooksView.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "ColoredVertex.hpp"
#include "Graphics.hpp"
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
extern const float native_one;
extern void __fastcall native_colored_vertex_ctor_423470(ColoredVertex* vertex);
void __cdecl screen_draw_rect_423650(const float* rectangle,std::uint32_t color) {
    current_animation_pool->flush_draws();
    alignas(ColoredVertex) unsigned char vertex_storage[sizeof(ColoredVertex)*4];
    native_construct_array_40bc20(vertex_storage,sizeof(ColoredVertex),4,
        reinterpret_cast<NativeArrayElementConstructor>(&native_colored_vertex_ctor_423470));

    reinterpret_cast<ColoredVertex*>(vertex_storage)[0].position=Vector3(*reinterpret_cast<const float*>(rectangle),*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+4),0.0f);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[1].position=Vector3(*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+8),*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+4),0.0f);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[2].position=Vector3(*reinterpret_cast<const float*>(rectangle),*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+12),0.0f);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[3].position=Vector3(*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+8),*reinterpret_cast<const float*>(reinterpret_cast<const unsigned char*>(rectangle)+12),0.0f);

    reinterpret_cast<ColoredVertex*>(vertex_storage)[0].position.x+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[0].position.y+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[1].position.x+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[1].position.y+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[2].position.x+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[2].position.y+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[3].position.x+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0);
    reinterpret_cast<ColoredVertex*>(vertex_storage)[3].position.y+=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4);

    reinterpret_cast<ColoredVertex*>(vertex_storage)[3].reciprocal_w=native_one;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[2].reciprocal_w=native_one;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[1].reciprocal_w=native_one;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[0].reciprocal_w=native_one;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[3].color=color;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[2].color=color;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[1].color=color;
    reinterpret_cast<ColoredVertex*>(vertex_storage)[0].color=color;

    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(4),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(1),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(5),0);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(2),0);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x14),6);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vertex_storage,sizeof(ColoredVertex));

    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db80();
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->reset_sprite_cache_424080();
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41dba0();
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db60();
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db40();
    reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->reset_color_cache_4240a0();

    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(4),4);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(1),4);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(5),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(2),2);
}
}

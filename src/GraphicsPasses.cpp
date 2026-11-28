#include "GraphicsPasses.hpp"

#include <Windows.h>
#include <timeapi.h>

#include <cstdio>

#include "Animation.hpp"
#include "ArchiveOwner.hpp"
#include "ClockScalar.hpp"
#include "DiagnosticAllocator.hpp"
#include "DiagnosticLog.hpp"
#include "EclDiagnostic.hpp"
#include "FunctionChainController.hpp"
#include "EclRuntime.hpp"
#include "GameRandom.hpp"
#include "GameResourceIo.hpp"
#include "Graphics.hpp"
#include "NativeRendererClassificationOwner.hpp"
#include "SpriteVertices.hpp"
#include "Vector3.hpp"
#include "WindowState.hpp"

namespace th20 {

extern GameRandom native_polygon_random_5ba4c4;
extern GameRandom native_random_5ba4e0;
extern GameRandom native_random_5ba4fc;
extern template Animation* DiagnosticAllocator::allocate_object<Animation>(const char*);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics* graphics);

// Non-owning view of a Graphics surface sprite. The 26B native member at
// 0x0044C570 submits the sprite to the current AnimationPool draw queue.
struct NativeSurfaceSprite : Animation {
    std::int32_t submit_draw_44c570();
};

// Startup factories in other subsystems; their results are owned elsewhere.
void* create_task_4ac1a0();
void* create_input_422b00();

// Centres the scaled frame inside the window viewport.
void Graphics::apply_render_offset() {
    float x = static_cast<float>(window_state.viewport_width - window_state.scaled_width) / 2.0f;
    float y = static_cast<float>(window_state.viewport_height - window_state.scaled_height) / 2.0f;
    ecl_diagnostic_hint("RenderOffet %f, %f\n", x, y);
    process_graphics.set_view_offset(static_cast<std::int32_t>(x), static_cast<std::int32_t>(y));
}

void NativeRendererClassificationOwner::reset_layer_marker_4dd820() {
    *(reinterpret_cast<std::uint8_t*>(this) + 0x6000E12) = 0xFF;
}

// Clears the offscreen target (when present) and the back buffer, then
// resets the per-frame AnimationPool render state.
std::int32_t __cdecl graphics_begin_frame_4dc5f0(void* graphics) {
    if (process_graphics.resource_19c != nullptr) {
        process_graphics.get_device()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                             0xFFFFFFFF, 1.0f, 0);
        if (process_graphics.get_device()->SetRenderTarget(
                0, static_cast<IDirect3DSurface9*>(process_graphics.resource_19c)) != D3D_OK) {
            ecl_diagnostic_hint("error SetRenderTarget\n");
        }
        process_graphics.get_device()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                             process_graphics.clear_color, 1.0f, 0);
    } else {
        process_graphics.get_device()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                             process_graphics.clear_color, 1.0f, 0);
    }
    current_animation_pool->reset_sprite_cache_424080();
    current_animation_pool->restart_state_41dba0();
    current_animation_pool->restart_state_41db60();
    current_animation_pool->restart_state_41db40();
    current_animation_pool->reset_color_cache_4240a0();
    current_animation_pool->restart_state_41dbc0();
    current_animation_pool->reset_draw_cache_475120();
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->reset_layer_marker_4dd820();
    current_animation_pool->invalidate_draw_owner_475150();
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool) + 0xCC) = 0.0f;
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(current_animation_pool) + 0xC8) = 0.0f;
    current_animation_pool->restart_state_41db80();
    static_cast<Graphics*>(graphics)->set_clip_41dce0(2);
    return 1;
}

// Clears depth inside the 416x480 frame of viewport 3 on the offscreen target.
std::int32_t __cdecl graphics_clear_scene_depth_4dd1c0(void*) {
    if (process_graphics.resource_19c != nullptr) {
        current_animation_pool->flush_draws();
        process_graphics.get_device()->SetRenderTarget(
            0, static_cast<IDirect3DSurface9*>(process_graphics.resource_19c));
        D3DRECT rect;
        rect.x1 = process_graphics.viewports[3].viewport.x;
        rect.y1 = process_graphics.viewports[3].viewport.y;
        rect.x2 = process_graphics.viewports[3].viewport.x + process_graphics.viewports[3].viewport.width;
        rect.y2 = process_graphics.viewports[3].viewport.y + process_graphics.viewports[3].viewport.height;
        process_graphics.get_device()->Clear(1, &rect, D3DCLEAR_ZBUFFER, process_graphics.clear_color,
                                             1.0f, 0);
    }
    return 1;
}

// Same as above for the second offscreen target and the playfield viewport.
std::int32_t __cdecl graphics_clear_overlay_depth_4dd2e0(void*) {
    if (process_graphics.resource_19c != nullptr) {
        current_animation_pool->flush_draws();
        process_graphics.get_device()->SetRenderTarget(
            0, static_cast<IDirect3DSurface9*>(process_graphics.resource_1a0));
        D3DRECT rect;
        rect.x1 = process_graphics.viewports[1].viewport.x;
        rect.y1 = process_graphics.viewports[1].viewport.y;
        rect.x2 = process_graphics.viewports[1].viewport.x + process_graphics.viewports[1].viewport.width;
        rect.y2 = process_graphics.viewports[1].viewport.y + process_graphics.viewports[1].viewport.height;
        process_graphics.get_device()->Clear(1, &rect, D3DCLEAR_ZBUFFER, process_graphics.clear_color,
                                             1.0f, 0);
    }
    return 1;
}

std::int32_t __cdecl graphics_select_backbuffer_4dd400(void*) {
    current_animation_pool->flush_draws();
    process_graphics.get_device()->SetRenderTarget(
        0, static_cast<IDirect3DSurface9*>(process_graphics.resource_1a4));
    process_graphics.get_device()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF000000,
                                         1.0f, 0);
    return 1;
}

std::int32_t __cdecl graphics_clear_view_points_4dc7c0(void*) {
    current_animation_pool->flush_draws();
    for (std::int32_t i = 0; i < 3; i++) {
        process_graphics.viewports[3].points[i].x = 0.0f;
        process_graphics.viewports[3].points[i].y = 0.0f;
        process_graphics.viewports[2].points[i].x = 0.0f;
        process_graphics.viewports[2].points[i].y = 0.0f;
        process_graphics.viewports[0].points[i].x = 0.0f;
        process_graphics.viewports[0].points[i].y = 0.0f;
        process_graphics.viewports[1].points[i].x = 0.0f;
        process_graphics.viewports[1].points[i].y = 0.0f;
    }
    return 1;
}

// Chain start-up for the Graphics node: version data, clocks, viewports,
// random streams seeded from the startup time, and the five surface sprites.
std::int32_t __cdecl graphics_startup_4dd600(void*) {
    load_version_data();
    default_timer_clock.set(1.0f);
    process_graphics.clear_color = 0xFF000000;
    process_graphics.initialize_viewports();
    process_graphics.apply_render_offset();
    process_graphics.startup_seed = timeGetTime();
    script_random.seed(process_graphics.startup_seed);
    native_polygon_random_5ba4c4.seed(process_graphics.startup_seed);
    native_random_5ba4e0.seed(process_graphics.startup_seed >> 1);
    native_random_5ba4fc.seed(process_graphics.startup_seed / 3);
    create_task_4ac1a0();
    create_input_422b00();
    static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->load_resources_44d020();
    process_graphics.surface_sprite_0 = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\mother.cpp:233 SprtInf");
    process_graphics.surface_sprite_1 = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\mother.cpp:234 SprtInf");
    process_graphics.surface_sprite_2 = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\mother.cpp:235 SprtInf");
    process_graphics.surface_sprite_3 = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\mother.cpp:236 SprtInf");
    process_graphics.surface_sprite_4 = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\mother.cpp:237 SprtInf");
    graphics_scene_draw_hook = nullptr;
    graphics_overlay_draw_hook = nullptr;
    return 0;
}

std::int32_t register_graphics_chain() {
    Graphics* graphics = &process_graphics;
    graphics->reset_view_selection();
    graphics->field_b14 = 0;
    std::int32_t result;
    FunctionChainNode* node = process_chain->create(graphics_update_4dc510);
    node->set_userdata(graphics);
    node->set_before_insert(graphics_startup_4dd600);
    node->enable();
    if ((result = process_chain->insert_update(node, 1)) != 0) {
        return result;
    }
    register_draw(1, graphics_begin_frame_4dc5f0, graphics);
    register_draw(14, graphics_draw_world_4dc8b0, graphics);
    register_draw(15, graphics_draw_scene_4d9120, graphics);
    register_draw(25, graphics_clear_scene_depth_4dd1c0, graphics);
    register_draw(26, graphics_draw_overlay_4d8e90, graphics);
    register_draw(47, graphics_clear_overlay_depth_4dd2e0, graphics);
    register_draw(48, graphics_draw_front_4d8f80, graphics);
    register_draw(66, graphics_select_backbuffer_4dd400, graphics);
    register_draw(67, graphics_draw_frame_4d9040, graphics);
    register_draw(110, graphics_clear_view_points_4dc7c0, graphics);
    process_graphics.get_device()->GetBackBuffer(
        0, 0, D3DBACKBUFFER_TYPE_MONO,
        reinterpret_cast<IDirect3DSurface9**>(&process_graphics.resource_1a4));
    return 0;
}


std::int32_t NativeSurfaceSprite::submit_draw_44c570() {
    return current_animation_pool->draw(this);
}

// The scene, overlay, front and frame passes each draw one surface sprite
// with alpha test off and depth writes disabled; scene and overlay can be
// replaced by a hook.
std::int32_t __cdecl graphics_draw_scene_4d9120(void*) {
    if (process_graphics.resource_19c != nullptr) {
        if (graphics_scene_draw_hook == nullptr) {
            process_graphics.get_device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
            process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
            graphics_disable_depth_writes(&process_graphics);
            process_graphics.set_clip_41dce0(3);
            static_cast<NativeSurfaceSprite*>(process_graphics.surface_sprite_0)->submit_draw_44c570();
            process_graphics.surface_sprite_0->set_packed_color(0xFFFFFFFF);
            static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->select_renderer_group_449e40(0x29);
            current_animation_pool->flush_draws();
            process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        } else {
            graphics_scene_draw_hook();
        }
    }
    return 1;
}

std::int32_t __cdecl graphics_draw_overlay_4d8e90(void*) {
    if (process_graphics.resource_19c != nullptr) {
        if (graphics_overlay_draw_hook == nullptr) {
            process_graphics.get_device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
            process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
            graphics_disable_depth_writes(&process_graphics);
            process_graphics.set_clip_41dce0(3);
            static_cast<NativeSurfaceSprite*>(process_graphics.surface_sprite_1)->submit_draw_44c570();
            process_graphics.surface_sprite_1->set_packed_color(0xFFFFFFFF);
            current_animation_pool->flush_draws();
            process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        } else {
            graphics_overlay_draw_hook();
        }
    }
    return 1;
}

std::int32_t __cdecl graphics_draw_front_4d8f80(void*) {
    if (process_graphics.resource_19c != nullptr) {
        process_graphics.get_device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        graphics_disable_depth_writes(&process_graphics);
        static_cast<NativeSurfaceSprite*>(process_graphics.surface_sprite_2)->submit_draw_44c570();
        current_animation_pool->flush_draws();
        process_graphics.surface_sprite_2->set_packed_color(0xFFFFFFFF);
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    }
    return 1;
}

// View modes 7 and 12 draw surface sprite 3; the others draw sprite 4.
std::int32_t __cdecl graphics_draw_frame_4d9040(void*) {
    if (process_graphics.resource_19c != nullptr) {
        static_cast<NativeRendererClassificationOwner*>(current_animation_pool)->perform_classification_44f3d0(0x1F, 0);
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        if (process_graphics.field_b0c_value() == 7 || process_graphics.field_b0c_value() == 12) {
            static_cast<NativeSurfaceSprite*>(process_graphics.surface_sprite_3)->submit_draw_44c570();
            process_graphics.surface_sprite_3->set_packed_color(0xFFFFFFFF);
        } else {
            static_cast<NativeSurfaceSprite*>(process_graphics.surface_sprite_4)->submit_draw_44c570();
            process_graphics.surface_sprite_4->set_packed_color(0xFFFFFFFF);
        }
        current_animation_pool->flush_draws();
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    }
    return 1;
}

// Composites the offscreen world target onto the 416x480 frame of viewport 3:
// an opaque-black quad drawn with alpha-only blending, then the second
// offscreen target is bound and cleared for the overlay passes.
std::int32_t __cdecl graphics_draw_world_4dc8b0(void*) {
    if (process_graphics.resource_19c != nullptr) {
        process_graphics.set_render_state_4d9db0(0x17, 8);
        current_animation_pool->flush_draws();
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        process_graphics.get_device()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        process_graphics.get_device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
        process_graphics.get_device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
        process_graphics.get_device()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        process_graphics.get_device()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
        process_graphics.get_device()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
        process_graphics.get_device()->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
        SpriteColoredVertex vertices[4];
        vertices[3].position = Vector3(static_cast<float>(process_graphics.viewports[3].viewport.x),
                                       static_cast<float>(process_graphics.viewports[3].viewport.y), 0.0f);
        vertices[2].position = vertices[3].position;
        vertices[1].position = vertices[2].position;
        vertices[0].position = vertices[1].position;
        vertices[1].position.x += static_cast<float>(process_graphics.viewports[3].viewport.width);
        vertices[2].position.y += static_cast<float>(process_graphics.viewports[3].viewport.height);
        vertices[3].position.x += static_cast<float>(process_graphics.viewports[3].viewport.width);
        vertices[3].position.y += static_cast<float>(process_graphics.viewports[3].viewport.height);
        vertices[3].reciprocal_w = 1.0f;
        vertices[2].reciprocal_w = 1.0f;
        vertices[1].reciprocal_w = 1.0f;
        vertices[0].reciprocal_w = 1.0f;
        vertices[0].color = 0xFF000000;
        vertices[1].color = 0xFF000000;
        vertices[2].color = 0xFF000000;
        vertices[3].color = 0xFF000000;
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        process_graphics.get_device()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
        process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices,
                                                       sizeof(SpriteColoredVertex));
        process_graphics.get_device()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        current_animation_pool->restart_state_41db40();
        process_graphics.get_device()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_SRCALPHA);
        process_graphics.get_device()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
        process_graphics.get_device()->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
        {
            current_animation_pool->flush_draws();
            process_graphics.get_device()->SetRenderTarget(
                0, static_cast<IDirect3DSurface9*>(process_graphics.resource_1a0));
            // The rectangle is filled but the clear covers the whole target.
            D3DRECT rect;
            rect.x1 = process_graphics.viewports[3].viewport.x;
            rect.y1 = process_graphics.viewports[3].viewport.y;
            rect.x2 = process_graphics.viewports[3].viewport.x + process_graphics.viewports[3].viewport.width;
            rect.y2 = process_graphics.viewports[3].viewport.y + process_graphics.viewports[3].viewport.height;
            process_graphics.get_device()->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                                 process_graphics.clear_color, 1.0f, 0);
        }
    }
    return 1;
}

// Opens th20.dat and loads the version record; both failures are reported
// to the diagnostic log and return -1.
std::int32_t load_version_data() {
    if (archive_owner.open("th20.dat")) {
        char name[128];
        std::int32_t size;
        sprintf_s(name, sizeof(name), "th20_%.4x%c.ver", 0x100, 'a');
        process_graphics.dynamic_buffer = read_game_resource(name, &size, 0);
        process_graphics.version_data_size = size;
        if (process_graphics.dynamic_buffer == nullptr) {
            // "error : データとゲームのバージョンが違います\r\n"
            report_log_error(&diagnostic_log,
                             "error : \x83\x66\x81\x5b\x83\x5e\x82\xc6\x83\x51\x81\x5b\x83\x80\x82\xcc"
                             "\x83\x6f\x81\x5b\x83\x57\x83\x87\x83\x93\x82\xaa\x88\xe1\x82\xa2\x82\xdc"
                             "\x82\xb7\r\n");
            return -1;
        }
    } else {
        // "error : データファイルが存在しません\r\n"
        report_log_error(&diagnostic_log,
                         "error : \x83\x66\x81\x5b\x83\x5e\x83\x74\x83\x40\x83\x43\x83\x8b\x82\xaa"
                         "\x91\xb6\x8d\xdd\x82\xb5\x82\xdc\x82\xb9\x82\xf1\r\n");
        return -1;
    }
    return 0;
}

} // namespace th20

// Full 49-mode / two-stage Animation draw dispatcher reconstructed from the
// immutable 5,993-byte original at 0x00443880. SOURCE-PRESENT NONEXACT:
// original 123 E8 calls, 49+31 dispatch and 32 in-body PE relocation roles
// are independently known, but this new typed semantic source is NOT yet
// whole-original-byte matched. Do not count the parent as exact.
#include "Animation.hpp"
#include "AnimationCallback.hpp"
#include "AnimationDrawModeOwner.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {
std::uint32_t __fastcall animation_draw_color_490(Animation*);
std::uint32_t __fastcall animation_draw_color_494(Animation*);
std::uint32_t __fastcall animation_draw_enabled(Animation*);
float __fastcall animation_inherited_aux_scale_x(Animation*);
std::int32_t __fastcall graphics_enable_fog(Graphics*);
std::int32_t __fastcall graphics_disable_fog(Graphics*);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
// Original 0x004408B0 consumes only Animation* in ECX; this source-level
// name and its unresolved body have no independent native exact credit.
std::int32_t __fastcall animation_draw_mode6(Animation*);
extern const float native_two;

#if defined(_M_IX86)
static_assert(offsetof(AnimationBase, color_490) == 0x490);
static_assert(offsetof(AnimationBase, color_494) == 0x494);
static_assert(offsetof(AnimationBase, flags) == 0x498);
static_assert(offsetof(Animation, callback) == 0x568);
static_assert(offsetof(Animation, field_570) == 0x570);
static_assert(offsetof(WindowState, scale) == 0x20C0);
#endif

// The original main object is AnimationPoolOwner (already exact external
// callers); this local declaration supplies its as-yet unsourced drawing
// member signatures only. No new instance or storage is constructed.
// Each provisional method corresponds to a distinct original physical E8
// destination recorded in config/animation-draw-boss-mode-e8.csv.
struct AnimationDrawDetailedOwner : AnimationDrawModeOwner {
    void prepare_render_geometry(Animation*);                 // 0x00445BC0
    std::int32_t draw_simple_mode7(Animation*);              // 0x00441C00
    std::int32_t draw_simple_mode8(Animation*);              // 0x00441F00
    std::int32_t draw_strip_mode9(Animation*, void*, int);   // 0x00445350
    std::int32_t draw_strip_mode11(Animation*, void*, int);  // 0x00445130
    std::int32_t draw_mesh_2425(Animation*, void*, int);     // 0x00443020

    void draw_rect_439a00(float, float, float, float, float,
                           std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43b960(float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43bc60(float, float, float, float, int, std::uint32_t);
    void draw_shape_43be80(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43a1c0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43cd40(float, float, float, float,
                            std::uint32_t, std::uint32_t, int);
    void draw_shape_43b0e0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43e2c0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43c180(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43d830(float, float, std::uint32_t);
    void draw_shape_43c4e0(float, float, float, float, float, int, std::uint32_t);
    void draw_shape_43c780(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43a2b0(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43a750(float, float, float, float, float, float, int,
                            std::uint32_t);
    void draw_shape_43ab20(float, float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43d9b0(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43dce0(float, float, float, float, float, int, std::uint32_t);
    void draw_shape_43df30(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
};

std::int32_t AnimationPoolOwner::draw(Animation* animation) {
    // Original ECX this is the existing game AnimationPoolOwner. The
    // same-layout local view provides names for currently unsourced private
    // renderer methods; no duplicate vtable or object storage is produced.
    auto* renderer = reinterpret_cast<AnimationDrawDetailedOwner*>(this);
    if ((animation->base.flags.word_04 & 1u) == 0) return -1;
    if (animation->callback) animation->callback->draw();
    if (!animation_draw_enabled(animation)) return -1;
    if (animation->field_570 != 0) return -1;
    graphics_disable_depth_writes(&process_graphics);
    const std::uint32_t mode = animation->base.flags.bytes_00.field_00;
    if (mode > 0x30) return 0;
    const auto quad_size = animation->base.variables.field_00 * 2;

    // Main original 49-entry switch at 0x0044391F. Cases 24,25 and 47/48
    // never reach the original 31-entry nested switch despite their IDs.
    switch (mode) {
    case 0:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode0(animation);
        return -1;
    case 1:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode1(animation);
        return -1;
    case 3:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode1(animation);
        return -1;
    case 2:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode2(animation);
        return -1;
    case 4:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode4(animation);
        return -1;
    case 5:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_quad_mode5(animation);
        return -1;
    case 6:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return animation_draw_mode6(animation);
        return -1;
    case 7:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_simple_mode7(animation);
        return -1;
    case 8:
        if (animation->base.channels_490.alpha != 0 ||
            animation->base.channels_494.alpha != 0) return renderer->draw_simple_mode8(animation);
        return -1;
    case 9:
    case 12:
    case 13:
    case 14:
        return renderer->draw_strip_mode9(animation, animation->geometry, quad_size);
    case 11:
        return renderer->draw_strip_mode11(animation, animation->geometry, quad_size);
    case 15:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        graphics_enable_fog(&process_graphics);
        renderer->draw_simple_mode8(animation);
        graphics_disable_fog(&process_graphics);
        return 0;
    case 24:
    case 25:
        return renderer->draw_mesh_2425(animation, animation->geometry, quad_size);
    case 47:
        return renderer->draw_mesh_2425(animation, animation->geometry, quad_size);
    case 48:
        graphics_enable_fog(&process_graphics);
        renderer->draw_mesh_2425(animation, animation->geometry, 3);
        graphics_disable_fog(&process_graphics);
        return 0;
    case 10:
    case 23:
        return 0;
    default:
        break;
    }

    // Shared native 0x00443C1D main branch for only original modes
    // 16..22 and 26..46. Its original nested table indexes mode-16.
    Vector3 position;
    float angle = animation->rotation_z_value();
    float width = animation->width();
    float height = animation->height();
    animation->position(position);
    if (animation->parent_55c &&
        (animation->base.flags.word_04 & (1u << 12)) == 0) {
        angle += animation->parent_55c->rotation_z_value();
    }
    renderer->prepare_render_geometry(animation);
    const std::uint8_t scale_mode = animation->base.flags.field_0c;
    if (scale_mode == 1 || scale_mode == 5) {
        width *= window_state.scale;
        height *= window_state.scale;
    } else if (scale_mode == 2 || scale_mode == 6) {
        width *= window_state.scale * 0.5f;
        height *= window_state.scale * 0.5f;
    }

    const float x = position.x;
    const float y = position.y;
    const int count = animation->base.variables.field_00;
    const int first = animation->base.flags.word_10;
    const int second = animation->base.flags.word_14;
    const float radius = animation->base.variables.field_10;
    const float delta = animation->base.variables.field_14;
    const float half_height = height / native_two;

    switch (mode) {
    case 16:
        renderer->draw_rect_439a00(x,y,width,height,angle,animation_draw_color_490(animation),animation_draw_color_490(animation),first,second);
        break;
    case 17:
        renderer->draw_shape_43b960(x,y,width,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 18:
        renderer->draw_shape_43bc60(x,y,width,angle,count,animation_draw_color_490(animation));
        break;
    case 19:
        renderer->draw_shape_43be80(x,y,width,height,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 20:
        renderer->draw_rect_439a00(x,y,width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),first,second);
        break;
    case 21:
        renderer->draw_shape_43a1c0(x,y,width,height,angle,animation_draw_color_490(animation),animation_draw_color_490(animation),first,second);
        break;
    case 22:
        renderer->draw_shape_43a1c0(x,y,width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),first,second);
        break;
    case 26: {
        const auto color = animation->base.flags.color_mode ? animation_draw_color_494(animation) : animation_draw_color_490(animation);
        renderer->draw_shape_43cd40(x,y,width,angle,animation_draw_color_490(animation),color,first);
        break;
    }
    case 27: {
        const auto color = animation->base.flags.color_mode ? animation_draw_color_494(animation) : animation_draw_color_490(animation);
        renderer->draw_shape_43b0e0(x,y,width,height,angle,animation_draw_color_490(animation),color,first,second);
        break;
    }
    case 28:
        renderer->draw_shape_43e2c0(x,y,width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),first,second);
        break;
    case 29:
        renderer->draw_shape_43be80(x,y,width + half_height,height,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 30:
        renderer->draw_shape_43be80(x,y,width - half_height,height,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 31:
        renderer->draw_shape_43c180(x,y,animation_inherited_aux_scale_x(animation),width,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 32:
        renderer->draw_shape_43d830(x,y,animation_draw_color_490(animation));
        break;
    case 33:
        // Original has an additional 0x004456C0 getter call before color_490;
        // the returned alternate color word is not used by this mode.
        animation_draw_color_494(animation);
        renderer->draw_shape_43c4e0(x,y,animation_inherited_aux_scale_x(animation),width,angle,count,animation_draw_color_490(animation));
        break;
    case 34:
        renderer->draw_shape_43c780(x,y,animation_inherited_aux_scale_x(animation),width,height,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 35:
        // Original computes auxiliary inherited scale twice in this mode.
        animation_inherited_aux_scale_x(animation);
        renderer->draw_shape_43c780(x,y,animation_inherited_aux_scale_x(animation)+half_height,width+half_height,height,
                                     angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 36:
        // Original computes auxiliary inherited scale twice in this mode.
        animation_inherited_aux_scale_x(animation);
        renderer->draw_shape_43c780(x,y,animation_inherited_aux_scale_x(animation)-half_height,width-half_height,height,
                                     angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 37:
        renderer->draw_shape_43a2b0(x,y,width,height,radius,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 38:
        renderer->draw_shape_43a750(x,y,width,height,radius,angle,count,animation_draw_color_490(animation));
        break;
    case 39:
        renderer->draw_shape_43ab20(x,y,width-radius*native_two,height-radius*native_two,
                                     radius,delta,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 40:
        renderer->draw_shape_43ab20(x,y,width-radius*native_two,height-radius*native_two,
                                     radius + delta / native_two,delta,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 41:
        renderer->draw_shape_43ab20(x,y,width-radius*native_two,height-radius*native_two,
                                     radius - delta / native_two,delta,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 42:
        renderer->draw_shape_43d9b0(x,y,width,animation_inherited_aux_scale_x(animation),angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 43:
        renderer->draw_shape_43dce0(x,y,width,animation_inherited_aux_scale_x(animation),angle,count,animation_draw_color_490(animation));
        break;
    case 44:
        renderer->draw_shape_43df30(x,y,width,animation_inherited_aux_scale_x(animation),height,angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 45:
        renderer->draw_shape_43df30(x,y,width+half_height,animation_inherited_aux_scale_x(animation)+half_height,height,
                                     angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 46:
        renderer->draw_shape_43df30(x,y,width-half_height,animation_inherited_aux_scale_x(animation)-half_height,height,
                                     angle,count,animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    default:
        // Original root table routes only the modes above through this stage.
        return 0;
    }
    return 0;
}
} // namespace th20

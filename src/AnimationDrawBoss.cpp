// Full 49-mode / two-stage Animation draw dispatcher reconstructed from the
// immutable 5,993-byte original at 0x00443880. SOURCE-PRESENT NONEXACT:
// original 123 E8 calls, 49+31 genuine pointer tables and 32 in-body PE
// relocation target roles are independently known. Current source compiles
// to both real switch pointer partitions, all 123 original call roles in
// original physical order (first 81 also at exact E8 instruction sites),
// and all 32 original data target-role counts. It is still NONEXACT:
// whole-parent native bytes/frame and later site locations differ.
#include "Animation.hpp"
#include "AnimationCallback.hpp"
#include "AnimationDrawModeOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
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
    std::int32_t draw_complex_mode6(Animation*);             // 0x004408B0 native thiscall
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
    // Native mode26 pushes Animation flag words +0x4AC AND +0x4A8;
    // callee 0x0043CD40 ends in RET 0x20, eight stack arguments.
    void draw_shape_43cd40(float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43b0e0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43e2c0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43c180(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43d830(float, float, std::uint32_t);
    // Native mode33 consumes BOTH packed colors; callee RET 0x20.
    void draw_shape_43c4e0(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
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
    if ((animation->base.flags.word_04 & 1u) == 0) return -1;
    if (animation->callback) animation->callback->draw();
    if (!animation_draw_enabled(animation)) return -1;
    if (animation->field_570 != 0) return -1;
    graphics_disable_depth_writes(&process_graphics);

    // Main original 49-entry switch at 0x0044391F. Cases 24,25 and 47/48
    // never reach the original 31-entry nested switch despite their IDs.
    switch (animation->base.flags.bytes_00.field_00) {
    case 0:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode0(animation);
    case 1:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode1(animation);
    case 4:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode4(animation);
    case 5:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode5(animation);
    case 6:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_complex_mode6(animation);
    case 7:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_simple_mode7(animation);
    case 8:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_simple_mode8(animation);
    case 15:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        graphics_enable_fog(&process_graphics);
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_simple_mode8(animation);
        graphics_disable_fog(&process_graphics);
        return 0;
    case 9:
    case 12:
    case 13:
    case 14:
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_strip_mode9(animation, animation->geometry, (animation->base.variables.field_00 * 2));
    case 11:
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_strip_mode11(animation, animation->geometry, (animation->base.variables.field_00 * 2));
    case 24:
    case 25:
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_mesh_2425(animation, animation->geometry, (animation->base.variables.field_00 * 2));
    case 47:
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_mesh_2425(animation, animation->geometry, (animation->base.variables.field_00 * 2));
    case 48:
        graphics_enable_fog(&process_graphics);
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_mesh_2425(animation, animation->geometry, 3);
        graphics_disable_fog(&process_graphics);
        return 0;
    case 2:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode2(animation);
    case 3:
        if (animation->base.channels_490.alpha == 0 &&
            animation->base.channels_494.alpha == 0) return -1;
        return reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_quad_mode1(animation);
    // Original primary switch has 49 DIRECT case pointers. Only the
    // explicitly named 28 cases below enter the true 31-pointer nested
    // switch; 24/25 and 47/48 are independent mesh routes.
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46: {
    // Native 0x00443C1D enters the nested switch for only 16..22 and
    // 26..46; the physical second jump-table indexes mode -16. Keep the
    // complete nested dispatcher in this same main-switch case block:
    // moving it outside inserts non-native return branches before it.
    Vector3 position;
    float angle = animation->rotation_z_value();
    float width = animation->width();
    float height = animation->height();
    animation->position(position);
    if (animation->parent_55c &&
        (animation->base.flags.word_04 & (1u << 12)) == 0) {
        angle += animation->parent_55c->rotation_z_value();
    }
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->bind_native_texture_state(animation);
    if (animation->base.flags.field_0c == 1 || animation->base.flags.field_0c == 5) {
        width *= window_state.scale;
        height *= window_state.scale;
    } else if (animation->base.flags.field_0c == 2 || animation->base.flags.field_0c == 6) {
        width *= window_state.scale * 0.5f;
        height *= window_state.scale * 0.5f;
    }


    switch (animation->base.flags.bytes_00.field_00) {
    case 26: {
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43cd40((position.x),(position.y),width,angle,animation_draw_color_490(animation),(animation->base.flags.color_mode ? animation_draw_color_494(animation) : animation_draw_color_490(animation)),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    }
    case 16:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_rect_439a00((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),animation_draw_color_490(animation),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    case 27: {
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43b0e0((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),(animation->base.flags.color_mode ? animation_draw_color_494(animation) : animation_draw_color_490(animation)),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    }
    case 20:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_rect_439a00((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    case 21:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43a1c0((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),animation_draw_color_490(animation),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    case 22:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43a1c0((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    case 37:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43a2b0((position.x),(position.y),width,height,(animation->base.variables.field_10),angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 38:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43a750((position.x),(position.y),width,height,(animation->base.variables.field_10),angle,(animation->base.variables.field_00),animation_draw_color_490(animation));
        break;
    case 39:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43ab20((position.x),(position.y),width-(animation->base.variables.field_10)*native_two,height-(animation->base.variables.field_10)*native_two,
                                     (animation->base.variables.field_10),(animation->base.variables.field_14),angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 40:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43ab20((position.x),(position.y),width-(animation->base.variables.field_10)*native_two,height-(animation->base.variables.field_10)*native_two,
                                     (animation->base.variables.field_10) + (animation->base.variables.field_14) / native_two,(animation->base.variables.field_14),angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 41:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43ab20((position.x),(position.y),width-(animation->base.variables.field_10)*native_two,height-(animation->base.variables.field_10)*native_two,
                                     (animation->base.variables.field_10) - (animation->base.variables.field_14) / native_two,(animation->base.variables.field_14),angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 28:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43e2c0((position.x),(position.y),width,height,angle,animation_draw_color_490(animation),animation_draw_color_494(animation),(animation->base.flags.word_10),(animation->base.flags.word_14));
        break;
    case 17:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43b960((position.x),(position.y),width,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 31:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43c180((position.x),(position.y),animation_inherited_aux_scale_x(animation),width,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 33:
        // Original passes BOTH native packed colors; the alternate-color
        // getter is a real eighth parameter, not an unused extra call.
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43c4e0((position.x),(position.y),animation_inherited_aux_scale_x(animation),width,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 34:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43c780((position.x),(position.y),animation_inherited_aux_scale_x(animation),width,height,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 35:
        // Original computes auxiliary inherited scale twice in this mode.
        animation_inherited_aux_scale_x(animation);
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43c780((position.x),(position.y),animation_inherited_aux_scale_x(animation)+(height / native_two),width+(height / native_two),height,
                                     angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 36:
        // Original computes auxiliary inherited scale twice in this mode.
        animation_inherited_aux_scale_x(animation);
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43c780((position.x),(position.y),animation_inherited_aux_scale_x(animation)-(height / native_two),width-(height / native_two),height,
                                     angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 18:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43bc60((position.x),(position.y),width,angle,(animation->base.variables.field_00),animation_draw_color_490(animation));
        break;
    case 19:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43be80((position.x),(position.y),width,height,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 29:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43be80((position.x),(position.y),width + (height / native_two),height,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 30:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43be80((position.x),(position.y),width - (height / native_two),height,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 32:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43d830((position.x),(position.y),animation_draw_color_490(animation));
        break;
    case 42:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43d9b0((position.x),(position.y),width,animation_inherited_aux_scale_x(animation),angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 43:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43dce0((position.x),(position.y),width,animation_inherited_aux_scale_x(animation),angle,(animation->base.variables.field_00),animation_draw_color_490(animation));
        break;
    case 44:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43df30((position.x),(position.y),width,animation_inherited_aux_scale_x(animation),height,angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 45:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43df30((position.x),(position.y),width+(height / native_two),animation_inherited_aux_scale_x(animation)+(height / native_two),height,
                                     angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    case 46:
        reinterpret_cast<AnimationDrawDetailedOwner*>(this)->draw_shape_43df30((position.x),(position.y),width-(height / native_two),animation_inherited_aux_scale_x(animation)-(height / native_two),height,
                                     angle,(animation->base.variables.field_00),animation_draw_color_490(animation),animation_draw_color_494(animation));
        break;
    default:
        break;
    }
    return 0;
    }
    case 10:
    case 23:
    default:
        return 0;
    }
}
} // namespace th20

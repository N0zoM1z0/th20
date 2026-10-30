#pragma once
// One game renderer receiver ABI shared by the original 5993B draw
// dispatcher and its mode-specific children. Mode7 has a complete strict
// native 753B implementation; the other declared methods remain separate
// original targets. The parent is a real AnimationPoolOwner, not new storage.
#include "AnimationDrawModeOwner.hpp"
#include <cstdint>

namespace th20 {
struct Vector2;
// The original main object is AnimationPoolOwner (already exact external
// callers); this shared declaration supplies its drawing member ABI.
// Unimplemented members remain provisional. No new storage is constructed.
// Each provisional method corresponds to a distinct original physical E8
// destination recorded in config/animation-draw-boss-mode-e8.csv.
struct AnimationDrawDetailedOwner : AnimationDrawModeOwner {
    // Original mode6 projected quad helper: six float parameters and one
    // 2-float output pointer; native RET 0x1C, no additional instance.
    void transform_projected_xy(Vector2* output, float x, float y,
                                float sine, float cosine, float tx, float ty);
    std::int32_t prepare_complex_mode6(Animation*);       // full original 0x00440340, strict exact
    std::int32_t draw_complex_mode6(Animation*);             // 0x004408B0 native thiscall
    std::int32_t prepare_simple_mode7(Animation*);          // actual original 0x00441430; EAX=0, RET 4
    std::int32_t draw_simple_mode7(Animation*);              // 0x00441C00
    std::int32_t draw_simple_mode8(Animation*);              // 0x00441F00
    std::int32_t draw_strip_mode9(Animation*, void*, int);   // 0x00445350
    std::int32_t draw_strip_mode11(Animation*, void*, int);  // 0x00445130
    std::int32_t draw_mesh_2425(Animation*, void*, int);     // 0x00443020

    // Native original 1980B rectangle source is int-returning, RET 0x24.
    std::int32_t draw_rect_439a00(float, float, float, float, float,
                           std::uint32_t, std::uint32_t, int, int);
    // Original whole 755B simple triangle fan EAX=0/RET 0x1C.
    std::int32_t draw_shape_43b960(float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43bc60(float, float, float, float, int, std::uint32_t);
    void draw_shape_43be80(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    // 240B original double-pass outline returns EAX zero, RET 0x24.
    std::int32_t draw_shape_43a1c0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    // Native mode26 pushes Animation flag words +0x4AC AND +0x4A8;
    // callee 0x0043CD40 ends in RET 0x20, eight stack arguments.
    void draw_shape_43cd40(float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    // Original 2169B closed line-strip returns EAX=0 / RET 0x24, not void.
    std::int32_t draw_shape_43b0e0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    // Native 1601B triangle draw returns EAX zero, RET 0x24.
    std::int32_t draw_shape_43e2c0(float, float, float, float, float,
                            std::uint32_t, std::uint32_t, int, int);
    void draw_shape_43c180(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43d830(float, float, std::uint32_t);
    // Native mode33 consumes BOTH packed colors; callee RET 0x20.
    void draw_shape_43c4e0(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43c780(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    // 1174B original center+rounded ring returns EAX zero, RET 0x24.
    std::int32_t draw_shape_43a2b0(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    // Original whole 971B rounded line strip EAX=0/RET 0x20.
    std::int32_t draw_shape_43a750(float, float, float, float, float, float, int,
                            std::uint32_t);
    // Original whole 1468B ring emitter: EAX=0 and RET 0x28, not void.
    std::int32_t draw_shape_43ab20(float, float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43d9b0(float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
    void draw_shape_43dce0(float, float, float, float, float, int, std::uint32_t);
    void draw_shape_43df30(float, float, float, float, float, float, int,
                            std::uint32_t, std::uint32_t);
};

} // namespace th20

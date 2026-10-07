#pragma once
#include "Timer.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Interpolation.hpp"
#include "AnmVariables.hpp"
#include "AnimationHandle.hpp"
#include "IntrusiveLink.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
struct AnimationCallback;
// Mixed flag storage observed through byte/word producers and consumers.
// Offset labels preserve unresolved roles; no packing or explicit padding.
struct AnimationFlags {
    std::uint16_t field_00;
    std::uint8_t bit_10 : 1;
    std::uint8_t other_02 : 7;
    std::uint8_t field_03;
    std::uint32_t word_04;
    std::uint8_t mode : 2;
    std::uint8_t other_08 : 6;
    std::uint8_t field_09, field_0a, field_0b;
    std::uint32_t word_0c, word_10, word_14, word_18, word_1c;
};
// Native immutable identity value at 0056E068; production data definition
// and its original global initialization contract remain pending.
extern const Matrix4 identity_matrix;
// Native nested constructors establish every value owner and its stride.
struct AnimationBase {
    Timer timer;
    std::int32_t field_10, field_14, field_18, field_1c, field_20, field_24, field_28;
    Vector3 vector_2c, vector_38, vector_44;
    Vector2 vector_50, vector_58, vector_60, vector_68, vector_70;
    float field_78, field_7c;
    Vector3 vector_80;
    VectorInterpolation interpolation_8c;
    IntegerTripleInterpolation interpolation_e0;
    IntegerInterpolation interpolation_134;
    VectorInterpolation interpolation_160;
    AngleInterpolation interpolation_1b4;
    Vector2Interpolation interpolation_1e0, interpolation_220, interpolation_260;
    IntegerTripleInterpolation interpolation_2a0;
    IntegerInterpolation interpolation_2f4;
    FloatInterpolation interpolation_320, interpolation_34c;
    Vector2 vectors_378[4], vector_398;
    float field_3a0, field_3a4;
    std::int32_t field_3a8, field_3ac, field_3b0, field_3b4;
    Matrix4 matrix_3b8, matrix_3f8;
    std::int32_t field_438, field_43c;
    std::uint16_t field_440;
    AnmVariables variables;
    Vector3 vector_484;
    std::uint32_t color_490, color_494;
    AnimationFlags flags;
    float field_4b8, field_4bc;
    AnimationBase() noexcept;
};
struct Animation {
    AnimationBase base;
    AnimationHandle handle;
    std::uint32_t index;
    Timer timer_4c8, timer_4d8;
    std::uint32_t field_4e8;
    IntrusiveLink<Animation> link_4ec, link_500, link_514, link_528, link_53c;
    // These two observed words remain semantically unresolved.
    std::uint32_t field_550, field_554;
    Animation* parent_558;
    Animation* parent_55c;
    float field_560;
    void* geometry;
    AnimationCallback* callback;
    std::uint32_t geometry_bytes, field_570, field_574;
    std::uint8_t field_578, field_579;
    Matrix4 matrix_57c;
    Vector3 vector_5bc;
    std::uint32_t field_5c8, field_5cc;
    Vector3 vector_5d0;
    std::uint32_t field_5dc, field_5e0;
    Animation() noexcept;
    ~Animation() noexcept;
    // Nonzero field_550 enters the native repeated-handle-clear loop.
    void release_resources();
    void reset();
    Vector3& position_ref();
    float inherited_scale_y();
    float inherited_scale_x();
    float height();
    float width();
};
// Actual pooled storage. Natural construction remains nonexact under the
// ANM EHsc recipe; do not change shared child contracts to erase cleanup.
struct PooledAnimation {
    Animation animation;
    IntrusiveLink<Animation> free_link;
    std::uint8_t active;
    std::uint32_t index;
    PooledAnimation();
};
static_assert(sizeof(AnimationBase) == 0x4c0);
static_assert(offsetof(AnimationBase, variables) == 0x444);
static_assert(offsetof(AnimationBase, flags) == 0x498);
#if defined(_M_IX86)
static_assert(sizeof(Animation) == 0x5e4);
static_assert(offsetof(Animation, link_4ec) == 0x4ec);
static_assert(offsetof(Animation, matrix_57c) == 0x57c);
static_assert(sizeof(PooledAnimation) == 0x600);
static_assert(offsetof(PooledAnimation, active) == 0x5f8);
#endif
}

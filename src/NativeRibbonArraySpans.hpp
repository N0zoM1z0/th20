#pragma once
// Original ribbon segment contains 60 Vector2 points at +0x000 and
// 60 float radii at +0x2D0. Each native end accessor is a separate 19B
// compiler/template-like source instance; original authorship is pending.
#include "Vector2.hpp"
#include <array>
namespace th20 {
struct NativeRibbonScalarSpan {
    std::array<float, 60> values;
    float* end_45dca0();
};
struct NativeRibbonPointSpan {
    std::array<Vector2, 60> values;
    Vector2* end_45dcc0();
};
static_assert(sizeof(NativeRibbonScalarSpan) == 0xF0);
static_assert(sizeof(NativeRibbonPointSpan) == 0x1E0);
} // namespace th20

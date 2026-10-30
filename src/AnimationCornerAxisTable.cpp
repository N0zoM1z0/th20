// Immutable original 96-byte Animation sprite quad corner anchor table.
// Two 0x30-byte axes, each with three 16-byte (four-float) mode records.
// This is original game .rdata, not executable .text credit.
#include "AnimationCornerProjectionOwner.hpp"
namespace th20 {
extern const NativeQuadAxisLayout native_quad_axis_layout[2] = {
    { { {-0.5f,  0.5f, -0.5f,  0.5f},
        { 0.0f,  1.0f,  0.0f,  1.0f},
        {-1.0f,  0.0f, -1.0f,  0.0f} } },
    { { {-0.5f, -0.5f,  0.5f,  0.5f},
        { 0.0f,  0.0f,  1.0f,  1.0f},
        {-1.0f, -1.0f,  0.0f,  0.0f} } },
};
static_assert(sizeof(native_quad_axis_layout)==96);
} // namespace th20

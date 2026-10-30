// Native original complete 78-byte game geometry XY transform (0x00445AD0).
// Genuine cdecl seven-stack-argument helper called by Animation shape Bosses.
#include "Vector2.hpp"
namespace th20 {
void __cdecl animation_shape_xy(Vector2& output, float x, float y,
                                float sine, float cosine, float tx, float ty) {
    output.x = x*cosine-y*sine+tx;
    output.y = x*sine+y*cosine+ty;
}
}

// Complete original 240B/76-i386 game outline rectangle wrapper strict exact.
// Two physical original rectangle E8 calls, original half-alpha packed RGB
// colors and two PE HIGHLOW 1.0f fields are independently attested;
// entire native game function replays zero-difference 240/240 bytes.
#include "AnimationDrawDetailedOwner.hpp"
#include <cstdint>

namespace th20 {
extern const float native_one;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43a1c0(
    float x, float y, float width, float height, float angle,
    std::uint32_t color_first, std::uint32_t color_second,
    std::int32_t horizontal_anchor, std::int32_t vertical_anchor) {
    const std::uint32_t outline_first=(color_first & 0x00FFFFFFu)
        | (((color_first >> 24) >> 1) << 24);
    const std::uint32_t outline_second=(color_second & 0x00FFFFFFu)
        | (((color_second >> 24) >> 1) << 24);
    draw_rect_439a00(x,y,width+native_one,height+native_one,angle,
                     outline_first,outline_second,horizontal_anchor,vertical_anchor);
    draw_rect_439a00(x,y,width,height,angle,
                     color_first,color_second,horizontal_anchor,vertical_anchor);
    return 0;
}
}

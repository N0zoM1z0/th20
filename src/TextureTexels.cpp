#include "TextureTexels.hpp"

namespace th20 {

void accumulate_texel1555(std::uint32_t* rgb, const Texel1555* pixel,
                          std::uint32_t& count) {
    if (!rgb) return;
    if (pixel->alpha) {
        rgb[0] += pixel->red;
        rgb[1] += pixel->green;
        rgb[2] += pixel->blue;
        ++count;
    }
}

void accumulate_texel4444(std::uint32_t* rgb, const Texel4444* pixel,
                          std::uint32_t& count) {
    if (!rgb) return;
    if (pixel->alpha) {
        rgb[0] += pixel->red;
        rgb[1] += pixel->green;
        rgb[2] += pixel->blue;
        ++count;
    }
}

void accumulate_texel8332(std::uint32_t* rgb, const Texel8332* pixel,
                          std::uint32_t& count) {
    if (!rgb) return;
    if (pixel->alpha) {
        rgb[0] += pixel->red;
        rgb[1] += pixel->green;
        rgb[2] += pixel->blue;
        ++count;
    }
}

void accumulate_texel8888(std::uint32_t* rgb, const Texel8888* pixel,
                          std::uint32_t& count) {
    if (!rgb) return;
    if (pixel->alpha) {
        rgb[0] += pixel->red;
        rgb[1] += pixel->green;
        rgb[2] += pixel->blue;
        ++count;
    }
}

} // namespace th20

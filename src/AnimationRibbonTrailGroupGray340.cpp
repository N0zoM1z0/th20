#include "NativeRibbonTrailGroup.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
#include "GameRandom.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_pi;
void __fastcall set_animation_flag_byte_01_zero(Animation* animation);
struct NativeTrailRGBA {std::uint8_t r,g,b,a;};
std::int32_t NativeRibbonTrailGroup::configure_gray_45e240(const Vector3& position, std::int32_t unused_token) {
    vertices_08[0].x=0.0f;
    vertices_08[0].y=0.0f;
    angle_308=native_polygon_random_5ba4c4.range(native_pi);
    timer_30c = 1;
    std::int32_t tail_alpha=0;
    for (std::int32_t index=0;index<64;++index) {
        reinterpret_cast<std::uint32_t&>(reinterpret_cast<Vector3*>(&colors_208)->operator[](index))=0xff505050u;
        if (index < 8) {
            reinterpret_cast<NativeTrailRGBA*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->r = static_cast<std::uint8_t>(255-(index<<5));
        }
        if (index >= 32) {
            reinterpret_cast<NativeTrailRGBA*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->a = static_cast<std::uint8_t>(255-(tail_alpha<<4));
            ++tail_alpha;
        }
    }
    animation->set_position(position);
    animation->set_layer(19);
    set_animation_flag_byte_01_zero(animation);
    return 0;
}
}

#include "NativeRibbonTrailGroup.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
#include "GameRandom.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_pi;
void __fastcall set_animation_flag_byte_01_one(Animation* animation);
struct NativeTrailAnimationConfigView { void configure_438c60(std::int32_t,std::int32_t,std::uint8_t,std::uint8_t); };
struct NativeTrailRGBA {std::uint8_t r,g,b,a;};
std::int32_t NativeRibbonTrailGroup::configure_pink_45e3a0(const Vector3& position, std::int32_t token) {
    token_31c = reinterpret_cast<void*>(static_cast<std::uintptr_t>(token));
    vertices_08[0].x=0.0f;
    vertices_08[0].y=0.0f;
    angle_308=native_polygon_random_5ba4c4.range(native_pi);
    timer_30c = 1;
    std::int32_t tail_alpha=0;
    for (std::int32_t index=0;index<64;++index) {
        reinterpret_cast<std::uint32_t&>(reinterpret_cast<Vector3*>(&colors_208)->operator[](index))=0xff0080ffu;
        if (index < 8) {
            reinterpret_cast<NativeTrailRGBA*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->b = static_cast<std::uint8_t>(255-(index<<5));
        }
        if (index >= 32) {
            reinterpret_cast<NativeTrailRGBA*>(&reinterpret_cast<Vector3*>(&colors_208)->operator[](index))->a = static_cast<std::uint8_t>(255-(tail_alpha<<4));
            ++tail_alpha;
        }
    }
    animation->set_position(position);
    animation->set_layer(15);
    set_animation_flag_byte_01_one(animation);
    reinterpret_cast<NativeTrailAnimationConfigView*>(animation)->configure_438c60(64,0,255,0);
    return 0;
}
}

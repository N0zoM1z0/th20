// Original 637-byte ScreenInf initializer at 0x00423BF0, 10 real modes.
// Source-present large Boss, not yet accepted as whole byte-exact.
#include "NativeScreenEffect.hpp"
#include "FunctionChainController.hpp"
#include "FunctionChain.hpp"
namespace th20 {
std::int32_t __cdecl screen_update_fade_out_4240c0(void*);
std::int32_t __cdecl screen_update_shake_4249f0(void*);
std::int32_t __cdecl screen_update_fade_in_424260(void*);
std::int32_t __cdecl screen_update_flash_424350(void*);
std::int32_t __cdecl screen_update_hold_424180(void*);
std::int32_t __cdecl screen_update_envelope_4244c0(void*);
std::int32_t __cdecl screen_update_solid_424460(void*);
std::int32_t __cdecl screen_draw_solid_424e00(void*);
std::int32_t __cdecl screen_draw_fade_424f30(void*);
std::int32_t __cdecl screen_draw_flash_424fa0(void*);
std::int32_t __cdecl screen_draw_hold_424e80(void*);
std::int32_t __cdecl screen_shutdown_425070(void*);

void NativeScreenInf::initialize_423bf0(
    std::int32_t mode, std::uint32_t p1, std::uint32_t p2,
    std::uint32_t p3, std::uint32_t p4, std::int32_t draw_priority) {
    switch (mode) {
    default:
        break;
    case 0:
        update_node=register_update(24,screen_update_fade_out_4240c0,this);
        draw_node=register_draw(draw_priority,screen_draw_solid_424e00,this);
        break;
    case 1:
        update_node=register_update(24,screen_update_shake_4249f0,this);
        break;
    case 2:
        update_node=register_update(24,screen_update_fade_in_424260,this);
        draw_node=register_draw(draw_priority,screen_draw_fade_424f30,this);
        break;
    case 3:
        alpha_18=255;
        update_node=register_update(24,screen_update_fade_out_4240c0,this);
        draw_node=register_draw(draw_priority,screen_draw_fade_424f30,this);
        break;
    case 5:
        update_node=register_update(24,screen_update_fade_in_424260,this);
        draw_node=register_draw(draw_priority,screen_draw_solid_424e00,this);
        break;
    case 4:
        update_node=register_update(24,screen_update_flash_424350,this);
        draw_node=register_draw(draw_priority,screen_draw_flash_424fa0,this);
        break;
    case 6:
        update_node=register_update(24,screen_update_hold_424180,this);
        draw_node=register_draw(draw_priority,screen_draw_fade_424f30,this);
        break;
    case 7:
        update_node=register_update(24,screen_update_hold_424180,this);
        draw_node=register_draw(draw_priority,screen_draw_hold_424e80,this);
        break;
    case 8:
        update_node=register_update(24,screen_update_envelope_4244c0,this);
        break;
    case 9:
        update_node=register_update(24,screen_update_solid_424460,this);
        draw_node=register_draw(draw_priority,screen_draw_fade_424f30,this);
        break;
    }
    update_node->set_shutdown_callback(screen_shutdown_425070);
    timer_30=0;
    mode_10=mode;
    field_1c=p1;
    field_20=p2;
    field_24=p3;
    field_28=p4;
}
} // namespace th20

// Entire original Card periodic gameplay Boss at 0x00486F60, 875B/262-i386.
// Natural C++20 source using real Card/Timer, Player/Enemy and Animation
// owners. All 28 original physical E8 target roles and 8 PE HIGHLOW
// destinations match; complete original code is whole strict exact.
#include "Card.hpp"
#include "NativeCardTickViews.hpp"
#include "NativeCardFinishViews.hpp"
#include "Player.hpp"
#include "EnemyController.hpp"
#include "Enemy.hpp"
#include <cstdint>
namespace th20 {
// Original external boundary floats: true native rdata addresses and
// original compiler role. The separately observed 0.05f uses a literal,
// just like its original pooled __real@3d4ccccd operand; no fake global.
extern const float native_card_y_edge_96_56fe7c;
extern const float native_card_y_edge_128_56cd98;
extern const float native_card_screen_height_448_56d7c0;

std::int32_t NativeCardTickView::update_486f60() {
    if ((reinterpret_cast<Card*>(this)->spell_flags.bits&1u)!=0) {
    ++reinterpret_cast<Card*>(this)->frames;
    if (reinterpret_cast<Card*>(this)->age.at_least(60) && ((reinterpret_cast<Card*>(this)->spell_flags.bits >> 9)&1u)==0)
        reinterpret_cast<NativeCardTickUiView*>(native_card_ui_5c069c)->clear_ui_flag0_487b90();
    if (reinterpret_cast<Card*>(this)->age.at_least(300) && ((reinterpret_cast<Card*>(this)->spell_flags.bits>>3)&1u)==0) {
        reinterpret_cast<Card*>(this)->bonus-= (reinterpret_cast<Card*>(this)->initial_bonus-reinterpret_cast<Card*>(this)->initial_bonus/3)/(reinterpret_cast<Card*>(this)->duration-300);
        reinterpret_cast<Card*>(this)->bonus-=reinterpret_cast<Card*>(this)->bonus%10;
    }
    reinterpret_cast<Card*>(this)->age++;
    if (reinterpret_cast<Card*>(this)->age.at_least(120)) {
        if (((reinterpret_cast<Card*>(this)->spell_flags.bits>>2)&1u)==0) {
            if ((reinterpret_cast<NativeCardBit8GetterView*>(this)->flag8_value_4888a0()==0 &&
                 native_card_y_edge_96_56fe7c>reinterpret_cast<Card*>(this)->context->player()->position_ref().y) ||
                (reinterpret_cast<NativeCardBit8GetterView*>(this)->flag8_value_4888a0()!=0 &&
                 reinterpret_cast<Card*>(this)->context->player()->position_ref().y>
                    native_card_screen_height_448_56d7c0-native_card_y_edge_96_56fe7c)) {
                for (std::int32_t i=0;i<3;++i) reinterpret_cast<Card*>(this)->info_handles[i].interrupt(3);
                reinterpret_cast<Card*>(this)->spell_flags.bits|=4u;
            }
        } else {
            if (((reinterpret_cast<Card*>(this)->spell_flags.bits>>8)&1u)==0 &&
                    reinterpret_cast<Card*>(this)->context->player()->position_ref().y>native_card_y_edge_128_56cd98 ||
                ((reinterpret_cast<Card*>(this)->spell_flags.bits>>8)&1u)!=0 &&
                    reinterpret_cast<Card*>(this)->context->player()->position_ref().y<
                    native_card_screen_height_448_56d7c0-native_card_y_edge_128_56cd98) {
                for (std::int32_t i=0;i<3;++i) reinterpret_cast<Card*>(this)->info_handles[i].interrupt(2);
                reinterpret_cast<Card*>(this)->spell_flags.bits&=~4u;
            }
        }
    }
    if (reinterpret_cast<Card*>(this)->context->enemy_controller()->selected(0)!=nullptr) {
        reinterpret_cast<Card*>(this)->position+=(reinterpret_cast<Card*>(this)->context->enemy_controller()->selected(0)->position_ref()-reinterpret_cast<Card*>(this)->position)*
            0.05f;
    }
    reinterpret_cast<Card*>(this)->effect_handle.set_position(reinterpret_cast<Card*>(this)->position);
    if (((reinterpret_cast<Card*>(this)->spell_flags.bits>>5)&1u)!=0 &&
        !reinterpret_cast<NativeCardTickBombView*>(reinterpret_cast<Card*>(this)->context->bomb_controller())->active_478130())
        reinterpret_cast<Card*>(this)->spell_flags.bits&=~0x20u;
    }
    return 1;
}
}

// Complete 797-byte Card Draw Boss at 0x00487590. This naturally compiled
// source preserves all 30 native E8 and 28 original PE HIGHLOW positions.
// The real Card, Animation, spell records and AsciiInf owners are borrowed.
// Original native source exactness is established by the independent strict
// verifier, not inferred from source presence or a call count.
#include "Card.hpp"
#include "Animation.hpp"
#include "Session.hpp"
#include "NativeCardRendererFileView.hpp"
#include "NativeCardFinishViews.hpp"
#include "NativeParticleAnimationAccess.hpp"
#include "NativeCardTickViews.hpp"
#include "NativeCardAsciiDrawView.hpp"
#include <cstdint>
#include <string_view>
namespace th20 {
extern const float native_card_x_266_56fe80;
extern const float native_card_x_282_56fe84;
extern const float native_card_x_360_56fe88;
extern const float native_card_y_37_56fe78;
#define CARD_DRAW_ASCII reinterpret_cast<NativeCardAsciiDrawView*>(native_card_renderer_5c0698)
#define CARD_RECORD() reinterpret_cast<NativeSpellRecordArrayView*>(reinterpret_cast<std::uint8_t*>(native_primary_records_50fc50(native_card_records_5c6108))+0xB08)->record_486e10(reinterpret_cast<Card*>(this)->spell_index)
#define CARD_CAPTURE() reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(CARD_RECORD())+0xC0)[which]
#define CARD_ATTEMPT() reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(CARD_RECORD())+0xC8)[which]

std::int32_t NativeCardDrawView::draw_487590() {
    if ((reinterpret_cast<Card*>(this)->spell_flags.bits&1u)!=0) {
        Animation* animation=reinterpret_cast<Card*>(this)->info_handles[2].resolve();
        if (animation!=nullptr) {
            CARD_DRAW_ASCII->set_font_488b00(2);
            CARD_DRAW_ASCII->set_layer_488a00(2);
            std::uint8_t alpha=reinterpret_cast<AnimationColorChannels*>(
                &reinterpret_cast<NativeParticleAnimationAccess*>(animation)->color_ref_45d0e0())->alpha;
            CARD_DRAW_ASCII->set_color_alpha_488940(alpha);
            if ((reinterpret_cast<Card*>(this)->spell_flags.bits>>1)&1u) {
                Vector3 count_position(native_card_x_266_56fe80,native_card_y_37_56fe78,0.0f);
                CARD_DRAW_ASCII->render_number_46cd40(count_position,static_cast<std::uint32_t>(reinterpret_cast<Card*>(this)->bonus),8,' ');
            } else {
                Vector3 dollar_position(native_card_x_282_56fe84,native_card_y_37_56fe78,0.0f);
                CARD_DRAW_ASCII->render_text_46ce90(dollar_position,"$");
            }
            Vector3 score_position(native_card_x_360_56fe88,native_card_y_37_56fe78,0.0f);
            std::int32_t which=session.field_70_is_two()?1:0;
            if (CARD_CAPTURE()>=100) {
                CARD_DRAW_ASCII->render_text_46ce90(score_position,"MASTER");
            } else if (CARD_ATTEMPT()>=100) {
                CARD_DRAW_ASCII->render_format_46c990(score_position,"%.2d/99+",CARD_CAPTURE());
            } else {
                CARD_DRAW_ASCII->render_format_46c990(score_position,"%.2d/%.2d",CARD_CAPTURE(),CARD_ATTEMPT());
            }
            CARD_DRAW_ASCII->set_font_488b00(0);
            CARD_DRAW_ASCII->set_layer_488a00(0);
            CARD_DRAW_ASCII->set_color_alpha_488940(0xFF);
        }
    }
    return 1;
}
#undef CARD_DRAW_ASCII
#undef CARD_RECORD
#undef CARD_CAPTURE
#undef CARD_ATTEMPT
}

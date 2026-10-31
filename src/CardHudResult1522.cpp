// Whole original 1,522-byte Card result HUD Boss with its genuine 7-entry
// switch-pointer table. Each borrowed HUD/AnimationFile owner is re-read at
// its real callsite, preserving native observer lifetimes and 51 real E8s.
// The two score thresholds are >= 1,000,000 and >= 1,000: correct inclusive
// comparisons are necessary even when alternate inequalities are equivalent.
#include "NativeCardFinishViews.hpp"
#include "AnimationFile.hpp"
#include "AnimationHandle.hpp"
#include <array>
#include <cstdint>
namespace th20 {
// Narrow non-owning receiver for script/digit display; the original full
// resource owner and original method spellings are not inferred here.
struct NativeCardGlyphView {
    void set_digit_44bd70(std::int32_t script);
    void hide_leading_450120();
    void show_digit_44fa30();
};
// Original getter is a true 20B native game field accessor; the observed
// field at +0x1A244 is a borrowed AnimationFile pointer, not a new owner.
struct NativeCardRendererFileView {
    AnimationFile* current_file_437950();
};
extern NativeCardRendererFileView* native_card_renderer_5c0698;
AnimationFile* NativeCardRendererFileView::current_file_437950() {
    return *reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x1A244);
}
void NativeCardHudView::report_spell_result_4b90e0(std::int32_t mode,
                                                    std::int32_t score) {
    // Retain original case sharing and source-order evaluations of the
    // 2-element and 10-element handle arrays instead of caching their bases.
    switch(mode) {
    case 0: {
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0] = (*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x31,-1,nullptr);
        std::int32_t remaining=score;
        std::int32_t divisor=10000000;
        std::int32_t visible=0;
        for (std::int32_t i=0;i<8;++i) {
            (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[i].retire();
            (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[i]=native_card_renderer_5c0698->current_file_437950()->spawn(nullptr,i+4,-1,nullptr);
            if(remaining/divisor!=0) visible=1;
            reinterpret_cast<NativeCardGlyphView*>(&(*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[i])->set_digit_44bd70(remaining/divisor+0xEF);
            if (!visible) {
                reinterpret_cast<NativeCardGlyphView*>(&(*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[i])->hide_leading_450120();
            } else {
                reinterpret_cast<NativeCardGlyphView*>(&(*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[i])->show_digit_44fa30();
            }
            remaining%=divisor;
            divisor/=10;
        }
        (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[8].retire();
        if(score>=1000000) {
            (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[8]=native_card_renderer_5c0698->current_file_437950()->spawn(nullptr,0xC,-1,nullptr);
            reinterpret_cast<NativeCardGlyphView*>(&(*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[8])->set_digit_44bd70(0xFD);
        }
        (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[9].retire();
        if(score>=1000) {
            (*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[9]=native_card_renderer_5c0698->current_file_437950()->spawn(nullptr,0xD,-1,nullptr);
            reinterpret_cast<NativeCardGlyphView*>(&(*reinterpret_cast<std::array<AnimationHandle,10>*>(reinterpret_cast<std::uint8_t*>(this)+0x94))[9])->set_digit_44bd70(0xFD);
        }
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x138)=1;
        *reinterpret_cast<AnimationHandle*>(reinterpret_cast<std::uint8_t*>(this)+0x114)=
            (*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x54,-1,nullptr);
        break;
    }
    case 1:
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0]=(*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x32,-1,nullptr);
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x138)=1;
        *reinterpret_cast<AnimationHandle*>(reinterpret_cast<std::uint8_t*>(this)+0x114)=
            (*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x54,-1,nullptr);
        break;
    case 2:
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1]=(*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x33,-1,nullptr);
        break;
    case 3:
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1]=(*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x34,-1,nullptr);
        break;
    case 4:
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[1]=(*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x35,-1,nullptr);
        break;
    case 6:
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0].retire();
        (*reinterpret_cast<std::array<AnimationHandle,2>*>(reinterpret_cast<std::uint8_t*>(this)+0xBC))[0]=(*reinterpret_cast<AnimationFile**>(reinterpret_cast<std::uint8_t*>(this)+0x2CC))->spawn("front",0x36,-1,nullptr);
        break;
    default:
        break;
    }
}
}

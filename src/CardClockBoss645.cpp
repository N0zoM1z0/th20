// Original entire 645B Card clock/record Boss at 0x004872D0.
// The x87 FWAIT after std::floor-to-int conversion comes from the genuine
// MSVC floating-point exception mode. Native calls __ftol2_sse_excpt, not
// ordinary __ftol2_sse; there are no inserted NOPs or hand opcodes.
// Every original E8 / PE HIGHLOW target and physical offset is preserved.
#include "Card.hpp"
#include "Session.hpp"
#include "GameController.hpp"
#include "NativeCardClockViews.hpp"
#include <cmath>
#include <cstdint>
namespace th20 {
extern GameController* current_game_controller;
#pragma float_control(push)
#pragma float_control(except, on)
void NativeCardClockView::process_clock_4872d0() {
    if ((reinterpret_cast<Card*>(this)->spell_flags.bits & 1u) != 0) {
        if (((reinterpret_cast<Card*>(this)->spell_flags.bits>>6)&1u)==0) {
            reinterpret_cast<Card*>(this)->start_time=native_card_window_time_5b6758.current_seconds_41cb10();
            reinterpret_cast<Card*>(this)->spell_flags.bits|=0x40u;
        }
    } else if (((reinterpret_cast<Card*>(this)->spell_flags.bits>>6)&1u)!=0) {
        reinterpret_cast<Card*>(this)->last_frames=reinterpret_cast<Card*>(this)->frames;
        reinterpret_cast<Card*>(this)->elapsed=native_card_window_time_5b6758.current_seconds_41cb10()-reinterpret_cast<Card*>(this)->start_time;
        const double fraction=std::fmod(reinterpret_cast<Card*>(this)->elapsed,native_card_tick_seconds_56fe60);
        reinterpret_cast<Card*>(this)->elapsed-=fraction;
        if(fraction >= native_card_tick_seconds_56fe60/native_card_double_two_56fe68)
            reinterpret_cast<Card*>(this)->elapsed+=native_card_tick_seconds_56fe60;
        std::int32_t seconds=static_cast<std::int32_t>(std::floor(reinterpret_cast<Card*>(this)->elapsed));
        if (seconds>=1000) seconds=999;
        std::int32_t hundredths=static_cast<std::int32_t>(
            (reinterpret_cast<Card*>(this)->elapsed-std::floor(reinterpret_cast<Card*>(this)->elapsed))*native_card_double_hundred_56fe70);
        reinterpret_cast<Card*>(this)->encode_time(seconds,hundredths);
        reinterpret_cast<Card*>(this)->elapsed=0.0;
        reinterpret_cast<Card*>(this)->spell_flags.bits &=~0x40u;
        if (current_game_controller->restart()==0) {
            const std::int32_t encoded=reinterpret_cast<Card*>(this)->encoded_time;
            std::int32_t diff=session.clamped_field_1f4();
            auto* record=native_card_play_5c60fc->primary_record_488740(diff)+0x1c;
            const std::uint32_t offset=reinterpret_cast<Card*>(this)->capture_index*4;
            *reinterpret_cast<std::int32_t*>(record+offset)=encoded;
        } else {
            std::int32_t diff=session.clamped_field_1f4();
            auto* record=native_card_play_5c60fc->alternate_record_488770(diff)+0x1c;
            const std::uint32_t offset=reinterpret_cast<Card*>(this)->capture_index*4;
            reinterpret_cast<Card*>(this)->encoded_time=*reinterpret_cast<std::int32_t*>(record+offset);
            if(reinterpret_cast<Card*>(this)->invalid_encoded_time()) reinterpret_cast<Card*>(this)->encode_time(999,99);
        }
        ++reinterpret_cast<Card*>(this)->capture_index;
    }
}
#pragma float_control(pop)
}

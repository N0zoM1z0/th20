#include "Card.hpp"
#include "EclDiagnostic.hpp"
#include "Session.hpp"

namespace th20 {
Card::Card() noexcept
    : name{}, spell_index(0), spell_flags{}, bonus(0), initial_bonus(0),
      duration(0), capture_index(0), frames(0), last_frames(0), start_time(0),
      elapsed(0), encoded_time(0), field_b8(0), player_index(0), context(nullptr) {
    ecl_diagnostic_hint("initialize CardInf\n");
}

// Signed remainders follow the native IDIV operations. Unsigned intermediates
// preserve native 32-bit addition/multiplication wrap for every input word.
void Card::encode_time(std::int32_t seconds, std::int32_t hundredths) {
    encoded_time = static_cast<std::int32_t>(static_cast<std::uint32_t>(seconds)+66u)%1000*100;
    encoded_time += static_cast<std::int32_t>(static_cast<std::uint32_t>(hundredths)+33u)%100;
    encoded_time = static_cast<std::int32_t>(static_cast<std::uint32_t>(encoded_time)
        +(static_cast<std::uint32_t>(seconds)+22u+static_cast<std::uint32_t>(hundredths))*100000u);
}

std::int32_t Card::invalid_encoded_time() {
    std::int32_t seconds = (encoded_time/100)%1000;
    std::int32_t hundredths = encoded_time%100;
    std::int32_t checksum = encoded_time/100000;
    return checksum-22 != (seconds+934)%1000+(hundredths+67)%100 ? 1 : 0;
}

bool Card::active() { return (spell_flags.bits&1u) != 0; }

void Card::bind_context(std::int32_t index) {
    player_index=index;
    context=&session.context(player_index);
}

Card* card(std::int32_t index) { return session.context(index).card(); }
}

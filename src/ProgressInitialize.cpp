#include "ProgressStorage.hpp"
#include "GameRandom.hpp"
#include "SecureCrt.hpp"

namespace th20 {
// Independent native consumers establish the second stream at 5BA4C4. Process
// construction and the complete enclosing stream owner remain pending.
extern GameRandom progress_random;
const char progress_score_default_name[]="--------";
const char progress_metadata_default_name[]="        ";

void ProgressProfile::initialize() {
    header.magic=0x5243;
    header.version=1;
    header.size=sizeof(ProgressProfile);
    for (std::int32_t difficulty=0; difficulty<7; ++difficulty) {
        for (std::int32_t rank=0; rank<10; ++rank) {
            scores[difficulty][rank].score=100000-rank*10000;
            scores[difficulty][rank].stage=1;
            strcpy_s(scores[difficulty][rank].name, sizeof(scores[difficulty][rank].name), progress_score_default_name);
            scores[difficulty][rank].timestamp=0;
            scores[difficulty][rank].continues=0;
            scores[difficulty][rank].slowdown=0;
        }
    }
    for (std::int32_t index=0; index<113; ++index) {
        auto& owned_spells=spells;
        owned_spells[index].identifier=index;
        std::uint32_t value=progress_spell_defaults[index];
        auto& destination=spells;
        destination[index].default_value=value;
    }
}

void ProgressMetadata::initialize() {
    header.magic=0x5453;
    header.version=2;
    header.size=sizeof(ProgressMetadata);
    strcpy_s(name, sizeof(name), progress_metadata_default_name);
    for (std::int32_t index=0; index<32; ++index) salt_1b0[index]=progress_random.next()&0xff;
    for (std::int32_t index=0; index<32; ++index) salt_1d2[index]=progress_random.next()&0xff;
    auto& owned_stones=stones;
    // The independently reviewed native accessor checks the nine-element bound.
    owned_stones.at(8)=9;
    update_integrity();
}
} // namespace th20

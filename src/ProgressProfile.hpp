#pragma once
#include "ProgressRecords.hpp"
#include <array>
#include <type_traits>

namespace th20 {
// Native construction allocates 123 physical records; startup assigns the
// currently active 113. The roles of the remaining ten slots are unknown.
struct ProgressSpell {
    char name[192];
    std::int32_t captures[2]{}, attempts[2]{};
    std::uint32_t identifier=0, default_value=0;
    std::int64_t field_d8=0;
};
struct ProgressStatistics {
    std::int64_t field_00=0;
    std::uint32_t first[7]{}, second[7]{}, field_40=0, field_44=0;
};
struct ProgressProfile {
    ProgressRecordHeader header;
    std::uint32_t field_0c=0, field_10=0;
    ProgressScore scores[7][10] = {0};
    std::array<ProgressSpell,123> spells = {0};
    std::uint32_t field_76a8=0;
    ProgressStatistics statistics = {0};
    PracticeScore practice[7][9];
    ProgressProfile() noexcept;
    void initialize();
};
// Native initialization consumes entries 0..112. The complete original table
// extent and startup definition remain pending; do not invent its remaining data.
extern std::uint32_t progress_spell_defaults[];
static_assert(std::is_aggregate_v<ProgressScore>);
static_assert(sizeof(ProgressSpell)==0xe0);
static_assert(offsetof(ProgressSpell, captures)==0xc0);
static_assert(offsetof(ProgressSpell, attempts)==0xc8);
static_assert(offsetof(ProgressSpell, identifier)==0xd0);
static_assert(sizeof(ProgressStatistics)==72);
static_assert(sizeof(ProgressProfile)==0x7ae8);
static_assert(offsetof(ProgressProfile, scores)==0x18);
static_assert(offsetof(ProgressProfile, spells)==0xb08);
static_assert(offsetof(ProgressProfile, field_76a8)==0x76a8);
static_assert(offsetof(ProgressProfile, statistics)==0x76b0);
static_assert(offsetof(ProgressProfile, practice)==0x76f8);
} // namespace th20

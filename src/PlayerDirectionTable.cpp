// Original TH20 signed Player movement direction data at 0x00572C48.
// This is one genuine externally linked .rdata[9][2] object, not a
// copy of the nine original rows embedded into each call site.
// Its 72 native PE bytes and the pinned MSVC x86 .rdata bytes are identical.
// The whole 3111-byte Player frame remains NONEXACT despite this data repair.
#include <cstdint>

namespace th20 {
extern const std::int32_t native_player_direction_table[9][2] = {
    { 0,  0}, { 0, -1}, { 0,  1},
    {-1,  0}, { 1,  0}, {-1, -1},
    { 1, -1}, {-1,  1}, { 1,  1},
};
static_assert(sizeof(native_player_direction_table) == 72);
} // namespace th20

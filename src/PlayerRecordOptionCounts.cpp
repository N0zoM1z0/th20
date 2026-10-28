// Original PlayerRecord clamp bounds and signed option-count division.
// Each complete method returns the native updated and/or derived integer.
#include "PlayerRecord.hpp"
#include <algorithm>
namespace th20 {
std::int32_t PlayerRecord::clamped_option_units() {
    field_30 = std::clamp(field_30,0,400);
    return field_30;
}
std::int32_t PlayerRecord::clamped_option_cap() {
    field_34 = std::clamp(field_34,400,400);
    return field_34;
}
std::int32_t PlayerRecord::available_option_count() {
    return clamped_option_units() / starting_power();
}
} // namespace th20

#include "PlayerRecord.hpp"
#include <algorithm>

namespace th20 {
std::int32_t PlayerRecord::clamped_field_4c() {
    field_4c=std::clamp(field_4c,0,500);
    return field_4c;
}
std::int32_t PlayerRecord::clamped_field_50() {
    field_50=std::clamp(field_50,100,500);
    return field_50;
}
void PlayerRecord::add_field_4c_clamped(std::int32_t amount) {
    field_4c+=amount;
    field_4c=std::clamp(field_4c,0,500);
}
std::uint8_t PlayerRecord::field_a4_value() { return field_a4; }
}

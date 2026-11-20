#include "PlayerRecord.hpp"
#include "NativeCardFinishViews.hpp"
#include <algorithm>
namespace th20 {
std::int32_t PlayerRecord::clamped_field_40() {
    field_40=std::clamp(field_40,10000,1000000);
    return field_40;
}
std::int32_t PlayerRecord::clamped_field_44() {
    field_44=std::clamp(field_44,0,1000000);
    return field_44;
}
std::int32_t PlayerRecord::clamped_field_48() {
    field_48=std::clamp(field_48,5000,10000);
    return field_48;
}
void PlayerRecord::add_field_3c_clamped(std::int32_t amount) {
    field_3c+=amount;
    field_3c=std::clamp(field_3c,0,1000000);
}
std::int32_t PlayerRecord::add_field_30_and_check(std::int32_t amount) {
    if (field_30>=field_34) return false;
    field_30+=amount;
    if (field_30>field_34) {
        field_30=field_34;
        native_card_hud_5c06a4->report_spell_result_4b90e0(2,0);
    }
    return (field_30-amount)/field_38 != field_30/field_38;
}
}

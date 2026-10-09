#include "PlayerRecord.hpp"

#include <algorithm>

namespace th20 {

PlayerRecord::PlayerRecord()
    : score(0),
      field_08(0),
      field_0c(0),
      field_10(0),
      field_14(0),
      field_18(0),
      field_1c(0),
      field_20(0),
      field_24(0),
      field_28(0),
      field_2c(0),
      field_2d(0),
      field_2e(0),
      field_2f(0),
      field_30(0),
      field_34(400),
      field_38(100),
      field_3c(0),
      field_40(10000),
      field_44(0),
      field_48(5000),
      field_4c(0),
      field_50(100),
      field_54(1),
      field_58(0),
      field_5c(0),
      field_60(0),
      field_64(0),
      field_68(0),
      field_6c(0),
      field_70(0),
      field_74(0),
      field_78(0),
      field_7c(0),
      field_80(0),
      field_84(0),
      field_88(0),
      field_8c(0),
      field_90(0),
      field_94(0),
      field_98(-1),
      field_9c(0),
      field_a0(0),
      field_a4(0),
      field_a5(0),
      field_a8(0),
      field_ac(0),
      field_b0(0),
      field_b4(0),
      field_b8(-1),
      field_bc(0),
      field_c0(0),
      field_c4(0),
      field_c8(0),
      field_cc(0),
      field_d0(0),
      field_d4(2),
      field_d8(0),
      field_dc(0),
      field_e0(0),
      field_e4(0),
      field_e8(0),
      field_ec(0) {}
std::uint64_t PlayerRecord::current_score() const {return score;}
void PlayerRecord::set_field_ec(std::int32_t value) {
    field_ec = value;
}
void PlayerRecord::set_field_30(std::int32_t value) {
    field_30 = value;
    field_30 = std::clamp(field_30, 0, 400);
}
void PlayerRecord::set_field_34(std::int32_t value) {
    field_34 = value;
    field_34 = std::clamp(field_34, 400, 400);
}
void PlayerRecord::set_field_38(std::int32_t value) {
    field_38 = value;
    field_38 = std::clamp(field_38, 100, 400);
}
void PlayerRecord::set_field_d4(std::int32_t value) {
    field_d4 = value;
    field_d4 = std::clamp(field_d4, 2, 10);
}
void PlayerRecord::set_field_d0(std::int32_t value) {
    field_d0 = value;
    field_d0 = std::clamp(field_d0, 0, 10);
}
void PlayerRecord::set_field_c0(std::int32_t value) {
    field_c0 = value;
    field_c0 = std::clamp(field_c0, 0, 10);
}
void PlayerRecord::set_field_c4(std::int32_t value) {
    field_c4 = value;
    field_c4 = std::clamp(field_c4, 0, 100);
}
void PlayerRecord::set_field_e4(std::int32_t value) {
    field_e4 = value;
    field_e4 = std::clamp(field_e4, 0, 99999999);
}
void PlayerRecord::set_field_4c(std::int32_t value) {
    field_4c = value;
    field_4c = std::clamp(field_4c, 0, 500);
}
void PlayerRecord::set_field_50(std::int32_t value) {
    field_50 = value;
    field_50 = std::clamp(field_50, 100, 500);
}
void PlayerRecord::set_field_54(std::int32_t value) {
    field_54 = value;
    field_54 = std::clamp(field_54, 1, 100);
}
void PlayerRecord::set_field_9c(std::int32_t value) {
    field_9c = value;
    field_9c = std::clamp(field_9c, 0, 100);
}
void PlayerRecord::set_field_a0(std::int32_t value) {
    field_a0 = value;
    field_a0 = std::clamp(field_a0, 0, 100);
}
void PlayerRecord::set_field_a4(std::uint8_t value) {
    field_a4 = value;
}
void PlayerRecord::set_field_a5(std::uint8_t value) {
    field_a5 = value;
}
void PlayerRecord::set_field_a8(std::int32_t value) {
    field_a8 = value;
    field_a8 = std::clamp(field_a8, 0, 100);
}
void PlayerRecord::set_field_b0(std::uint8_t value) {
    field_b0 = value;
}
void PlayerRecord::set_field_44(std::int32_t value) {
    field_44 = value;
    field_44 = std::clamp(field_44, 0, 1000000);
}
void PlayerRecord::set_field_3c(std::int32_t value) {
    field_3c = value;
    field_3c = std::clamp(field_3c, 0, 1000000);
}
void PlayerRecord::set_field_40(std::int32_t value) {
    field_40 = value;
    field_40 = std::clamp(field_40, 10000, 1000000);
}
void PlayerRecord::set_field_48(std::int32_t value) {
    field_48 = value;
    field_48 = std::clamp(field_48, 5000, 10000);
}
void PlayerRecord::set_field_ac(std::int32_t value) {
    field_ac = value;
    field_ac = std::clamp(field_ac, 0, 100);
}
void PlayerRecord::set_field_5c(std::int32_t value) {
    field_5c = value;
    field_5c = std::clamp(field_5c, 0, 10000);
}
void PlayerRecord::set_field_64(std::int32_t value) {
    field_64 = value;
    field_64 = std::clamp(field_64, 0, 1000);
}
void PlayerRecord::set_field_68(std::int32_t value) {
    field_68 = value;
    field_68 = std::clamp(field_68, 0, 1000);
}
void PlayerRecord::set_field_6c(std::int32_t value) {
    field_6c = value;
    field_6c = std::clamp(field_6c, 0, 1000);
}
void PlayerRecord::set_field_70(std::int32_t value) {
    field_70 = value;
    field_70 = std::clamp(field_70, 0, 1000);
}
void PlayerRecord::set_field_60(std::int32_t value) {
    field_60 = value;
    field_60 = std::clamp(field_60, 0, 5000);
}
void PlayerRecord::set_field_74(std::int32_t value) {
    field_74 = value;
    field_74 = std::clamp(field_74, 0, 4);
}
void PlayerRecord::set_field_78(std::int32_t value) {
    field_78 = value;
    field_78 = std::clamp(field_78, 0, 4);
}
void PlayerRecord::set_field_7c(std::int32_t value) {
    field_7c = value;
    field_7c = std::clamp(field_7c, 0, 4);
}
void PlayerRecord::set_field_80(std::int32_t value) {
    field_80 = value;
    field_80 = std::clamp(field_80, 0, 4);
}
void PlayerRecord::set_field_84(std::int32_t value) {
    field_84 = value;
    field_84 = std::clamp(field_84, 0, 999999);
}
void PlayerRecord::set_field_88(std::int32_t value) {
    field_88 = value;
    field_88 = std::clamp(field_88, 0, 999999);
}
void PlayerRecord::set_field_8c(std::int32_t value) {
    field_8c = value;
    field_8c = std::clamp(field_8c, 0, 999999);
}
void PlayerRecord::set_field_90(std::int32_t value) {
    field_90 = value;
    field_90 = std::clamp(field_90, 0, 999999);
}
void PlayerRecord::set_field_94(std::int32_t value) {
    field_94 = value;
    field_94 = std::clamp(field_94, 0, 999999);
}
void PlayerRecord::set_field_bc(std::int32_t value) {
    field_bc = value;
    field_bc = std::clamp(field_bc, 0, 7);
}
void PlayerRecord::set_field_d8(std::int32_t value) {
    field_d8 = value;
    field_d8 = std::clamp(field_d8, 0, 7);
}
void PlayerRecord::set_field_b8(std::int32_t value) {
    field_b8 = value;
    field_b8 = std::clamp(field_b8, -1, 7);
}
void PlayerRecord::set_field_1c(std::int32_t value) {
    field_1c = value;
}
void PlayerRecord::set_field_24(std::int32_t value) {
    field_24 = value;
}
void PlayerRecord::set_field_20(std::int32_t value) {
    field_20 = value;
}
void PlayerRecord::set_field_28(std::int32_t value) {
    field_28 = value;
}
std::int32_t PlayerRecord::starting_power() {
    field_38 = std::clamp(field_38, 100, 400);
    return field_38;
}

std::int32_t PlayerRecord::field_10_value() {return field_10;}
std::int32_t PlayerRecord::field_14_value() {return field_14;}

} // namespace th20

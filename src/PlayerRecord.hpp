#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace th20 {

// Actual 240-byte value stored twice in the session player table. Original
// names are unknown; offset labels preserve that uncertainty. The compiler
// supplies the native gaps at A6/A7 and B1..B3; no explicit padding is needed.
struct PlayerRecord {
    std::uint64_t score;
    std::int32_t field_08;
    std::int32_t field_0c;
    std::int32_t field_10;
    std::int32_t field_14;
    std::int32_t field_18;
    std::int32_t field_1c;
    std::int32_t field_20;
    std::int32_t field_24;
    std::int32_t field_28;
    std::uint8_t field_2c;
    std::uint8_t field_2d;
    std::uint8_t field_2e;
    std::uint8_t field_2f;
    std::int32_t field_30;
    std::int32_t field_34;
    std::int32_t field_38;
    std::int32_t field_3c;
    std::int32_t field_40;
    std::int32_t field_44;
    std::int32_t field_48;
    std::int32_t field_4c;
    std::int32_t field_50;
    std::int32_t field_54;
    std::int32_t field_58;
    std::int32_t field_5c;
    std::int32_t field_60;
    std::int32_t field_64;
    std::int32_t field_68;
    std::int32_t field_6c;
    std::int32_t field_70;
    std::int32_t field_74;
    std::int32_t field_78;
    std::int32_t field_7c;
    std::int32_t field_80;
    std::int32_t field_84;
    std::int32_t field_88;
    std::int32_t field_8c;
    std::int32_t field_90;
    std::int32_t field_94;
    std::int32_t field_98;
    std::int32_t field_9c;
    std::int32_t field_a0;
    std::uint8_t field_a4;
    std::uint8_t field_a5;
    std::int32_t field_a8;
    std::int32_t field_ac;
    std::uint8_t field_b0;
    std::int32_t field_b4;
    std::int32_t field_b8;
    std::int32_t field_bc;
    std::int32_t field_c0;
    std::int32_t field_c4;
    std::int32_t field_c8;
    std::int32_t field_cc;
    std::int32_t field_d0;
    std::int32_t field_d4;
    std::int32_t field_d8;
    std::int32_t field_dc;
    std::int32_t field_e0;
    std::int32_t field_e4;
    std::int32_t field_e8;
    std::int32_t field_ec;
    PlayerRecord();
    std::uint64_t current_score() const;
    void set_field_ec(std::int32_t value);
    void set_field_30(std::int32_t value);
    void set_field_34(std::int32_t value);
    void set_field_38(std::int32_t value);
    void set_field_d4(std::int32_t value);
    void set_field_d0(std::int32_t value);
    void set_field_c0(std::int32_t value);
    void set_field_c4(std::int32_t value);
    void set_field_e4(std::int32_t value);
    void set_field_4c(std::int32_t value);
    void set_field_50(std::int32_t value);
    void set_field_54(std::int32_t value);
    void set_field_9c(std::int32_t value);
    void set_field_a0(std::int32_t value);
    void set_field_a4(std::uint8_t value);
    void set_field_a5(std::uint8_t value);
    void set_field_a8(std::int32_t value);
    void set_field_b0(std::uint8_t value);
    void set_field_44(std::int32_t value);
    void set_field_3c(std::int32_t value);
    void set_field_40(std::int32_t value);
    void set_field_48(std::int32_t value);
    void set_field_ac(std::int32_t value);
    void set_field_5c(std::int32_t value);
    void set_field_64(std::int32_t value);
    void set_field_68(std::int32_t value);
    void set_field_6c(std::int32_t value);
    void set_field_70(std::int32_t value);
    void set_field_60(std::int32_t value);
    void set_field_74(std::int32_t value);
    void set_field_78(std::int32_t value);
    void set_field_7c(std::int32_t value);
    void set_field_80(std::int32_t value);
    void set_field_84(std::int32_t value);
    void set_field_88(std::int32_t value);
    void set_field_8c(std::int32_t value);
    void set_field_90(std::int32_t value);
    void set_field_94(std::int32_t value);
    void set_field_bc(std::int32_t value);
    void set_field_d8(std::int32_t value);
    void set_field_b8(std::int32_t value);
    void set_field_1c(std::int32_t value);
    void set_field_24(std::int32_t value);
    void set_field_20(std::int32_t value);
    void set_field_28(std::int32_t value);
    std::int32_t starting_power();
};
static_assert(sizeof(PlayerRecord) == 240);
static_assert(alignof(PlayerRecord) == 8);
static_assert(std::is_standard_layout_v<PlayerRecord>);
static_assert(std::is_trivially_copyable_v<PlayerRecord>);
static_assert(offsetof(PlayerRecord,field_a8)==0xa8);
static_assert(offsetof(PlayerRecord,field_b4)==0xb4);
static_assert(offsetof(PlayerRecord, score) == 0x00);
static_assert(offsetof(PlayerRecord, field_08) == 0x08);
static_assert(offsetof(PlayerRecord, field_2c) == 0x2c);
static_assert(offsetof(PlayerRecord, field_30) == 0x30);
static_assert(offsetof(PlayerRecord, field_38) == 0x38);
static_assert(offsetof(PlayerRecord, field_a4) == 0xa4);
static_assert(offsetof(PlayerRecord, field_a5) == 0xa5);
static_assert(offsetof(PlayerRecord, field_a8) == 0xa8);
static_assert(offsetof(PlayerRecord, field_b0) == 0xb0);
static_assert(offsetof(PlayerRecord, field_b4) == 0xb4);
static_assert(offsetof(PlayerRecord, field_ec) == 0xec);

} // namespace th20

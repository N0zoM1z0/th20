#pragma once
#include "Context.hpp"
#include "PlayerRecord.hpp"
namespace th20 {
// Native flags expose two independent low-bit setters; higher roles are unknown.
struct SessionFlags {
    union {
        std::uint32_t bits;
        struct { std::uint32_t bit0:1, bit1:1, retained:30; } fields;
    };
};
// Two real PlayerRecord values; alignment supplies the trailing four-byte gap.
struct PlayerTable {
    PlayerRecord players[2];
    std::int32_t field_1e0, field_1e4, continue_count;
    std::int32_t field_1ec, field_1f0, field_1f4, field_1f8, field_1fc;
    std::int32_t field_200, field_204, field_208, field_20c, field_210;
    std::int32_t field_214, field_218, field_21c, field_220;
    PlayerTable() noexcept;
    void add_continue_count(std::int32_t delta);
    PlayerRecord& player(std::int32_t index);
    std::int32_t mode();
    std::int32_t clamped_field_1fc();
    std::int32_t clamped_field_204();
    std::int32_t clamped_field_208();
};
// Actual process Session. Native construction and accessors establish every
// subobject below. Original scalar names retain their offsets and uncertainty.
struct Session {
    Context contexts[2];
    std::uint64_t field_60;
    std::int32_t field_68;
    SessionFlags flags;
    std::int32_t field_70, field_74, field_78, field_7c, field_80;
    PlayerTable table;
    double field_2b0;
    std::int32_t field_2b8, field_2bc;
    Session() noexcept;
    void increment_continue_count();
    void set_flag0(std::uint32_t value);
    void set_flag1(std::uint32_t value);
    Context& context(std::int32_t index);
    PlayerTable& player_table();
    std::int32_t mode();
    std::int32_t clamped_field_1fc();
    std::int32_t clamped_field_204();
};
extern Session session;
PlayerTable& player_table();
PlayerRecord* player_record(std::int32_t index);
EnemyController* enemy_controller(std::int32_t index);
static_assert(sizeof(PlayerTable) == 0x228);
static_assert(offsetof(PlayerTable,field_1e0) == 0x1e0);
static_assert(offsetof(PlayerTable,field_220) == 0x220);
#if defined(_M_IX86)
static_assert(sizeof(Session) == 0x2c0);
static_assert(offsetof(Session,field_60) == 0x60);
static_assert(offsetof(Session,flags) == 0x6c);
static_assert(offsetof(Session,table) == 0x88);
static_assert(offsetof(Session,field_2b0) == 0x2b0);
#endif
}

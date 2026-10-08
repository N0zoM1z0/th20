#include "Session.hpp"
#include <algorithm>
namespace th20 {
PlayerTable::PlayerTable() noexcept
    : field_1e0(1), field_1e4(0), continue_count(0),
      field_1ec(0), field_1f0(0), field_1f4(0), field_1f8(0), field_1fc(0),
      field_200(-1), field_204(-1), field_208(0), field_20c(0), field_210(0),
      field_214(0), field_218(0), field_21c(0), field_220(-1) {}
Session::Session() noexcept
    : field_60(0), field_68(0), flags{}, field_70(0), field_74(0),
      field_78(0), field_7c(0), field_80(0), field_2b0(0.0), field_2b8(0), field_2bc(1) {}
Session session;
Context& Session::context(std::int32_t index) { return contexts[index]; }
PlayerTable& Session::player_table() { return table; }
PlayerTable& player_table() { return session.player_table(); }
PlayerRecord* player_record(std::int32_t index) {
    return session.context(index).player_record();
}
PlayerRecord& PlayerTable::player(std::int32_t index) { return players[index]; }
std::int32_t PlayerTable::mode() { return field_1e0; }
std::int32_t Session::mode() { return table.mode(); }
std::int32_t PlayerTable::clamped_field_1fc() {
    field_1fc = std::clamp(field_1fc,0,999); return field_1fc;
}
std::int32_t PlayerTable::clamped_field_204() {
    field_204 = std::clamp(field_204,-1,9999); return field_204;
}
std::int32_t PlayerTable::clamped_field_208() {
    field_208 = std::clamp(field_208,0,99999); return field_208;
}
std::int32_t Session::clamped_field_1fc() { return table.clamped_field_1fc(); }
std::int32_t Session::clamped_field_204() { return table.clamped_field_204(); }
EnemyController* enemy_controller(std::int32_t index) {
    return session.context(index).enemy_controller();
}
void PlayerTable::add_continue_count(std::int32_t delta) {
    continue_count = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(continue_count) + static_cast<std::uint32_t>(delta));
    continue_count = std::clamp(continue_count,0,9);
}
void Session::increment_continue_count() { table.add_continue_count(1); }
void Session::set_flag0(std::uint32_t value) { flags.fields.bit0 = value; }
void Session::set_flag1(std::uint32_t value) { flags.fields.bit1 = value; }

} // namespace th20

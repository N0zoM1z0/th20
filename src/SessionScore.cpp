#include "Session.hpp"
#include "PlayerRecord.hpp"

namespace th20 {

void PlayerRecord::add_score(std::uint64_t amount) {
    score += amount / 10;
    if (score >= 1000000000u)
        score = 999999999u;
}

void Session::add_score(std::uint32_t amount) {
    auto& values = table;
    auto& record = values.player(0);
    record.add_score(amount);
}

} // namespace th20

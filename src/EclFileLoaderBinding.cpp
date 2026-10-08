#include "EclFileLoader.hpp"
#include "Session.hpp"

namespace th20 {
void EclFileLoader::bind_player(std::int32_t index) {
    player_index = index;
    context = &session.context(player_index);
}
} // namespace th20

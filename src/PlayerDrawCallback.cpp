// Entire original Player draw callback, preserving the forwarded return value.
// The original callback registration/owner remains unclassified.
#include "Player.hpp"
namespace th20 {
std::int32_t player_draw_callback(void* userdata) {
    return static_cast<Player*>(userdata)->draw();
}
}

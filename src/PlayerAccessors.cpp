// Complete game-owned Player fixed position and scalar, and native
// 33-entry fixed-position history array end (no synthetic array storage).
#include "Player.hpp"
namespace th20 {
IntPoint& Player::fixed_position_ref() { return fixed_position; }
void Player::set_clock_scale(float value) { clock_scale = value; }
template<class T, unsigned Count>
T* PlayerValues<T,Count>::end() { return values + Count; }
template IntPoint* PlayerValues<IntPoint,33>::end();
} // namespace th20

// Complete game-owned Player fixed position and scalar, and native
// 33-entry fixed-position history array end (no synthetic array storage).
#include "Player.hpp"
namespace th20 {
IntPoint& Player::fixed_position_ref() { return fixed_position; }
void Player::set_clock_scale(float value) { clock_scale = value; }
template<class T, unsigned Count>
T* PlayerValues<T,Count>::end() { return values + Count; }
template IntPoint* PlayerValues<IntPoint,33>::end();

// Original game-specific 33-frame Player fixed-position history capacity.
// Native 16-byte __thiscall template instantiation at 0x004FFFE0.
template<class T, unsigned Count>
std::uint32_t PlayerValues<T,Count>::size() const { return Count; }
template std::uint32_t PlayerValues<IntPoint,33>::size() const;

// Complete 22B original indexed access to the 33-frame Player fixed
// coordinate history, with signed index as native 8-byte element stride.
template<class T, unsigned Count>
T& PlayerValues<T,Count>::at(std::int32_t index) { return values[index]; }
template IntPoint& PlayerValues<IntPoint,33>::at(std::int32_t index);
} // namespace th20

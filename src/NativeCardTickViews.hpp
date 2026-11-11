#pragma once
#include <cstdint>
namespace th20 {
// Borrowed non-allocating views on the original Card and its HUD owner.
// Real Card storage/offsets are defined in Card.hpp; the HUD prefix before
// +0x3344 remains unspecified, so this is not a fake padded aggregate.
struct NativeCardTickView { std::int32_t update_486f60(); };
struct NativeCardBit8GetterView { std::uint32_t flag8_value_4888a0() const; };
struct NativeCardTickUiView { void clear_ui_flag0_487b90(); };
struct NativeCardTickBombView { bool active_478130() const; };
}

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
// The original registration at 0x00487B10 publishes two C callbacks:
// Update enters our 875B exact Boss; draw enters a separate 797B game
// draw function still not source-exact. Both bridges are distinct 13B heads.
struct NativeCardDrawView { std::int32_t draw_487590(); };
struct NativeCardSetupView { std::int32_t register_callbacks_487b10(std::int32_t index); };
std::int32_t __cdecl card_tick_callback_4885d0(NativeCardTickView* card);
std::int32_t __cdecl card_draw_callback_488680(NativeCardDrawView* card);
}

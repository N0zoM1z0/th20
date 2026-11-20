# Screen rectangle constructor and renderer cache-reset helpers

This checkpoint reconstructs three original native support functions used by the 1407B ScreenInf Graphics rectangle renderer at `0x00423650`.

## `0x0040BC20` — strided constructor loop (56B)

`native_construct_array_40bc20` invokes a `__thiscall` element constructor with each element address in ECX, then advances the base by the caller-supplied stride. The unsigned count is post-decremented exactly as in the native loop. The Screen rectangle path uses it to construct four contiguous 20-byte `ColoredVertex` records with the existing `ColoredVertex::ColoredVertex` head at `0x00423470`.

## `0x00424080` — sprite cache reset (24B)

`NativeAnimationResetHooks::reset_sprite_cache_424080` clears the native AnimationPoolOwner pointer cache at `+0x6000E18`.

## `0x004240A0` — color-mode cache reset (21B)

`NativeAnimationResetHooks::reset_color_cache_4240a0` writes `0xFF` to the native renderer color-mode cache at `+0x6000E0F`.

## Exactness evidence

The canonical units `native_construct_array_40bc20`, `renderer_reset_sprite_cache_424080`, and `renderer_reset_color_cache_4240a0` each passed whole-function C++20 replay: **56/56, 24/24, and 21/21 bytes**, respectively. All three original bodies have no PE HIGHLOW relocations; the constructor loop's indirect constructor call is preserved as a real typed function pointer, not replaced with inline assembly.

# Animation VM Vector2 coordinate normalizer: whole 95B exact

The original `0x00438EB0` is a 95-byte/28-instruction `__cdecl` Animation
VM helper. It normalizes a two-float vector with independent original screen
extents, then clamps negative normalized x and y components to positive zero.
The natural C++ source is `src/AnimationVector2CoordinateNormalize95.cpp`.
The `Vector2*` parameter spelling expresses the actual two-float value layout;
the original i386 ABI remains two pointers and no receiver.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise`
produces the complete **95/95** original function, including the 28 original
instructions and both PE HIGHLOW data references:

| Native field | Role |
| --- | --- |
| `+0x0E` DIR32 | x divisor, 640.0 at `0x0056CDAC` |
| `+0x25` DIR32 | y divisor, 480.0 at `0x0056CDA8` |

The exact original branch form is a strict-negative clamp. It preserves
negative zero and NaN and is not replaced by `std::max`, which would change
NaN behavior. The helper is called by the large Animation VM at `0x0042B5D0`.

`scripts/verify-animation-vector2-coordinate-normalize95-native.py` verifies
the immutable whole-function SHA, complete instruction boundary, return,
absence of E8 and both physical HIGHLOW targets. The canonical one-source
replay is `replay-exact-units.py --source
src/AnimationVector2CoordinateNormalize95.cpp`.

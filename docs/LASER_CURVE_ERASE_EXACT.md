# LaserCurveInf::erase() — exact native path-point erasure

The Curve-family vtable at 0x00571214 dispatches slot +0x44 to
LaserCurveInf::erase() at 0x004C9380. The complete native body is 266 bytes.
Its two integer arguments preserve the original gate: when the second
argument is nonzero and field_6CC is also nonzero, it returns zero without
changing the Laser state.

The active path walks the native LaserCurvePathPoint array at +0x1328 using
the Type2 point count at +0x718 and the original 0x20-byte record stride.
Each record contributes its leading Vector3 position. Every third point
(index modulo 3 equals zero) spawns a bullet animation through the active
Context's BulletController and AnimationFile, using the Type2 color and
script base 0xD4. The method then sets the Laser state to 1 and returns zero.
Unlike the Line and Infinite variants, this Curve path-point handler does not
run the screen-edge predicate or sample the continuous Laser axis.

## Strict replay

The natural C++ implementation in src/LaserCurveErase.cpp strictly replays
266/266 bytes under the pinned MSVC x86 /Od profile. All 238 ordinary bytes
and all seven original call/data relocations match, including the Vector3
constructor, Context/BulletController accessors, AnimationFile spawn and
security-cookie check. No assembly or padding is used.

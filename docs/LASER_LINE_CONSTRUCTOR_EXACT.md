# `LaserLineInf::LaserLineInf()` — exact Line-family constructor

The original Line constructor at `0x004C88E0` is an 88-byte natural C++
initializer list. The original `create_laser` diagnostic identifies the class
as `LaserLineInf`; its factory allocates `0x18F8` bytes and calls this
constructor. The vtable is `0x00571148`, and the recovered class layout in
`src/LaserLineInf.hpp` has the same `0x18F8` extent.

The implementation in `src/LaserLineConstructor.cpp` constructs the common
`Laser` base, installs the Line vtable, constructs `LaserType0Parameters` at
`+0x6F8`, then constructs three real `Animation` members at `+0x74C`, `+0xD30`
and `+0x1314`. The Type0 constructor is explicitly `noexcept`, matching its
native no-extra-EH construction path and allowing the derived constructor to
retain the native compact prologue.

## Strict replay receipt

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` replay is **88/88 exact**. All 64 ordinary bytes and all six original
relocation destinations match: base `Laser` constructor, Line vtable, Type0
parameter constructor, and three `Animation` constructors. No alignment bytes
or machine padding are included in the function's coverage.

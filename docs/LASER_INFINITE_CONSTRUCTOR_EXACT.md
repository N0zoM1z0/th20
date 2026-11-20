# `LaserInfiniteInf::LaserInfiniteInf()` — exact concrete-family constructor

The Infinite-family constructor at `0x004C8880` is an 87-byte natural C++
constructor. `src/LaserInfiniteConstructor.cpp` expresses the native member
order directly: construct the common `Laser` base, install the Infinite vtable
`0x005712E8`, construct `LaserType1Parameters` at `+0x6F8`, zero the word at
`+0x76C`, and construct the two `Animation` subobjects at `+0x770` and
`+0xD54`. The complete object size is `0x1338`, independently asserted in
`LaserInfiniteInf.hpp`.

The Type1 parameter constructor is explicitly `noexcept`: its native body
initializes two Vector3 subobjects, scalar parameters, the native growth-speed
constant and the real PMR command vector without an EH frame. This lets the
concrete constructor retain the original no-extra-EH layout while the base
Laser constructor remains independently potentially throwing.

## Strict replay receipt

The canonical MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` replay is **87/87 exact** with no padding or alignment credit. All 67
ordinary bytes and all five relocations match their native destinations: the
Laser base constructor at `0x004C85B0`, Infinite vtable `0x005712E8`, Type1
parameter constructor at `0x0047C030`, and both Animation constructors at
`0x00448B40`. The following nine native `INT3` bytes are alignment outside
the function and are not counted.

# `LaserBeamInf::LaserBeamInf()` — exact type-3 Beam constructor

The original type-3 branch diagnostic at `0x00571508` names the concrete
class `LaserBeamInf`. Its native factory at `0x004C8020` allocates `0x1D30`
bytes and calls the 122-byte constructor at `0x004C8390`. That constructor
installs vtable `0x00571374`, whose circle-cancel slot `+0x30` inherits the
15-byte `Laser::cancel_circle()` default. This is distinct from the type-2
`LaserCurveInf` class, which is `0x1370` bytes and owns the path-point cancel
handler at `0x004CA830`.

The natural C++ layout in `src/LaserBeamInf.hpp` is: `Laser` base `+0x000`,
`LaserType3Parameters` `+0x6F8`, `Animation` `+0x748`, one float `+0xD2C`,
and two actual 0x800-byte storage arrays at `+0xD30` and `+0x1530`. The arrays
are value-initialized in C++, producing the two native `memset(0, 0x800)`
calls. They are real zeroed storage, not padding.

## Strict replay receipt

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` replay is **122/122 exact**. All 98 ordinary bytes and all six original
relocation destinations match: base constructor, vtable, Type3 parameter
constructor, Animation constructor, and both `_memset` calls. The Type3
parameter constructor is `noexcept`, matching its native no-extra-EH member
construction boundary.

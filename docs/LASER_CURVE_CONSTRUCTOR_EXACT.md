# `LaserCurveInf::LaserCurveInf()` — exact type-2 Curve constructor

The original type-2 branch diagnostic at `0x00571550` names the concrete class
`LaserCurveInf`. Its native factory at `0x004C8080` allocates `0x1370` bytes
and calls the 159-byte constructor at `0x004C8410`. That constructor installs
vtable `0x00571214`, whose circle-cancel slot `+0x30` is the natural-C++
`LaserCurveInf::cancel_circle()` implementation at `0x004CA830`.

The constructor's natural C++ initializer list restores the real member graph:
`Laser` base, `LaserType2Parameters` at `+0x6F8`, two `Animation` members at
`+0x754` and `+0xD38`, a float at `+0x131C`, four scalar/pointer lanes through
`+0x132C`, and `LaserCurvePathState` at `+0x1330`. The `+0x131C` float is the
native `1.1f` constant at `0x0056F798`; it is not integer `1`.

## Strict replay receipt

The locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` replay is **159/159 exact**. All 131 ordinary bytes and all seven
original relocation destinations match, including both Animation calls, the
original `1.1f` data relocation and the separately exact path-state constructor
call. The Type2 parameter constructor is explicitly `noexcept`, matching its
native no-extra-EH member construction boundary.

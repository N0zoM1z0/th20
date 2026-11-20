# `LaserBeamInf::initialize_laser()` — exact type-3 initialization

The original type-3 initializer at `0x004D3110` is the `+0x14` virtual slot
for the `0x1D30`-byte `LaserBeamInf` object. Its natural C++ implementation
in `src/LaserBeamInitialize.cpp` is a complete 275-byte strict match.

The method copies the Type3 parameter block, sets the native Laser state and
position, binds the selected Session Context, installs the parameter length,
angle, field discriminator and handle, fills all 512 float entries at
`+0xD30` from `Laser+0x74`, writes the original `1.0f` global at `+0x78`,
clears `+0xD2C`, then resets the real Animation subobject at `+0x748` and sets
its native byte-01 flag. The second 0x800-byte storage lane at `+0x1530` is not
touched by this initializer.

## Strict replay receipt

The pinned MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc` replay is **275/275 exact**. All 255 ordinary bytes and all five
original relocation destinations match: Type3 parameter assignment at
`0x004C8C90`, Laser context selection at `0x004D7DD0`, the native 1.0f
constant at `0x0056C8CC`, `Animation::reset` at `0x004299D0`, and the original
byte-01 helper at `0x0045E5B0`. The Type3 parameter assignment is maintained
as a separate natural C++ helper; its own duplicate +0x38 alias store has a
six-byte register-scheduling difference and receives no exact credit.

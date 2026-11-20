# Beam path-state constructor — exact native boundary

The constructor at `0x004C82C0` owns a 64-byte subobject placed at
`LaserBeamInf + 0x1330`. Its complete executable function body is 190 bytes.
The following five `INT3` bytes are section alignment and are compared
separately; they are not counted as function coverage.

The natural C++ constructor in `src/LaserBeamPathState.cpp` reproduces the
original member initialization order: scalar words at offsets `+0x00`, `+0x04`,
`+0x08`, `+0x0C`, `+0x10`; real `Vector3` constructors at `+0x14` and `+0x20`;
a real `Angle(0.0f)` constructor at `+0x2C`; and zeroed float lanes at
`+0x30`, `+0x34`, and `+0x38`. The final word at `+0x3C` is deliberately not
initialized, matching the native body.

## Strict replay receipt

Under the locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` profile, the complete COFF contribution is 195 bytes: 190 bytes
of constructor body plus five alignment bytes. The canonical replay compares
all 195 bytes, matches all 175 non-relocation bytes, and resolves all five
original relocations (EH handler, security cookie, two `Vector3` constructors,
and `Angle(float)`) to their original destinations. No assembly, source padding,
or duplicate byte credit is used. The C++ type spelling is reconstructed from
the observed subobject role; original source name and authorship remain unknown.

The authored classification is medium-confidence and independent of byte
matching: the 64-byte subobject is constructed at a fixed `LaserBeamInf`
member offset by the distinct game Beam constructor, and its scalar/member
initialization is part of the game-owned object lifecycle. The original class
spelling and source file are still inferred.

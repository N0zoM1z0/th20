# CORE/EXACT-376 — six entire Angle/Animation drawing ABI helpers, 372 native bytes

The immutable user-selected original is Japanese TH20 v1.00a Steamless,
whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Six **distinct physical whole native functions** already had natural,
type-correct maintained C++20 source in `src/Angle.cpp`,
`src/AnimationParameters.cpp`, and `src/ClockScalar.cpp`, but had
remained marked `reconstructed` in the original tracking ledger. Their
existing canonical compiler objects were independently checked against
the complete original native PE and now promoted to **strict exact**,
without rewriting code or inventing new object owners:

| Original native function | Physical entry | Entire native extent | Original SHA-256 |
| --- | --- | ---: | --- |
| `normalize_angle` | `0x00438540` | **187B / 47 instructions** | `25ea65cdf8d60f41fb1042d65b25099a6bfd6f4839da270149e6d6ec96ba2070` |
| `add_angles` | `0x00438600` | **29B / 10 instructions** | `b2e5c83e215d0bcd9e5b48def193ed9bc6ec12aa83f77f8698c6e8c98a41f11c` |
| `Animation::set_rotation` | `0x00450590` | **33B / 13 instructions** | `e607cb0ac5b758812bf387d2e36f57a4c85ca07d651466bf2de4bcc05c16c8d6` |
| `Animation::set_rotation_z` | `0x004505C0` | **47B / 15 instructions** | `46839d3538cfe9a767e11aa9862990439d31b44c82cacb0d0805203b25ecd1ce` |
| `Animation::set_scale_58` | `0x004864F0` | **60B / 18 instructions** | `fd5e1e065f7e3e3be99f84df9fdaddfb9901b946a1e6fc79eaeac577a6c7ae91` |
| `ClockScalar::operator float` — folded `Angle` alias | `0x004292E0` | **16B / 9 instructions** | `b78458fac1588efb66e0042f43bbd25e774fa5c22c3d5210ba70e30213820e51` |

Total: **372 new original exact bytes**, six nonoverlapping original
physical addresses, **112 independent original instructions**.
The original 273-byte `BulletController::draw_group` at `0x0047DB70`
uses the 16B float converter, 29B angle addition, 33B rotation setter
and 60B scale setter. Its *whole caller* is still independently
**NONEXACT** (currently 283B emitted versus 273B original) and
receives **zero exact credit** in this checkpoint.

## Whole native gameplay and all independently original references

The original 187-byte `normalize_angle` performs the bounded original
±π reduction and preserves the original signed comparisons, float
rounding and native loop break protocol. Its original PE `.reloc`
independently specifies **eight HIGHLOW / DIR32 fields** at
`+0x0E`, `+0x1F`, `+0x27`, `+0x58`, `+0x64`, `+0x79`,
`+0x81` and `+0xAA`. Their actual original targets are the
native 32-bit floats at `0x0056E0F0` (+π),
`0x0056E0F8` (-π), and `0x0056C8D0` (2.0f).
Its natural maintained C++ emits **187/187 strict exact native bytes**,
including all 47 original instructions and eight independent references.

`add_angles` is the full native 29-byte wrapper computing the real
two-float addition then calling the original `normalize_angle` at
`0x00438540`: its sole native E8 field at `+0x14` agrees with the
real COFF symbol and original target. The 33-byte Animation
`set_rotation` wrapper has its sole E8 field at `+0x16` targeting
the separate, entire original `Animation::set_rotation_z` at
`0x004505C0`. The 47-byte setter stores the genuine Z rotation
in the native AnimationBase vector and sets native word-flag bit 1;
the 60-byte `set_scale_58` stores both real float components into
the native Animation vector and sets actual word-flag bit 2. Both
setters have **no static external relocations**. All complete source
bodies reproduce original class members, field offsets and return ABI.

The 16-byte float accessor is a case of **linker-equivalent source
folding**. Both currently maintained
`ClockScalar::operator float() const` (in `src/ClockScalar.cpp`)
and `Angle::operator float() const` (in `src/Angle.cpp`)
independently compile to the *same complete 16-byte original
instruction sequence at physical `0x004292E0`*. The original
inventory already maps that physical entry to `ClockScalar`.
Only **one strict unit** is accepted there through the existing
`ClockScalar` canonical owner; no second `Angle` unit, additional
16-byte credit, or duplicate match row was created. The
`BulletController::draw_group` path is a legitimate caller of
the same 16-byte physical native conversion body.

Independent evidence `.analysis/core376-original-leaf-independent-relocations.json`
was produced by decoding original whole PE E8 call operands and
original `.reloc` HIGHLOW fields **before** promoting any ledger
row. All 10 original nonempty relocation fields across the six
functions match the complete existing COFF function body at the same
native offset/type and independently observed target, with **zero
relocation mismatches**. The remaining three whole methods contain
no external relocation fields.

## Original locked compiler objects and exact affected-only cold replay

These sources were **already source-present**, with real class
interfaces and exact locked MSVC object receipts. No source or public
header change was needed. Retained owner profiles:

- `src/Angle.cpp`: C++20, MSVC i386 `/Od /Ob0 /GS- /fp:strict`,
  preserving its existing native angle reduction and wrapper bodies
- `src/AnimationParameters.cpp`: C++20 i386 `/Od /Ob0 /GS
  /fp:precise /sdl /EHsc`, preserving all Animation member offsets
- `src/ClockScalar.cpp`: C++20 i386 `/Od /Ob0 /GS-
  /fp:precise`, crediting only its one folded original physical entry

The precise change scope is **three already canonical source/object
providers** with **30 previously exact units + six newly promoted**.
A filtered actual cold replay
`scripts/replay-exact-units.py --source src/Angle.cpp --source
src/AnimationParameters.cpp --source src/ClockScalar.cpp`
passed **36/36 strict native units across three cold objects**.
Private complete strict log:
`.analysis/core376-angle-animation-replay.log`.

No unrelated source/header cold replay, original PE modification,
manual assembly, instruction padding or exactness relaxation was used.
This closes real callee ABI boundaries needed by the *still nonexact*
273-byte Bullet single-group drawing boss; it does not claim that
whole caller, the 5,993-byte native Renderer draw, or whole game
runtime equivalence is complete.

# CORE/RECON-810 — correct original 16B STL array range-failure boundary; 60B+34B+16B strict exact

The immutable original Japanese TH20 v1.00a Steamless binary is fixed by
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

This checkpoint extends [the complete 60B game texture-lookup and 34B
checked `std::array::at` proof](ANIMATION_TEXTURE_LOOKUP_60_AND_STL_ARRAY_34_STRICT.md)
to a **third original physical whole-native function**, the authentic
MSVC STL out-of-range helper
`std::array<th20::AnimationFile*,42>::_Xran` at
**`0x00428C80..0x00428C8F`**, **16/16 original code bytes /7 i386
instructions**. Its original function boundary was wrongly listed as
**13 bytes** by the initial automatic Ghidra function inventory, which
truncated the original last `nop; pop ebp; ret` epilogue. Re-reading the
real immutable original x86 resolves that mistake. The new 16B entire
original body is accepted as **library**, excluded from authored game
method and game `.text` byte counts.

The original 34B `std::array<AnimationFile*,42>::at` uses a genuine
unsigned index check against 42/`0x2A`. On out-of-bounds index its real
`E8` at `0x0043EB1D` calls this physically separate `_Xran` at
`0x00428C80`. The range-failure method pushes an actual original
**PE HIGHLOW** `0x00428C84` pointer to the immutable
**30-byte NUL-terminated string** at `0x0056DC28`:
`invalid array<T, N> subscript`, and physically calls the original
library `std::_Xout_of_range` at **`0x00540EF5`** through its real E8
at `0x00428C88`, displacement field `+0x9`.

The entire 16B original native body is independently attested:

```text
00428C80  push ebp
00428C81  mov ebp, esp
00428C83  push 0x0056DC28
00428C88  call 0x00540EF5
00428C8D  nop
00428C8E  pop ebp
00428C8F  ret
```

The one maintained real C++ source `src/AnimationTextureLookup.cpp`
instantiates both original genuine `std::array::at` and `_Xran` library
methods naturally, as well as the enclosing original 60B authored
game `AnimationQuadSubmitOwner::texture_for_sprite`. The fixed MSVC
19.44.35211 x86 compiler emits all three with their true original
symbol types, original call references and original data target string;
**each complete body and all relocations match exactly**, including the
16B real original epilogue and independent PE HIGHLOW and E8 targets.
The three exact canonical units are
`animation_texture_lookup_60` (game),
`animation_texture_array_at_34` (library) and
`animation_texture_array_xran_16` (library).

Focus replay and original-PE verification:

    scripts/repo-python scripts/verify-animation-texture-lookup-native.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationTextureLookup.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target

**3/3 complete exact methods from one new canonical source/object**;
only **60B/one whole function** adds to original authored gameplay.
The remaining **34B+16B =50B** are original STL library code, excluded
from game-authored credit, and the original 30B diagnostic string is
original data rather than extra `.text` game code. Only this one new
translation unit was cold replayed; previous old canonical compiler
sources/headers affected **zero**, no full cold replay. This refines
source-present mapped methods and strict units **1,233 →1,236**,
protected canonical object/receipt providers **256 →257**, and distinct
physical original game functions **586 →587**, with their total
nonoverlapping authored game bytes **189,564 →189,624**. The separate
original 3,159B quad submit and 5,993B Animation draw parents still
remain SOURCE-PRESENT but **NONEXACT**.

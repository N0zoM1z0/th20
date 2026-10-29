# CORE/RECON-809/810 — original 60-byte game texture lookup and its genuine 34-byte STL checked array access strict exact

> **Subsequent CORE/RECON-810:** The authentic third original compiler-library method `std::array<AnimationFile*,42>::_Xran` is **16/16B/7-i386 exact** and the original Ghidra 13B provisional boundary was wrong. The *one same source* now has **3/3** whole strict units (60B game +34B/16B library), one new object. [Original 16B range-failure proof](ANIMATION_TEXTURE_LOOKUP_60_STL_ARRAY_34_16_EXACT.md). Some two-unit counts below describe the preceding investigation, not current state.

The original immutable Japanese TH20 v1.00a Steamless executable has
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint closes one **complete original game-owned 60B/21-i386
renderer texture lookup at `0x00445A00`**, and one separate
**34B/14-i386 original MSVC STL `std::array<AnimationFile*,42>::at`
at `0x0043EB10`**. Both are pinned-compiler **whole-native strict exact**;
**only 60B is new original authored game code**. The 34B child is
compiler/STL library-owned, explicitly excluded from authored-game counts.
The **3,159B** enclosing quad submit Boss remains SOURCE-PRESENT/NONEXACT
and no whole-game linker/executable playability is asserted.

## The genuine game texture lookup, exact native fields and ABI

The immutable original `0x00445A00..0x00445A3B` body uses an ECX receiver
that matches the existing no-storage `AnimationQuadSubmitOwner` C++ source
ABI. At native owner offset `+0x06000730` lives a real fixed-length array
of **42 `AnimationFile*` pointers**. The incoming 32-bit texture ID is
split by an actual signed arithmetic right-shift of eight (`sar ecx,8`)
for the **file-array index** and an unsigned low-byte mask (`and eax,0xff`)
for the **within-file texture index**. The original code indexes the real
`AnimationFile::textures` pointer at file offset **`+0x58`**, multiplies
the low-byte index by the genuine **24B/0x18 `TextureRecord` stride**, and
returns the actual `IDirect3DTexture9*` pointer at the beginning of that
record. The C++ return type `IDirect3DBaseTexture9*` is ABI-compatible
because the D3D9 texture interface derives from the base texture interface;
no fake separate global texture owner or unexplained source-level cast is
needed. Native x86 size assertions cover the `TextureRecord` and
`AnimationFile` layouts.

The entire original game body is **60B, 21/21 x86 instruction heads and
one genuine `E8` instruction at `0x00445A1E`**. Its signed displacement
physically resolves to `0x0043EB10`. It has **zero genuine original PE
HIGHLOW fields**. One maintained natural C++ expression reproduces it:

```cpp
return files.at(static_cast<std::int32_t>(id) >> 8)
    ->textures[id & 0xffu].texture;
```

The first typed probe that introduced an intermediate `AnimationFile*`
local variable compiled to **66B/23 i386** rather than the original
60B/21. Removing the unnecessary but real intermediate variable gives
the entire original **60/60 native instruction-byte sequence** apart
from the one actual relocatable E8 field. This is natural source-level
value lifetime recovery, not an assembler patch or a prefix comparison.

## Why `std::array::at` matters: a genuine checked 34B STL helper

The original `0x0043EB10..0x0043EB31` is a separate **34B/14-x86
compiler library method**. Its native `cmp [ebp+8], 0x2a` tests exactly
**42** entries, and the original `jb` condition falls through only
when the index is within the array. On out-of-range input it makes a
true direct E8 at `0x0043EB1D` to `0x00428C80`, the original array
range-error path; on accepted input its original
`lea eax,[ecx+eax*4]` forms the native four-byte pointer slot address.
The method ends in the entire original `ret 4`, with zero original PE
HIGHLOW fields and one real E8 relocation.

The source's **`files.at(...)`** is essential to the exact **COFF
symbol identity**: using unchecked `files[...]` generated a similar
60-byte game method, but its relocation referred to a **different
`operator[]` symbol**, not the actual checked original library member.
We re-reviewed the original 34B native range guard rather than trusting
that initial codegen similarity. With `.at`, the one new object contains
both the original 60B game method and genuine
`std::array<th20::AnimationFile*,42>::at`; both have the correct real
COFF symbol and original-PE call targets. The 34B STL method is
classified `origin=library`, `disposition=exclude`, and contributes
**zero** original authored game bytes. Its E8 target `0x00428C80`
remains a separate original library/error helper, not newly game-owned.

## Independent physical original proof and changed-only canonical replay

The new standalone original-PE verifier
`scripts/verify-animation-texture-lookup-native.py` disassembles both
complete physical native bodies from the immutable original executable,
checks the true file+texture address and index operands, complete returns,
zero original HIGHLOW for each method, and the two genuine physical E8
origins (`0x00445A1E→0x0043EB10` and
`0x0043EB1D→0x00428C80`). It is independent of our C++ compiler
candidate and original Ghidra provisional names.

Pinned MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` compiles **one new source**
`src/AnimationTextureLookup.cpp` to
`build/core809-canonical/AnimationTextureLookup.obj` with its genuine
compiler receipt. Its two whole canonical units are:

- `animation_texture_lookup_60`: complete **60/60 original authored
game bytes**, one actual original E8 to the library helper.
- `animation_texture_array_at_34`: complete **34/34 original STL/library
bytes**, one actual original E8 to the range-error helper, **excluded
from authored game exact coverage**.

Reproduce only the changed source and independent original PE:

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-texture-lookup-native.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationTextureLookup.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target

Focused strict replay passed **3/3 whole native functions in one new
cold object/receipt**. No older shared header, protected canonical source,
prior acceptance fixture or compiler profile changed; old affected native
replay scope is **zero**. No unfiltered full cold replay was performed.

Live original authored whole strict counts advance from **586 to 587
distinct physical game functions** and **189,564 to 189,624 native
original game bytes**. Both new whole native mappings raise source-present
**1,233→1,236**, strict canonical units **1,233→1,236** and distinct
protected compiler objects/receipts **256→257**. The library addition
is a real canonical strict unit but not a game-authored function.
The separate 3,159B submit Boss and 5,993B parent Animation draw Boss
remain NONEXACT, as do 12,140B Bullet commands, 41,967B Enemy ECL and
39,470B ANM VM giant original functions.

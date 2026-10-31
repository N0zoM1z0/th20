# CORE/RECON-1090 — complete original 40B Renderer 42-file AnimationFile lookup, whole strict exact

Immutable Japanese TH20 Steamless v1.00a target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The previously source-absent game-owned `0x00437970` is now a whole
**40B/15-instruction i386** `AnimationPoolOwner::file_by_index`
method, entire original native SHA-256
`8b9fce492db39f692e526a4181a320e25860bcf30fed6c69430d98f68ff2a3f9`.
It is a genuine game Renderer resource lookup, not another alias for
the already exact folded `std::array::operator[]` method.

The original native file registry lives at Renderer instance
**`this+0x06000730`**, an actual array of **42 `AnimationFile*`
pointers**. The original function constructs a borrowed view of
that array, indexes by the live signed 32-bit stack argument, and
returns the actual file pointer. The original complete 40B has
**one E8 at `+0x1B` to `0x00414580`**, a separate previously
accepted complete **22B** four-byte array-index method; it has
**zero PE HIGHLOW** and ends at genuine `ret 4`. There is no
null check, generation check, hidden allocation or independent
file ownership invented in the C++ source.

The meaningful
[`src/AnimationFileByIndex40.cpp`](../src/AnimationFileByIndex40.cpp)
uses the existing real `AnimationPoolOwner` class and actual
`std::array<AnimationFile*,42>` at the observed owner displacement.
Under pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` it
naturally reproduces the **whole original 40B/15 instructions**,
**36/36 native nonrelocated bytes**, and original unique E8
relocation at COFF field `+0x1C ->0x00414580` without introducing
a second renderer instance or padded owner class.

This completes an important actual game caller/callee triangle:
original AnimationBase **`+0x18`** file getter `0x00437470`
(whole exact 29B) and **`+0x1C`** getter `0x00437500`
(previously whole exact 29B) both physically call this **same**
40B game file registry at their genuine E8 `+0x14`. The new
[118B whole-exact Animation handle rebind](ANIMATION_HANDLE_REFRESH_118_29_STRICT_EXACT.md)
then uses the distinct +0x18 route and, after spawning a new
handle, republishes actual file identifiers to both original
AnimationBase slots. The two 29B functions are distinct original
function heads, but this 40B underlying table lookup exists at
**one original address only**. No helper or caller code is
recredited as part of this 40B new game function.

Independent read-only
[`verify-animation-file-by-index40-native.py`](../scripts/verify-animation-file-by-index40-native.py)
SHA-attests the entire original 40B/15 machine code, the full
original 22B folded array-index method, and the actual original
E8 from both 29B file getters. It verifies the unique real
COFF/PE relocation target and whole pinned canonical receipt:

```text
animation_pool_file_by_index_40: exact (40/40 bytes)
Exact replay: 1/1 units, 1 affected cold object
```

This contributes **one new distinct game-authored exact physical
native function /40 original executable `.text` bytes**. The
previously accepted 22B folded `std::array::operator[]` is generic
code and receives no new authored-game credit; the 118B and two
29B game functions are independently accounted for. The overall
project still lacks full executable linkage and playability; this
source unit was verified without any entire-project cold replay.

```sh
scripts/repo-python scripts/verify-animation-file-by-index40-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFileByIndex40.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

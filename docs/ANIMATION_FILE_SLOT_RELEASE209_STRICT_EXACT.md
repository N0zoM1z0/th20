# CORE/RECON-971 — complete 209B RendererPool 42-slot `AnimationFile` release strict exact

Locked Japanese TH20 Steamless v1.00a original SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0044C430` is the complete game-owned **209B/61-i386**
RendererPool entry-level `AnimationFile` lifetime release, physically
called by numerous original frame/resource clients. It owns no
additional file storage in the maintained source: the original pool
has a **42-element pointer table at receiver `+0x06000730`**.

[`scripts/verify-animation-file-slot-release209-native.py`](../scripts/verify-animation-file-slot-release209-native.py)
reads the immutable original PE and verifies all 209 executable bytes,
61 instructions, native `ret 4`, every original **eight E8 site/target
pairs**, one physical allocator HIGHLOW `+0x87 -> 0x005B8894`,
original 42-entry range test and `+0x06000730` array address:

| Original E8 offset | Physical original destination |
| --- | --- |
| `+0x18` | `0x00450870`, actual `std::array<AnimationFile*,42>::size()` returning 42 |
| `+0x39` | `0x0043EB10`, previously whole exact `std::array<AnimationFile*,42>::at()` |
| `+0x5A/+0x79/+0xA3/+0xC0` | `0x00414580`, actual physical folded `std::array::operator[]` 4-byte index implementation |
| `+0x61` | **`0x0044AB00`** independently exact [284B `AnimationFile::clear()`](ANIMATION_FILE_CLEAR284_STRICT_EXACT.md) |
| `+0x8B` | `0x00447330`, actual 103B allocator file-object pointer retirement, **separate open source** |

The method checks signed index nonnegativity, the actual unsigned 42
bound, and file-slot non-nullness. It then clears the file, retires the
allocated `AnimationFile*` through a pointer-to-pointer object owner,
and **sets its table entry to null twice** as the original `/Od` code
does. The repeated store is retained, not optimized out by hand.

[`src/AnimationFileSlotRelease209.cpp`](../src/AnimationFileSlotRelease209.cpp)
uses a natural existing `std::array<AnimationFile*,42>` view and
[`src/NativeFileClearPoolView.hpp`](../src/NativeFileClearPoolView.hpp),
the same original-backed pool owner ABI shared with independently exact
284B file clearing and 94B texture release. No 96MB owner allocation,
manual x86, fake padding or relocated original target-byte copies.

A first source cached the table pointer and emitted **147B**, short of
the original by 62B. Recomputing the actual receiver+offset for each
array access emitted **212B** and the same original 60 native instruction
heads except the initial branch scheme. The faithful original unoptimized
lexical guard contains an intentionally **empty invalid-index branch**,
then the active cleanup branch. This naturally makes MSVC emit two
short `jl/jb` and the actual `jmp` rather than two 6B long conditional
branches; it produces the **entire original 209B/61 i386** body.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` delivers **173/173 nonrelocated bytes and
all nine genuine original relocation fields**. Original-target-bound
local replay included the affected resource lifecycle chain:

```text
animation_file_slot_release_209: exact (209/209 bytes)
animation_file_clear_284: exact (284/284 bytes)
animation_texture_record_release_94: exact (94/94 bytes)
Exact replay: 3/3 units, 3 cold objects
```

This credits **one new original game-authored 209B head/+209 native
`.text` bytes**; it does not double-credit the 284B parent File clear
child, 94B texture retirement or folded STL methods. The 103B allocator
retire, 691B Renderer detachment and full pool allocation/linking
remain separately unresolved. No global cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-file-slot-release209-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationFileSlotRelease209.cpp --source src/AnimationFileClear284.cpp --source src/AnimationTextureRelease94.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

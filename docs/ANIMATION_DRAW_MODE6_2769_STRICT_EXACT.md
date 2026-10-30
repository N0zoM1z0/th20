# CORE/RECON-844 — complete original 2,769B Mode6 renderer Boss, 2,792B strict canonical exact

The immutable locked Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a whole original game-authored Animation mode6 renderer method
at **`0x004408B0`**. It is an entire **2,769B /683 original x86 instruction
head** function with original `sub esp,0x64` and `ret 4`, not a short
leaf/prefix. The function's native body is followed by **3B original compiler
alignment** and **five real 4-byte mode-switch pointer fields**, so its true
whole COFF/native comparison extent is **2,792B**. The surrounding original
5,993B Animation Draw dispatcher at `0x00443880` calls this physical head,
but that separate enclosing dispatcher remains **SOURCE-PRESENT/NONEXACT**.

The maintained ordinary C++
[`src/AnimationDrawMode6.cpp`](../src/AnimationDrawMode6.cpp) now builds under
the pinned x86 MSVC 19.44.35211 profile
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
with **all 2,769B /683 original executable instructions, exact native
`0x64` frame, all 111 original relocations**, and the original genuine
3B alignment/five-pointer table. **Complete strict canonical result:
2,792/2,792 bytes, zero differences.** The one actual original 2,769B
game function is credited **once**; the NOP/table data are strictly verified
but are not credited as game `.text` function bytes.

## Independent original PE census and source-replay proof

The independent
[`scripts/verify-animation-draw-mode6-native.py`](../scripts/verify-animation-draw-mode6-native.py)
extracts the entire original game `.text` extent, disassembles the
complete 683 native i386 heads, and reads actual PE `.reloc` HIGHLOW
entries. It independently attests all **28 E8 instruction sites and native
callee heads**, all **78 in-body HIGHLOW physical site/target identities**
and the five after-RET original case pointers. It also checks native
`COMISS/JBE` fog handling, original case entry instruction-head validity,
real `0x64` frame and the original 3B alignment, independently of the
candidate C++ source or object.

| Entire original extent | Independent exact source/native replay |
| --- | --- |
| **2,769B /683 real x86** | **2,769/2,769 native executable code exact**, original 683 i386 and frame0x64 |
| **28 actual E8 direct calls** | **28/28 original instruction offsets and independently mapped physical destinations exact** |
| **78 genuine in-body PE HIGHLOW fields** | **78/78 source COFF DIR32 physical offsets, actual global owner/addend/target identities exact** |
| **3B alignment after `ret 4`** | **3/3 original compiler-generated alignment bytes exact** |
| **Five PE-relocated switch pointer fields** | **5/5 original physical offsets and true case-entry targets exact**, same 2/2/1 code-pointer alias partition |
| **Entire 2,792B body + native compiler data** | **2,792/2,792 strict canonical zero-difference relocated bytes** |
| Non-relocated bytes across complete extent | **2,348/2,348 identical** before applying the full original relocation roles |

The original 28 true E8 calls consist of one whole strict original
1,378B Mode6 screen projection setup (`0x00440340`), one genuine Vector3
constructor, two native Vector3 additions and one subtraction, one
complete 25B depth wrapper, **16** original color-channel saturation/tint
calls (`0x0043F520`), **four** original divide-by-255 color-channel
multiply calls (`0x0043F4F0`), the already whole strict 3,159B quad-submit
Boss (`0x0043F6A0`), and the real compiler security cookie check.
The 78 original in-body PE HIGHLOW target classes include 21 actual live
Graphics viewport reads, 42 separate actual quad B/G/R/A channel fields,
eight original 1.0f, two 2.0f, real WindowState scaled dimensions and
448.0f, the compiler cookie, and the genuine case-table base reference.
No external dependency or identical callee is counted again as new exact
source here.

The complete original five case pointers in the actual original PE
`0x00441384..0x00441397` are:

```text
0x004409FC  0x004409FC  0x00440CFE  0x00440CFE  0x004410D2
```

These original case targets are all genuine x86 instruction heads in the
full original function. Their identity and table-base address were
independently established from the original PE before source acceptance.
The generated COFF's *own* local symbol table confirms its actual four
native local symbol values/section and corresponding original target:

| Genuine compiler local symbol | Source-relative offset | Original physical target |
| --- | --- | --- |
| `$LN32` (after-RET table base) | `+0xAD4` | `0x00441384` |
| `$LN7` (case modes 0/1) | `+0x14C` | `0x004409FC` |
| `$LN16` (case modes 2/3) | `+0x44E` | `0x00440CFE` |
| `$LN24` (case mode 4) | `+0x822` | `0x004410D2` |

This is important: a merely *same-sized* candidate with a fabricated
case table would not satisfy the actual COFF symbol offsets, independent
native case instruction heads, the physical original jump-table reference
at body offset `+0x143`, and five independently relocated after-RET code
pointers. There are **83** actual HIGHLOW/DIR32 records in the complete
comparison extent, not merely the 78 body records, and **111 real COFF
relocation records total** including the 28 original E8 REL32 calls.

[`scripts/verify-animation-draw-mode6-source-roles.py`](../scripts/verify-animation-draw-mode6-source-roles.py)
recompiles only this entire source to a separate diagnostic COFF object,
checks original calls/data positions and all four compiler local case
labels, and confirms **2,348/2,348 non-relocation bytes**. Independently,
`config/match-units.toml` explicitly enumerates the original 111 symbol,
type, physical offset and target roles from original game owner/callee
identity, not from solving the PE field being compared. The pinned build
receipt and canonical strict byte replay then establish the stronger
accepted full-native result:

```text
animation_draw_mode6_boss_2769: exact (2769/2769 coverage bytes; 2792/2792 compared bytes)
Exact replay: 1/1 units, 1 cold objects
```

## Correcting previous wrong hypotheses, without fake source padding

The historical [CORE/RECON-843 source frontier](ANIMATION_DRAW_MODE6_2769_FIVE_CASE_SOURCE_FRONTIER.md)
was honest for its earlier MSVC candidate: same source extent but
`682` instructions, frame `0x70`, only 389/2,348 non-relocation bytes
identical, 6 E8 physical sites and 15 HIGHLOW sites aligned. It was a
**candidate-specific state**, not an immutable property of the original
code or proof that the C++ implementation could not become exact.

The corrections below were independently checked against the original
complete native instructions and actual game data, not adjusted by adding
arbitrary unused temporaries or copied machine-code bytes.

1. **Real mode-specific colors live in real shared RGBA locals.** The
   original sources choose color490 or color494 for modes 0/1, two real
   source colors for modes 2/3, and both blended colors for mode 4. Four
   B/G/R/A calls per actual tint and four original divide-by-255 calls
   for mode4 are preserved. In fog branches, the native source writes
   actual shared quad B/G/R/A byte fields directly; an earlier local
   color overwrite erased original data reference identities.
2. **Original float local lifetime recovers the real `0x64` frame.** Modes
   0/1 use one real fog-fade local for both primary fog and later optional
   distance-window alpha adjustments. Mode 4 overwrites the previously
   consumed depth local with the real fog fraction, matching the original
   x87/SSE ownership. Previous extra independently live C++ fade/depth
   values made a larger `0x70`/`0x68` stack. There are no inert locals.
3. **Main default is a genuine first physical mode branch.** The original
   compiler places its real out-of-range default jump before cases 0/1.
   An ordinary C++ `switch` with a leading `default: break;` naturally
   generates that native code order and original five 32-bit case pointers.
4. **The near/far fog branch source order matters.** The original uses
   `COMISS depth,near` and `JBE` to jump to the direct-color branch,
   executing fog interpolation code first when distance exceeds the
   near boundary. Earlier source wrote the near-color branch first and
   reversed the compiler's branch formation, causing hundreds of native
   byte and many relocation-site differences. Expressing the original
   native fog-first ordering in **all three** source case groups recovered
   **28/28 original E8 physical sites, 78/78 body HIGHLOW fields, full
   2,769B code length and native frame** without reordering semantics.
5. **Bit20 test uses the original shift-and-mask protocol.** Original
   instructions at `+0x35B` are `shr ecx,0x14; and ecx,1`, not
   a single `and ecx,0x100000`. Those source expressions test the same
   flag for ordinary integers but generate different native instructions;
   writing the real `(flags.word_04 >> 20) & 1` recovers both operands.
6. **Lower depth bound comparison preserves NaN semantics.** The original
   loads the Animation lower depth bound **first**, then `COMISS` it
   against the current depth and uses original **`JB`** to pass through.
   The previous inverted source `!(depth>lower)` read the operands in the
   opposite order, emitted `JA`, and rejected unordered inputs that the
   original permits. `if (lower >= depth) return -1;` naturally emits the
   entire original operand order, `COMISS/JB` behavior and final remaining
   original machine-code bytes.

The original Mode6 renderer supports all genuine modes 0/1, 2/3 and 4,
with original alpha and RGB fog behavior, original graphics tint,
real four-vertex 28B quad color sharing and the exact original quad-submit
Boss call. None of this proves the *enclosing* 5,993B `AnimationPoolOwner::draw`
parent exact; it is **still a separate source-present/NONEXACT big Boss**.

## Scoped verification and authored-game credit

Only the changed game renderer source `src/AnimationDrawMode6.cpp` is
cold-compiled and replayed as **one newly accepted canonical unit/one
new pinned COFF object/receipt**. There are **zero affected previously
exact C++ sources, shared headers or compiler profiles**. Unrelated
strict units are not recompiled; no whole-graph cold replay is run.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode6-native.py
nice -n 15 scripts/repo-python scripts/verify-animation-draw-mode6-source-roles.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode6.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```

The game-authored exact ledger credits **one complete new original
2,769B game method** and no additional data/table bytes or already
credited child bytes. The live verified totals become **601 distinct
game-authored whole-native exact physical functions /203,872 original
`.text` bytes**, **1,247 source mappings /1,248 strict units /266
canonical pinned compiler objects/receipts**. These numbers describe
verified reconstruction progress; the game as a whole is still not
linked or playable from the maintained sources.

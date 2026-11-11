# The 2,227B Glyph Text Boss: original 22-case font switch and full table

At original `0x00415830`, the Japanese Steamless v1.00a TH20 glyph text
rasterizer has **2,227B of executable code /470 i386 instructions**. Its
original one-byte NOP at `+0x8B3` precedes **22 genuine 32-bit jump
pointers** at `0x004160E4..0x0041613B`. The full physical contribution
is therefore **2,316B**, not merely the 2,227B body; the 22 pointer fields
are independently attested original PE HIGHLOW relocations. The code
itself contains 25 original E8 and 43 in-body HIGHLOW fields, including
one jump-table reference. The original executable SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

## Recovering original per-font semantics

The previous maintained `src/GlyphTextCore2227.cpp` incorrectly grouped
several font indices with identical *eventual* outputs, and omitted their
actual assignments to both the radius and the text baseline. Its compiler
selected only indices 1..21, emitted a subtract-one dispatch and a
21-pointer trailing table, producing 2,080B/486 decoded instructions in
the old diagnostic (which included data misinterpreted as instructions).

The immutable native table instead indexes **0..21 directly** with
**17 distinct target labels**. In original dispatch order, aliases are
`{0,7,11}`, `{6,8}`, `{12,13}` and `{18,19}`; indices 1,2,3,
4,5,14,15,16,17,20 and 21 each have a physically separate, genuine
radius+baseline assignment block even where their values are identical.
The maintained source now spells these true original branches explicitly,
including the `font=0`/default branch. The natural C++ compiler generates
all **22** real case pointers with the **same 17-label alias partition**.
The original path also initializes the base radius and baseline **before**
calling the canvas allocator, which uses the actual original diagnostic
string `D:\cygwin\home\zun\prog\th20\src\core\grpfont.cpp:920 AflDIB`,
not the historical placeholder. This corrects observable initialization
order and genuine native allocation diagnostics without adding dummy code.

## Whole-source compiler comparison

Pinned MSVC 19.44 x86 C++20 (`/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`) now emits a complete **2,316B COFF
contribution**, including a compiler-generated 22-pointer table starting
at the original physical offset `+0x8B4`. The code body in the current
candidate is **2,228B/472 i386**, with its `ret` at `+0x8B3` and no
alignment NOP; the original code is **2,227B/470 i386**, with its `ret`
at `+0x8B2` followed by the NOP. Thus total contribution and pointer
table location match, **but the parent remains NONEXACT**.

| Scope | Previous source | Recovered source | Original |
| --- | ---: | ---: | ---: |
| Complete contribution | 2,080B | **2,316B** | **2,316B** |
| Original in-code E8 / source REL32 | 25 | **25** | 25 |
| Original in-code HIGHLOW / source DIR32 | 33 | **43** | 43 |
| Genuine trailing pointer fields | 21 | **22** | 22 |
| Table alias partition | Wrong | **17/17 correct** | 17 |
| First physically aligned E8 sites | 3 | **4** | 25 |
| Physically aligned in-code data fields | Not admitted | **7/43** | 43 |

The nonrelocated body and most physical field locations still differ. The
first post-switch E8 is candidate `+0x2F3` versus original `+0x2E7`;
no byte-level parent credit is added. Do not equate matching sizes or
alias partitions with exact source.

The current whole-original and candidate check is
[`verify-glyph-text-core2227-native.py`](../scripts/verify-glyph-text-core2227-native.py).
Only the changed C++ translation unit was cold-replayed. Its existing
**132B glyph job capture and 23B destructor both remained strict exact**
(2/2 units, one compiled object), and the separate 56B queue bridge
remained exact through a read-only receipt comparison. No unfiltered replay
was run, and no shared public header was modified.

The next useful source work is to reconcile the 12-byte post-switch
misalignment and compiler/EH local lifetimes, while preserving the now
correct original 22-pointer font table and real per-font assignments.

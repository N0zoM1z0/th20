# CORE/RECON-1082 — complete original 35B/108B/488B/200B/140B glyph PMR insertion/growth parent source, NONEXACT

Immutable original TH20 Japanese Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The game-owned **2,245B/612-i386 glyph-mask compositor** `0x00416420`
uses genuine `std::pmr::vector<std::array<int32_t,2>>` stencil
offsets, and its two original E8 calls `+0x165/+0x4DD` into
`0x00416330` are the entry to a **five-function compiler-template
control-flow graph**, not just a 35B leaf.

Ghidra read-only native decompilation and independent complete native
machine-code disassembly confirm the physical graph:

```text
Game-owned glyph compositor 0x00416420 (2245B, 37 E8)
  | E8 +0x165 and +0x4DD
  v
std::pmr::vector::emplace_back 0x00416330 (35B, 2 E8)
  | E8 +0x0B folded std::_Unfancy; E8 +0x17
  v
_Emplace_one_at_back 0x00413370 (108B, 4 E8)
  | E8 +0x2C/+0x43 folded std::_Unfancy
  | E8 +0x38 -> 0x004132E0 (140B non-growth construction)
  ` E8 +0x61 -> 0x004133E0 (488B reallocation)
                         | E8 +0x146/+0x162/+0x18B
                         v
                 0x00413920 (200B uninitialized move)
```

Five original **complete physical code extents** and their independently
pinned canonical source frontiers under MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` are:

| Original head | Complete original | Natural maintained source | Compiler discrepancy |
| --- | ---: | ---: | --- |
| `0x00416330` `emplace_back(const&)` | **35B/15 i386, 2 E8/0 HIGHLOW** | **33B/13, 1 E8/0 DIR32** | Additional live old native pointer forwarding to folded `0x0040B280` |
| `0x00413370` `_Emplace_one_at_back` | **108B/40, 4 E8/0 HIGHLOW** | **78B/30, 2 E8/0 DIR32** | Two extra native pointer-forwarding calls and different argument stack lifetime |
| `0x004133E0` `_Emplace_reallocate` | **488B/170, 14 E8/2 HIGHLOW** | **467B/163, 13 E8/2 DIR32** | Old native vector placement/move and real STL lowering differences |
| `0x00413920` `_Uninitialized_move` | **200B/65, 9 E8/2 HIGHLOW** | **191B/62, 8 E8/2 DIR32** | One additional native forwarded pointer/action; EH owner still real |
| `0x004132E0` `_Emplace_back_with_unused_capacity` | **140B/52, 5 E8/0 HIGHLOW** | **125B/47, 4 E8/0 DIR32** | Original pointer forwarding and allocator construction differs |

The `std::array<int32_t,2>` type is important: its original 8B
element size and 16B PMR-vector ABI are independently demonstrated
inside the real 2,245B game Boss, and its native complete folded
22B index receives four original E8 from that Boss. The C++20 source
in [`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
**naturally instantiates all five** methods. The 35B helper and
108B/200B/140B compiler functions were previously marked as
`unclassified` with no source, a false historical status now corrected
in the function ledger to **SOURCE-PRESENT, NONEXACT**, with actual
compiler symbol names and native physical boundaries. The already
source-present 488B `_Emplace_reallocate` uses the corrected
`std::array`-based MSVC mangled symbol (not the obsolete struct tag).

The independent read-only
[`verify-glyph-pmr-five-parents-native.py`](../scripts/verify-glyph-pmr-five-parents-native.py)
SHA-pins all five **whole original** bodies, every native decoded
instruction boundary, original E8/HIGHLOW counts, and the genuine
parent call graph from the original 2,245B game Boss; it checks the
actual current complete generated COFF bodies **without shortened
comparison**, and revalidates eight separate whole-exact native PMR
children. The accepted supporting PMR source contains genuine
**84B growth, 19B allocator helper, 58B PMR allocate, 42B overflow,
36B capacity, 42B/28B/39B backout, 13B orphan, 165B Change-array
and 81B reallocation guard** functions already verified independently.
That **does not** make these five parent methods exact by transitivity.

Controlled source variants varying `std::pmr::vector::emplace_back`,
`push_back`, lvalue/rvalue forwarding, and `insert` also failed to
naturally reproduce the old native full 35B/108B/488B method chain;
no low-level function was faked merely to close the byte gap.

**Admission: no new strict unit for any of these five parents and
no new game-authored exact function/bytes.** The original full
2,245B game Boss remains SOURCE-PRESENT/NONEXACT; all previously
accepted **24/24 native exact** PMR/vector/color descendants are
replayed only in their one affected source object. No global cold
replay or target binary modification was run.

```sh
scripts/repo-python scripts/verify-glyph-pmr-five-parents-native.py
scripts/repo-python scripts/verify-glyph-mask-emplace35-native.py
scripts/repo-python scripts/verify-glyph-vector-growth488-native.py \
  --candidate-object build/core1052-canonical/GlyphMaskComposite2245.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```

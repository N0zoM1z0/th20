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
  | E8 +0x0B -> shared 8B std::move; E8 +0x17
  v
_Emplace_one_at_back 0x00413370 (108B, 4 E8)
  | E8 +0x2C/+0x43 -> shared 8B forwarding leaf
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
| `0x00416330` `emplace_back(const&)` | **35B/15 i386, 2 E8/0 HIGHLOW** | **34B/14, 2 E8/0 DIR32** | Both native E8 positions and all non-relocation bytes match; native trailing NOP at `+0x1C` is absent |
| `0x00413370` `_Emplace_one_at_back` | **108B/40, 4 E8/0 HIGHLOW** | **108B/40, 4 E8/0 DIR32** | Every non-relocation byte and all four E8 positions match |
| `0x004133E0` `_Emplace_reallocate` | **488B/170, 14 E8/2 HIGHLOW** | **488B/170, 14 E8/2 DIR32** | Every non-relocation byte and all fourteen E8 positions match; both absolute fields are at the native HIGHLOW offsets |
| `0x00413920` `_Uninitialized_move` | **200B/65, 9 E8/2 HIGHLOW** | **200B/65, 9 E8/2 DIR32** | One additional native forwarded pointer/action; EH owner still real |
| `0x004132E0` `_Emplace_back_with_unused_capacity` | **140B/52, 5 E8/0 HIGHLOW** | **140B/52, 5 E8/0 DIR32** | Every non-relocation byte and all five E8 positions match |

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

## 2026-11-25 follow-up: decode the forwarding leaf and test explicit C++ move boundaries

Read-only native Ghidra context for `0x00416330` resolves its actual operation:

```cpp
uVar1 = move<>(param_1);
FUN_00413370(this, uVar1);
```

The 35B member therefore has a real two-edge chain: `std::move<>` at
`+0x0B` to the shared 8B `0x0040B280` forwarding leaf, then the 108B
`_Emplace_one_at_back` backend at `+0x17`. The shared 8B head is already
accepted as a common reference-forwarding primitive (including distinct
`std::move`, `std::forward`, `std::addressof` and `_Unfancy` uses); it receives
no duplicate authored-byte credit here. The exact template specialization
used by this old `move<>` call is not proven from the Ghidra prototype alone.

Several ordinary C++ source paths were rebuilt under the pinned profile:

- `offsets.emplace_back(std::move(displacement))` selects the rvalue-reference
  vector specialization, but still emits a complete **33B/13-i386** wrapper
  with one E8 to the modern `_Emplace_one_at_back` template. It does not add
  the native out-of-line `move<>` E8.
- Explicit `__declspec(noinline)` instantiations of both
  `std::move<GlyphMaskOffset&>` and `std::move<const GlyphMaskOffset&>` do not
  force the modern vector template to retain a separate call. The complete
  historical pre-specialization wrapper was 33B/13 with one E8; see the
  current 34B/14 member-template specialization in the 2026-11-25 follow-up.
- A separate natural free forwarding function
  `append_glyph_mask_offset(GlyphMaskOffsets&, const GlyphMaskOffset&)`
  emits **26B/11-i386** with two E8, but its ABI is `__cdecl` with two stack
  arguments and its second target is the modern 33B `emplace_back` wrapper,
  not the original 108B backend.
- A temporary derived-vector member wrapper emits **25B/11-i386** with one
  E8 to the modern vector template. Its changed container type also expands
  the whole compositor to **2,276B/589-i386**, 47 E8 and only 4/37 aligned
  positions. It is rejected and never enters maintained headers.

The native member's `__thiscall` receiver/one-argument ABI, explicit
`std::move<>` call and direct backend edge are still not reproduced by the
current standard-library source. No wrapper is promoted, no original leaf is
credited, and `src/GlyphMaskComposite2245.cpp` remains unchanged by these
experiments. The complete 35B helper and all five PMR parents remain
SOURCE-PRESENT/NONEXACT.

## 2026-11-25 follow-up: restore the three complete PMR insertion/growth bodies

The current `GlyphMaskComposite2245.cpp` now provides explicit C++20 member
specializations for the old vector call graph. Under the pinned MSVC profile,
the 108B `_Emplace_one_at_back`, 140B `_Emplace_back_with_unused_capacity`
and 488B `_Emplace_reallocate` candidates have exactly the native lengths,
instruction counts, E8 positions and every non-relocation code byte. The
488B candidate has 14 REL32 and two DIR32 relocations; those absolute fields
occupy the exact original PE HIGHLOW sites `+0x06/+0x15`. The 8B shared
`std::move` primitive is complete-byte exact.

The public 35B wrapper is now 34B/14 heads with both original E8 sites and
all non-relocation bytes matching after removing the native `+0x1C` NOP. The
NOP is not synthesized. The 200B `_Uninitialized_move` is now 200B/65 with
9 E8/2 DIR32 versus native 200B/65, 9 E8/2 HIGHLOW; after normalizing only
those real relocation fields and E8 displacements, all 200 code bytes match.
The 92B backout member and 31B allocator bridge also match every
non-relocation byte and all original E8 positions. The whole five-parent
chain and 2,245B game compositor remain SOURCE-PRESENT/NONEXACT because
callee/relocation identities and the 35B wrapper NOP are not fully restored.

The independent `verify-glyph-mask-emplace35-native.py --candidate-object`
checks the complete 8B/34B/108B/140B/488B bodies, all call sites and both
parent insertion edges. A targeted `replay-exact-units.py --source
src/GlyphMaskComposite2245.cpp` rebuild retained 24/24 existing exact
PMR/color descendants. The compositor remains 2,128B/561-i386 with
37/37 E8 target roles, 7/37 aligned E8 positions, 292/1,960 ordinary bytes
and 819 aggregate E8 offset distance.

## 2026-11-25 follow-up: restore the uninitialized-move pointer forwarding call

The maintained glyph source now explicitly instantiates the natural
`std::move<GlyphMaskOffset*&>` pointer-lvalue forwarding specialization with
`__declspec(noinline)`. This preserves the real loop operation in the original
200B `_Uninitialized_move` parent: load the current raw iterator pointer,
forward that pointer through the shared 8B move leaf, then pass the returned
pointer to `_Uninitialized_backout_al::_Emplace_back`.

The complete current candidate is **200B/65 i386, 9 E8, 2 DIR32** and
matches the original 200B/65 body byte-for-byte after normalizing only its
real E8 displacement and absolute relocation fields. The 92B backout member
and 31B allocator bridge are likewise complete in length/instruction count
and match all non-relocation bytes and call offsets. These remain
**SOURCE-PRESENT/NONEXACT** because target identities/relocation types differ;
there is no parent or generic STL byte credit.
The other current PMR parent frontiers remain: 35B wrapper 34B/14 (native
35B/15, one NOP absent), `_Emplace_one_at_back` 108B/40, no-growth 140B/52,
and reallocation 488B/170. Their natural C++ candidates preserve all native
E8 counts; 108B/140B/488B non-relocation code bytes match, while relocation
site types/targets remain a separate exactness requirement.


## 2026-11-25 follow-up: restore the 200B iterator/backout move path

The maintained `GlyphMaskComposite2245.cpp` now specializes the actual
`std::_Uninitialized_backout_al<polymorphic_allocator<GlyphMaskOffset>>`
for the TH20 two-word glyph element and the matching
`std::_Uninitialized_move<GlyphMaskOffset*, GlyphMaskAllocator>` entry.
This is ordinary C++ template code; no assembly, byte injection, or padding
is used.

The complete native `0x00413920` 200B function now has a 200B/65-i386
candidate with all nine E8 offsets and both absolute relocation fields in
the original positions. After zeroing only genuine E8 displacement and
PE/COFF absolute relocation fields, all 200 bytes match. The old loop
sequence is restored: two `_Get_unwrapped` calls, the backout local
initialization/constructor, an out-of-line element `std::move`, the
backout insertion member, `_Release`, and the backout destructor.

The two nested helpers are also reconstructed as complete C++ functions:

| Native head | Native extent | Candidate extent | Body result |
| --- | ---: | ---: | --- |
| `0x00413280` backout element insertion | 92B/34-i386, 3 E8 | 92B/34-i386, 3 E8 | Every non-relocation byte and call offset matches |
| `0x00413A90` allocator move-construction wrapper | 31B/14-i386, 2 E8 | 31B/14-i386, 2 E8 | Every non-relocation byte and call offset matches |
| `0x0040B2A0` `_Get_unwrapped` | 10B/6-i386 | 10B/6-i386 | Complete body matches |

The 31B wrapper still calls a **69B** current-MSVC
`polymorphic_allocator::construct` body, whereas the original 31B wrapper
calls a separate **78B** native construction helper at `0x00413AB0`.
That old 78B helper remains the deepest unresolved leaf. The 31B
`__autoclassinit2` lowering also retains a separate native call-site
frontier. Thus the 200B/92B/31B bodies are source-present and strongly
converged, but are not promoted to whole-function exactness. The 35B
public wrapper still omits its native trailing NOP, and the 2,245B game
Boss remains NONEXACT.

The 140B and 488B parents now route their element construction through
the same natural 31B move-construction wrapper at their original E8
positions. Their full 140B/52-i386 and 488B/170-i386 bodies remain
byte-identical outside real relocation fields. An explicit instantiation of
the backout `_Emplace_back<const GlyphMaskOffset&>` allocator-traits path
also retains the existing 22B `Normal_allocator_traits::construct` exact
child. All 24 previously accepted PMR/color child units pass the
source-scoped replay; no full cold replay was run.

Targeted checks:

```sh
scripts/repo-python scripts/replay-exact-units.py --source src/GlyphMaskComposite2245.cpp
scripts/repo-python scripts/verify-glyph-pmr-five-parents-native.py
scripts/repo-python scripts/verify-glyph-mask-emplace35-native.py --candidate-object build/core1052-canonical/GlyphMaskComposite2245.obj
scripts/repo-python scripts/verify-glyph-vector-growth488-native.py --candidate-object build/core1052-canonical/GlyphMaskComposite2245.obj
```

**CORE/RECON-1082 UPDATED STATUS:** This original 35B helper and its complete 108B backend, 488B vector reallocation, 200B uninitialized move, and 140B non-growth construction now have [real std::pmr::vector<std::array<int32_t,2>> source-present NONEXACT records](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md). The original complete 35B still differs from the current natural 33B/13 C++20 template; old SOURCE-ABSENT/unclassified claims below are historical. All 24 already accepted PMR/color descendants remain whole exact.

# CORE/RECON-1055 — original 35B glyph-mask offset insertion, genuine native 2-call ABI frontier

The original TH20 Japanese Steamless v1.00a executable is locked to
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The source-present, but NONEXACT, game-owned **2,245B/612-i386 glyph
compositor** `0x00416420` physically calls a **35B/15-i386** vector
insertion helper at `0x00416330` from *both* its BGRA32 and ARGB4444
mask-offset loops: original E8 at `+0x165` and `+0x4DD`.

The complete original 35B body is SHA-256
`bd26f62ba6f30fe4d6e5845561e0cc2ecdd80da8bc771cdcdd260e25109343b4`.
It ends with `ret 4`, has **no PE HIGHLOW**, and contains exactly two
physically original E8 instructions:

| Original E8 site | Actual native destination | Role |
| --- | --- | --- |
| `+0x0B` | `0x0040B280` | already strict-exact eight-byte pointer forwarding leaf |
| `+0x17` | `0x00413370` | separate original 108B vector insertion/backend path, not yet source-exact |

The native compositor's two E8 edges, the complete physical original
35B function and all nested original call targets are independently
SHA-attested by
[`verify-glyph-mask-emplace35-native.py`](../scripts/verify-glyph-mask-emplace35-native.py).
This is not a guessed function name from a Ghidra label or a shortened
COFF function prefix.

The maintained
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
naturally instantiates `std::pmr::vector<GlyphMaskOffset>::emplace_back`
with an actual signed two-word glyph displacement for both real
color-mode branches. However, under pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, the current
`emplace_back(const GlyphMaskOffset&)` instantiation is a complete
**33B/13-i386** function, with just **one** E8 at source field
`+0x11` into the compiler's `_Emplace_one_at_back` template helper.
That is **not** the original 35B/15, two-E8 function or its real
callee graph, even though both express a meaningful vector insertion.
No folded child is substituted for original `0x00413370` without
independent source proof.

Therefore original `0x00416330` stays **unclassified/SOURCE-ABSENT,
NONEXACT** at its complete native 35B extent. The larger game
compositor is SOURCE-PRESENT/NONEXACT (maintained candidate
1,987B/538 instructions vs original 2,245B/612). Its already strict
PMR constructor/destructor/iterator/default-resource helpers and
22B glyph packed-color ctor remain accepted as *independent* native
physical heads; **nothing new is credited for this 35B helper**.
Its original compiler spelling and exact forwarded allocation ABI
remain unresolved. Avoid manually stitching two authentic original
E8 calls into a fake source body, injecting native bytes, altering
class tags globally, or crediting a smaller 33B candidate as whole 35B.

This checkpoint changes **evidence, a provisional ledger row, and
an obsolete verifier print**, not reconstruction code or canonical
profiles. Hence **zero cold source replays are required**; a fresh
locked original PE check and unchanged-unit source receipt check are
sufficient. No project-wide cold replay is used.

```sh
scripts/repo-python scripts/verify-glyph-mask-emplace35-native.py
scripts/repo-python scripts/verify-glyph-canvas-width20-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
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
  wrapper remains 33B/13 with one E8.
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

## 2026-11-25 follow-up: old pointer-forwarding call and current MSVC controls

The native `0x00416330` wrapper's first E8 is the shared 8B pointer-identity
`std::move<>` helper, not an allocator operation. Its original instruction
sequence is a `thiscall` method: save ECX, load the sole stack pointer
argument, call `0x0040B280`, push the returned pointer, restore ECX, then call
the 108B `0x00413370` backend. The native body is the complete 35B/15-i386
function with `ret 4`, no PE HIGHLOW, and two direct E8 edges.

The repository already demonstrates a real natural-C++ way to preserve this
shared old-MSVC helper: `src/FrontDialogueAllocate156.cpp` explicitly
instantiates `std::move<std::uint8_t*&>` with `__declspec(noinline)`, and its
caller emits the original 8B out-of-line E8. `src/CardTextPayloadNative.cpp`
likewise preserves `std::move<std::pmr::polymorphic_allocator<char>&>` for the
108B PMR string move. These are source precedents for the helper, not evidence
that the glyph insertion wrapper is exact.

For the glyph path, the following pinned C++20 experiments were compiled:

- Explicit noinline `std::move<const GlyphMaskOffset&>` plus ordinary
  `std::pmr::vector::emplace_back` does not retain a move E8; the vector
  template consumes the value as a forwarding reference and current MSVC
  removes the identity operation.
- Explicit pointer-reference and pointer-rvalue `std::move` specializations
  likewise disappear when the result is immediately dereferenced into the
  current vector `emplace_back` body.
- A derived-vector member wrapper calling `Base::emplace_back` is only
  **25B/11-i386, one E8**. A `push_back`/`back` wrapper is **33B/13-i386,
two E8**, but those calls target modern `push_back` and `back`, not the
  original 108B `_Emplace_one_at_back`.
- A pointer-local forwarding wrapper does preserve the pointer `std::move`
  E8, but its address-taken local triggers `/GS` and grows to **65B/24**.
  A direct pointer-rvalue member wrapper is **39B/15** with one E8, not the
  original two-E8 graph.

The pinned MSVC 19.44 `vector` header confirms `_Emplace_one_at_back` is
private (at `vector:837`); the public `emplace_back` delegates to it, while
`push_back` also delegates to it. A natural derived class cannot call that
private implementation directly. No private-access shim, `#define private
public`, inline assembly, manual bytes or padding was introduced. The
original 35B/108B compiler-template parent chain remains SOURCE-PRESENT,
NONEXACT; the maintained compositor source is unchanged by these probes.

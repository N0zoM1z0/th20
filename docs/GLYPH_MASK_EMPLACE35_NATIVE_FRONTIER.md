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

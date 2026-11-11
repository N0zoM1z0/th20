# CORE/RECON-1109 — 508B/511B Renderer Boss class-key specialization, full-body relocation-role proof and regression gate

Immutable target: TH20 Japanese Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The two previously reconstructed Renderer animation-list updates at **`0x00449870`
(508B/152 i386)** and **`0x00449B20` (511B/153 i386)** have complete
maintained C++ implementations in
[`AnimationRendererListUpdate508.cpp`](../src/AnimationRendererListUpdate508.cpp)
and [`AnimationRendererListUpdate511.cpp`](../src/AnimationRendererListUpdate511.cpp).
The algorithms are real two-pass update/recursive-retirement/deferred-release
loops. They had been **498B and 501B** with the pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, each missing the same
ten-byte, actual native `IntrusiveList<Animation>` local-preclear call.

## New executable evidence: targeted class specialization

A private global change from `struct IntrusiveList<T>` to
`class IntrusiveList<T>` had previously recovered the missing instruction,
but contaminated hundreds of otherwise exact template consumers. The new
[`probes/AnimationRendererListClassTag.hpp`](../probes/AnimationRendererListClassTag.hpp)
instead introduces **one explicit `class IntrusiveList<Animation>` specialization**.
It retains the genuine 24B node/link/tail layout and actual methods from
the generic class, **without changing the public `src/IntrusiveLink.hpp` or
the template for any other `T`**. It is deliberately provided *only* to two
standalone probe translation units, each of which includes the **real maintained
Boss `.cpp` file**, rather than a copied or shortened implementation:

- [`AnimationRendererListUpdate508ClassProbe.cpp`](../probes/AnimationRendererListUpdate508ClassProbe.cpp)
- [`AnimationRendererListUpdate511ClassProbe.cpp`](../probes/AnimationRendererListUpdate511ClassProbe.cpp)

Pinned MSVC now naturally emits the ten-byte native `/sdl` instruction at
original E8 opcode **`+0x30 -> 0x0040C080`** before the original real list
constructor at `0x00418A50`; no hand-authored machine code, dead local or
padding is used. The typed class remains a real C++ template specialization,
with a genuine user-defined original-algorithm constructor.

| Whole original function | Private class-specialized candidate | All original E8 / PE relocations | Nonrelocation bytes |
| --- | --- | --- | --- |
| `0x00449870` primary, 508B/152-i386 | **508B/152-i386** | **30 E8 +5 HIGHLOW**, same field sites and independently decoded targets | **368/368** equal |
| `0x00449B20` secondary, 511B/153-i386 | **511B/153-i386** | **30 E8 +5 HIGHLOW**, same field sites and independently decoded targets | **371/371** equal |

A real executable verification program,
[`scripts/probe-animation-renderer-list-class-tag.py`](../scripts/probe-animation-renderer-list-class-tag.py),
recompiles only the two affected probes, SHA-locks the target through the
repository verifier, independently decodes all native E8 destinations and
PE HIGHLOW fields, and checks **all 35 compiler-emitted COFF relocation
positions, types and symbol-to-original-target role bindings per Boss**.
It rejects any invented address or unrecognized symbol, ensures the two
functions' whole code sizes/instruction counts, and compares **every one**
of the 368/371 original ordinary code bytes. These are not normalized
prefixes and no original relocation is masked without a real corresponding
COFF field and separately identified destination.

## Corrected scoped exact-consumer audit

The test must compare the **complete configured COFF contribution**, not
mistake compiler-generated after-ret padding for changed function code. The
first experimental script falsely called **730B/503B/67B** a regression
because the game-authored code extents of those functions are
**725B/498B/62B**. In reality, their canonical unit configurations
already use **`compare_size = 730/503/67`**, including the genuine trailing
five bytes. Recompiling the entire actual `Animation.cpp` translation unit
under the class specialization and using `compare_size` for **all 38
accepted original units** confirms **38/38 full structural exact**.
The test was corrected before any canonical acceptance or commit.

The remaining complication is a real **source/API symbol migration**:
`IntrusiveList<Animation>*` is decorated `PAU?$IntrusiveList...` when
the generic `struct` declaration is used, but `PAV?$IntrusiveList...`
when the explicit `class` specialization is active. The separately exact
411B recursive retirement function changes its mangled parameter symbol,
although its instructions do not change. Moving the specialization into
mainline therefore requires consistent explicit inclusion in all relevant
translation units and updating true COFF relocation symbol identities
against the original independent target addresses. A naive merge would
risk unresolved linker symbols and inconsistent template specializations.

Read-only inventories found **76 canonical units across 16 exact compiler
objects** exposing Animation intrusive list/link symbols; a *global*
edit to `src/IntrusiveLink.hpp` would instead touch **828 exact units
across 235 object providers**. The explicit specialization remains a
bounded route that avoids changing unrelated `IntrusiveList<T>` template
instantiations. Actual helper **40B list constructor/42B reset** heads
remain independently NONEXACT under current source; the specialization
alone still makes the former 31B and the latter has the original
one-byte register-selector gap. Do not count either helper twice.

**At this proof checkpoint, both Renderer parents are still SOURCE-PRESENT,
NONEXACT in the canonical ledger**. Their full-body structural and 35-role
agreement in isolated clones is not a canonical/ODR-complete build, and no
508+511 authored bytes are added before actual affected exact consumers and
symbol identities are migrated and strictly replayed.

## Fast reproduction; never run full cold replay

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-renderer-list-class-tag.py
```

This compiles **exactly three isolated objects**, never builds/replays the
full graph and never edits the public template or accepted exact units.
Historical baseline proofs remain
[508B/511B Renderer list frontier](ANIMATION_RENDERER_LIST_UPDATE_508_511_NATIVE_FRONTIER.md)
and [40B/42B list helpers](ANIMATION_RENDERER_LIST_HELPERS_40_42_NATIVE_FRONTIER.md).

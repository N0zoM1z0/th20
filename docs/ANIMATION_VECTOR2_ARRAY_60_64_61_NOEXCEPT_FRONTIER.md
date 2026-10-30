# CORE/RECON-944 — three original 75B Vector2 array constructors: verified noexcept ABI frontier, NOT canonical exact

Immutable original: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

This investigation **does not add any accepted strict unit, source-present mapping,
or authored-game exact byte**. It distinguishes original-only PE verification,
private compiler experiments and actual canonical source consistency. Older
handoff notes treating color and vertex constructors as equally unfinished are
superseded: color arrays of 60 and 64 `AnimationHandle` entries have already
been independently strict exact; the remaining open bodies here are specifically
three `Vector2`-array constructions.

## Three independent complete original PE bodies

[`scripts/verify-animation-vector2-array-noexcept-frontier-native.py`](../scripts/verify-animation-vector2-array-noexcept-frontier-native.py)
independently checks the complete original function body (75B/27 i386), real
five following `INT3` alignment bytes, all three original HIGHLOW fields,
one E8 site and destination, and the actual native parent E8:

| Native body | Count and parent | Original code/relocations |
| --- | --- | --- |
| `0x0045D500` | **60 Vector2**; 60B ribbon segment constructor calls it at `0x0045D61A` | 75B native +5B `INT3`; E8 `+0x33 -> 0x0040BC20` |
| `0x0045DE80` | **64 Vector2**; whole-exact 103B trail group constructor calls it at `0x0045DEF2` | 75B native +5B `INT3`; E8 `+0x33 -> 0x0040BC20` |
| `0x0045F260` | **61 Vector2**; whole-exact polygon segment constructor calls it at `0x0045F3CA` | 75B native +5B `INT3`; E8 `+0x33 -> 0x0040BC20` |

All three physically reference native EH handler `+0x06 -> 0x00567600`,
security cookie `+0x13 -> 0x005B25C0`, actual `Vector2()` constructor
callback `+0x27 -> 0x004398A0`; native E8 `+0x33 -> 0x0040BC20` is the
EH vector constructor. Exact element size is 8 and the element counts are
60/64/61, respectively. These are **real original function heads**, unlike
the rejected old interior-address 19B color-end hypothesis.

## Diagnostic codegen, current failure and admission blocker

The existing authoritative [`src/Vector2.hpp`](../src/Vector2.hpp) declares
`Vector2();` and `src/Vector2.cpp` supplies the original separately accepted
native constructor source. Under the pinned MSVC 19.44 x86 C++20 `/Od /Ob0
/GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, a natural
`std::construct_at(&std::array<Vector2,64>)` source built with the
**existing real header** generated a **33B** non-EH array constructor,
not the original 75B body. This was not accepted.

An **isolated private copy** of `Vector2.hpp` with only the declaration
changed to `Vector2() noexcept;`, plus a separate test TU containing natural
`std::construct_at` invocations for `std::array<Vector2,60>`, `...64`,
and `...61`, generated **80B complete COFF contributions for all three**.
Every contribution has **75 function bytes plus the five real INT3** and
**64/64 nonrelocated comparable bytes** matching the respective original,
with the four true native relocation field offsets/types and the real
`Vector2` constructor callback. This is strong evidence that an explicit
noexcept constructor declaration explains the shared compiler ABI, but
**structural-exact in an isolated test is not canonical exactness**.
The reproducible ignored probe lives at:

```text
.analysis/gptweb-vector2-noexcept-scope/Vector2_noexcept.hpp
.analysis/gptweb-vector2-noexcept-scope/Probe.cpp
build/gptweb-vector2-noexcept-scope/Probe.obj
```

A real canonical change would need to reconcile the `noexcept`
exception specification with `src/Vector2.cpp` and every other translation
unit so the program has **one consistent C++ ODR declaration**. A real
transitive source-include graph inspection counted **237 `.cpp` files**
including `Vector2.hpp` directly or indirectly, **230 existing canonical
source providers**, and **871 existing strict units** in the affected
closure. The other seven are currently source-present but do not provide
strict units. Changing shared `src/Vector2.hpp` while replaying only the
three new array bodies would leave a very large unverified regression risk;
that was deliberately not done. The user explicitly prefers fast affected-only
validation and no full cold replay; this frontier requires its own careful
reconciliation scope and honest regression accounting.

The canonical `.hpp`/`.cpp`, unit manifest and all previously accepted
receipts were **left unchanged**. This analysis is **original-native facts
plus diagnostic compiler evidence only**. None of these three functions
is in `config/matches.csv`, so exact game coverage and source mapping
metrics remain at the preceding checkpoint.

### Fast independent original PE reproduction

```bash
scripts/repo-python scripts/verify-animation-vector2-array-noexcept-frontier-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

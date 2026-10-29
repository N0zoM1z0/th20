# CORE/RECON-768 — native-exact 47-byte SprtID inequality and full original 456-byte resolver compiler frontier

The target remains the hash-locked Japanese TH20 v1.00a Steamless binary,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This milestone admits **one newly original-native-exact game-owned 47-byte
function**, not the 456-byte parent. The larger original resolver is
independently reconstructed in a **private complete 456B /141 x86 source
hypothesis** with **20/20 physical original E8/COFF field offsets and no
nonrelocation differences**, but its runtime owner/handle ABI and aliasing
still need reconciliation with already strict native game callers.

## One whole 47-byte game function now exact

Native original head `0x00449460`, native extent **47 complete code bytes /
16 i386 instructions**, is a four-byte live ID comparison against another
four-byte ID **by const reference**. The original locked executable directly
calls it at `0x0044CE8B` inside the original 456-byte handle resolver. The
same immutable original executable has RTTI strings naming two closures
within `SprtCtrlInf::getSprt(SprtID)` and `LinkInf<SprtInf*>` predicates.
These independent original executable facts establish the four-byte game
value type; neither Ghidra's generic name nor an earlier README was used to
award game authorship.

The maintained C++20 source is one natural, shared semantic body:

```cpp
bool SprtID::operator!=(const SprtID& rhs) const {
    return value != rhs.value;
}
```

It compiles with the pinned original candidate MSVC 19.44.35211 x86,
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, to precisely
**47/47 original native bytes, zero COFF or PE relocations**. The complete
function and genuine return cleanup are compared by
`replay-exact-units.py --source src/SprtID.cpp`, with fresh compiler object
and receipt. Its own canonical unit is `sprtid_inequality_47`. The three
other natural four-byte `SprtID` value methods are declared and implemented
in the same source, but are **not** independently credited as new original
physical game functions: previously accepted original folded code can share
their compiled code shapes.

## Recovering the much larger original pool resolver without false credit

The original 456-byte/141-x86 game function at `0x0044CD00` contains
**20 real original direct E8 call sites**. Native code tests the four-byte
`SprtID` by member equality and bitmask, performs two distinct by-value
`std::function` predicates on the special-ID search path, and checks
0x600-stride pooled records at +0x710 for normal IDs. This was independently
verified through raw E8 displacements and original RTTI, as documented in
[the original pool resolver investigation](ANIMATION_POOL_RESOLVER_456_TYPED_NATIVE_FRONTIER.md).

The original 456-byte full function was *also* fully regenerated in a
**source-only private ABI research probe** under
`.analysis/core763-before_zero-assign_in_if.cpp`, using a native four-byte
`SprtIDProbe` value, natural member methods, genuine two-list
`std::function` searches, shared result variable, real repeated array
subscripts and one common no-match return. The low-priority pinned-compiler
x86 object `build/core763-probe/before_zero-assign_in_if.obj` has exactly
**456 bytes /141 x86 instruction heads and 20 ordinary COFF REL32 fields**.
Every nonrelocated whole code byte matches the locked original. The original
**20/20 true native E8 destinations, operand positions and field sizes**
match independently decoded original executable bytes (not solved from the
COFF under comparison). Detailed original PE/COFF comparisons are in ignored
`.analysis/core768-resolver-private-original-field-proof.json`.

This **does not establish canonical exactness**: that private original-shaped
method has a provisional `PoolOwnerProbe` class, separately modeled
`SprtIDProbe` identity and a reinterpretation of live `AnimationHandle`
as its unresolved original sprite ID representation. The maintained
`src/AnimationPoolHandleResolve.cpp` deliberately remains a normal, typed,
noncanonical **`AnimationPoolOwner::resolve_handle(uint32_t)` source** matching
existing callers' publicly proven ABI. It improves from the earlier
**364B/111 x86/12-field** candidate to **410B/122 x86/13-field** after
restoring both independent original list indexing operations, a common
selected result and the correct normal pool repeated lookup order; it is
still **NONEXACT** versus the native 456B/141 x86/20 E8. No hand-authored
assembly, fake symbol or target byte patch was used.

## Why the obvious public header conversion was rejected and repaired

The alternative private hypothesis promoted `resolve_handle(SprtID)` and a
new `AnimationHandle::operator!=(const SprtID&)` to live shared public
headers. The 456-byte parent then itself compiled as native byte-exact,
but conversion of existing `uint32_t` caller IDs to a C++ aggregate **added
six bytes** to previously accepted original **51B** handle resolver,
**66B** set-handle-position, **246B** handle-interrupt and **43B** retire
wrapper. The direct C++20 `std::bit_cast` alternative generated an extra
compiler helper and enlarged the 51B call to 64B. This is a real ABI
source-level question, not a reason to weaken matching criteria or count
the 456-byte parent prematurely.

The pre-edit compiler receipt graph shows the header mutation would actually
affect **119 old canonical source/object providers and 495 exact units**.
Rather than silently skip or discard the failed dirty hypothesis, its complete
public header/source diff is preserved at
`.analysis/core767-provisional-sprtid-public-diff.patch`, and the entire
compiler-exact typed parent source at
`.analysis/core767-provisional-typed-resolver-exact.cpp`. The published
headers/callers were restored to the previous validated ABI, and **all
nine native original functions in the three old canonical source objects
actually rebuilt during the experiment** were subsequently cold rebuilt and
strictly reverified **9/9** using `--source` filters on:

- `src/BulletCollisionHandle.cpp` (2 complete original exact units)
- `src/AnimationHandlePosition.cpp` (4 complete original exact units)
- `src/AnimationHandleRetire.cpp` (3 complete original exact units)

The 119-provider header closure did not need to be replayed, because the
header was restored to the identical committed source before finalizing. The
new `SprtID.hpp` is not inserted into the old public compiler include graph.
For this committed change, **one new canonical source/object/47B unit** is
cold compiled. No unfiltered all-project cold replay is run.

## Accounting and remaining parent work

Game-authored strict whole-original coverage increases by precisely
**one complete game function and 47 nonoverlapping `.text` bytes**:
**563 /187,092 to 564 /187,139**. Source-present mappings become **1,210**;
canonical units become **1,211** in **248** object/receipt providers.
The original 456-byte `SprtCtrlInf::getSprt(SprtID)` remains **NONEXACT** in
public maintained source (zero exact byte credit for its parent), while the
private compiler-equivalent source and all original native evidence remain
available for a future ABI/lifetime-safe refactor.

The separate Bullet extended-command boss at `0x0047DCF0` (12,140B) also
remains source-absent and **NONEXACT**, despite the previously accepted
207→208/210 complete original child-call source closure. Neither privately
matched isolated code nor a Git commit establishes whole-program linkage,
original relocation equivalence or playability.

# CORE/RECON-773 — exact original 47-byte SprtID-by-reference equality and preserved full resolver

The locked Japanese TH20 v1.00a Steamless original PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains an entire original **47-byte /16 x86-instruction** physical game
method at **`0x00449400`**, separate from both the already exact **47-byte
`SprtID` inequality at `0x00449460`** and the previously accepted original
**45-byte immediate-value predicate at `0x00449430`**. Its body takes an
actual 4-byte ID receiver and another 4-byte ID by const reference, compares
their contained words and returns `bool` with the real original `ret 4`.

This method is not inferred from two identically sized bodies alone. The
original **456-byte game `SprtCtrlInf::getSprt(SprtID)` resolver** now has
independently verified exact source and immutable original RTTI showing its
`LinkInf<SprtInf*>` reference-capturing lambdas. The linked native predicate
caller at original **`0x00449600`** resolves the current linked `Animation*`,
selects its live ID at `Animation+0x4C0`, and **physically E8-calls the
`0x00449400` comparison at `0x00449620`**. The source-level owner `SprtID`
therefore matches the actual original argument/receiver value protocol, not
merely a conveniently shaped compiler alias.

The exact maintained implementation is part of the existing real
`src/SprtID.hpp` and `src/SprtID.cpp`:

```cpp
bool SprtID::operator==(const SprtID& rhs) const {
    return value == rhs.value;
}
```

The locked MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits exactly **47/47 original whole-native
bytes and 16/16 x86 heads**, zero COFF relocations. It has its own canonical
unit `sprtid_ref_equality_47` at `0x00449400`, sharing the **existing**
`build/core768-canonical/SprtID.obj` source provider rather than adding
another duplicate object. There is no target prefix comparison, compiler
padding or duplicate physical game-byte credit.

The only existing shared compiler input touched was `src/SprtID.hpp`, whose
pre-edit actual receipt `headers` closure included exactly **two existing
canonical sources/objects and two strict units**: `src/SprtID.cpp` (previous
47B inequality) and `src/AnimationPoolHandleResolve.cpp` (previous complete
456B resolver). Only these two providers were cold rebuilt at low priority,
and both old strict methods remained **47/47 and 456/456**. Together with the
new 47B equality, the affected-only replay passed **3/3 complete strict
functions across two actual cold objects**:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/SprtID.cpp --source src/AnimationPoolHandleResolve.cpp

The full resolver's 20 independently original-PE-proven E8 call sites remain
unchanged and are rechecked with
`scripts/repo-python scripts/verify-animation-pool-resolver-native.py`.
There was **no unfiltered cold replay** and no public AnimationHandle or
AnimationPoolOwner ABI change.

Source-present mappings increase **1,210 →1,211**; canonical strict units
**1,212 →1,213**, using the same **249** object/receipt providers; distinct
whole game authored exact functions **565 →566** and real nonoverlapping
original .text bytes **187,595 →187,642**. The genuine **12,140B Bullet
command** parent and the 41,967B Enemy ECL dispatcher remain NONEXACT.

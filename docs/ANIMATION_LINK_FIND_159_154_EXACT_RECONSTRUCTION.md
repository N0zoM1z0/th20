# CORE/RECON-774 — entire original 159-byte Animation link predicate and 154-byte list wrapper, both strict exact

The immutable Japanese TH20 v1.00a Steamless comparison PE is attested by
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint reconstructs **two additional complete and physically
distinct original game-owned methods, 313 total original .text bytes**, in
the same maintained `src/AnimationPoolHandleResolve.cpp` owner as the recently
accepted whole **456-byte /141-instruction** handle resolver. All three
original functions remain separate whole-native intervals; exact child
methods are not fractional credit for an enclosing parent.

## Original function boundaries and source semantics

| Original head | Whole native body | Physical role | Actual locked MSVC source |
| --- | ---: | --- | --- |
| `0x0044A500` | **159B /47 x86** | Walk a real `IntrusiveLink<Animation>` next-pointer chain, evaluate each link against the caller's live **40-byte by-value** `std::function<bool(IntrusiveLink<Animation>&)>`, return the first matched link or null. Natural value-object EH lifetime includes destructor at both normal and matched exits | `th20::find_link_with_predicate`, one ECX-receiver `__fastcall` with by-value predicate, full original `ret 0x28` |
| `0x0044A5A0` | **154B /46 x86** | Fetch actual list's next link, copy the same by-value predicate into the native 159B walker, return its result or null and destroy the original predicate. The native compiler emits a real `std::function` copy constructor and SEH cleanup | `th20::AnimationLookupList::find_if`, on the real list wrapper, full original `ret 0x28` |

These functions are game-owned custom intrusive container traversal and
lookup behavior, not independent credit for the compiler's standard-library
`std::function` constructors/destructors. The source uses real `IntrusiveLink`
properties and one shared natural C++ semantic body per original method.
The historical original spelling of the internal link method or namespace
is not inferred from matching code alone; the ECX-receiver and 40-byte
stack-value calling conventions are native-confirmed and exactly matched.

## Independently native-PE-verified call and data anchors

The maintained `scripts/verify-animation-pool-resolver-native.py` reads and
disassembles the **entire original source-independent executable** and
checks each of the following original call-site/destination pairs, rather
than using a modern COFF relocation to guess the destination:

| Original function | Original native E8 sites and independently decoded destinations | Genuine original PE HIGHLOW fields |
| --- | --- | --- |
| `0x0044A500` | `0x0044A542 →0x00449630` (real predicate invocation); `0x0044A55E →0x00414400` (destructor); `0x0044A56B →0x0040FF90` (next link); `0x0044A586 →0x00414400` (destructor) | `0x0044A506 →0x0056844D` (SEH); `0x0044A515 →0x005B25C0` (security cookie) |
| `0x0044A5A0` | `0x0044A5D2 →0x0040FF90`, `0x0044A5DE →0x0040FF90` (next link twice); `0x0044A5F2 →0x004140F0` (`std::function` copy); `0x0044A5FA →0x0044A500` (walker); `0x0044A621 →0x00414400` (destructor) | `0x0044A5A6 →0x0056847D` (SEH); `0x0044A5B5 →0x005B25C0` (security cookie) |

Both functions have their complete genuine original RET instructions and
separate SEH states. The independent locked PE `.reloc` directory confirms
**all four HIGHLOW locations** (not merely addresses found by disassembly).
The 159B function's **six** and 154B function's **seven** canonical COFF
relocations each match these independently decoded exact field locations,
relocation kinds, source symbol identities and original target addresses.
Every nonrelocation instruction byte matches as well.

## Scoped native validation and existing boss preservation

The existing whole-native-exact 456B parent at original `0x0044CD00`
physically calls the 154B list wrapper at `0x0044CD90` and
`0x0044CDED`; the wrapper's original E8 at `0x0044A5FA` calls the
separate 159B link predicate. The newly restructured natural C++ source
correctly models that real two-stage call hierarchy. Unlike the historical
single combined search loop, it reproduces every original function extent
and original EH destructor lifetime without duplicated source bodies.

The pinned MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiled the **one affected existing**
`src/AnimationPoolHandleResolve.cpp` provider serially at low priority.
Canonical full-native replay passed **all 3/3 whole functions** in its
single existing `build/core772-canonical/AnimationPoolHandleResolve.obj`
source/object provider:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolHandleResolve.cpp

Results are original **456/456B**, **159/159B**, **154/154B** strict zero
difference after exact independent original relocation replay. No public
header, old object profile, previously exact other source file or shared
layout changed; actual old affected scope was **one canonical provider /
one old strict unit (456B)** plus the **two new strict units**. No whole-graph
cold replay ran. The separate pinned 47-byte SprtID reference equality and
inequality still compile independently from their unchanged source.

Game-authored strict coverage advances **566 →568 distinct physical original
methods** and **187,642 →187,955 disjoint original game .text bytes**. The
native strict unit graph advances **1,213 →1,215** and source-present
mappings **1,211 →1,213**. Distinct canonical object/receipt providers
remain **249** because the two new methods use the existing entire
Animation pool source object. The separate 12,140-byte Bullet command,
41,967-byte Enemy ECL dispatcher and 39,470-byte Animation VM remain
**NONEXACT**; exact list children do not prove these larger parents.

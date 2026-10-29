# CORE/RECON-757 — entire original 456-byte Animation handle resolver: typed C++ / original-PE semantic frontier (NONEXACT)

The immutable Japanese TH20 v1.00a Steamless original PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains one **456-byte /141 i386-instruction** original game-owned
`0x0044CD00` function. Original executable RTTI strings independently identify
both `<lambda_1>` and `<lambda_2>` as **`SprtCtrlInf::getSprt(SprtID)`**
closures, with `LinkInf<SprtInf*>` as their predicate argument. This confirms
a source identity that was not established by generic Ghidra
`FUN_0044cd00` names or by the historical handoff's opaque pool owner.
The maintained ABI alias `AnimationPoolOwner::resolve_handle(uint32_t)` is
preserved because its actual existing callers are already fully native exact.
This is not a claim that our C++ class spelling was the original spelling.

## Independent original native behavior

The new `scripts/verify-animation-pool-resolver-native.py` independently
re-reads the locked PE and decodes all **141 original instruction heads**, the
entire original 456-byte extent and **all 20 actual E8 direct-call sites**.
Each original call site's signed i386 relative displacement is resolved to
its real destination and checked independently of any C++ source, Ghidra
symbol name, or previous text record.

The original function has two distinct branches:

1. **Normal pool ID:** Reject ID zero; extract the low 16-bit array index.
   Unless it is `0xFFFF`, select the real 0x600-byte pool record in the
   owner at original `+0x710`. Check its actual `active` byte at record
   `+0x5F8`, and compare the live Animation handle word at record
   `+0x4C0` with the full incoming ID. On inactive/mismatched records,
   the original resets only its **by-value local ID** and returns null,
   rather than modifying the caller's handle. A valid record returns its
   embedded Animation pointer. The original helper at `0x004494D0`
   physically indexes with `imul ... 0x600`; the equality/inequality
   helper at `0x00449460` receives the actual stored handle.
2. **Special ID, low word `0xFFFF`:** Iterate the original one-element
   0x48-byte lookup-group array at owner `+0x6C8`. Search the first
   observed intrusive list at group `+0x00`, then the second at
   `+0x18`, with **two distinct by-reference ID-capturing lambdas**
   materialized as separate 40-byte by-value `std::function` predicates.
   Both original searches invoke the same `0x0044A5A0` link search, whose
   actual native `ret 0x28` independently confirms its 40-byte incoming
   predicate value. Each predicate walks real links and compares the
   linked Animation's `+0x4C0` handle against the full captured ID.
   Either match returns the node's Animation pointer; no match returns null.
   The original `0x00449490` group subscript uses a true 0x48 stride.

The third list-shaped 24-byte remainder of each 0x48-byte group is presently
**a layout hypothesis**, not a newly established game method or an assertion
that the original function uses three lists. It is named
`unreviewed_third` in the local, separately typed source-only structure.
This avoids inventing public `AnimationPoolOwner` fields across hundreds of
existing compiler inputs while still preserving the observed group stride.
All original normal and special branch source semantics are represented by
one maintained typed method in `src/AnimationPoolHandleResolve.cpp`, with a
natural `std::function<bool(IntrusiveLink<Animation>&)>` finder and real
`std::array`/`PooledAnimation` layouts.

## CORE/RECON-768 subsequent compiler evidence and actual current state

The original 456B game method remains **NONEXACT** publicly, but independently
reviewed native `SprtID` value ABI and natural two-list/three repeated
pool-index body have now been reproduced in an ignored **456/456-byte,
141/141-instruction, 20/20 original-REL32-field private source probe**.
The private model still has unresolved C++ owner/handle tag and aliasing
identities, so that structural proof does **not** add original native exact
credit. One real callee, 47B `SprtID::operator!=(const SprtID&)` at
`0x00449460`, is separately whole strict exact and recorded in the canonical
ledger. The published scalar-interface semantic source now emits
**410B/122 instructions/13 COFF relocations** after more faithful typed
list and pool access (up from 364B/111/12 at CORE/RECON-757). A proposed
public SprtID signature change broke four already strict caller lengths,
so its diff was preserved privately, the public ABI restored, and all
**nine affected prior canonical units from three actually rebuilt old
objects** were rigorously revalidated. See
[CORE/RECON-768 original exactness and ABI experiment](SPRTID_47_NATIVE_EXACT_AND_RESOLVER_ABI_FRONTIER.md)
for independent original-PE proofs and scoped compiler evidence.

The earlier 364B measurements below are dated **CORE/RECON-757** compiler
results, not the current public maintained-source build. They are not new
strict exact credit.

## Pinned compiler experiment and what is NOT exact

The new source compiles successfully with the installed pinned MSVC
19.44.35211 x86 compiler, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`. The **complete emitted C++ parent is 364 bytes /111 x86
instructions /12 COFF relocations**, versus the **original 456 bytes /141
x86 instructions /20 actual E8 calls**. In particular, the current
`uint32_t` ABI alias produces direct scalar comparison and masking instead
of the original `SprtID` member equality/mask/assignment calls, and the
provisional container access does not reproduce every original native
`std::array`/lambda dispatch call. These are substantial compiler/codegen
and exact ABI differences; there is no prefix comparison, padded function,
assembly patch, fake target or manufactured call to claim false equality.

Accordingly the **entire 456-byte parent is source-present, reconstructed
but NONEXACT**. Its origin is game-authored based on real original
`getSprt(SprtID)` RTTI plus actual pool/handle call graph. It is **not**
in `config/matches.csv`, **not** in `config/match-units.toml`, and contributes
**zero newly exact original bytes**. Both the prior 282-byte exact recursive
retirement path and the exact 37/43-byte wrappers *call* this separate
unproven parent, but exact callers never prove an exact callee or complete
whole-game linkage.

## Reproducible narrow work scope

- `scripts/repo-python scripts/verify-animation-pool-resolver-native.py`
  independently checks all 20 original PE E8 target identities, actual
  original stride/access operands, the 40-byte original std::function
  argument ABI and two immutable original RTTI strings.
- `nice -n 15 scripts/compile-probe.sh src/AnimationPoolHandleResolve.cpp
  build/core757-probe/AnimationPoolHandleResolve.obj /nologo /c
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
  compiles the full source without an original-executable patch.
- Private compare `.analysis/core757-animation-resolve-probe.cpp` and
  `build/core757-probe/AnimationPoolHandleResolve.obj` are **probes only**;
  neither is an accepted canonical unit nor committed.
- Only a **new source file**, focused original-PE verifier, source-present
  mapping, origin audit and documentation changed. No public C++ header,
  compiler profile or prior canonical unit input changed: **zero old native
  providers or exact units require cold replay**, and no full cold replay
  was run. Public tracking/progress/manifest consistency is validated.

Follow-up: recover the original four-byte `SprtID` value method contract
and its real `std::function`/list member signatures without breaking already
exact callers, then try whole 456-byte compiler/relocation replay. Do not
turn this provisional semantic result into exact credit prematurely.

# CORE/RECON-772 — entire 456-byte original Animation pool handle resolver, native strict exact

> **Subsequent exact-child closure (CORE/RECON-774/777):** Both original 159B and 154B link search methods below this already exact parent are now whole strict exact from the same maintained C++ owner. See [the complete native list proof](ANIMATION_LINK_FIND_159_154_EXACT_RECONSTRUCTION.md). The original ID capture is independently corrected to **by-value**, not the earlier assumed by-reference capture, in the [43B original lambda and vtable proof](ANIMATION_POOL_SPRT_LAMBDA_VALUE_CAPTURE_43_EXACT_RECONSTRUCTION.md). Counts below reflect the earlier CORE/RECON-772 checkpoint.

**The entire original function at `0x0044CD00` is now byte exact.** Its
maintained single C++ body lives in `src/AnimationPoolHandleResolve.cpp`.
The Japanese TH20 v1.00a Steamless immutable comparison PE is attested by
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This supersedes the historical **NONEXACT** 364B/410B candidates and the
private 456B typed-ABI probe in CORE/RECON-757/768. Those experiments remain
as provenance, not current acceptance claims.

## Whole-native source and original-type resolution

The real original executable has **456 game-authored .text bytes /141 original
i386 instructions** ending at `0x0044CEC7`, with **20 genuine E8 direct calls**
and **zero original PE HIGHLOW fields within this function**. Independent RTTI
names `SprtCtrlInf::getSprt(SprtID)` with two distinct `LinkInf<SprtInf*>`
predicate lambdas. Native call sites independently prove that the original
input is a four-byte by-value `SprtID`, rather than an arbitrary untyped
integer, and that the real receiver visits an owner array at +`0x6C8`
(one group of stride `0x48`) or pooled animations at +`0x710`
(stride `0x600`).

The original normal path checks a full ID's `0xFFFF` low-word special
selector, validates the target record `active` byte at +`0x5F8`, compares
its `Animation+0x4C0` live ID with the complete input and returns the real
`Animation*`. The special path constructs **two distinct four-byte value-capturing
lambda predicates** as genuine by-value `std::function<bool(IntrusiveLink<Animation>&)>`
objects (40-byte argument ABI), asks the first then second live intrusive
list to find the captured ID, and returns the matching live link's node.
The null/invalid paths clear only the *by-value* ID before returning null,
not the caller's handle. Both list queries access the original owner group
and share one source-level found-link receiver, as corroborated by original
stack-lifetime and machine-code operand order.

The repository's previously accepted callers all use
`AnimationPoolOwner::resolve_handle(uint32_t)`, which already has the **same
native four-byte register/stack ABI** as original `getSprt(SprtID)`. A direct
public aggregate-signature switch was independently tested but enlarged
four already exact original callers by six bytes each. Instead, the
published function preserves that public API and models genuine SprtID
member-operation sites as **typed lvalue views of the existing by-value
four-byte stack input**, with no adapter function, duplicate owner,
compiler-only fake temporaries or target byte patch. The `SprtID` type
and its natural members live in `src/SprtID.hpp`/`src/SprtID.cpp`.
These local MSVC x86 representation views are intentionally narrow, not a
claim of portable C++ strict-aliasing semantics or historical source-level
class names. The owner and handle field widths are attested through existing
live-source x86 layout assertions.

## Independent original PE relocations; full canonical strict match

The standalone `scripts/verify-animation-pool-resolver-native.py` verifies
**all twenty original E8 instruction sites** directly from the original
PE independently of compiled C++, plus its entire native extent, real
`+0x48/+0x600` strides, identity fields and RTTI. The new original unit in
`config/match-units.toml` uses each *corresponding independent original E8
site-to-target witness*, not a relocation destination reverse-solved from
under-comparison target operand bytes. The original targets, with repeated
occurrences kept as separate physical relocation fields, include:

| Call family | Original target | Evidence |
| --- | --- | --- |
| `SprtID` equality and mask | `0x00449430`, `0x004495A0` | original by-value parameter calls; these may share folded original bodies with other accepted types and are not separately recredited |
| Two 0x48-array accesses | `0x00449490` | genuine `imul ..., 0x48` native helper |
| Lambda construction, std::function, list selection | `0x00447960`, `0x00446CC0`, `0x00446D30`, `0x0044A5A0` | original two different lambda owners, true 40B std::function by-value passing |
| Match result node dereference | `0x0040C300` | original `IntrusiveLink<Animation>::node_value()` |
| Invalid ID resetting | `0x004117A0` | actual four-byte integer ID assignment call |
| Three 0x600-array accesses | `0x004494D0` | real indexed pooled record helper |
| ID reference inequality | `0x00449460` | **separately strict exact 47/47-byte** `SprtID::operator!=(const SprtID&)` |

A pinned MSVC **19.44.35211 x86** cold build with `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` emits **exactly 456B /141
instructions and 20/20 COFF REL32 fields at the original offsets**.
Every field's COFF symbol is recorded and linked to the independent native
E8 original target. **All 456 bytes** pass canonical relocation replay
with **zero differences**. The final canonical unit is
`animation_pool_resolve_handle_whole_456`, object
`build/core772-canonical/AnimationPoolHandleResolve.obj` plus locked
compiler receipt, verified by:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolHandleResolve.cpp --source src/SprtID.cpp

The same bounded replay strictly verifies the separate **47/47-byte**
original `SprtID` reference inequality method at `0x00449460`, unit
`sprtid_inequality_47`. The callback/lambda and original STL helper
bodies outside these two accepted physical functions do **not** silently
receive independent exact-game bytes.

Only `src/AnimationPoolHandleResolve.cpp` (previously noncanonical), the new
`src/SprtID.cpp`/`SprtID.hpp`, tracking/evidence and manifest were changed.
**No previously accepted public headers or canonical compiler input was
changed.** The current affected scope is **two new canonical source objects /
two strict units; zero old strict objects to replay**. Existing exact callers
retain the original known four-byte ABI and source content. The rejected
public SprtID signature experiment and all original x86 evidence remain in
ignored `.analysis/core767-*` and `.analysis/core771-*`/`core772-*` probes.
No unfiltered whole-graph cold replay ran.

## Accurate original-game accounting and open bosses

At the preceding CORE/RECON-768 checkpoint, the 47B `SprtID` inequality
was already entered in the exact ledgers: **564 functions /187,139 bytes**.
This checkpoint adds **one new physical original game function, the complete
456-byte resolver**, giving **565 distinct authored whole exact original
functions /187,595 disjoint .text bytes**. Source-present mappings remain
**1,210**, configured canonical units rise **1,211 →1,212** and distinct
pinned canonical object/receipt providers **248 →249**.

These numbers describe *whole function exactness*, not whole-game linkage.
The genuine **12,140-byte Bullet command** parent remains source-absent and
NONEXACT despite 208/210 of its E8 calls now landing on separate exact
canonical game/library children. Other remaining large functions (Enemy ECL
41,967B, Animation VM 39,470B, Player main 3,111B and Bullet draw 273B)
are still separate NONEXACT work. Original compiler-runtime and STL code
are not counted as original authored game-function coverage.

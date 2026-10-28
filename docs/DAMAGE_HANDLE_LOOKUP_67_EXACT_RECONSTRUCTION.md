# CORE/EXACT-407 — entire 67-byte native DamageHandle lookup with safe Identifier32 ABI

Immutable original: user-approved TH20 Japanese v1.00a Steamless
`resources/th20.exe`, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete game-authored `DamageHandle::resolve()` at
`0x004C0E10..0x004C0E52` is now **67/67 strict native exact**
with all **24 original x86 instructions**. Whole original SHA-256:
`5923181925b73f04f66b774a6f2ac47db67b4336ed25a6d35ebaa2b5fdeaf818`.
The independently canonical source is
`src/DamageHandleLookup.cpp` and the locked unit is
`damage_handle_resolve`. This is **one new complete
nonoverlapping native game-owned body**, not an automatically
inherited match from its already exact 166B caller.

## Real PlayerShot damage lookup and by-value Identifier32 protocol

The original entire method first calls the actual
`th20::hit_controller(0)` to retrieve the genuine game's
`HitCtrlInf` owner. It then copies the live four-byte
`DamageHandle` raw ID into a separate by-value
`Identifier32` local and passes that actual typed value
to `HitCtrlInf::find(Identifier32)`. If the game lookup
returns null, it clears the original DamageHandle
word to zero and returns null; otherwise it returns the
real `DamageRegion*`. No null-check for the global Hit
controller itself is added, because the original code
contains none.

This preserves the original `DamageHandle`'s 4-byte raw
scalar field and complete 24-byte
`DamageHandle::DamageHandle(uint32_t)` constructor,
physically folded with `PackedColor` at `0x004142A0`.
Simply retyping that member as `Identifier32` made its
constructor emit a 37-byte wrapper that calls the
separate Identifier32 constructor, **breaking the original
24-byte native ABI**. That header change was tested only
privately, never admitted into source. The two affected
larger source constructors, including their original
post-body CC alignment, were also inspected independently
before rejecting the unnecessary type change.

Instead, the maintained method uses MSVC's
`__builtin_bit_cast(Identifier32, value)`, a true
compiler builtin implementing the same defined bit-copy
semantics as C++20 `std::bit_cast` between two
trivially copyable equal-sized types. It creates a genuine
Identifier32 local **without** an unsafe C++ strict-alias
pointer cast, an unobserved constructor, or a library helper
call. A direct `std::bit_cast` library call under pinned
`/Od /Ob0` emitted additional compiler helper instructions,
so it was not accepted as original. The builtin naturally
emits the original live `mov` into stack slot
`[ebp-0xC]`, followed by the original by-value
argument and native HitCtrlInf call.

The locked source-specific MSVC 19.44.35211 profile is
`/nologo /c /std:c++20 /Od /Ob0 /GS- /Gy /Zl
/arch:SSE2 /fp:precise /EHsc`. The original entire
67-byte method has no stack-security cookie and no
synthetic local buffers; the source-specific `/GS-`
produces exactly that body. Its real enclosing object
and older exact constructors preserve their independently
pinned compiler flags. No assembly, fake signature,
inert local, instruction padding or partial code
comparison was used.

## Independent original PE fields and native callee corroboration

Fresh original x86 decoding found exactly two direct
original E8/REL32 call sites, and the independent original
PE `.reloc` table found **no HIGHLOW fields**:

| Original E8 byte field | Original target | Independently complete callee |
| --- | --- | --- |
| `+0x0C` | `0x00478EC0` | 26B `hit_controller(int)`, unit `hit_controller_get` |
| `+0x26` | `0x004C0D00` | 264B `HitCtrlInf::find(Identifier32)`, unit `hit_controller_find` |

Both actual PE field offsets/types and native target
destinations match the MSVC COFF object exactly.
The earlier native original callee bodies are independently
accepted exact, though these two symbol spellings had
**no previously admitted outbound relocation to reuse**:
their true original PE destinations are the independent
reference authority. Do not claim prior outbound
symbol relocation corroboration that does not exist.
Full immutable target SHA, complete x86 instructions,
E8 field offsets and true original destination proof:
`.analysis/core407-damage-original-pe-refs.json`.
The complete native unit is **59/59 nonrelocation bytes
plus 8/8 independently original relocated bytes = 67/67
strict original bytes**.

## Bounded affected-source replay and preserved exact bosses

The only actual public input edit to
`src/PlayerStorage.hpp` corrects a stale comment;
**no raw member layout, calling convention, old constructor,
native function body or other common ABI changed**.
The existing `src/PlayerShotReset.cpp` comment also
reflects that its 67-byte callee is now separately exact.
The new source provider has one genuinely new strict
unit at `build/core407-canonical/DamageHandleLookup.obj`.

The **old compiler receipt include closure, captured before
editing**, contains exactly **26 existing source providers /
79 strict units**. Adding one new source object/unit gives
**80/80 exact original units across 27 freshly cold-built
source providers**, in six serialized reduced-priority
batches of **5 + 31 + 10 + 10 + 19 + 5**. Full independent
scope and results:
`.analysis/core407-damage-preedit-closure.json`,
`.analysis/core407-damage-replay-groups.json`,
`.analysis/core407-damage-replay-batch0.log` through
`batch5.log`.

All previously complete native PlayerShot reset and
retirement methods (269B, 32B, 166B, 55B, 41B),
the 966B whole Player initial reset and the separate
1,518B Player options boss remain unchanged and strictly
exact. The 67B DamageHandle original was counted
**once**, with no duplicate credit for the
26B Hit controller accessor or the 264B HitCtrlInf finder.
No unfiltered all-repository cold replay or assertion
of whole-game linked/runtime equivalence is made.


## Independent exact callee receipt refresh

Before final admission, the original 26B `hit_controller(0)`
and 264B `HitCtrlInf::find` unit references were checked
through their existing canonical `src/HitCtrlInf.cpp`
provider. Its prior compiler receipt had stale broader
`inputs` inventory hashes from unrelated changed sources,
despite its directly included header bytes being unchanged.
No repository-wide replay was needed. A separate scoped
cold rebuild and strict replay of just this actual
callee owner passed **16/16 original exact units in one
additional cold object**, including both exact call
destinations. Full log:
`.analysis/core407-hit-controller-callee-replay.log`.

This optional source-local native-callee revalidation is
**additional to**, not a replacement for, the **80/80
actually affected source-unit replay across 27 objects**.
The two verification sets are disjoint: **96 distinct
strict units in 28 scoped cold objects**, with no
all-graph cold rebuild. No old exact original byte or
game-authored function gains duplicate credit.

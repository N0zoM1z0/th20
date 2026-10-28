# CORE/EXACT-352 — complete 143-byte EffectInfo scheduled request queue

The immutable original is the user-approved Japanese TH20 v1.00a Steamless
executable, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The *whole original* `EffectInfo::queue_effect` at `0x0049DC60..0x0049DCEE`
is **143 bytes / 49 native i386 instructions** with independent original
interval SHA-256
`445a91f570eff302bd7bdd752a6eb80b226f6e207a0f6809d2bfd525c0370c36`.
The entire game-owned function is now strict exact in the maintained
`src/EffectQueue.cpp`, not a copied decompiler fragment or a shortened
function prefix.

## Complete native queue protocol, verified by independent consumer

The original function obtains the first actual
`std::array<EffectRequest,1024>` entry at `EffectInfo+0x103C` using the
native out-of-line array indexing helper. It tests the signed `type`
field at the front of each **72-byte** request, scanning up to **1024**
requests and incrementing the record pointer by 72 bytes whenever a slot
is in use. For the first `type < 0`, it writes the incoming effect kind to
`+0`, preserves the address of the caller's actual `EffectParameters` in
`+4`, stores the optional original **`Animation*` existing-animation pointer** at `+8`, and stores
the incoming **delay frames** at `+0xC`. It then copies **56 bytes** of
original parameter payload by calling the actual native `memcpy`, writing
into `EffectRequest+0x10`. The loop ends after the first accepted entry;
if none is available, it ends without allocation.

Independently inspected the actual consumer at `0x0049D4A0`: it reads
`EffectRequest+0xC` as the countdown (decrements when positive) and
passes `EffectRequest+0x8` to the later effect creation call as its
optional existing-animation argument. The separate entire original
**227-byte** spawner at `0x0049DB70` proves that the value is an
**`Animation*`**, not the signed integer policy inferred at the earlier
CORE/EXACT-352 checkpoint. That earlier type interpretation was incorrect
and has been explicitly corrected in CORE/EXACT-361. The native queue
method also has **`void` return**:
its previous provisional `EffectRequest*` signature reflected incidental
`EAX` contents, not a real return path. The public
`src/ItemResourceOwners.hpp` ABI is now typed as
`void queue_effect(int delay_frames,int kind,const EffectParameters&
parameters,Animation* existing_animation)`, and the maintained source contains **no**
artificial integer-to-pointer casting or guessed return value.

## Original call references and exactness

The original PE has exactly **two** direct `E8 / REL32` references in the
complete native function:

| Native displacement offset | Original target | Function |
| --- | --- | --- |
| `+0x1A` | `0x00449490` | `std::array<EffectRequest,1024>::operator[](0)` |
| `+0x75` | `0x00543E20` | native `memcpy` |

These references were independently extracted from the unmodified original
x86 instructions, and the natural C++20 candidate exposes matching COFF
relocations at the exact offsets and symbol types; original reference
evidence lives under `.analysis/core352-EffectQueue-original-calls.json`.
No PE `HIGHLOW` fields occur in this 143-byte interval.

With the pinned MSVC 19.44.35211 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` profile, the entire function emits
**143/143 exact native bytes**, matching **49/49 instructions** and both
independent native call targets, with the strict original relocation
oracle rather than just a structural-exact diagnostic. No assembly,
inert locals, injected NOPs, copied original bytes, fake resource owners or
unverified shortening are used.

## Bounded cold replay and corrected existing caller ABI

Only the genuine source inputs changed: `src/EffectParameters.hpp` and its
constructor `src/EffectParameters.cpp`, the typed queue interface in
`src/ItemResourceOwners.hpp`, plus the new complete `src/EffectQueue.cpp`
provider. The old compiler receipt include closure selected **8 existing
canonical source providers / 29 exact units**. The new whole queue adds
one object/unit, yielding **30/30 exact units across nine freshly built
objects**, in three serialized low-priority scoped batches of **8+21+1**.
This includes the already exact original 332-byte Player graze feedback
caller, the separately exact Bullet collision and item dependencies.

The corrected return type changes the **compiler-decorated symbol name**
in the Player graze caller's one `REL32` relocation at native `+0x92`.
The canonical caller manifest was updated to the new true `void` symbol,
while retaining the exact same independently attested native callee
`0x0049DC60`, relocation offset and type. Its fresh strict comparison
again passes **332/332 bytes**. No compiler profile was relaxed, no
original executable or Ghidra database changed, and no unfiltered whole
graph cold replay was performed.

Scope/proof logs: `.analysis/core352-impact-before-edits.json`,
`.analysis/core352-replay-groups.json`, and
`.analysis/core352-replay-batch{0,1,2}.log`.

The separately original `EnemyController::graze_reward_active` and other
effect rendering/lifetime functions remain independent nonexact roots;
this queue acceptance does not establish complete game linkage or runtime
behavioral equivalence.

## Later CORE/EXACT-358 consumer closure

The separate original complete **271-byte** `EffectInfo::process_queued_effects`
frame at `0x0049D4A0` is now strict exact. It reads precisely the 143-byte
queue producer's `type`, optional existing `Animation*`, `delay` and 56-byte
parameter payload, then runs both entire 1024-slot native gameplay loops.
The original 227-byte `spawn_effect` operation it calls is now independently
strict exact as of CORE/EXACT-361.
Read the [full 271-byte frame proof](EFFECT_REQUEST_FRAME_271_EXACT_RECONSTRUCTION.md).

## CORE/EXACT-361 independently revised field-type evidence

The original 227-byte spawner independently proves the old `policy` member
type at request offset `+8` was wrong. The actual field is an optional
existing `Animation*` and is now maintained as such in both producer and
consumer, without changing any of the 143-byte queue's native bytes.
The real complete 143B method and corrected 332B Player graze caller
replayed strict exact along with all 32/32 affected units. See
[the full native 227B spawn and ABI correction](EFFECT_SPAWN_227_EXACT_RECONSTRUCTION.md).

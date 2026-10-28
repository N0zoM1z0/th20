# CORE/EXACT-280 — original exact Timer multiplication and inequality used by Bullet collision

The immutable Japanese TH20 v1.00a Steamless PE is the source of truth,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Both **complete original native Timer member functions** below were
independently verified from the original PE assembly, and then emitted by
normal C++20 with real `Timer` storage and locked MSVC 19.44 x86 `/Od
/Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` without any asm,
NOP padding, ABI facade, raw original bytes or partial function matching.

| Complete native Timer method | Original address | Native bytes | Native relocs | Canonical strict result |
| --- | --- | ---: | ---: | --- |
| `Timer::operator*(std::int32_t) const` | `0x0045C2E0` | **23** | 0 | **23/23** |
| `Timer::operator!=(std::int32_t) const` | `0x0047C620` | **46** | 0 | **46/46** |

The 23-byte method loads the signed `current` field from native `Timer+0x04`
and uses a genuine 32-bit signed `IMUL` by the supplied factor. Its `thiscall`
return is a **full 32-bit integer**, with original 4-byte callee stack cleanup.
The 46-byte method compares exactly that same live signed value against the
incoming integer, stores the boolean selection through a genuine eight-byte
compiler local frame, and returns with the authentic byte-bool/
`MOVZX eax, byte ptr [...]` path. Original source spelling remains inferred.

Original complete native body SHA-256s are
`0dacebea328ebf83bc9dd2fd5bed86aac058f0c233e000eca177b0fb90f5247a`
and `b6dd0cf6f53dd6a2abb77cc1171ae65c935be3ab2d4484a17698804d08025dcd`.
Neither method has any external COFF relocation, so the exact comparator
strictly compares **all 23 and all 46 original bytes**. Both are implemented
in `src/TimerCollision.cpp` as genuine `Timer` members, with their natural
original interfaces in `src/Timer.hpp`; full canonical evidence is
`.analysis/core280-timer-collision-canonical-replay.log`, exactly
**2/2 newly cold-built complete native units in one object**.

## Why this matters for the separate 2,018-byte Bullet collision boss

Original `Bullet::process_collision` at `0x00484A20` is a **whole 2,018B /
532-instruction game state machine**, still **not exact**. Its original
collision-result cleanup uses the native **46B inequality** at
`0x0047C620` to decide whether to interrupt the existing animation
handle. Its graze-fade path invokes the authentic **23B integer multiply**
at `0x0045C2E0`, passing factor two to compute fade from the current Timer.
Earlier complete-function C++ drafts instead inlined
`Timer::current * 2` and called `!Timer::equals(0)`, which can reproduce
similar gameplay but not the real original callee identity nor its
stack and register protocol. Private complete native 2,018B probes now
use the true members. Their parent remains nonexact and contributes
**zero accepted parent bytes** at this checkpoint. The 466B circular
and 777B rectangular Player collision children, seven Animation
mode/tint helpers and exact 51B+44B AnimationHandle chain remain exact.

## Scoped old native regression, not a repository-wide cold replay

`Timer.hpp` is a broadly used actual shared header. Compiler-generated
receipts independently show a **genuine union of 113 already accepted
source providers and 629 previously exact native units** that include
this header. All 113 providers were **cold-recompiled under the strict
locked MSVC profile**, and all **629/629 old complete native units
strictly replayed exact**, including the 1,846B Bullet physics boss,
662B cancellation, 781B screen wrap, 777B Player rectangle collision,
466B Player circle collision, Enemy ECL, rendering and Timer roots.
Only compiler-private MSVC `$SG` local string literal symbols changed;
for every modified manifest anchor, an independent check preserved the
original relocated offset, COFF type and fixed native PE destination.
The affected provider was then recompiled and checked strictly again.
No function bytes, external native relocation destinations or compare
rules were relaxed.

With the two new entire functions this is **631/631 native strict units
across 114 fresh compiler objects**. The focused scoped replay is in
`.analysis/core280-timer-collision-affected-replay-part-{0..9}.log`,
with reproducible `$SG` audit at
`.analysis/core280-timer-collision-sg-corrections.jsonl`. **No
unfiltered whole-repository cold replay** was performed.

The remaining major open whole game roots include 2,018B Bullet collision,
1,404B command11, 273B draw group, 3,735B shot emitter, 12,140B Bullet
command sequencer and 41,967B Enemy opcode dispatcher. None is credited
from a complete helper's acceptance.

# Animation::update — 39,470-byte VM Boss source reconstruction

## 2026-11-28 math-adapter identity correction

Independent complete CRT sections establish that opcodes `0x20`, `0x21` and
`0x22` call tangent, acos and atan. Earlier sqrt/asin/acos labels were wrong;
the maintained names, source bodies and canonical bindings are now corrected.
See [the complete origin review](CRT_X87_CONTROL_TANGENT_ORIGIN_REVIEW.md).
The VM compiled before/after with the same locked profile: all 39,764 bytes of
its complete contribution and all four runtime sections agree after exactly
three external-name substitutions. The 505-call original target multiset is
retained. The VM remains NONEXACT. The focused candidate below is unchanged;
later narrative sections preserve earlier source checkpoints.

## 2026-11-24 current source checkpoint: typed variable-length instruction header

The 39,470B native boss is **SOURCE-PRESENT, NONEXACT** in
`src/AnimationUpdate39470.cpp`. `src/AnmInstruction.hpp` models the native
fixed header: signed opcode at `+0`, unsigned byte advance at `+2`, signed
frame at `+4`, and operand flags at `+6`. `first_operand` at `+8` anchors the
variable-width operand stream; the byte-advance field, not `sizeof`, advances
the script PC. The main VM cursor and case-3 scan cursor use this typed record.
The 160 explicit case labels plus the default sentinel cover all 161 native dispatch entries; the full 505-call target multiset remains present.

The current focused candidate is **39,764B COFF contribution**: **39,124B
code plus the 640B 160-entry compiler switch table**, 8,458 code instructions,
frame `0x7F8`, 505 E8 calls and 214 DIR32 relocations (161 switch-label plus
53 external data/constructor/cookie references). The code is 346 bytes shorter
than the original 39,470B body. Modeling the native controller gate through
the two-bit `AnimationModeBits::mode` and expressing its frozen-controller
exit directly restores the original byte-register sequence. Reversing the
frame comparison into a ready-to-dispatch branch, with the out-of-time path
falling through to the shared motion/interpolation epilogue, moves the first
call-site mismatch from E8 index 7 to index 14: **the first 14 consecutive
E8 positions now align**. Expressing opcode 0's flag clear through the
one-bit `AnimationFlagByte02::bit_10` view and indexing the native opcode map
through its real `0x00435284` sentinel base with the already-checked
`opcode + 1` cursor trims another four code bytes and two instruction heads.
The 636-byte table begins with the signed-opcode `-1` sentinel at index zero;
the range-checked `opcode + 1` cursor now indexes from the true `0x00435284`
base rather than forming a negative array index. It is source-defined as native
`.rdata` in `src/AnimationOpcodeDispatchTable.cpp`; its dedicated probe compares
all 636 COFF bytes and the external ABI symbol against the original PE.
SHA-256: `a030f37522ea5b860c9a06ab56c02978832b477fd4e7c6f94957fbadc7cab34d`.
The source models the native `0xA0` sentinel as the switch `default`, not a
redundant explicit case: the original 161st jump-table entry is exactly the
same `0x0042B8D3` default branch as the out-of-range route. This removes one
compiler switch entry and four bytes from each of the code/table contributions
without changing the 505-call target multiset. The candidate now has **19/505**
exact physical E8 offsets and aggregate E8-offset distance **53,958 bytes**;
all 505 original call targets and the three child-spawn/writeback subsequences
remain verified.
The opcode `0x72` child-spawn operand branch now tests the flagged integer
path first, matching the original `JE`-to-raw / fall-through-to-conversion
layout; this keeps the native integer-conversion call at the 17th E8 site only
16 bytes later than its original offset (previously 42 bytes), without changing
the complete 505-call target multiset or the Boss contribution size.
Opcode `0x77` now follows the same native lifetime and branch ordering: resolve
the previous file before reading the mode flag, take the `JE` zero-mode branch,
and let flagged integer conversion fall through. Its previous-file call moves
from +0x4A2 to +0x478 (native +0x468), and its integer conversion from +0x4EF
to +0x4D5 (native +0x4D1). The total E8-offset distance falls another 68 bytes
to **53,872 bytes**, with the 505-call multiset and contribution size unchanged.
Opcode `0x7C` now uses the same ordering: previous-file lookup first, `JE` to
mode-2, and `JE` to the raw operand path. Its previous-file E8 is at +0x613
(native +0x60D), and its integer conversion is at +0x670 (native +0x676),
reducing the whole-Boss offset distance another 56 bytes to **53,816 bytes**.
Opcode `0x74` now emits the original `JE`-to-raw / fall-through-to-integer
conversion branch rather than the inverse `JNE` layout. Its integer-conversion
call is at +0x7E1 versus native +0x7F1; this is a control-flow ordering match,
not a claim that its physical call offset is closer.
Opcode `0x73` now uses the native `JE`-to-raw / integer-conversion-fallthrough
layout as well. The focused compiler probe pins its `83 E1 01 74 26` branch
sequence; all 505 call targets remain exact, while aggregate E8 offset distance
increases by 26 bytes to **53,848**. This records control-flow fidelity without
claiming a call-site convergence win.
Opcode `0x75` now follows the same original branch order. The probe pins its
`83 E2 01 74 26` sequence, with the integer-conversion path falling through
and the raw-operand path taken by `JE`. All 505 native call targets still
match; this second control-flow correction moves aggregate E8 offset distance
another 26 bytes to **53,874**, not a physical-site improvement.
Opcode `0x78` now materializes the returned `AnimationHandle` as a named
local before calling `resolve()`. This restores the original C++ object
lifetime: native code passes a stack result slot to `spawn_child_and_update`,
then calls `AnimationHandle::resolve` with that same slot address. The prior
prvalue `.resolve()` expression let MSVC reuse EAX as the receiver instead.
The candidate now emits its own local-handle `LEA`/resolve pair and the original
spawn-update/resolve call subsequence. The whole contribution grows by 4B to
39,764B, the physical E8 matches rise from 16 to 19, and the aggregate offset
distance is now **53,958 bytes**. This is a semantic/lifetime recovery, not a
claim of improved aggregate call-site convergence; all 505 original targets
and the child-update-plus-vector-transform sequence remain verified.

The affected File/operand closure strictly replayed **21/21 units in 8 cold
objects**, including the 165/244/301/835B operand leaves, 338B script loader
and 619B child-update helper. The eight VM leaf bodies independently verify
**305/305 bytes** with zero ordinary-byte differences. The original body has
55 PE HIGHLOW fields. This is source and ABI progress, not exactness: no
39,470B exact unit or game-byte credit is claimed.

Target: Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original function is `0x0042B5D0..0x00434FFD`, **39,470 bytes**.
Its immutable PE body SHA-256 is
`044f8246c167aaaf50c00a46a86baa1898e70af55ca5715bcc2450289ba83b87`.

## Recovered dispatcher structure

- 8,559/8,559 i386 instructions cover the full original body.
- 505 original E8 call sites reach 81 distinct callees.
- 55 physical PE HIGHLOW relocation fields are present in the function.
- 23 native callers include `AnimationFile::bind_animation`, both child
  spawn paths, renderer update paths, and multiple gameplay/effect owners.
- The switch contains **all 161 original case labels**, values spanning
  `0x00` through `0xA0` (with the original unimplemented holes preserved).
- The opcode handlers cover timers and control flow, integer/float operands,
  transforms, interpolations, colors, animation spawning, renderer effects,
  random values, and geometry state.

## Natural C++ implementation

`src/AnimationUpdate39470.cpp` defines the actual
`std::int32_t Animation::update()` member. It compiles with the locked MSVC
19.44 x86 C++20 profile and contains no handwritten assembly, naked
functions, NOP padding, dummy memory accesses, or fake code-size fillers.
The recovered call graph is progressively bound to maintained C++ owners:
`Animation`, `AnimationFile`, `AnimationHandle`, `Timer`, `ClockScalar`,
`Motion`, `Interpolation<T>`, `GameRandom`, `GameController`, and the existing
color/geometry helpers. The process-global clock, polygon random stream,
current GameController pointer, zero Vector3 and native float constants now
use their existing typed owners rather than decompiler `DAT_` names. The
opcode dispatch byte table and the remaining global Vector3 are explicitly
typed address-owned data views (`native_animation_opcode_dispatch_435284`
and `native_vector_5c5540`). The original +0x18 animation-file lookup now calls the already
reconstructed whole-exact `NativeAnimationLegacyFileView::previous_file_437470`
member instead of a numeric borrowed-call adapter; its sibling +0x1C getter
remains distinct. The eight exact color/fade/vector-configuration leaves are
now called through their typed owner views. Opcode temporaries also recover
real `Color3`, `Vector3`, `Vector2`, and `Angle` object lifetimes and their
existing native constructors rather than raw byte/word arrays and numeric
constructor adapters. Both four-corner paths now use real `Vector3[4]`
arrays; MSVC emits a 56-byte array-construction helper that is byte-identical
to the original native `0x0040BC20` helper. All eight screen-coordinate
normalizer calls bind directly to the exact typed `normalize_coordinates_438eb0`
leaf and the four output vectors use `AnimationBase::vectors_378`/`vector_398`.
All numeric `FUN_` call macros and the generic numeric call-view declarations
have now been removed from the Boss source. The 0x4397F0 CRT wrapper is
identified as `fmod` (not `atan2`) and is bound to its 48/48-byte exact
`ScalarMath::floating_remainder` owner.

The two original random-threshold sign-mask expressions are represented as
natural IEEE-754 unary negation (the original 16-byte XMM mask is the repeated
`0x80000000` sign bit). The original postfix Timer increment is kept distinct
from the separate prefix increment helper. The two child-spawn families now
use direct return-by-value `AnimationHandle` initialization, with no placement
operator-new shim.

## Exactness status — deliberately not claimed

The current candidate metrics are recorded in the **typed variable-length
instruction update** at the top of this report. The detailed compiler-history
paragraphs below preserve earlier source checkpoints (including the former
37,152B contribution) and are historical snapshots, not current metrics.
The latest focused probe pins the 53 external DIR32 references by symbol and
multiplicity; their sites and roles are not claimed to be exact.

The source now uses the original exact typed owners for the +0x18 file lookup,
all seven color/fade/vector-configuration operations, the eight screen-
coordinate normalizer calls, the Session-to-EffectInfo lookup plus
`EffectInfo::spawn_effect` at opcode 0x7A, the exact 59-byte
`Timer::add_unscaled` leaf used by opcode 4, and the existing exact
`NativeCardRendererFileView::current_file_437950` getter used by all three
negative-index sprite fallbacks. The latter is independently checked as
20/20 bytes with no relocations. Both Timer postfix-decrement sites now call
`timer_4c8--`; the Angle and two float interpolation-duration writes call their
real typed members, with the Angle specialization independently verified
22/22 bytes. Opcode 0x20 now calls the exact CRT tangent adapter
(35/35 bytes). A subsequent lexical-lifetime pass moved 65 one-opcode locals
into their case scopes, removed 12 unused decompiler temporaries, and reduced
the frame another four bytes to `0x858` without changing any opcode or call
site. The four scalar trig opcodes now call the natural cdecl
`scalar_math::{sine,cosine,arccosine,arctangent_single}` wrappers directly; all
four 35-byte CRT adapters replay exactly, including the corrected acos/atan
units and their original `_acos`/`_atan` relocations. Opcode 0x24 now calls
`polar_components`, an 88/88-byte exact cdecl helper that writes independent
x/y output pointers and preserves both original float-wrapper relocations.
The original helper's ECX value is unused, so the natural free-function
signature replaces the former numeric member-call view. This removes a
further four bytes and one instruction head from the preceding 40,812-byte
checkpoint. The preceding Timer/interpolation/math-adapter pass reduced
the stack frame from `0x874` to `0x85c`. Opcode temporaries use natural `Color3`,
`Vector3`, `Vector2`, and `Angle` objects. Both four-corner paths now use
`Vector3 corners[4]`; the MSVC-generated 56-byte array-construction helper is
byte-identical to original `0x0040BC20`, and the normalizer leaf replays exact
at 95/95 bytes. The VM's effect opcode now uses the existing exact Session
lookup and `EffectInfo::spawn_effect` member, preserving its hidden
`AnimationHandle` return and original receiver/argument ABI. The candidate
is 212 bytes larger than the previous 40,836-byte checkpoint as these
corner-array lifetimes and typed owners were restored; this is semantic
progress, not a size optimization.

The generic `NativeAnimationVmCallView` has now been removed completely.
A further 120 calls to Animation, AnimationFile, Motion, AnimationHandle,
Timer, ClockScalar, GameRandom, GameController, Vector3, and Float/Vector/Angle
interpolation/config owners were expanded into direct natural C++ member
expressions; the associated numeric `FUN_` wrappers were deleted.
A further 308 VM operand/value lookups were rewritten from numeric `FUN_`
macros to direct `Animation::integer_argument`, `float_argument`,
`integer_value`, and `float_value` member calls. The source now spells these
high-frequency operations as their real owner methods, with no change to the
measured Boss code or its 505-call target multiset.
Calls formerly routed through numeric method stubs now bind to maintained
`Animation`, `Timer`, `Interpolation`, `AnimationFile`, `Motion`, `GameRandom`,
`GameController`, `ClockScalar`, `EffectInfo`, `NativeCardRendererFileView`,
`Vector3`, `ScalarMath`, and `MotionMath` owners. The two original `0x4397F0`
call sites now use the exact typed `std::fmod` wrapper; the 14 previous-file
lookups and corner-projection dispatch also use direct typed C++ owners.

A second prologue/case lifetime pass replaced the two raw Timer pointer
increments with `timer_4d8++` and `timer_4c8++`, removed the copied entry
callback pointer, and scoped file lookup, random, scan and clock temporaries.
It removes another **112 bytes / 15 instruction heads** from the previous
40,808-byte checkpoint and reduces the frame from `0x858` to `0x84c`. A
subsequent typed-field pass replaces 65 additional raw offset expressions
with AnimationBase channel/vector/variable/flag members, converts the parent
16-word variable copy to `AnmVariables` assignment, and restores the
Vector3[4] transfer as typed vector copy/reset. That pass removes another
**116 bytes / 16 instruction heads** from 40,716B and reduces the frame to
`0x844`. The flag storage now has one-byte union aliases for the native
`+0x49A`, `+0x4A1`, and `+0x4A3` bytes while retaining the named bitfield views;
23 affected Animation consumers compile with the same packed layout. The Boss
has no remaining raw `this + offset` member expressions. A final interpolation
owner pass removes 48 temporary pointers and binds the five embedded
Vector/Angle/Float interpolation objects plus three Vector2 fields directly to
their `AnimationBase` members. The original shared Angle-mode/reset call
addresses and all 505 call destinations are retained. It removes another
**68 bytes / 8 instruction heads** from 40,600B and reduces the frame from
`0x844` to `0x830`. The next Boss-local cleanup removes three dead decompiler
scratch values (`this_local`, `local_ac`, and `local_750`) and spells six
unused spawn-result handles as discarded return values while preserving all
spawn calls. The dead stores account for another **48 bytes / 5 instruction
heads** from 40,532B and reduce the frame to `0x824`. A broad result-expression
pass then collapses 174 immediate float-return scratch assignments, 23
integer/float argument pointer temporaries, and the shared `iVar2` register
spill. The source now assigns helper results directly to their destination
values and writes through the typed argument accessors. This removes another
**3,172 bytes / 410 instruction heads** from 40,484B and reduces the frame to
`0x80C`; the full 505-call target multiset and all 161 opcode labels remain
unchanged. The same typed-return pass then inlines the three remaining
spawn-child handles that are immediately resolved and dereferenced. Their
`AnimationHandle` temporaries are now expressed as direct `spawn_child(...).resolve()`
and `spawn_child_and_update(...).resolve()` chains, with the same return
semantics and no changed E8 targets. This removes another **48 bytes / 6
instruction heads** from 37,312B and leaves a 37,264-byte contribution with
36,620 code bytes and a 644-byte switch table. The stack allocation is now
`0x800`, four bytes below the original `0x804`. A follow-up owner pass removes
five more one-use Animation receiver aliases from the discarded-child spawn
opcodes. The three resolved-child results are now typed as `Animation*` and
write their X/Y channels through `base.vector_484`, rather than integer pointer
arithmetic; the four component locals become direct conditional member
assignments, while the transformed Vector3 path retains its ordered inputs.
The five receiver-alias removals account for another **60 bytes / 10
instruction heads** from 37,264B and reduce the frame from `0x800` to `0x7EC`.
The follow-up restores the three previous-file calls to their original order
before the VM integer-value reads and replaces three remaining raw Vector3
stack temporaries with direct `AnimationBase::vector_2c` / `vector_484`
assignments. The `0x77`/`0x7C` child-writeback paths and the `0x78` child-update
plus transformed-Vector3 path now have independently pinned original E8
subsequences: two spawn/resolve/two-float-writeback sequences and one
spawn/resolve/transform sequence. This removes another **52 bytes** from
37,204B. The current contribution is **37,152B** (36,508B code plus the 644B
switch table), with 7,920 code instructions and a `0x7F8` frame (12B below
the original `0x804`). The full 505-call target multiset and all three
child-call subsequences remain intact. A subsequent global-owner pass removes
the remaining raw `DAT_` globals from the Boss: the process `ClockScalar`,
`GameRandom`, `GameController*`, zero `Vector3`, seven native float constants,
opcode dispatch table and remaining `Vector3` data all have typed C++ names.
The function now has **215 DIR32 relocations** (162 switch-label and 53
external data/constructor/cookie references), up from 210; the focused probe
pins all 53 external symbol roles and their multiplicities. This is source
ownership recovery, not an exact relocation-site claim.

This remains a complete compiling semantic source translation, not a strict
exact match. It has no `match-units.toml` exact unit and contributes **zero**
new exact functions. The candidate is now **2,318 bytes smaller overall** than the original body:
36,508 bytes of code plus a 644-byte compiler switch table. The code portion
has 639 fewer decoded instruction heads than the original body, so the byte
gap is not an instruction-count proxy. The original stack allocation is
`sub esp, 0x804`; the current candidate now uses `sub esp, 0x7F8` after
removing obsolete Timer pointer temporaries, numeric call-view paths, unused
decompiler locals and over-scoped opcode temporaries. Absolute-data relocation
ownership and the remaining instruction/frame-layout differences are
unresolved. No exactness credit is claimed from call-target
parity alone.

The next pass should reconcile the 0x0C stack-frame delta, absolute-data
references, and ordinary instruction bytes using natural C++ types and
lifetimes. Do not add padding or assembly to close the size gap.

## Focused verification

The current focused Boss probe compiles the full 161-opcode source, verifies
all 505 original call destinations, checks the natural 56-byte Vector3 array
helper against `0x0040BC20`, and pins the current 37,152-byte contribution and
`0x7F8` frame. It also checks the original ordered child-spawn/resolve/writeback
subsequences (two child writebacks and one child-update/vector-transform path). The changed Animation flag/owner closure was independently
compiled across 23 affected translation units and strict-replayed as **112/112
units in 20 cold objects**. The separate Timer/ScalarMath closure strict-replayed
as **29/29 units in 3 cold objects**. These are targeted source closures, not a
full-project cold replay; the Boss itself remains explicitly NONEXACT.

```bash
scripts/repo-python scripts/probe-animation-update39470.py
scripts/repo-python scripts/verify-animation-vm-leaves-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

# Animation::update — 39,470-byte VM Boss source reconstruction

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
`Motion`, `Interpolation<T>`, `GameRandom`, and the existing color/geometry
helpers. The original +0x18 animation-file lookup now calls the already
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

The current candidate COFF contribution is **40,696 bytes**: **40,052 bytes
of code plus a 644-byte, 161-entry compiler-generated switch table**. The
code portion decodes to 8,382 instruction heads and 505 E8 calls, compared
with the original 39,470-byte body / 8,559 instruction heads / 505 E8 calls.
The candidate has 505 REL32 call relocations and 210 DIR32 relocations; the
original PE body has 55 physical HIGHLOW fields.

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
22/22 bytes. Opcode 0x20 now calls the existing exact CRT sqrt adapter
(35/35 bytes). A subsequent lexical-lifetime pass moved 65 one-opcode locals
into their case scopes, removed 12 unused decompiler temporaries, and reduced
the frame another four bytes to `0x858` without changing any opcode or call
site. The four scalar trig opcodes now call the natural cdecl
`scalar_math::{sine,cosine,arcsine,arccosine}` wrappers directly; all four
35-byte CRT adapters replay exactly, including the newly added asin/acos
units and their original `_asin`/`_acos` relocations. Opcode 0x24 now calls
`polar_components`, an 88/88-byte exact cdecl helper that writes independent
x/y output pointers and preserves both original float-wrapper relocations.
The original helper's ECX value is unused, so the natural free-function
signature replaces the former numeric member-call view. This removes a
further four bytes and one instruction head from the preceding 40,812-byte
checkpoint. The preceding Timer/interpolation/sqrt pass reduced
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
`0x800`, four bytes below the original `0x804`.

This remains a complete compiling semantic source translation, not a strict
exact match. It has no `match-units.toml` exact unit and contributes **zero**
new exact functions. The candidate is now **2,206 bytes smaller overall** than the original body:
36,620 bytes of code plus a 644-byte compiler switch table. The code portion
has 633 fewer decoded instruction heads than the original body, so the byte
gap is not an instruction-count proxy. The original stack allocation is
`sub esp, 0x804`; the current candidate now uses `sub esp, 0x800` after
removing obsolete Timer pointer temporaries, numeric call-view paths, unused
decompiler locals and over-scoped opcode temporaries. Absolute-data relocation
ownership and the remaining instruction/frame-layout differences are
unresolved. No exactness credit is claimed from call-target
parity alone.

The next pass should reconcile the 0x04 stack-frame delta, absolute-data
references, and ordinary instruction bytes using natural C++ types and
lifetimes. Do not add padding or assembly to close the size gap.

## Focused verification

The current focused Boss probe compiles the full 161-opcode source, verifies
all 505 original call destinations, checks the natural 56-byte Vector3 array
helper against `0x0040BC20`, and pins the current 40,532-byte contribution and
`0x830` frame. The changed Animation flag/owner closure was independently
compiled across 23 affected translation units and strict-replayed as **112/112
units in 20 cold objects**. The separate Timer/ScalarMath closure strict-replayed
as **29/29 units in 3 cold objects**. These are targeted source closures, not a
full-project cold replay; the Boss itself remains explicitly NONEXACT.

```bash
scripts/repo-python scripts/probe-animation-update39470.py
scripts/repo-python scripts/verify-animation-vm-leaves-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

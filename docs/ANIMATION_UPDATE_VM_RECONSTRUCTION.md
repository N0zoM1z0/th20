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
Remaining numeric call-view declarations are scoped to unreconstructed
helper owners.

The two original random-threshold sign-mask expressions are represented as
natural IEEE-754 unary negation (the original 16-byte XMM mask is the repeated
`0x80000000` sign bit). The original postfix Timer increment is kept distinct
from the separate prefix increment helper. The two child-spawn families now
use direct return-by-value `AnimationHandle` initialization, with no placement
operator-new shim.

## Exactness status — deliberately not claimed

The current candidate COFF contribution is **40,912 bytes**: **40,268 bytes
of code plus a 644-byte, 161-entry compiler-generated switch table**. The
code portion decodes to 8,400 instruction heads and 505 E8 calls, compared
with the original 39,470-byte body / 8,559 instruction heads / 505 E8 calls.
The candidate has 505 REL32 call relocations and 213 DIR32 relocations; the
original PE body has 55 physical HIGHLOW fields.

The source now uses the original exact typed owners for the +0x18 file lookup,
all seven color/fade/vector-configuration operations, the eight screen-
coordinate normalizer calls, the Session-to-EffectInfo lookup plus
`EffectInfo::spawn_effect` at opcode 0x7A, the exact 59-byte
`Timer::add_unscaled` leaf used by opcode 4, and the existing exact
`NativeCardRendererFileView::current_file_437950` getter used by all three
negative-index sprite fallbacks. The latter is independently checked as
20/20 bytes with no relocations. Opcode temporaries use natural `Color3`,
`Vector3`, `Vector2`, and `Angle` objects. Both four-corner paths now use
`Vector3 corners[4]`; the MSVC-generated 56-byte array-construction helper is
byte-identical to original `0x0040BC20`, and the normalizer leaf replays exact
at 95/95 bytes. The VM's effect opcode now uses the existing exact Session
lookup and `EffectInfo::spawn_effect` member, preserving its hidden
`AnimationHandle` return and original receiver/argument ABI. The candidate
is 212 bytes larger than the previous 40,836-byte checkpoint as these
corner-array lifetimes and typed owners were restored; this is semantic
progress, not a size optimization.

This remains a complete compiling semantic source translation, not a strict
exact match. It has no `match-units.toml` exact unit and contributes **zero**
new exact functions. The total contribution is **+1,442 bytes**, comprising
+798 bytes of code and the 644-byte compiler switch table. The code portion
has 159 fewer decoded instruction heads than the original body, so the byte
gap is not an instruction-count proxy. The original stack allocation is
`sub esp, 0x804`; the current candidate now uses `sub esp, 0x85C` after
removing the obsolete Timer pointer temporaries and numeric call-view paths.
Absolute-data relocation ownership and the remaining instruction/frame-layout
differences are unresolved. No exactness credit is claimed from call-target
parity alone.

The next pass should reconcile the 0x70 stack-frame delta, absolute-data
references, and ordinary instruction bytes using natural C++ types and
lifetimes. Do not add padding or assembly to close the size gap.

## Focused verification

```bash
scripts/repo-python scripts/probe-animation-update39470.py
scripts/repo-python scripts/verify-animation-vm-leaves-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

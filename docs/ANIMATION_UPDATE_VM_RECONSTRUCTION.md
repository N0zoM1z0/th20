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
remains distinct. Remaining numeric call-view declarations are explicitly
scoped to unreconstructed helper owners.

The two original random-threshold sign-mask expressions are represented as
natural IEEE-754 unary negation (the original 16-byte XMM mask is the repeated
`0x80000000` sign bit). The original postfix Timer increment is kept distinct
from the separate prefix increment helper. The two child-spawn families now
use direct return-by-value `AnimationHandle` initialization, with no placement
operator-new shim.

## Exactness status — deliberately not claimed

The current candidate object is **41,004 bytes / 8,721 instructions / 505
E8 calls**, compared with the original 39,470 / 8,559 / 505. The candidate
has 505 REL32 call relocations and 213 DIR32 relocations; the original PE
has 55 physical HIGHLOW fields. The source also restores the native shared
return-one block to its original late function-tail position and removes the
redundant `void*` alias for the member `this` pointer. An independent
target-multiset check now
confirms that **all 505 candidate E8 calls resolve to the exact same 505
original target addresses**, including the postfix Timer helper, both
AnimationFile child-spawn helpers, and both corner-projection dispatches.

This is a complete compiling semantic source translation, not a strict exact
match. It has no `match-units.toml` exact unit and contributes **zero** new
exact functions. The remaining difference is **+1,534 bytes / +162 decoded
instructions**. The original stack allocation is `sub esp, 0x804`; the current
candidate uses `sub esp, 0x874`. Absolute-data relocation ownership and the
remaining instruction/frame-layout differences are still unresolved. No
exactness credit is claimed from call-target parity alone.

The next pass should reduce the Ghidra-style function-scope temporary set
into natural opcode-local lifetimes, replace remaining numeric borrowed view
calls with their real C++ owners, and reconcile the candidate stack frame,
DIR32 data references, and all ordinary bytes. Do not add padding or assembly
to close the size gap.

## Focused verification

```bash
scripts/repo-python scripts/probe-animation-update39470.py
scripts/repo-python scripts/verify-animation-vm-leaves-native.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

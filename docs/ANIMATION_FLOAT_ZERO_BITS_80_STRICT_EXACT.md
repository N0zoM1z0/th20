# CORE/RECON-996 — original 80B float positive-zero byte predicate, strict exact

The locked target is Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The previously unidentified original `0x0045D270..0x0045D2BF` is a complete
**80-byte /27 x86-instruction** bitwise zero test of a four-byte value.
It is a real native helper called by the separately strict-exact
**202B** `std::fill_n<float>` source at `0x0045D360`, original E8 `+0x43`.
No original game algorithm or 2,884B particle-update parent is inferred
from that connection.

## Original physical code and relocation roles

[`verify-animation-float-zero80-native.py`](../scripts/verify-animation-float-zero80-native.py)
independently pins the complete 80B original body SHA-256
`5dec067b58b2da92ce0e6da0ce707ece83c1c5f0b94e0ad4db4bf26fba11372b`,
checks its genuine `ret` at 80B, its actual original E8 offsets and the
PE HIGHLOW site. The original 202B parent is separately SHA-pinned and its
physical call to this helper is checked; the acceptance is not based on a
provisional Ghidra name.

| Original body relocation field | Target | Verified role |
| --- | --- | --- |
| `+0x07`, DIR32 / PE HIGHLOW | `0x005B25C0` | compiler security cookie |
| `+0x23`, REL32 | `0x00544D77` | actual CRT `memcmp`, E8 opcode at `+0x22` |
| `+0x48`, REL32 | `0x005429EE` | compiler cookie check, E8 opcode at `+0x47` |

The natural source [`src/AnimationFloatZeroBits80.cpp`](../src/AnimationFloatZeroBits80.cpp)
initializes a real local `float` to `+0.0f`, compares its **four object bytes**
with the input via `std::memcmp`, and tests for equality. It does **not**
replace this with numerical equality: `-0.0f` is numerically equal to
`+0.0f` but has a different IEEE-754 object representation, so
`*input == 0.0f` would change the original semantics and code generation.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits exactly **80B/27 instructions**,
**68/68 identical original nonrelocated bytes**, and the same three
original PE field offsets, relocation types and target destinations.
The maintained one-function canonical unit
`animation_float_zero_bits_80` passed a **one-source, one-object cold build**:

```text
animation_float_zero_bits_80: exact (80/80 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The preexisting original 202B `std::fill_n<float>` and its 123B color
counterpart remain independent exact parents. Their acceptance must be
checked in the **affected-only** scope, never by an unfiltered project-wide
cold replay. No `src/Timer.hpp`, particle-grid object layout or renderer
ABI was changed to obtain this match.

**Origin qualification:** the actual helper is almost certainly a
compiler/library floating-point fill optimization, but its original C++
spelling and physical folded-symbol owner remain unproven. It is recorded as
`CxxRuntime / unknown origin`, not game-authored code. It adds one local
whole-native exact function unit and 80 uniquely compared physical bytes,
**zero credited authored-game bytes**. The original 2,884B particle update
and 5,993B Animation Draw Boss remain separately NONEXACT.

```sh
scripts/repo-python scripts/verify-animation-float-zero80-native.py \
  --candidate-object build/core996-canonical/AnimationFloatZeroBits80.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationFloatZeroBits80.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/AnimationRibbonFillN123202.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

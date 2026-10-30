# CORE/RECON-965 — complete original 236B recursive Animation raw-world-position Boss strict exact

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0044CB80` is a complete game-authored **236B/77-i386**
`Animation` position-composition function. This is distinct from the
previously accepted public `Animation::position` and
`Animation::transform_position` methods: it returns a raw composed
`Vector3` by reference and recurses through its real `parent_558`
without adding viewport/window scaling. Its caller graph includes the
separate original `0x004512B0` animation spawning/positioning path;
the large caller is not inferred exact from this callee.

## Immutable original native and return evidence

[`scripts/verify-animation-raw-world-position236-native.py`](../scripts/verify-animation-raw-world-position236-native.py)
independently checks every original function byte through genuine
`ret 4`, all 77 i386 instructions, **eight native E8 sites and
physical destinations**, one original security-cookie **HIGHLOW
`+0x07 -> 0x005B25C0`**, the self-recursion site and the four actual
following `INT3` alignment bytes:

| Original E8 | Original physical destination | Meaning |
| --- | --- | --- |
| `+0x2C/+0x44` | `0x00429570` | Two genuine typed `Vector3::operator+` bodies |
| `+0x93` | `0x00437930` | Parent Animation rotation Z getter |
| `+0xA4` | `0x00458FA0` | Genuine three-lane `rotate_xy` on the returned vector |
| `+0xAF` | `0x00422E10` | Native Vector3 parent-position temporary constructor |
| `+0xC7` | **`0x0044CB80`** | Physically real recursive **self-call**, not a guessed neighboring method |
| `+0xD3` | `0x004296E0` | Actual `Vector3::operator+=` to add parent position |
| `+0xE1` | `0x005429EE` | Native security-cookie checker |

The original function first composes `Animation::vector_5bc`,
`AnimationBase::vector_2c`, and `AnimationBase::vector_484` in that
order. It recurses only if a real parent exists and the native
`base.flags.word_04` bit 12 is clear. If bit 5 is set, it rotates the
result's XY lanes by the parent's actual rotation Z, then recursively
adds the parent's raw world position. No unrelated inherited viewport
scale or fake pointer field is included. Parent-cycle policy is outside
this original source reconstruction.

[`src/AnimationRawWorldPosition236.cpp`](../src/AnimationRawWorldPosition236.cpp)
uses the *existing maintained `Animation` layout*, a zero-extra-storage
source-level derived view, real `Vector3` operations, and a natural
recursive call to the same native method. No global `Animation.hpp`
modification, memory-access dummy statement, manual NOP or x86 assembly
was needed. Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` produces the entire authentic
236B body and **200/200 nonrelocated bytes**, all eight true E8 and
the original HIGHLOW. Source-scoped canonical original-target replay:

```text
animation_raw_world_position_236: exact (236/236 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This adds **one distinct game-authored whole exact function and +236
native `.text` bytes**; previously accepted math operations and their
possibly folded aliases are not counted again. The full 2,884B particle
Update and remaining 39,470B Animation VM remain separate nonexact
parents; whole-game build/link/playability is not claimed.

```bash
scripts/repo-python scripts/verify-animation-raw-world-position236-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRawWorldPosition236.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

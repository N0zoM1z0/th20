# CORE/RECON-980 — entire original 92B locked Renderer PRNG generation whole strict exact

Original immutable Japanese TH20 Steamless v1.00a PE SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native game function `0x00449D20` is a complete **92B/30-i386**
locked RandomState advance, not a Timer method. The real original
receiver contains a four-byte `RandomState` member at `+0x04` and
stores the next full-width output word at `+0x14`, returning its low
8 bits as an unsigned byte in EAX. The method locks real process
`LockRegistry` slot **10** and releases the guard before returning.

## Independent original PE, true ownership and compilation profile

[`scripts/verify-animation-renderer-random-pulse92-native.py`](../scripts/verify-animation-renderer-random-pulse92-native.py)
authenticates all 92 original code bytes, all 30 i386 instructions,
native return, the actual five E8 original instruction sites and
physical destinations, and the two real PE HIGHLOW relocations:

| Original relocation | Physical target / role |
| --- | --- |
| E8 `+0x1A/+0x23/+0x45` | `0x0040C310/0x0040B730/0x0040B900`, native lock slot, guard ctor/dtor |
| E8 `+0x2E` | `0x004235F0`, **already separately classified library `RandomState::next()`**, not a game Timer increment |
| E8 `+0x53` | `0x005429EE`, actual compiler `/GS` cookie verification |
| DIR32 `+0x07` | `0x005B25C0`, genuine native stack security cookie |
| DIR32 `+0x16` | `0x005C0240`, native process recursive-lock registry |

The prior Ghidra pseudo-C listed a generic `FUN_004235F0` and
mistakenly suggested an untyped `uint*`; independent comparison to the
original physical callee and source shows it is the already documented
**four-byte STL-compatible `RandomState`**. The method's two typed
member offsets are verified, not assumed from nearby names.

The maintained non-owning
[`src/NativeRendererRandomPulse.hpp`](../src/NativeRendererRandomPulse.hpp)
records the true `RandomState+0x04` and published word `+0x14` with
bounded, explicitly unknown intermediate fields; it does not invent
Renderer ownership or allocate a new pool object. Its natural
[`src/AnimationRendererRandomPulse92.cpp`](../src/AnimationRendererRandomPulse92.cpp)
uses `std::lock_guard<std::recursive_mutex>` and
`last_14=random_04.next()`, with a normal byte return.

**Compiler-profile discovery matters here.** Pinned MSVC 19.44 x86
C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl` (without
`/EHsc`) emits the exact original native 92B/30-instruction function
with **64/64 nonrelocated byte matches and all seven real COFF fields**.
The same source with `/EHsc` emits an **incorrect 141B** function due
to a C++ EH frame absent from the original PE. The first attempt using
untyped pointer casting under `/EHsc` emitted an incorrect **154B**
function: it had both an EH frame and extra pointer temporaries.
These were rejected; the original-specific no-EH profile is a real
compiler difference, not a synthetic instruction patch.

```text
animation_renderer_random_pulse_92: exact (92/92 bytes)
Exact replay: 1/1 unit, 1 cold object
```

One new original **game-authored whole exact function/+92 native `.text`
bytes** is credited. The original `RandomState::next()` remains
`origin=library/exclude` and is not counted again; unrelated Renderer
update loops remain independently NONEXACT until complete original
replay. No unfiltered full cold replay or linked-game claim.

```bash
scripts/repo-python scripts/verify-animation-renderer-random-pulse92-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRendererRandomPulse92.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

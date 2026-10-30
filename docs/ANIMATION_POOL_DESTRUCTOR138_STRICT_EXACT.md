# CORE/RECON-991 — whole original 138B AnimationPool owner destructor, native 5B INT3 alignment, fully typed lifetime chain

Locked original Japanese TH20 Steamless v1.00a executable SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x00449260` is the complete game-owned **138B/41-i386**
AnimationPool owner's destruction routine. The actual PE also contains
**five `INT3` alignment bytes immediately following its final `ret`**.
The full pinned MSVC C++20 COFF function contribution has **143B**,
and all five physical padding bytes are identical to the original PE.
Canonical coverage is **138 original function bytes**, with
**`compare_size = 143`** to validate the *entire* compiled function
plus native alignment, not merely a convenient first 138B prefix.

## Independently evidenced real object layout

The original native destructor order is a stronger constraint than
old provisional Ghidra labels. Every original call target was resolved
against the immutable PE and previously accepted source:

| Real receiver offset | Actual original C++ subobject | Original E8 target |
| --- | --- | --- |
| `this+0x6C8` | First **72B Renderer** containing three 24B Animation intrusive lists | E8 `+0x38 -> 0x00449490` 0x48 stride selector, then E8 `+0x3F -> 0x0044A3A0` independently whole exact **339B Renderer double-list retirement** |
| `this+0x6000818` | Original trailing **`Animation`** (real 0x5E4-byte class) | E8 `+0x4E -> 0x00449370`, existing full original `Animation::~Animation` 62B |
| `this+0x710` | Original **`AnimationPool` containing 65,536 `PooledAnimation` records × 0x600 bytes**, true 96MiB class | E8 `+0x5C -> 0x004491E0`, previously accepted 78B array destructor |
| `this+0xDC` | Original resident **`Animation`** at the exact offset preceding the renderer state | E8 `+0x6A -> 0x00449370`, same existing 62B Animation destructor |
| `this+4` | Real native **`Worker`** (16B including `std::jthread` and termination flag), **not `std::recursive_mutex`** | E8 `+0x75 -> 0x0040B980`, existing whole exact 71B `Worker::~Worker` |

This distinction was discovered by checking real previously accepted
native originals: the first attempt guessed that `this+4` was a mutex;
that source correctly failed to emit the original final destructor
call. Independent inspection established the true original
`Worker::~Worker` at `0x0040B980`. The maintained
[`src/AnimationPoolDestructor138.cpp`](../src/AnimationPoolDestructor138.cpp)
uses actual `Worker`, `Animation`, `NativeRendererClassificationView`,
and `AnimationPool` classes, with static assertions for **all five**
native original member offsets. Unknown small gaps retain **opaque
bytes**, not invented methods, virtual storage, or guessed roles.
It is a structural ABI view **only**: this source does not create a
new pool allocation or constructor, and the 96MiB records are the
existing true `AnimationPool`, not a synthetic dummy array.

## Whole original body and physical relocation proof

[`scripts/verify-animation-pool-destructor138-native.py`](../scripts/verify-animation-pool-destructor138-native.py)
independently checks the immutable original complete body digest
`63ef2762cf0d0d8868c8ab23868ae6ae725ca763a8fa93e5c8a01ede495f8393`,
41 complete x86 instructions, genuine `ret`, all six native E8
positions/destinations, EH handler PE HIGHLOW
`+0x06 -> 0x005679A0`, security cookie HIGHLOW
`+0x15 -> 0x005B25C0`, all typed member offsets, two authentic
compiler `nop` instructions and **exactly five original `INT3`**
alignment bytes after the function.

The initial natural typed constructor/destructor probe with a guess
about the final `std::recursive_mutex` emitted **132B** and missed
`Worker` destruction. The correct class with a **real `Worker`
member** naturally emits **138B/41 instructions plus its complete 5B
INT3 alignment** under pinned MSVC 19.44 x86 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`. Its
eight genuine COFF relocations point exactly to the physically
attested 6 E8 and 2 PE HIGHLOW. There is no manual NOP, handwritten
machine code, target copy or partial prefix matching.

Original-target-bound scoped replay includes the entire new destructor,
its previously whole exact 339B/308B game release chain and actual
previously accepted `Worker` source:

```text
animation_pool_destructor_138: exact (138/138 coverage bytes; 143/143 compared bytes)
animation_renderer_all_retire_339: exact (339/339 bytes)
animation_pool_release_308: exact (308/308 bytes)
worker_destruct: exact (71/71 coverage bytes; 76/76 compared bytes)
... eight other accepted Worker units exact
Exact replay: 12/12 units, 4 cold objects
```

This adds **one distinct original game-authored whole 138B head/+138
native `.text` bytes**. Previously credited 339B/308B Animation
release, two 62B Animation destructors, 78B array destructor and
71B Worker destructor are not counted again. Neither executable
linkage nor game playability is claimed. No full cold replay occurred.

```bash
scripts/repo-python scripts/verify-animation-pool-destructor138-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPoolDestructor138.cpp --source src/AnimationRendererAllRetire339.cpp --source src/AnimationPoolRelease308.cpp --source src/Worker.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

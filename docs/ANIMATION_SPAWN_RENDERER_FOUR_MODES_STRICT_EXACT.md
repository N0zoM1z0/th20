# CORE/RECON-959 — four complete original 72B/75B Renderer spawn modes whole strict exact

Locked original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The full original [922B `AnimationFile::spawn` Boss](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md)
chooses one of **four distinct game-authored Renderer list-registration
functions** by its actual native flags. They share the same two physical
24-byte intrusive Animation lists: the primary one is at offset zero,
the secondary at `+0x18`. Each returns a genuine `AnimationHandle` by
value via the compiler's hidden return address, and publishes the new
Animation through the same original pool-registration call. All four
complete C++ functions are now individually **whole original strict exact**.

## Original-only PE audit and actual parent E8s

[`scripts/verify-animation-spawn-renderer-four-modes-native.py`](../scripts/verify-animation-spawn-renderer-four-modes-native.py)
independently reads the locked original executable and checks all four
complete function boundaries, actual i386 instruction counts and
`ret 8`, **two E8 site/destination pairs per method**, **one genuine
PE HIGHLOW site/target per method**, native `Animation+0x4E8`
renderer pointer, link field `Animation+0x4EC`, the real 24-byte
secondary-list address and the four physical E8 sites from the
independently exact 922B parent:

| Original native function | Physical native calls | Original full body |
| --- | --- | --- |
| `0x0044B7F0` — primary append | E8 `+0x27 -> 0x00411EA0` and `+0x3A -> 0x0044C8F0`; parent E8 `0x00451011` | **72B/24 i386**, `60/60` nonrelocation bytes |
| `0x0044B840` — primary prepend | E8 `+0x27 -> 0x0044A6B0` and `+0x3A -> 0x0044C8F0`; parent E8 `0x00450FF8` | **72B/24 i386**, `60/60` nonrelocation bytes |
| `0x0044B8E0` — secondary append | E8 `+0x2A -> 0x00411EA0` and `+0x3D -> 0x0044C8F0`; parent E8 `0x00450FC2` | **75B/25 i386**, `63/63` nonrelocation bytes |
| `0x0044B890` — secondary prepend | E8 `+0x2A -> 0x0044A6B0` and `+0x3D -> 0x0044C8F0`; parent E8 `0x00450F8D` | **75B/25 i386**, `63/63` nonrelocation bytes |

The single native HIGHLOW in each source function references the
original current AnimationPool pointer at **`0x005C0028`**:
original field offset `+0x36` for 72B modes and `+0x39` for 75B
modes. The `0x00411EA0` append helper is a previously accepted
folded `IntrusiveList` physical body. The `0x0044A6B0` prepend and
`0x0044C8F0` handle-publication callee are **separate native functions**;
their independent C++ source exactness is not assumed from these callers.

## One C++ class shared by all four methods and the 922B parent

[`src/NativeSpawnRendererView.hpp`](../src/NativeSpawnRendererView.hpp)
declares **one** Renderer view with two existing
`IntrusiveList<Animation>` subobjects, no artificial padding, and
four original member-method entrypoints. The same declaration is
included by [the 922B Boss](../src/AnimationFileSpawn922.cpp) and
[`src/AnimationSpawnRendererFourModes.cpp`](../src/AnimationSpawnRendererFourModes.cpp).
The source uses actual `Animation::field_4e8`, `link_4ec` and genuine
`IntrusiveList<Animation>` `append/prepend` typed methods. A nominal
`AnimationPoolOwner` child only declares the true hidden-return
handle-publishing ABI at `0x0044C8F0`; its original owner/storage remains
externally unresolved, not invented as a new runtime allocation.

One original `AnimationHandle` result is returned naturally by value.
This reproduces the original return-address calling convention without
an explicit fake `void*` hidden output argument, manually inserted NOP,
handwritten x86 or patching an object.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and original-target-bound relocation replay:

```text
animation_spawn_renderer_normal_72: exact (72/72 bytes)
animation_spawn_renderer_flag2_72: exact (72/72 bytes)
animation_spawn_renderer_flag4_75: exact (75/75 bytes)
animation_spawn_renderer_flag6_75: exact (75/75 bytes)
animation_file_spawn_922: exact (922/922 bytes)
Exact replay: 5/5 affected units, 2 cold objects
```

The four newly accepted distinct game-authored methods contribute
**four original function heads /294 unique `.text` bytes**. The
previously accepted 922B Boss and child list/library functions are not
recredited. Full Renderer pool ownership, startup, other native callees
and whole-game linking/playability remain unfinished. No global cold
replay was run.

```bash
scripts/repo-python scripts/verify-animation-spawn-renderer-four-modes-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationSpawnRendererFourModes.cpp --source src/AnimationFileSpawn922.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

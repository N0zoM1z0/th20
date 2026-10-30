# CORE/RECON-960 — full original RendererPool mode 20B, selection 38B and 72B-stride index 20B strict exact

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original whole-exact [922B `AnimationFile::spawn`](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md)
uses a concrete RendererPool member mode flag at `+0x6C4`, its
72-byte-stride Renderer slot array at `+0x6C8`, and the independent
20B slot index helper. These are three **complete native original
functions**, not an assumed monolithic SDK pool implementation:

| Original function | Real native meaning | Source and exact result |
| --- | --- | --- |
| `0x00449490` — **20B/9-i386** | Element address: base + index×`0x48`, native `ret 4`, **zero PE relocations** | Natural C++ 72-byte slot array, **20/20 strict exact**; template/index source origin uncertain, **zero game-authored byte credit** |
| `0x0044C8A0` — **20B/9-i386** | Read actual game pool mode preference at receiver `+0x6C4`, native `ret`, **zero relocations** | One natural game-owned property getter, **20/20 strict exact** |
| `0x0044C8C0` — **38B/14-i386** | Select a Renderer using receiver `+0x6C8` view array, E8 `+0x1B -> 0x00449490`, native `ret 4`, **zero in-body PE HIGHLOW** | Natural game-owned selection method, **38/38 strict exact** |

## Independent immutable-original PE proof and callers

[`scripts/verify-animation-spawn-pool-selection-native.py`](../scripts/verify-animation-spawn-pool-selection-native.py)
reads the original PE, fully disassembles all 20/20/38 executable bytes,
checks complete 9/9/14 instruction boundaries/returns, actual native
stride and member offsets, original E8 site/target for the selector,
**zero HIGHLOW in all three**, and all three actual E8 sites in the
whole original 922B parent:

- `0x00450D74` calls native `0x0044C8A0` to query alternate selection;
- `0x00450D57` and `0x00450D8C` call `0x0044C8C0`, passing native
  Renderer indices 0 and 1;
- `0x0044C8DB` physically calls the native index `0x00449490`.

[`src/NativeSpawnAnimationPoolView.hpp`](../src/NativeSpawnAnimationPoolView.hpp)
contains a single **non-owning** Renderer pool ABI view: it does not
invent the large original Renderer storage, and explicitly leaves the
72-byte record's internal fields unresolved. The same declaration is
included by [`src/AnimationFileSpawn922.cpp`](../src/AnimationFileSpawn922.cpp)
and the natural three-method
[`src/AnimationSpawnPoolSelection.cpp`](../src/AnimationSpawnPoolSelection.cpp).
No external proprietary renderer headers, handwritten asm, artificial
alignment bytes or raw original code copies were needed.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and complete original-target-bound local replay:

```text
animation_spawn_pool_index_20: exact (20/20 bytes)
animation_spawn_pool_preference_20: exact (20/20 bytes)
animation_spawn_pool_selector_38: exact (38/38 bytes)
animation_file_spawn_922: exact (922/922 bytes)
Exact replay: 4/4 units, 2 cold objects
```

This adds **three** native strict unit/source mappings but **only two
custom game-authored original functions /58 native `.text` bytes**.
The 20B array index is source-proven exactly but remains
`origin=unknown/review` and is **not** claimed as game-authored code.
The 922B parent and previously exact renderer-spawn methods receive no
repeated credit. Complete Renderer pool allocation/startup and the
39,470B Animation VM remain independent unfinished work. No unfiltered
full cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-spawn-pool-selection-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationSpawnPoolSelection.cpp --source src/AnimationFileSpawn922.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

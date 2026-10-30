# CORE/RECON-958 — original entire 922B AnimationFile::spawn Boss strict exact

Original Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real `0x00450CB0` is a **922B /269-i386** game-authored
`AnimationFile::spawn` method. Unlike the many previously accepted
83B/57B/55B wrappers, this is the **entire seven-visible-argument game
resource/allocation/VM/render-spawn Boss**, returning an `AnimationHandle`
by value via a compiler-generated hidden return-object pointer. Its
native original `ret 0x20` confirms eight stack slots, not eight
explicit source parameters. The full method was source-absent at the
previous checkpoint and is **now 922/922 whole strict exact**.

## Independent immutable-original native proof

[`scripts/verify-animation-file-spawn922-native.py`](../scripts/verify-animation-file-spawn922-native.py)
reads the original PE, checks the original whole 922-byte SHA-256
`696333456f3244a79e4401d452c4ad30b377183b9c76c6ffe601dc7260874476`,
all 269 x86 instructions through `ret 0x20`, six authentic following
`INT3` bytes, **all 20 original E8 physical sites AND targets**, all
**14 real PE HIGHLOW locations AND native targets**, original typed
position/flag branches, physical 640/384/2/16 floats and original E8
caller at `0x0045D255` from the independent 83B particle wrapper.
The accepted method's original link roles are:

| Native behavior | Original PE physical evidence |
| --- | --- |
| File lock | LockRegistry global `0x005C0240` and slot 9, original recursive-mutex `lock_guard` ctor/dtor E8 `+0x32/+0x3B/+0x377` |
| Allocation | Increment actual `AnimationFile+0x68` count, pool global `0x005C0028`, E8 `+0x5C -> 0x0044C9B0`, optionally publish Animation pointer |
| Resource validation | Original native stem predicate E8 `+0x83 -> 0x00446DE0`, diagnostic E8 `+0x97 -> 0x0040C6B0` using real original data `0x0056E584` |
| Renderer selection | Original pool-backed selector E8 `+0xA7/+0xDC -> 0x0044C8C0`, mode preference E8 `+0xC4 -> 0x0044C8A0`, native game `flags & 16` |
| Template and placement | Native `AnimationFile::apply_template` E8 `+0xEF -> 0x00438B70`, renderer pointer at Animation+`0x4E8`, bit `0x200` set; optional layer and native byte mode |
| World vector | Native zero-vector ctor E8 `+0x210 -> 0x00422DD0`, optional position and flag-1 offset path using original `640.0f`,`384.0f`,`2.0f`,`16.0f` actual PE HIGHLOW constants |
| Animation VM | Original **39,470B** VM E8 `+0x295 -> 0x0042B5D0` (callee **still independently nonexact**), Vector3 ctor/world-position E8 `+0x29D/+0x2A9` |
| Four original resource/render modes | Original E8 `+0x2DD -> 0x0044B890`, `+0x312 -> 0x0044B8E0`, `+0x348 -> 0x0044B840`, `+0x361 -> 0x0044B7F0`; native source-level low-two-bit `AnimationFlags` mode assignment, original `AnimationHandle` result by value |
| Security and retirement | Original native EH handler `0x0056872D`, security cookie `0x005B25C0` and E8 `+0x38F -> 0x005429EE` |

All data/call sites, not merely these representative roles, are pinned in
the 34-entry relocation manifest for the complete source.

## Recovering native control flow instead of patching byte differences

The maintained [`src/AnimationFileSpawn922.cpp`](../src/AnimationFileSpawn922.cpp)
uses the real existing `AnimationFile`, `Animation`, `AnimationHandle`,
`LockRegistry`, `AnimationPoolOwner`, and ordinary
`std::lock_guard<std::recursive_mutex>` APIs and genuine original
member/flag offsets. The original renderer and filename-predicate
source class identities are not established, so they are labeled as
**provisional non-owning ABI views**: the physical original native
addresses/call/return shapes are established, but no invented Renderer
class storage or playable renderer is claimed.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` experiments on complete functions found:

| Source evolution | Complete compiler contribution | Exactness conclusion |
| --- | --- | --- |
| Original exploratory whole C++ | 931B/271-i386, 20 E8/12 HIGHLOW | Wrong cached-pool load and branch order; rejected |
| Correct global pool reads and original position-case order | 930B/269-i386, 20 E8/14 HIGHLOW | Remaining incorrect mode-bit assignment and branch target; rejected |
| True `AnimationFlags.bits_08.mode = 0` instead of byte-wide mask | 922B/269-i386, 20 E8/14 HIGHLOW, 785/786 nonrelocation bytes | One incorrect control-flow jump, source still NONEXACT |
| Preserve the original `if (position)` assignment *inside* the zero-position `else` lexical scope | **922B/269-i386**, all 34 relocations, **786/786 nonrelocated bytes** | **Full original-target-bound 922/922 strict exact** |

The final seemingly redundant nested condition remains because the
original unoptimized `/Od` compiler physically emitted it. It is
real source-level branch structure, **not a manually inserted NOP,
inline assembler, target/object patch, or truncated prefix comparison**.

## Actual C++ ABI reconciliation and local replay

The previously strict [83B particle spawn wrapper](ANIMATION_PARTICLE_SPAWN_WRAPPER_83_STRICT_EXACT.md)
was originally written with a provisional explicit `void*` hidden-return
argument. Direct original evidence and the new actual 922B source
establish the true member signature:

```cpp
AnimationHandle AnimationFile::spawn(const char* expected_stem,
    int32_t script, const Vector3* position, float rotation,
    int32_t layer, uint32_t flags, Animation** output);
```

[`src/AnimationParticleSpawnWrapper83.cpp`](../src/AnimationParticleSpawnWrapper83.cpp)
was therefore independently rewritten to call this **same real typed
member** and return an `AnimationHandle` by value. Its C++ method symbol
and native 922B E8 COFF symbol were both corrected to reflect one real
compiler-hidden output pointer. There is no second physical function
and the 83B source was not credited twice. Both sources were freshly
compiled and checked against their **actual original target relocation
identities** in an affected-only replay:

```text
animation_file_spawn_922: exact (922/922 bytes)
animation_particle_spawn_wrapper_83: exact (83/83 bytes)
Exact replay: 2/2 units, 2 cold objects
```

The new full 922B Boss contributes **one original authored game head
/+922 native `.text` bytes** and one pinned C++20 provider. The already
accepted 83B wrapper is a regression check, not a new game head.
The 2,884B particle Update parent, distinct 39,470B Animation VM and
complete game executable build/link/play remain independent open work.
No unfiltered whole-graph cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-file-spawn922-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationFileSpawn922.cpp --source src/AnimationParticleSpawnWrapper83.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

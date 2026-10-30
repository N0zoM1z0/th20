# CORE/RECON-949 — original 47B particle-grid creation and 31B Timer reset strict exact

Original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real `0x0045D000` is a **47B/18-i386** game-owned cdecl creation
wrapper. It allocates the genuine **0x1940-byte** polymorphic particle
grid group via the independently exact
[156B factory](ANIMATION_PARTICLE_GRID_FACTORY156_STRICT_EXACT.md),
then invokes the distinct original `0x0045CFE0` **31B/12-i386**
configuration method. This is a real two-part call chain, not an
inferred exact child from an accepted parent.

## Original PE independent verification

[`scripts/verify-animation-particle-grid-create47-native.py`](../scripts/verify-animation-particle-grid-create47-native.py)
decodes both original complete function boundaries and returns,
verifies **all three E8 physical sites/targets**, both original
HIGHLOW positions/targets and the real configuration ABI:

| Physical original | Native destination or action |
| --- | --- |
| 47B marker HIGHLOW `+0x09` | `0x0056EC30`, the actual diagnostic creation marker |
| 47B allocator HIGHLOW `+0x0F` | `0x005B8894`, original process allocator pointer |
| 47B E8 `+0x13` | `0x0045C090` genuine whole-exact 156B allocation factory |
| 47B E8 `+0x26` | `0x0045CFE0` genuine 31B configuration method |
| 31B E8 `+0x12` | `0x00423520` original Timer assignment zero, at group `+0x1930` |
| 31B return | Native `ret 8`, reflecting **two present but intentionally unused** configuration arguments; return value zero |

The natural [`src/AnimationParticleGridCreate47.cpp`](../src/AnimationParticleGridCreate47.cpp)
uses the genuine `DiagnosticAllocator::allocate_object<...>` with
`extern template` and one consistent class owner; the config method
in [`src/AnimationParticleGridConfig31.cpp`](../src/AnimationParticleGridConfig31.cpp)
resets the real Timer and returns zero. The two stack arguments are
preserved in the ABI without inventing gameplay semantics for them.
No explicit x86, inserted stack manipulation, fake NOP or copied bytes.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` with complete strict original-target-bound relocation:

```text
animation_particle_grid_create_47: exact (47/47 bytes)
animation_particle_grid_config_31: exact (31/31 bytes)
Existing 156B factory/172B ctor/49B delete/two 78B array helpers: exact
Exact replay: 7/7 units, 5 cold objects
```

These are **two genuine custom game-authored original heads /78 physical
`.text` bytes**. The generated factory and array helpers are not
credited again. The separate virtual update/interrupt methods are still
source absent or nonexact, and whole-game linkage/playability is not
claimed. No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-particle-grid-create47-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleGridCreate47.cpp --source src/AnimationParticleGridConfig31.cpp --source src/AnimationParticleGridGroupFactory156.cpp --source src/AnimationParticleGridGroupCtor172.cpp --source src/AnimationParticleGridArrays200.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

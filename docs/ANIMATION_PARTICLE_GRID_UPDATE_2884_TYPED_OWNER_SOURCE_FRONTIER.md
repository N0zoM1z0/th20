# CORE/RECON-1107 — source-present 2,884B particle-grid Update with real effect resource ownership

This checkpoint promotes the full game-authored 200-particle virtual Update
at **`0x0045C360..0x0045CEA3`** into maintained
[`src/AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp).
The immutable Japanese TH20 Steamless v1.00a target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`;
its complete original Update has **2,884 bytes/768 i386 instructions**,
body SHA-256 `0d8c82a2018031e59c5e7172e08318e133f3513b6fc4639a1bab506c41eb02d1`,
**99 genuine E8 calls, 25 PE HIGHLOW fields**, and one real `ret` at
`0x0045CEA3`. The original PE-relocated six-entry vtable at `0x0056EC14`
points slot 1 to this function; slot 3 points to the independently exact
92B Stop sibling. Twelve real `INT3` bytes separate these bodies.

The original Ghidra inventory missed the 2,884B Update boundary. The
[original-only proof](../scripts/verify-animation-particle-grid-update2884-native.py)
and temporary, rolled-back Ghidra reconstruction were preserved in
[CORE/RECON-953](ANIMATION_PARTICLE_GRID_UPDATE_2884_ORIGINAL_NATIVE_FRONTIER.md)
and [CORE/RECON-966](ANIMATION_PARTICLE_GRID_UPDATE_2884_TEMP_GHIDRA_AND_TYPED_FRONTIER.md).
This newly verified native boundary is now separately recorded in the
sorted function and origin ledgers instead of extending or shortening a
Ghidra neighbor's function.

## Correct game owners and complete call sequence

The earlier experimental C++ contained two false or provisional access
shapes in each of **four** particle-spawn branches. It treated a global
selector as returning an AnimationFile directly, then modeled the actual
`EffectInfo::animation_file()` call as an unused palette lookup. The
original instructions establish the following chain instead:

1. Original E8 `+0x1E0/+0x24F/+0x2B5/+0x333` to
   [`particle_effect_info_for_session_437520`](PARTICLE_EFFECT_INFO_LOOKUP26_STRICT_EXACT.md).
   This now separately **whole strict exact 26B** free function uses the
   actual `Session` global, indexed `Session::context`, and
   `Context::effect_info()`.
2. Original E8 `+0x1F6/+0x25F/+0x2CB/+0x349` to the already-exact **38B**
   [`EffectInfo::animation_file`](../src/ItemLifecycleAccess.cpp).
   This is a genuine `__thiscall` member on the returned `EffectInfo*`,
   and its result is the borrowed `AnimationFile*` used for the next call.
3. Original E8 `+0x227/+0x28A/+0x2FC/+0x37A` to the already-exact **83B**
   `NativeParticleSpawnFileView::spawn_45d210`, using the real hidden
   `AnimationHandle` return result and original `"effect"` resource name,
   scripts `0x95/0x95/0x95/0x96`, and an original slot argument. The same
   `effect_index` variable supplies the session selector and the final
   spawn parameter, as shown by the original stack reads. The value is
   initialized to zero in this path; hardcoding distinct literals in the
   C++ would lose the original variable relationship.

The class ABI for the exact 83B spawn is now maintained once in
[`NativeParticleSpawnFileView.hpp`](../src/NativeParticleSpawnFileView.hpp),
and the 26B accessor declaration is shared through
[`ParticleEffectInfoLookup26.hpp`](../src/ParticleEffectInfoLookup26.hpp).
Both independently accepted child objects were rebuilt once after the
header extraction: **83/83** and **26/26** full relocated bytes still exact.
The existing `NativeParticleAnimationAccess` class provides the separately
exact **25B age** and **19B color-word** getters with their actual
`__thiscall` ABI; no invented free-function substitute remains.
The real `Timer::changed()` source is used for the folded original
`0x0045D030` timer gate, also seen independently in other exact callers.

Beyond the four resource paths, the maintained C++ preserves the 200-handle
lifetime loop, two exact 202B Vector3 normalization calls, two exact 57B
interpolation-forwarding calls, game random polar offsets, integer stages
**0 → 1 → 2** at `NativeParticleGridGroup+0x15E8`, four indexed child
color/variable copies, and final Timer advance. The 200-element handle and
integer stage arrays use native four-byte `std::array` indexing instead of
incorrect `Vector3` reinterpretation; their folded 22B original physical
callee was already exact and is not credited again.

## Native result and remaining Boss frontier

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiles the **entire maintained source** into
**2,969B/763 i386 instructions**, **99 REL32 and 25 DIR32** relocations.
All **99 original E8 target roles remain in the same ordered call sequence**;
the caller instruction positions, frame/local allocation, x87/SSE polar
argument evaluation, and some ordinary native bytes remain different.
The original is **2,884B/768 instructions**; this candidate is
**SOURCE-PRESENT, NONEXACT**. Similar function names and exact children do
not make the parent exact. No `match-units.toml` unit or
`matches.csv` authored credit is added for this parent.

Several source probes changed the compiler size without improving overall
correctness: using an unrelated free palette function had the wrong
receiver/return value; hardcoding `0` for the spawn slot omitted a real
shared variable; removing the Animation pointer alias perturbed the
frame/register allocation; C++17/C++20 did not resolve early float
argument evaluation. These are preserved under ignored `.analysis/`.
Remaining work is the original stack frame (0x19C after MSVC alignment),
the five initial Vector3 constructors/ESI lifetime, polar argument stack
spills and the subsequent paired per-particle loops.

The only native cold replays after extracting the child interfaces were
the **two exact 26B and 83B providers**. The 2,884B source was compiled as
one independent NONEXACT probe, not included in an all-graph cold replay.
The receipt verifier's separate [scoped input-closure regression](../scripts/test-scoped-build-receipt.py)
ensures that moving this unrelated probe translation unit does not require
cold-replaying the other exact objects: it permits unrelated source-path
changes while rejecting modified included headers, changed owned source,
object bytes, compiler profile or target identity.

The move from `probes/` to `src/` exposed an unrelated receipt-freshness
issue: the previous verifier demanded an identical global source filename
set even when the moved path was not part of an object's compiler-captured
include closure. The existing receipt verifier now accepts only changes to
unrelated source paths whose basenames cannot shadow its recorded inputs;
it still requires the exact object hash, compiler profile, owned source,
all compiler-observed include bytes, and target identity. Focused regressions
passed **two positive and five negative** cases (source/header tampering,
include shadowing, profile, and object bytes), and existing 26B, 83B,
92B, 417B, and Timer exact objects were individually reverified without
cold recompilation. This is not a bypass of original-byte matching.

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-particle-grid-update2884.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/ParticleEffectInfoLookup26.cpp \
  --source src/AnimationParticleSpawnWrapper83.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

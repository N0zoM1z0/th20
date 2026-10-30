# CORE/RECON-963 — original 77B stem-string comparison and 17B PMR forwarding strict exact

Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The [922B `AnimationFile::spawn` Boss](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md)
reads an optional filename stem and invokes a **17B/8-i386** native
forwarder at `0x00446DE0`. That calls a distinct complete **77B/29-i386**
length/content comparison at `0x0044B400`; this method in turn calls
native string length `0x00411180`, PMR string data accessor `0x0040F2C0`
and length-aware byte comparison `0x00447200`.

[`scripts/verify-animation-spawn-stem-comparison-native.py`](../scripts/verify-animation-spawn-stem-comparison-native.py)
checks every original PE byte, full 77B and 17B instructions and actual
returns, **three physical E8 fields/targets in the 77B method**, one
physical E8 in the 17B forwarding method, zero PE HIGHLOW fields in
both, and the real 922B parent E8 `0x00450D33 -> 0x00446DE0`.

The maintained [`src/NativeAnimationSpawnStem.hpp`](../src/NativeAnimationSpawnStem.hpp)
models the original `std::pmr::string` receiver as a **non-owning view**
with actual `+0x04` string-data storage and native `+0x14` length.
[`src/AnimationSpawnStemCompare77.cpp`](../src/AnimationSpawnStemCompare77.cpp)
uses ordinary C++20 caller/receiver flow and native length-aware
comparison, not copied x86 or synthetic NOPs. Ghidra had described both
original functions as `void`, but the real original native return value
is preserved in EAX and gates the 922B file-stem validity branch.

The 17B free function was additionally retyped to the already accepted
**`const std::pmr::string*`** argument of the real 922B caller, with
the corresponding *same* MSVC COFF symbol. The original 922B Boss was
recompiled after changing it to include that shared declaration.
Locked MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` and native-target-bound strict replay:

```text
animation_spawn_stem_compare_77: exact (77/77 bytes)
animation_spawn_stem_forward_17: exact (17/17 bytes)
animation_file_spawn_922: exact (922/922 bytes)
Exact replay: 3/3 units, 2 cold objects
```

Both newly reconstructed functions remain `origin=unknown/review`;
the generic STL/PMR-versus-game authorship of these comparison helpers
is not sufficiently established to claim original game-authored bytes.
They add **two source-present whole strict original heads /94 bytes**,
but **zero newly credited game-authored functions/bytes**. The distinct
73B length-aware compare at `0x00447200` remains a separate leaf until
its own strict source is demonstrated, and enclosing 2,884B particle
Update remains SOURCE ABSENT. No global cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-spawn-stem-comparison-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationSpawnStemCompare77.cpp --source src/AnimationFileSpawn922.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

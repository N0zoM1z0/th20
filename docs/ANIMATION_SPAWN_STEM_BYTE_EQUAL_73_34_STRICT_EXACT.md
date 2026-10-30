# CORE/RECON-964 — complete original 73B length-aware string equality and 34B byte compare whole strict exact

Original immutable Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The existing [77B PMR stem comparison](ANIMATION_SPAWN_STEM_77_17_STRICT_EXACT.md)
used by the original [922B `AnimationFile::spawn` Boss](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md)
physically calls **`0x00447200`**, a complete **73B/29-i386**
length-aware byte equality function. It calls **`0x0044BE00`**, a
separate **34B/16-i386** wrapper around the actual game-linked CRT
`memcmp` at **`0x00544D77`**. These are original native functions with
independent boundaries, not extra snippets of the 77B or 922B parents.

[`scripts/verify-animation-spawn-stem-bytes-native.py`](../scripts/verify-animation-spawn-stem-bytes-native.py)
reads the locked original PE and verifies **all code bytes**, original
returns and instruction counts, native E8 site/target pairs
`0x0044B43F -> 0x00447200`, `0x00447226 -> 0x0044BE00`, and
`0x0044BE10 -> 0x00544D77`, and **zero original PE HIGHLOW** in both
methods. The original **21 `INT3` alignment bytes** following the
34B body are verified separately and never credited as game code.

`0x00447200` checks whether the two native lengths match, returns
false if they differ, returns true when both lengths are zero, and
otherwise returns whether the `memcmp` result is zero. The 34B
helper passes through all three native arguments and returns the
full `memcmp` result. This is length-aware binary equality, not an
unbounded `strcmp` over independently NUL-terminated strings.

The maintained
[`src/AnimationSpawnStemByteCompare.cpp`](../src/AnimationSpawnStemByteCompare.cpp)
uses ordinary C++20 comparisons, `std::memcmp`, a natural saved return
value, and the same native call types declared by
[`src/NativeAnimationSpawnStem.hpp`](../src/NativeAnimationSpawnStem.hpp).
Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits both whole bodies with the genuine
call relocations. Original-target-bound scoped replay:

```text
animation_spawn_stem_equal_73: exact (73/73 bytes)
animation_spawn_stem_compare_bytes_34: exact (34/34 bytes)
animation_spawn_stem_compare_77: exact (77/77 bytes)
animation_spawn_stem_forward_17: exact (17/17 bytes)
animation_file_spawn_922: exact (922/922 bytes)
Exact replay: 5/5 units, 3 cold objects
```

These two new units add **107 native source-present strict bytes**, but
both remain `origin=unknown/review` for their likely C++ standard-library
roles. No new authored-game function or byte credit is claimed; the
previous 77B, 17B and 922B parents are not counted again.
The separate 56B native string length `0x00411180` remains open and
needs its own independently whole-exact source. No global cold replay.

```bash
scripts/repo-python scripts/verify-animation-spawn-stem-bytes-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationSpawnStemByteCompare.cpp --source src/AnimationSpawnStemCompare77.cpp --source src/AnimationFileSpawn922.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

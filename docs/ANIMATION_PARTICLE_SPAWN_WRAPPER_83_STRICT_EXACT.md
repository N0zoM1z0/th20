# CORE/RECON-957 — original full 83B particle AnimationFile spawn wrapper strict exact

> **CORE/RECON-958 update:** The original 922B callee `0x00450CB0` is now
> [independently whole strict exact](ANIMATION_FILE_SPAWN_922_STRICT_EXACT.md).
> The 83B wrapper now uses the same actual `AnimationFile::spawn`
> typed return-by-value `AnimationHandle` ABI and symbol, instead of the
> original provisional `void*` shim. Its entire original **83/83** body
> was recompiled and revalidated after this correction; historical source
> guesses below remain for evidence only.

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Native `0x0045D210` is an **83B/30-i386** game-specific six-parameter
wrapper around the distinct original **922B** Animation file spawn
Boss at `0x00450CB0`. This wrapper is physically called four times in
the verified full 2,884B particle virtual Update Boss at
`0x0045C587`, `0x0045C5EA`, `0x0045C65C` and `0x0045C6DA`.

## Original PE call-graph and control-flow evidence

[`scripts/verify-animation-particle-spawn83-native.py`](../scripts/verify-animation-particle-spawn83-native.py)
reads original file-backed PE code and checks the full original 83B
body, 30 actual decoded instructions through `ret 0x18`, **one real
E8 `+0x45 -> 0x00450CB0`**, **zero PE HIGHLOW**, all four original
2,884B parent E8 sites and actual targets, and native control flow:

- Original last six-argument method parameter at `+0x1C` is compared
  with `1`. The native local mode flag becomes **16 if equal**, otherwise
  **0**, without falsely asserting a more specific gameplay enum name.
- The caller's other four inputs and one float input are forwarded to
  the 922B core, along with the real extra arguments `-1`, flag and `0`.
- The result is the original output-pointer argument, as confirmed by
  the final native `mov eax,[ebp+8]` and `ret 0x18`.

[`src/AnimationParticleSpawnWrapper83.cpp`](../src/AnimationParticleSpawnWrapper83.cpp)
keeps one non-owning `NativeParticleSpawnFileView` ABI declaration and
uses normal `if/else` and method forwarding. The complete original
922B callee's semantics remain a separate reconstruction target;
this accepted wrapper does **not** claim it to be source present or
whole exact. Other parameter meanings remain provisional where the
original body only passes raw values.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` naturally emits all 83 bytes/30 instructions,
79/79 nonrelocated code bytes and the authentic single call relocation.
Strict original-target-bound canonical replay:

```text
animation_particle_spawn_wrapper_83: exact (83/83 bytes)
Exact replay: 1/1 unit, 1 cold object
```

This adds **one original authored-game whole exact function /83 `.text`
bytes**. The four parent call sites and enclosing 2,884B Update remain
source absent/nonexact until their own complete original-bound replay.
No global cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-particle-spawn83-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationParticleSpawnWrapper83.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

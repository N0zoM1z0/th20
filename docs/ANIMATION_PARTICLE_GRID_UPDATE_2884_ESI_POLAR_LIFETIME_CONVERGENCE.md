# CORE/RECON-1111 — 2,884B particle Update: real ESI/age and polar lifetime convergence

The genuine TH20 Japanese Steamless v1.00a particle-grid virtual Update is
at **`0x0045C360`**, exactly **2,884B/768 i386**. It is SHA-pinned in
[`verify-animation-particle-grid-update2884-native.py`](../scripts/verify-animation-particle-grid-update2884-native.py)
together with its six-slot native vtable, all 99 physical E8 site/target
pairs, 25 actual PE HIGHLOW fields and 12 trailing `INT3` bytes. The
full maintained C++ source is
[`AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp).
**This parent remains SOURCE-PRESENT, NONEXACT**.

## Three actual original source/ABI corrections

These are used-source changes, not artificial padding or dead variables:

1. **Emitter index initialization:** The old source declared
   `int emission_index=0` despite only reading this value after
   `emission_index=timer_1930.time*4` in the positive active-emission
   branch. The original native prologue initializes **two**, not three,
   local integer states; the emitter slot is derived from the Timer
   before every use. The maintained source now declares
   `int emission_index;` and assigns its value before first use.
   This removes one extra ordinary C++ initialization without changing
   the branch's integer state or emitting invalid reads.
2. **Real age/owner comparison lifetime:** Original E8 `+0x91D` calls
   `NativeParticleAnimationAccess::age_45d0a0()`; the original next
   instruction is **`mov esi,eax`**. Original E8 `+0x92A` then calls
   `Animation::variables()` and the original **`cmp esi,edx`** compares
   the saved age across that effectful call. The earlier C++ introduced
   `const int elapsed=...`, leading MSVC `/Od` to store the age on the
   stack rather than preserve it in ESI, and omitting the original
   callee-saved `push esi`/`pop esi`. The maintained source writes the
   source-semantic equivalent condition directly as
   `child->age_45d0a0() >= owner->variables().field_00+1`, preserving
   the original function-call sequence and naturally restoring the
   ESI prologue/epilogue and exact first five Vector3 constructor E8
   sites. The actual typed animation access class remains unchanged.
3. **Meaningful polar-angle evaluation:** The first
   `rotation_z_value()` result is actually used as the first polar
   angle, so it is captured into a real `const float angle`; the second
   heading is formed by first reading the owner's rotation, then using
   **`direction += owner->variables().field_28`** before passing
   the resulting direction to the second `polar` call. This C++
   ordering preserves the original side-effecting getter sequence
   while avoiding the historical compiler's unnecessary push/copy
   intermediates. Earlier experiments with a function-pointer cast,
   separate radius temporaries, or evaluating variables before the
   rotation yielded worse code or the wrong native call order.

## Complete bounded build and measurable distance

The genuine locked MSVC 19.44 i386 profile is
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Both before and after, the *complete* 99 original E8 target roles and
25 original PE HIGHLOW data roles are still reconstructed, including
all four Session→EffectInfo→AnimationFile→83B spawn branches, two
Vector3 normalization calls, four child color copies and both real
integer-stage transitions. These are compared against independently
locked original destinations; they are **not** inferred from matching
candidate relocation counts.

| Measured property | Previous maintained source | This checkpoint | Original native |
| --- | ---: | ---: | ---: |
| Whole compiler code bytes | 2,969 | **2,924** | 2,884 |
| Whole i386 instructions | 763 | **760** | 768 |
| E8 / COFF REL32 calls | 99 | **99** | 99 |
| PE HIGHLOW / COFF DIR32 | 25 | **25** | 25 |
| E8 opcode offsets exactly aligned | 0 /99 | **6 /99** | 99 /99 |
| Sum of absolute differences between corresponding E8 offsets | 7,558 | **3,639** | 0 |
| First 20 E8 offset absolute-difference sum | 659 | **119** | 0 |
| Original ESI push/age-across-call lifetime | No | **Yes** | Yes |

The previous 2,969B candidate source is retained as
`.analysis/gptweb-particle-owner-probes/EffectChainSpawnSlot.cpp`; its
noncanonical compiled object was removed during storage cleanup.
Rebuild it with `scripts/compile-probe.py` if needed. The current
2,924B candidate is reproducible from the maintained single-source probe. Size converged **45B** toward the real game function, and the
native early original E8 instruction sites now align where they
previously did not. The 2,924B candidate's original-code difference
remains **40B and eight i386 instructions**. These bytes are *not*
accepted as original code; code length alone has no matching credit.

## New independent original-role checker

[`verify-animation-particle-grid-update2884-candidate-roles.py`](../scripts/verify-animation-particle-grid-update2884-candidate-roles.py)
reads the immutable PE, runs its SHA-pinned original verifier, decodes
all 99 genuine E8 relative targets, and checks each actual candidate
COFF REL32 symbol against its independently fixed game target **in
original call order**. It does likewise for **all 25 candidate DIR32
symbol roles** against the original physical PE HIGHLOW data targets
in order. It rejects missing/extra calls, non-E8 REL32 sites, any
changed destination, and loss of native ESI lifetime. It then reports
the **whole-function** candidate size, instruction count, E8 physical
site alignment and numeric displacement from the original. It never
accepts a prefix, changes any expected target bytes, substitutes a
fake relocation, or grants a strict match.

This role checker now runs automatically after the existing
[`probe-animation-particle-grid-update2884.py`](../scripts/probe-animation-particle-grid-update2884.py)
compiles the *one* real maintained function:

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-particle-grid-update2884.py
```

The original `0x0045C360` **2,884B/768-i386** remains NONEXACT;
there is **no new match-unit or game-authored byte credit**. Remaining
original-native differences are mainly the 0x19C aligned local stack
frame (candidate still larger), early float-argument push/spill order,
and per-loop pointer/register lifetime. The strict **26B EffectInfo**,
**51B Event**, **92B Stop** and associated already exact descendants
are separate functions and were not modified; no all-project cold replay
was performed.

**2026-11-27 native Vector3 local-role recovery:** The maintained source now
uses `basis` as the original polar-output and vector-difference scratch, while
`tangent` is the separately normalized second direction. This is derived from
the original call operands, not from decompiler variable names: the native
configuration call forwards `position` from `[EBP-0x40]`, `tangent` from
`[EBP-0x4C]`, `gradient` from `[EBP-0x1C]`, and `velocity` from
`[EBP-0x34]`; the polar and subtraction scratch is `[EBP-0x10]` (`basis`).
The candidate now assigns the same source roles, but the pinned MSVC build
places position/tangent/gradient/velocity/basis at `[EBP-0x44]`,
`[EBP-0x50]`, `[EBP-0x20]`, `[EBP-0x38]`, and `[EBP-0x14]` respectively: a
uniform four-byte displacement. The targeted
whole-source probe remains **2,881B/767 i386**, with **99/99 call roles** and
**25/25 data roles** intact, **6/99** E8 sites aligned and total call-offset
delta **883**. This is a source/dataflow correction, not an exactness claim;
the remaining frame-local allocation and x87/SSE argument materialization
still need compiler-level explanation.

**2026-11-27 repeated-owner reload update:** The cached Animation pointer
snapshot is removed. Native instructions repeatedly reload the current group
member from this+4 before variables, slowdown, vector_5bc_ref, and interpolation
calls; the source now evaluates animation->... at each original access point.
This is more faithful to the actual owner-retargeting semantics than retaining
a stale pointer snapshot. The maintained whole function now compiles to
**2,881B/767 i386**, only **3 bytes and one instruction below** the 2,884B/768
native body, while preserving all **99/99 E8 target roles**, **25/25 DIR32
roles**, the **0x19C frame**, and native ESI age-across-call lifetime. Physical
E8 alignment is **6/99**, total offset delta **883** (first 20: **107**); this
trades the previous direct-spawn checkpoint's 14 aligned calls / 712 total
delta for the more accurate repeated member loads. The original parent remains
**NONEXACT**, with no new exactness credit.

A bounded MSVC /Od source-order matrix tested all **120 permutations** of the
five Vector3 locals and all **24 permutations** of the scalar/pointer locals.
They all emitted the same 2,881B/767 body: declaration reordering alone does
not change this compiler's live-range stack-slot assignment. Moving the
color-word union to four function/block positions likewise left the body
unchanged. A natural four-named AnimationHandle result-local hypothesis
emitted **2,901B/771**, 6/99 aligned and 2,411 total E8 offset delta, so it is
rejected as a worse candidate. These controls narrow the remaining local-layout
frontier to actual temporary/materialization and lifetime semantics, not simple
declaration order.

**CORE/RECON-1112 CURRENT SOURCE UPDATE (2026-11-25):** The four
particle-emitter branches now assign the real `spawn_45d210(...)` return
value directly into `colors_08[emission_index + n]`, rather than materializing
an additional named `AnimationHandle` local and then copying it. This is a
natural C++ return-value/assignment expression; it retains all four distinct
script IDs and the original Session → EffectInfo → AnimationFile → spawn
resource chain. The pre-owner-reload checkpoint compiled to **2,856B/756 i386**
(down 20B/four instructions from 2,876B/760). All **99/99 original E8
target roles** and **25/25 original PE HIGHLOW data-target roles** remain
identical and in order. Physical E8-site alignment improves from **8/99 to
14/99**; total absolute E8 offset delta falls from **1,463 to 712**, and the
first-20 delta falls from **92 to 87**. The native **0x19C** frame and ESI
age-across-call lifetime remain. The complete 2,884B/768-i386 game Boss is
still **SOURCE-PRESENT/NONEXACT**; no parent exactness credit is claimed.
The maintained one-object probe and independent original-role verifier both
pass for the complete 2,856B historical candidate; the current 2,881B candidate is independently reproduced by the same probe.

# CORE/RECON-1111 — 2,884B particle Update: ESI/age, polar and shared-child lifetime convergence

The genuine TH20 Japanese Steamless v1.00a particle-grid virtual Update is
at **`0x0045C360`**, exactly **2,884B/768 i386**. It is SHA-pinned in
[`verify-animation-particle-grid-update2884-native.py`](../scripts/verify-animation-particle-grid-update2884-native.py)
together with its six-slot native vtable, all 99 physical E8 site/target
pairs, 25 actual PE HIGHLOW fields and 12 trailing `INT3` bytes. The
full maintained C++ source is
[`AnimationParticleGridUpdate2884.cpp`](../src/AnimationParticleGridUpdate2884.cpp).
The pre-RECON-1112 checkpoint compiled to **2,876B/760 i386** after the 2026-11-20
shared-child lifetime recovery; **this parent remains SOURCE-PRESENT,
NONEXACT**.

## Four actual original source/ABI corrections

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

4. **Shared child-pointer lifetime:** The four emitter color/variable
   propagation blocks and the later 200-slot update loop reuse the same
   native local pointer slot, `[EBP-0x54]`. The original writes a resolved
   child into that slot at `0x45C73F`, `0x45C79C`, `0x45C7F9`,
   `0x45C880`, and `0x45C8F9`, then reads that same slot for child methods
   and later interpolation calls. The maintained C++ now declares one
   `Animation* child` and assigns it at each resolve site rather than
   declaring five block-local pointers. Each assignment dominates every
   use in its branch/iteration, preserving behavior while matching the
   native lifetime and reducing needless `/Od` stack slots.

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

| Measured property | 2,969B source | 2,924B checkpoint | Current checkpoint | Original native |
| --- | ---: | ---: | ---: | ---: |
| Whole compiler code bytes | 2,969 | 2,924 | **2,881** | 2,884 |
| Whole i386 instructions | 763 | 760 | **767** | 768 |
| E8 / COFF REL32 calls | 99 | 99 | **99** | 99 |
| PE HIGHLOW / COFF DIR32 | 25 | 25 | **25** | 25 |
| E8 opcode offsets exactly aligned | 0 /99 | 6 /99 | **6 /99** | 99 /99 |
| Sum of absolute differences between corresponding E8 offsets | 7,558 | 3,639 | **883** | 0 |
| First 20 E8 offset absolute-difference sum | 659 | 119 | **107** | 0 |
| Local stack frame | — | 0x1AC | **0x19C** | 0x19C |
| Original ESI push/age-across-call lifetime | No | Yes | **Yes** | Yes |

The previous 2,969B candidate source is retained as
`.analysis/gptweb-particle-owner-probes/EffectChainSpawnSlot.cpp`; its
noncanonical compiled object was removed during storage cleanup. Rebuild it
with `scripts/compile-probe.py` if needed. The pre-RECON-1112 2,876B candidate is a historical checkpoint; the
maintained single-source probe now reproduces the **2,881B/767** repeated-owner candidate; the 2,856B/756 direct-spawn checkpoint is retained as a historical comparison.
The shared child-pointer lifetime first removed **48B** from the 2,924B
checkpoint and restored the native **0x19C** frame, aligning eight E8 sites
with total offset delta **1,463**. RECON-1112 then changed all four named
`AnimationHandle` temporaries into direct `colors_08[index] = spawn(...)`
assignments: this removes a further **20B/four instructions**, improves
alignment from **8/99 to 14/99**, and cuts total E8 offset delta from
**1,463 to 712** (first 20 sites: 87). The 2026-11-27 repeated-owner reload now gives a **2,881B/767** candidate,
only 3B and one instruction shorter than native. These bytes are *not* accepted
as original code, and code length alone has no matching credit. A more
aggressive const-reference center probe compiled to 2,856B/758, but was
rejected: the native explicitly materializes a 12-byte Vector3 snapshot
before copying it to the three group fields, so the maintained source keeps
the value copy and changes only the independently evidenced child-pointer
lifetime plus the direct spawn-result assignments.

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
compiles the *one* real maintained function. The 2026-11-20 source
checkpoint reported 2,876B/760 i386 and 8/99 physical E8 sites aligned;
the current source reports 2,881B/767 i386 and 6/99 aligned, preserving
every original call/data role and the exact 0x19C local frame:

```sh
nice -n 15 scripts/repo-python scripts/probe-animation-particle-grid-update2884.py
```

The original `0x0045C360` **2,884B/768-i386** remains NONEXACT;
there is **no new match-unit or game-authored byte credit**. The candidate's
0x19C local frame now matches the original; remaining differences are the
early float-argument push/spill order, Vector3 local-slot placement, and
some per-loop register lifetimes. The strict **26B EffectInfo**,
**51B Event**, **92B Stop** and associated already exact descendants
are separate functions and were not modified; no all-project cold replay
was performed.

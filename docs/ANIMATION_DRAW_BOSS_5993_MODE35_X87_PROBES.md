# CORE/RECON-908 — 5,993B Animation Draw Boss: mode 35/36 original x87 return spill and SSE operand frontier

The immutable Japanese TH20 Steamless 1.00a target is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The enclosing original game function `0x00443880` is **5,993B /1,501 i386
instructions**, with **123 E8** and **32 in-body PE HIGHLOW**, plus its two
**49+31 real pointer-switch tables**. It remains **SOURCE-PRESENT,
NONEXACT** in [`src/AnimationDrawBoss.cpp`](../src/AnimationDrawBoss.cpp).
All accepted rendering children are unaffected by this report.

## Original PE disassembly and constrained native comparison

The original first inherited auxiliary-scale call in mode 35 is at original
`+0xFC8`, followed by `fstp dword ptr [ebp-0x160]` at `+0xFCD`.
Mode 36 has the corresponding original E8 at `+0x10B5` and same-stack-slot
store at `+0x10BA`. The unmodified maintained candidate emits `fstp st(0)`
(discarded x87 result) instead, four bytes shorter at each site. The
original next 35-mode color E8 is `+0xFD6`; in the candidate it is
`+0xFD2`. Later original arithmetic loads the returned second scale into
`xmm0` and the saved half-height into **`xmm1`** before `addss xmm0,xmm1`;
the current candidate uses a memory operand with `addss`, which differs
without necessarily changing numerical results. Both are real remaining
source/ABI issues. The first x87 spill has no independently established
subsequent read in this route; naming an otherwise unused capture does **not**
prove the original source owner or correct its later SSE lifetime.

Scoped pinned MSVC x86 complete-function probes use
`.analysis/gptweb5993-score.py`, `.analysis/gptweb5993-diff.py`, source
variants in `.analysis/gptweb5993-first-scale/`,
`.analysis/gptweb5993-scale-lane/`, and private COFF objects in
`build/gptweb-probe/DrawBossFirstScale_*.obj` and
`DrawBossLane_*.obj`. The true original 5,993B executable function is
not conflated with the **6,316B total candidate COFF contribution**
containing real padding and the 80 switch-table pointers.

| Whole-function probe | COFF contribution / decoded x86 | Total E8 | Physically aligned original E8 sites | First diverging E8 |
| --- | --- | ---: | ---: | --- |
| Maintained source, `/sdl /GS /fp:precise` | **6,316B /1,501** | 123 | **86/123** | Original `+0xFD6` vs object `+0xFD2` (index 81) |
| Capture mode 35 first inherited-scale x87 result in a `float` local | **6,320B /1,499** | 123 | **85/123** | Original `+0x10A7` vs object `+0x10A3` (index 84) |
| Capture only mode 36 first scale | 6,320B /1,499 | 123 | 82/123 | Still diverges at `+0xFD6` |
| Capture both first scale results | 6,324B /1,497 | **122** | 84/123 | Original `+0x10A7` vs object `+0x10A3` |

Capturing the mode-35 result aligns the three additional *consecutive*
color/scale E8 sites `+0xFD6`, `+0xFE4`, `+0x1016` and moves the first
mismatch to the actual mode-35 rendering call at `+0x10A7`. However it
**loses overall matching E8 sites**, increases total size and changes
later instructions; its source local has no proven consumer. Therefore
**it is not admitted** and the production source is unchanged.

The full-body baseline is invariant under separately tested
`/fp:strict`, `/fp:fast`, and `/EHsc`; all retain 6,316B, 1,501 x86 and
86/123 physically matching E8 sites. Disabling `/sdl` or `/GS` instead
destroys the original early call and cookie ABI, generating 6,288B and
122 E8, so those profiles are rejected. Changing the used half-height
local to mutable, `volatile` or `const volatile`, or similarly adjusting
the second scale result, has **no useful byte/relocation-site effect**
in seven further isolated full-function probes. The real original
`xmm1` loading and remaining nine in-body HIGHLOW site placements
must be independently reconciled as a *source lifetime/evaluation-order*
problem, not as a compiler switch or dummy padding exercise.

No strict 5,993B unit, parent-body credit, modified accepted canonical
object, source edit, or broad cold replay results from this research.
The last accepted baseline remains independently documented in
[the native 80-table and stack frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md).

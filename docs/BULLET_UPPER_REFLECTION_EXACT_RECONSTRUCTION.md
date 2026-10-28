# CORE/EXACT-218 — 277-byte original Bullet upper-edge reflection

Original target: Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original **277-byte** function at `0x00483150` is called
by the still-open **832-byte** native four-direction Bullet boundary boss at
`0x00482A60`. It is now maintained as `Bullet::reflect_at_upper_y` in the
same real `src/BulletReflection.cpp` as the other exact three directions and
typed original command/controller interfaces. The original source spelling
remains inferred; instruction/body/ABI boundaries are original and complete.

The function chooses the current BulletController vector Y when positive;
otherwise it reads the actual `BulletExtendedCommands::at(4).vector_18.y`
from its own game-owned Bullet. Original native `448.0f` (`0x0056D7C0`) and
`2.0f` (`0x0056C8D0`) define the upper threshold:
`position.y < 448.0f / 2.0f - limit / 2.0f`. The exact native `comiss/jbe`
branch and unordered/NaN behavior are preserved. Crossing the threshold
returns 1 regardless of flag `word_3c & 0x10`; when that flag is absent, it
calls the genuine Angle float getter/assignment to negate the angle, then
mirrors the Y position around `448.0f - limit`. All thirteen native
relocations are independently anchored to actual Context/Controller,
command slots, Angle operations, native original float and SSE-sign objects.

Locked MSVC x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
emits **225/225 identical non-relocation bytes** across the entire 277B
function. A fresh canonical replay verifies **277/277 full original bytes**
including all 13 relocations, and the pre-existing **five** same-source units
still replay exactly: `6/6` units in the new object.

Adding one method to shared `src/Bullet.hpp` caused a new compiler-private
MSVC `$SG` renumbering for four Dialogue diagnostic literals, from
`$SG117758..117761` to `$SG117759..117762`; their relocation destinations
and original native bytes were unchanged. The complete shared-header include
closure of six other old objects, **35/35 prior exact units**, was freshly
recompiled and strictly replayed. **This batch: 36/36 distinct affected units,
seven cold objects**; no unfiltered whole-graph cold replay. Proof logs:
`.analysis/core218-bullet-reflections-replay.log` and
`.analysis/core218-bullet-header-affected-replay.log`.

The native complete 832B four-direction dispatcher, native 3,735B
single-shot emitter and 41,967B Enemy opcode dispatcher remain nonexact.
A private complete 832B source investigation exists under `.analysis/`;
no prefix match or unfinished branch is admitted as an exact function.

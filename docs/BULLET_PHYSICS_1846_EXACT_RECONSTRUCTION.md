# CORE/EXACT-262 — complete exact original 1,846-byte Bullet physics state machine

Target: immutable Japanese TH20 v1.00a Steamless PE, whole SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original `Bullet::update_physics()` state machine at
**`0x00485B60..0x00486295`**, previously a major unresolved gameplay boss,
is now maintained in `src/BulletPhysics.cpp` as normal typed C++20 with
**1,846/1,846 original code bytes strict exact**. The original complete
MSVC compiler contribution **includes** its two-byte internal alignment
and four-entry switch table: **1,864/1,864 original bytes strict exact**.
All **517 original x86 instructions** and **84 original relocation sites**
are reproduced. The original function whole-code SHA-256 is
`52127c18b3eb70751ce6c9ca21a35fb8e78b1b4281bea758fbd1f2c533220018`.

## Original compiled contribution and independent relocated data identity

The entire game machine-code function `0x00485B60..0x00486295` is exactly
**1,846 bytes**. It is followed by native **`66 90`** at
`0x00486296..0x00486297`, then the original four-entry, 16-byte
**jump table at `0x00486298..0x004862A7`**. The table contains these
true game-code targets, independently confirmed as original instruction
boundaries by complete Capstone native disassembly:

| Native switch index | Original target | Original meaning |
| ---: | --- | --- |
| 0 | `0x00485D67` | Active command-processing loop, state 1 |
| 1 | `0x00485CC7` | Half-velocity / Timer reset route, state 2 |
| 2 | `0x00486041` | State-3 short movement and default-clock reset |
| 3 | `0x004860E4` | State-4 clock reset |

Those **1,864 bytes** are the complete source-file MSVC `.text$mn` COFF
contribution, exactly compared under the manifest's `compare_size = 1864`.
The subsequent eight native `CC` bytes at `0x004862A8..0x004862AF`
are separate linker alignment, **not attributed to this C++ source
function or faked as a code tail**. The native full 1,872-byte
PE span (including linker alignment) SHA-256 is
`57585b00033af007f11038d2758c4231800fcc861675ee851460be9140e3f996`.

Exactly **84 original relocation positions** (including the 4 native
switch-table entries) were independently checked from the real PE:
for every direct original `call` and every relocated data read, the
Capstone-decoded *native semantic operand* fixes the callee or data
address, rather than retrieving/assuming the comparison solver's
answer. The four table destinations were separately read as original
little-endian PE words and verified against full original code
instruction heads. This checked the exact offsets, types, target
addresses and source COFF symbols before canonical replay. Private
attestation is maintained at
`.analysis/core262-physics-native-independently-attested-relocations.json`
and `.analysis/core262-physics-native-anchors-summary.log`. No
synthetic machine bytes, shortened extents or fake relocated variables
are admitted.

## Complete game physics behavior and the actual natural C++ source

The original member sets native BulletFlags bit 10, postfix-increments
`timer_508`, retires bullets marked for removal by bit 3, and saves
the actual global `default_timer_clock` at `0x005AEFE4`. It computes
slowdown from real `timer_4d8.fraction()` and
`timer_4e8.fraction()` outside states 2/3/4 if bit 9 permits it;
its float interpolation at `+0x474` updates the real scale and
conditionally clears command/scale bits.

The source uses the **true original `switch(state)` with `case 1..4`**.
MSVC automatically emits the native local `state - 1` dispatch index;
an earlier independent but semantically similar source wrote
`switch(state - 1)` and introduced a different local stack frame.
State 2 shares the native real position half-step, then genuine float
Timer assignments and a common reset path with state 1. State 1 runs
the original 12,140-byte external full command sequencer and loops
through actual 0/1/2/3/7/8/9/10/11 Bullet command flags, including the
832B four-boundary boss; the command 5/13 Timer cases can cause the
original additional whole-loop iteration. On completion state 1
integrates velocity through the actual `ClockScalar` and genuine
`Vector3` return-by-value operators, retaining the original two-lane
and Z behaviors and native function ABI. State 3 and state 4 share
native clock and float Timer reset behavior without fabricated owner
fields. The end of all branches checks the native real SpriteData,
conditionally invokes the already exact 781-byte screen-wrap method,
tests real floor/screen bounds, decrements two native counters, advances
the real Animation and retires out-of-bounds/completed bullets. The
original default clock is restored before normal or early return.

The complete source was obtained through multiple independently
compared entire-function MSVC builds, **not** a decompiler-code paste:

- Original first entire natural draft emitted 1,935B of function code
  and 467/517 native instruction mnemonics aligned.
- Typed right-shift native flag checks, actual postfix Timer semantics
  and common state-2 reset/fallthrough reduced the draft to 1,849B
  of game code and 490/517 native instruction mnemonics.
- Correctly arranging the actual state-2/1 shared reset path recovered
  the real command loop, reaching **513/517** original instruction kinds.
- Replacing two separately named Timer fraction locals with the genuine
  inline multiplication expression and using the real **`2.0f` literal**
  restored the complete **517/517** original mnemonic sequence.
- The original early exit from the state-2 reset branch is a real
  **`break` from `switch`**, not a duplicated long `goto`, removing
  one surplus five-byte jump and producing exactly 1,846 code bytes.
- Most importantly, restoring real **`switch(state)` / cases 1..4**
  preserved every actual branch and return while recovering the original
  **0x88-byte stack frame**, all 1,528 non-relocation bytes of the
  **1,864-byte** code/table contribution and the exact native table
  relocation identities. No inert compiler-shaping local is present.

The locked MSVC 19.44 x86 profile is `/nologo /c /std:c++20 /Od
/Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`, invoked with
reduced scheduling priority. The canonical strict result is
**`bullet_update_physics: exact (1846/1846 coverage bytes; 1864/1864
compared bytes)`** in
`.analysis/core262-physics-complete-canonical-replay.log`.

## Scoped shared-header regression and remaining whole-game roots

This new complete real member only adds two narrow genuine external
method ABIs to the existing `src/Bullet.hpp`:
`advance_command11` (original 1,404-byte body) and
`run_extended_commands` (original 12,140-byte body). Their **separate
whole functions remain nonexact**; they are not faked as subbranches
or credited by this caller's exactness. Real name and source spelling
are inferred, and whole-game linking/running remain distinct goals.

The actual compiler receipt dependency closure of modified `Bullet.hpp`
is **27 previously accepted native source providers / 65 existing strict
native units**. All 27 were freshly rebuilt, including the exact
662-byte Bullet cancellation and the real 781-byte four-way wrap boss.
**65/65 old units strictly replay exact** with no changed native
relocation targets or native code. Some private `$SG` compiler-assigned
string symbol identifiers were renumbered only after checking original
relocation offset, type and native data destination, and then the
entire affected source was recompiled and strictly replayed.
With the newly accepted complete physical function this is
**66/66 affected native strict units across 28 fresh cold source
objects**, not an unfiltered whole-repository cold replay. The focused
logs are
`.analysis/core262-physics-affected-replay-part-{0..2}.log` and
`.analysis/core262-physics-complete-canonical-replay.log`.

Remaining significant independent nonexact roots include the
**1,404B** Bullet command-11 corner geometry parent,
**2,018B** Bullet collision root,
**273B** single-group drawing,
**3,735B** single-shot Bullet emitter,
**12,140B** Bullet command sequencer and
**41,967B** Enemy ECL opcode dispatcher. The whole 1,846B physics
boss is **no longer open**; prior frontier reports are dated evidence,
not a conflicting current status.

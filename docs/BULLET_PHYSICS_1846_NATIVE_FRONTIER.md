# CORE/AUDIT-258 — complete native 1,846-byte Bullet physics state machine and whole-body C++ probes

The immutable Japanese TH20 v1.00a Steamless executable is the original
source of truth, whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This investigation covers the **entire native game-authored**
`Bullet::update_physics()` at `0x00485B60..0x00486295`, not an isolated
case arm, hand-picked prefix or fabricated split function. No exact-code
credit is claimed for this still-unmatched 1,846-byte root.

## Independently verified original extents, calls and switch ownership

The original function body is **1,846 bytes / 517 x86 instructions**,
whole native SHA-256
`52127c18b3eb70751ce6c9ca21a35fb8e78b1b4281bea758fbd1f2c533220018`.
There are **57 direct CALL instructions to 30 distinct targets** and an
original indirect jump-table dispatch at `0x00485CC0` using a native
**four-entry 16-byte table** at `0x00486298..0x004862A7`, with the
original targets, in order:

| State switch index | Original destination |
| ---: | --- |
| 0 | `0x00485D67` |
| 1 | `0x00485CC7` |
| 2 | `0x00486041` |
| 3 | `0x004860E4` |

**Whole compiler contribution is 1,872 bytes**, not 1,846. A real
**two-byte `66 90` NOP** at `0x00486296..0x00486297` follows the
complete 1,846B code, the original four pointer entries then follow,
and eight original `CC` alignment bytes occupy
`0x004862A8..0x004862AF`. The next original function starts at
`0x004862B0`. SHA-256 of this entire native code, padding and table
contribution is
`57585b00033af007f11038d2758c4231800fcc861675ee851460be9140e3f996`.
The original table SHA-256 is
`cc64f81603834e6264a7dff016a0ac580be9515ba62507bf02221b6cd3bb555a`.
Source candidates must ultimately compare the **entire native 1,872B
contribution and every switch-table relocation**, never just code bytes.

The original source owner is a true `Bullet` at native size `0x528`.
The entire function first sets native Bullet flags bit 10, advances its
real `Timer` at +`0x508`, conditionally retires an inactive Bullet, and
saves/restores the actual process `default_timer_clock` from
`0x005AEFE4`. It computes a Timer-based slowdown scalar if the Bullet
is outside states 2/3/4 and bit 9 is clear, samples the original float
interpolation at +`0x474` when command bit 22 is set, and dispatches
four actual state paths. The active-state path runs the genuine native
command operations and may repeat the whole update until no command
completes; another path performs the original half-velocity motion and
shares the original Timer/clock reset. The common exit re-evaluates
real SpriteData extents, invokes existing exact Bullet screen wrapping,
checks native playfield bounds, decrements gameplay counters and retires
an animation-completed or out-of-bounds Bullet while restoring the
original clock.

**Already individually strict-exact dependencies** in the real call graph
include original `Bullet::advance_command0/1/2/3/7/8/9/10`, the complete
832B boundary handler, 781B screen-wrap, true SpriteData resource access,
Timer float assignment, 291B Bullet retirement and the full 181B floor
predicate. Original command-11 at `0x00481200` is **1,404B and remains
nonexact**, even though its three geometric support functions are now
whole strict exact. Original `Animation::update()` is a separate
**39,470-byte** child at `0x0042B5D0`, also not exact. No caller or child
is counted as proof of this root.

## Three entire natural MSVC C++20 root trials, compared separately

All candidates are complete native game-state C++20 method bodies built
with the locked MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` profile and independently inspected with
Capstone against all 517 original instructions. The private header
`.analysis/core258-Bullet.hpp` adds **provisional**, unowned methods
only within ignored analysis sources. No fake no-op layout or machine
code padding is installed in production.

| Complete source hypothesis | `.text$mn` COFF contribution | Actual code to final `ret` | Original instruction mnemonic positions in order | Comparison result |
| --- | ---: | ---: | ---: | --- |
| `.analysis/core258-BulletUpdatePhysics.cpp` | **1,952B** | **1,935B** | **467/517** | Not exact |
| `.analysis/core258-BulletUpdatePhysics-v2.cpp` | **1,860B** | **1,844B** | **487/517** | Not exact |
| `.analysis/core258-BulletUpdatePhysics-v3.cpp` | **1,868B** | **1,849B** | **490/517** | Not exact |
| Immutable original native code + switch table and alignment | **1,872B** | **1,846B** | **517/517** | Exactness target, not yet reached |

The initial complete source includes all four state arms, command
updates, two real bound checks, default-clock restore and Bullet
retirement, but a naive command-bit check and duplicated state-2 clock
reset put its compiled code **89B above** the original. Reconstructing
native right-shift-and-mask flag predicates, post-incrementing the
actual `Timer` rather than prefix-incrementing, preserving the common
state-2 reset route and using signed comparison for the native command
index reduced the **whole emitted code to 1,844B** and aligned 487 of
517 original instruction mnemonics. A third complete candidate restores
additional original bit-3/bit-22/bit-12 checks, improving to **490/517
original mnemonic positions**, but its **1,849B code is still 3B
longer than the entire original 1,846B code**. Its full `.text$mn`
contribution is 1,868B, still **4B shorter than the real 1,872B
code+alignment+table contribution**.

The remaining mismatches are actual **control flow, return-object ABI
and live float/counter semantics**, not missing arbitrary padding:

- The original has an additional command-bit-26/state-2 update/re-entry
  region at native offsets approximately `+0x207..+0x228`. Current
  candidates do not yet emit that entire native set of calls and tests;
  a superficial conditional or `goto` is not sufficient.
- Original Vector3 position integration at approximately
  `+0x170..+0x196` uses the genuine 2.0f argument and native hidden
  return-object flow. A candidate can match its call destination but
  still produce the wrong SSE temporary slots/register ordering.
- Native command-state fallthrough and repeated clock resets share
  several sites; current state-2 code still has one mismatched branch
  and another inserted sequence rather than the native common path.
- An original shifted bit-12 check, signed counters and flag-handling
  branch widths still differ in some whole-source trials. Specifically
  one trial wrongly used unsigned `command_index` comparisons, yielding
  `jae`/`jbe` instead of original signed `jge`/`jle`.
- The compiler-generated four-way jump table, its original entry
  addresses and the exact two-byte NOP / trailing CC alignment must
  align simultaneously with complete code. The candidate's unrelocated
  diagnostic 16B table cannot establish original jump destinations.

**No canonical manifest unit, authored source mapping or exact function
credit was created** for `0x00485B60`. The exact previous 275 authored
functions / 71,363 original bytes remain protected. The private
complete-body probes, compiler objects/receipts and native disassembly
are retained under ignored `.analysis/core258-*` and
`build/core258-probes/`; no probe was admitted by length or partial
mnemonic similarity.

## Regression scope and pending large roots

This batch changes only English evidence notes and source-navigation
references. **Zero existing native source files, public headers,
compiler flags, canonical manifests or original relocated data targets
change**, so precisely **zero old or new units need cold replay**.
Running a full unfiltered cold replay would give no new information and
is expressly disallowed. Target SHA-256 and tracking ledgers were
checked without adding exact coverage.

Major separate whole roots remain nonexact: **273B** group drawing,
**1,404B** Bullet command-11, **1,846B** physics, **2,018B** collision,
**3,735B** single-shot Bullet emitter, **12,140B** Bullet update and
**41,967B** Enemy opcode dispatcher. Work on original full functions,
not tiny leaf-only extraction, remains the priority.

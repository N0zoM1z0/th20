# CORE/RECON-333 — entire 1,518-byte Player option rebuilding boss: maintained nonexact C++ frontier

The immutable TH20 v1.00a Japanese Steamless target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete original *game-owned* `Player::rebuild_option_animations(int)`
function occupies `0x004FACA0..0x004FB28D`: **1,518 native bytes, 418
complete i386 instructions**, original interval SHA-256
`0efafdd89cb2d190c5bc4eca1ecd4f1343b1da8c6032d23870a6a6b4127b779b`.
The original Ghidra database attests eight native callers, including the
separately **966/966 exact** Player reset root `0x004FB450`, and 29 distinct
native callees. Source now exists for the *entire* original control-flow
frontier at **`src/PlayerOptionRebuild.cpp`**, but the original parent is
**NONEXACT and receives zero canonical match credit**. Neither 1,518
original bytes nor any prefix are added to `config/matches.csv` or
`config/match-units.toml`.

## Complete observable control-flow, not a truncated helper

The maintained function retains the original initial Renderer view selection
and real PlayerShotController flag-0 bitfield setter; optional negative
requested-count replacement with the native PlayerRecord signed count; real
three-`std::clamp` PlayerRecord operands, signed option division and resource
ownership branches; state-dependent retiring/creating and resolving option
AnimationHandles; signed/unsigned ten-slot main option iteration and
12-slot secondary option clearing; both real WeaponStone focused/unfocused
virtual offset forwarding methods and the two-original-Weapon virtual
option initializer; 128.0f float-to-fixed `IntPoint` conversion; original
-999.0f Animation Y marker, both independent hidden-return animation spawn
wrappers and the native final option index publication.

The newly exact ABI dependencies now used directly include:

- `AnimationFile::spawn_flag2` — independently exact **57B** call wrapper at
  `0x0049CBF0`, distinct from the separately exact 57B non-flagged wrapper
  `0x00450C70`; the early branch must not bypass the native aggregate-return
  ABI by calling the full seven-argument spawn directly
- `Player::animation_file_ref()` — independently exact **17B** actual
  getter at `0x00421810`, returning Player's true AnimationFile pointer
- Real PlayerRecord option count and clamps (including reused existing
  `starting_power` at `0x004B81D0`), actual WeaponStone vtable slots and
  option-pair initialization, complete 165B option field broadcast, real
  AnimationHandle release, and both 10/12-slot PlayerValues index bodies
- Correct source expression of the original option-offset conditional:
  the focused and unfocused arms independently call the real array index
  getter, and the original final position write obtains the indexed record
  again instead of substituting a cached pointer merely to shorten code

The two script words accessed from **actual PlayerShotData+0x88 and +0xA8**
are independently observable native memory reads; they fall inside a
previously documented serialized damage-cap matrix. **Their enclosing
resource schema, script-array cardinality and semantic names are unresolved.**
The maintained source intentionally labels these raw serialized reads as
a provisional boundary; it does not invent or modify the PlayerShotData
allocation, target executable, fake table body or independent engine owner.
This prevents an unsupported declaration of two new permanent arrays from
silently changing the known resource layout.

## Fresh original PE and complete compiler evidence

A fresh original PE full-span Capstone decode independently finds **57
native direct `REL32` call instructions**, plus **three actual `HIGHLOW`
relocation fields** in the original PE's `.reloc` table. They are original
fields `+0x2C -> 0x005C0028` (published Renderer owner) and
`+0x1A9/+0x4AB -> 0x0056FD7C` (actual original -999.0f).
Full independent original offsets and targets, not inferred from a
candidate's bytes, are preserved in ignored
`.analysis/core333-independent-native-parent.json`.

Full source, compiled with locked MSVC 19.44.35211 i386
`/std:c++20 /Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise /EHsc`, emits
**1,587B and 420 complete i386 instructions**. Ordered original/candidate
Capstone mnemonic alignment is **390/418 native instruction kinds**; the
candidate has **62 COFF relocation fields** versus the original's **60
independently observed native references**. The latest revision restores
the original `0x0049DA50` fastcall AnimationHandle value-clear call after
cancellation, rather than replacing that call with an inline field store.
The physical 20-byte callee is separately strictly exact in
[CORE/EXACT-335](ANIMATION_HANDLE_VALUE_CLEAR_EXACT_RECONSTRUCTION.md). The entire original
8-byte-aligned stack realignment sequence through `+0x16` and the original
nine-byte ending/`ret 4` are identical; the generated native frame still
uses `sub esp,0xB4` instead of original `sub esp,0x9C` (24 extra bytes of
active local storage). Remaining differences include local temporary
ownership, early and late AnimationHandle release call structure, selected
PlayerValues re-reads and resource script conversion/virtual-call ordering.
No claim is made that mnemonic overlap proves execution equivalence.

The **actual used aggregate result** of Player option fixed-position
addition is explicitly 8-byte aligned as an ordinary live `IntPoint` value.
This naturally reproduces the original MSVC x86 `push ebx; mov ebx,esp;
sub esp,8; and esp,-8 ...` stack alignment; switching the candidate from
`/GS` to the original function's observed `/GS-` likewise removes an
unobserved security cookie. Neither change uses inert locals, synthetic
stubs, inline assembly, byte padding, fake return values or a shortened
comparison range. Previous private explorations remain under `.analysis/`
for forensic reproduction; the resulting maintained compiler probe is
`build/core333-probes/PlayerOptionRebuild-maintained.obj` plus its
`.receipt.json`, with counts in
`.analysis/core333-maintained-root-check.txt`.

## Verification scope and still-open frontier

This checkpoint introduces **one source-present, authored, nonexact
whole-function mapping**, but does not modify any existing canonical exact
source/header/profile or accept any newly exact native range. Its affected
**canonical exact replay scope is zero**; the source itself was compiled
with the locked toolchain and independently compared over its entire
1,586-byte emitted contribution against the entire original 1,518-byte
span. No unfiltered full-graph cold replay was run or needed.

The native parent remains open until all codegen, stack-local, relocation,
resource-layout and gameplay-branch differences are reconciled with
independent original evidence and strict whole-unit canonical replay.
This full-source checkpoint is not a claim of a buildable linked game or
runtime-equivalent original executable.

## CORE/RECON-343 later whole-parent control-flow and literal audit

The maintained complete C++20 owner `src/PlayerOptionRebuild.cpp` has been
corrected after re-reading the **whole original** i386 call graph, not simply
trusting the earlier decompiler/control-flow hypothesis:

1. The late option-Animation spawn at original native `+0x423..+0x4B4`
   **unconditionally** obtains the Player's AnimationFile and issues one
   real 57-byte `AnimationFile::spawn(...)` wrapper call. An earlier source
   version introduced a second file-null guard that the native PE does
   *not* contain. That guard and its extra `Context::player()` and
   `Player::animation_file_ref()` calls were removed. The genuine earlier
   branch at original `+0x110..+0x190` still checks for a null file and
   calls the distinct `spawn_flag2` wrapper only when non-null.
2. Each script slot at native PlayerShotData `+0xA8` / `+0x88` is now read
   via an independently formed base pointer and a **separate 4-byte
   displacement** from the real WeaponStone option-variant index. Using
   a direct `script_table[index]` emits a different scaled-SIB access in
   MSVC `/Od`; the native original instead shifts the index by two bits
   and adds the displacement to the previously saved table base. The
   actual resource sub-schema remains unresolved, and no new permanent
   resource arrays were declared.
3. Both original Animation Y markers are actual literal **`-999.0f`**,
   confirmed by the original PE `0x0056FD7C` float bytes. Using that
   natural C++ literal instead of a separate `extern const float`
   avoids extra `/Od` floating-point spill/reload operations in both
   branches. The generated COFF constant is `__real@c479c000`.
4. The original option-offset `IntPoint` destinations are now acquired
   **before** evaluating the WeaponStone focused/unfocused float source,
   preserving the native method call and destination evaluation order.
   The real aligned eight-byte result still participates in both final
   fixed-coordinate copies; no inert locals, inline assembly, manual
   NOPs or exact-build conditional branches were introduced.

Fresh compiler run: original **1,518B / 418 instructions / 57 direct E8
calls / 3 original PE HIGHLOW fields**; maintained natural C++20 source
**1,518B / 411 instructions / 410 of the original 418 mnemonic kinds in
order / 57 REL32 and 3 DIR32 COFF relocations**. The first complete
22-byte stack-realignment prologue and final nine-byte return sequence
match the original, but the intermediate frame and option fixed-position
lifetime remain different. Of the three independently grounded native
absolute fields, the Renderer global still occurs at `+0x2C`, the early
-999.0f literal now matches the native `+0x1A9`, **but the late float
literal is at COFF `+0x49F`, versus original `+0x4AB`**. Therefore,
**the function is still NOT exact** despite the coincidentally identical
overall 1,518-byte length and same number of relocation sites. The
independent full-function diagnostic reports only **704/1,278
nonrelocation bytes aligned**, not a strict match.

Proof files (ignored private analysis): the source-shape experiments
`.analysis/core336-*`, `.analysis/core337-*`, `.analysis/core338-*`,
`.analysis/core339-*`, `.analysis/core341-*`, and `.analysis/core342-*`,
and the chosen latest locked compiler build
`build/core343-probes/PlayerOptionRebuild.obj` with matching receipt.
Quantitative result: `.analysis/core343-refined-boss-evidence.txt`.

The affected **accepted exact-unit replay scope is zero**: only one
already source-present but nonexact C++ provider and its evidence record
changed; no canonical headers, exact source, exact object profiles or
original anchors changed. The full original root remains on the open list,
with 8 native instructions and coordinate/temporary ownership not yet
reconstructed. No full cold replay was run.

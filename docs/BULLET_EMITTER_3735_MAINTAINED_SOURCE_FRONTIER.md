# CORE/RECON-514 — complete 3,735-byte Bullet emitter boss in maintained C++

Comparison source of truth: the immutable Japanese TH20 v1.00a Steamless
original at `resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**An entire, compiled, game-owned Bullet emitter C++20 implementation is now
maintained as `src/BulletEmitter.cpp`**, bound to
`std::int32_t BulletController::emit(const ShotParameters&,
std::shared_ptr<ShotMetadata>, int, int, float)` and the original head
`0x004818E0`. It remains **NONEXACT**: it adds one new *source-present*
whole-game function mapping but **zero accepted original exact bytes**, no
new strict canonical unit and no new claim that a game executable can link.
Its separately exact 339B caller `BulletController::fire()` at
`0x00481780` invokes the original physical emitter at `0x004818E0`
through the native E8 at `0x00481839`, independently verified directly in
original PE x86. The original game's author-owned event scheduler is a
large real boss, not a fabricated toy or split leaf implementation.

## Independent original full method and compiler contribution

The original **complete body is 3,735 bytes / 935 native i386
instructions**, at `0x004818E0..0x00482776`, with whole-body SHA-256
`54c8c60dc8ca5aaf6a97e094db9447150152849e904741f1f110455b002e051d`.
The *native whole compiler contribution* also includes:

- The **one original 0x90 NOP** at `0x00482777`.
- A **13-entry (52-byte) original dispatch table** at `0x00482778`.
- An **11-entry (44-byte) original dispatch table** at `0x004827AC`.
- Then eight separate original **0xCC linker-alignment bytes** at
  `0x004827D8..0x004827DF`, not game body credit.

The original code has **60 E8 calls to 43 unique original callee heads**.
The native x86 branches at `0x00481A7C` and `0x004823B5` jump through
those independent 13- and 11-entry tables; every original table word
lands on a decoded original native instruction head, not a compiler
candidate position. The correct original comparison scopes are therefore
**3,735B method**, **3,832B method+NOP+tables**, **3,840B including
linker alignment**. Counting a generated table as part of a method and
comparing mismatched scopes is invalid. This was independently checked
from the original PE, rather than inherited from prior research notes.

## Maintained whole gameplay control-flow and real typed owners

The former isolated complete private reconstruction draft at
`.analysis/core290-BulletEmitterFull-RealMetadataLifetime.cpp` has now
been promoted, examined, and corrected into `src/BulletEmitter.cpp`.
The production method uses the real existing `BulletController`, Bullet
0x528, ShotParameters 40B, ShotMetadata 0x4C, true 0x158-byte BulletStyle,
64-byte Bullet ExtendedCommand, by-value `std::shared_ptr<ShotMetadata>`,
real `std::pmr::vector<BulletCommand>` and the actual game Animation
owners. There is no replacement anonymous byte-array object or fake
Renderer layout. It performs every important whole-boss phase:

1. Take a Bullet from the actual intrusive free list; return 1 when
   empty, detach the link and prepend it to the active list.
2. Read the incoming metadata pointer once (`descriptor.get()`), move
   its shared ownership into `Bullet+0x98`, bind the genuine per-Player
   `Context`, and initialize actual per-shot timers and state.
3. Compute native row-dependent shot speed and all **13 first-mode
   shot patterns** including fan/parity, layered rings, random speed
   and angle, elliptic/sine geometry and the real `shot.count` parity.
4. Set the true Angle, Vector3 position/velocity, origin Z, flags,
   command fields, interpolation and native Timer state.
5. Acquire the actual native pool Animation, bind its real file/style
   script, optionally spawn the child animation, then implement all
   **11 cancel/style table entries** with their real color/cancel flags.
6. Inspect actual `ShotMetadata::commands` PMR vector and its first
   opcode, perform the original early command-1 transition/interrupt,
   update the entire Bullet extended-command and Animation systems.
7. Check the real player distance and optional early Bullet
   deactivation/return, release the incoming shared owner normally on
   every return/exception path.

The original native owner at `0x0044C9B0` allocates an Animation in its
real pool; the typed ABI `Animation* AnimationPoolOwner::allocate_animation()`
is now exposed in the actual production `AnimationRuntimeOwner.hpp` so
the full emitter can compile without copying the old private provisional
owner header. **That separate 298B method remains source-absent/nonexact**.
Neither its state layout nor an invented implementation is smuggled into
`src/`, and complete final linking is still out of scope.

## Native evidence forced a genuine source-level correction

Native original instruction operands at emitter `+0x112..+0x16E`
test the **signed number of shot rows `> 1`** before entering its
stepped-speed calculation. The older private C++ source used the
logically equivalent reverse branch `if (shot.rows < 2)`; its emitted
`/Od` branch orientation was wrong even though gameplay arithmetic
could agree. Six complete compiled alternatives with real control-flow
and locals were compared against the entire original function, not a
cropped prefix. The maintained source now checks `if (shot.rows > 1)`
and computes the same native per-row speed expression in the then
branch. Ordered native instruction-mnemonic alignment improves from
**787/935** to **792/935** while preserving the original field reads.
No fake locals or artificial byte padding were inserted to shrink the
absolute size difference.

Earlier original reanalysis also corrected a much more serious gameplay
hypothesis: original `EtamaArgInf*` metadata is read from the incoming
shared_ptr only once, **before** its owner is moved; additional
`bullet->metadata->` getter calls were not original. Likewise the
first shot fan uses **`ShotParameters::count` at +0x24**, not rows at
+0x26, for its parity test. The promoted C++ preserves both fixes.
These are gameplay and ownership discoveries, not micro-optimization
choices. The historic 63B original `std::shared_ptr` move-assignment
callee `0x0047C530` is still not exact under today's library template;
one source path cannot be declared whole exact merely because it
calls a semantically equivalent move operation.

## Locked real compiler result: whole source present, NOT exact

One independent fresh pinned MSVC 19.44.35211 x86 compile using
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits the complete function in
`build/core513-probes/BulletEmitter.obj`:

| Entire-method measure | Original native | Current whole C++ candidate |
| --- | ---: | ---: |
| Original executable method code | **3,735B** | **3,516B** |
| Decoded code instructions | **935** | **890** |
| Complete code + actual NOP/tables | **3,832B** | **3,612B** |
| Ordered original instruction mnemonic kinds | **935** | **792 aligned** |
| Direct calls / COFF references | **60 original E8** | **116 total COFF fields**; exact original relocations NOT established |

The candidate generates its own switch tables and exception/unwind
structure but they have **not** achieved full exact native target/
labels, shared_ptr lifetime compiler sequence, byte length or address
relocations. It is NOT 3,735/3,735, not a 3,832-byte compiler
contribution, and is not eligible for canonical exact admission.
The whole candidate and original diagnostics are in ignored
`.analysis/core514-emitter-maintained-score.json`,
`.analysis/core514-emitter-branch-comparison.json`,
`.analysis/core514-emitter-whole-original-attestation.json`, and
`.analysis/core514-emitter-original-attestation.log`.
Original source naming/translation-unit boundaries also remain
unproven; `BulletController::emit` is a descriptive maintained symbol.

## All public-header effects were handled, no full cold replay

Adding a single real declaration to `src/AnimationRuntimeOwner.hpp`
changes a shared compiler input. Before editing, the existing locked
native unit receipts identified exactly **38 affected original source
objects and 91 complete strict original units**, recorded in
`.analysis/core513-emitter-preedit-receipt-closure.json`. All 38
providers were cold rebuilt under their *own existing canonical*
source/unit profiles; no whole-game/global compiler rebuild was run.
An independent source-vs-immutable-PE comparison verified **all 91
entire original code bodies**, exact nonrelocated bytes, original
REL32 and original absolute destinations.

Only the ordinary MSVC private literal label in the already exact
Bullet cancel source changed: `$SG183076` -> `$SG183077`. Both source
labels contain the **identical original native string** `"bullet"` at
original address `0x0056FD14`, read independently from the original
PE. The actual relocation field in the 662B native Bullet cancel
at `0x0047C9B0` was unchanged. The manifest changes only that
compiler-private symbol spelling, not any original destination or
comparison scope. After reconciling that independently verified
source identity, **91/91 full strict units passed scoped native
replay** from the new cold objects — including the 1,404B Bullet
command-11 boss, 1,846B Bullet physics, 2,018B collision, Player
1,518B option rebuild, Dialogue and all other real header consumers.

Private evidence: `.analysis/core514-emitter-scoped-cold-build.log`,
`.analysis/core514-emitter-scoped-cold-build-summary.json`,
`.analysis/core514-emitter-91unit-native-byte-audit.json`,
`.analysis/core514-emitter-scoped-91unit-replay.log`.

**Status:** Source-present mappings increase **1,177 -> 1,178**.
Game-authored exact remains **452 complete functions / 153,901
original bytes**, and strict canonical units/unique compiler object
providers remain **1,178 / 238**. No original byte credit was added
for the nonexact emitter or its undefined allocation callee. The
separate 12,140B Bullet command-controller and 3,735B emitter remain
major unresolved native exactness tasks, alongside Player 555B/3,111B,
Enemy 41,967B and Animation VM 39,470B. This is an actual maintained
large-boss source frontier, not a final playable game claim.

# Current TH20 reconstruction handoff

**Checkpoint:** CORE197 adds complete native Enemy 700/701 queued-parameter branches to the same whole-root host; CORE197 native concrete-Laser allocation audit and CORE195 exact creator remain protected.
This is the **current** entrypoint for the next agent, not a cumulative session
log. Read [AGENTS.md](../AGENTS.md) first for exactness policy, source rules,
`gpt-web: ` commit subjects and **affected-only** replay requirements. This
handoff describes the live state on 2026-10-28; older batch counts in focused
evidence documents are historical, not competing current status.

## Repository, target and canonical status

- Worktree: `main`, with CORE/EXACT-185 saved as commit `2713b35`
  (`gpt-web: reconstruct exact Bullet file getter for Enemy opcode 555`).
  CORE186 555 integration is `126eb2a`; CORE187 shared 609–612 branch is
  `25935c1`; CORE188 ABI/COW is `0358825`. CORE/EXACT-190 adds one
  genuine complete 151-byte EnemyController resource selector and preserves
  the unchanged CORE188 full-root host. Inspect the live Git status and
  `git log -5 --oneline` for the newest checkpoint.
  Factory has no network/push. **Do not discard dirty or ignored work:** the
  user explicitly said the single worker owns all modifications.
- Target: Japanese TH20 **v1.00a Steamless**, `resources/th20.exe` (ignored),
  SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
  Do not switch to the Steam-original backup or any other release. See
  [target provenance](TARGET_PROVENANCE.md) and `config/target.toml`.
- Live ledgers: **6,928** target function candidates, **1,017** source-present
  mappings, **1,008** physical canonical strict units, **222** confirmed
  authored exact functions / **57,991** authored exact bytes. The 167 current
  canonical objects cover **182,382** comparison bytes. **Nine**
  source-present whole-function mappings remain nonexact. These are not a
  whole-game completion percentage; see generated [progress](PROGRESS.md).
- The **41,967-byte** native `EnemyState::execute_opcode()` at `0x0048C010`
  is still **not machine-code exact**. Its *single complete-root source draft*
  covers **132 effective opcode values / 100 primary heads** and passes
  **42,424 / 42,424** `-O2`/UBSan **and** ASan+UBSan whole-root host scenarios
  (ASan `vptr` excluded for unresolved fixture RTTI; leak checks enabled). Do not claim
  partial native root bytes as exact functions.

## Latest work to resume

CORE197's further **whole Enemy queued-parameter** integration has now
added two original primary heads **opcode 700 (269B/59 native instructions/10
calls)** and **701 (289B/67 instructions/11 calls)**, independently verified
from the locked PE and case-path catalogue. Both use the real 396B queued
record/metadata two-pointer COW selector semantics; 700 writes four floats
across the selected record's true ShotParameters position and metadata
`field_14`, and 701 writes five integer words to metadata `+0x24..+0x34`.
Original read order, full state images, COW isolation and earlier partial
writes on exceptions are checked. **337 added scenarios** include 80 actual
shared-owner COW copies, 144 first-time owner creation, 64 list growth cases
and 33 staged exceptions. All previous 42,087 cases remain passing, so the
active **84-TU entire-root** host passes **42,424/42,424** under both GCC13
O2/UBSan and O2/ASan+UBSan (only unrelated vptr unavailable, leaks on).
This new private draft is `.analysis/core197-enemy-dispatch-candidate.cpp`,
with `.analysis/core197-queued-parameters-host-cases.inc`, full logs and
SHA-bound `.analysis/core197-enemy-whole-root-proof.json`. Independent native
originals are `.analysis/core197-native-700-701-audit.json` and complete
.asm files. [Read opcode 700/701 whole-root evidence](ENEMY_WHOLE_ROOT_700_701_QUEUED_PARAMETERS.md).
It adds **zero native exact credit** and requires **zero new canonical cold
replay units**; the unchanged CORE195 **223/223** affected native strict
unit receipts remain valid. The original 41,967-byte Enemy root stays
nonexact. This queued-opcode work and the separately labeled CORE197 concrete
Laser constructor audit are distinct focused source/proof artifacts, not
competing reconstruction roots.


CORE197 independently audits the **nine still-open complete native
functions** immediately below CORE195's now-exact Laser creator: four
**92-byte** concrete allocation wrappers (Line/Infinite/Beam/Curve),
their **88/87/159/122-byte** typed derived constructors and the common
**522-byte** Laser base constructor. Original allocated object sizes are
`0x18F8/0x1338/0x1370/0x1D30`. The native call chains establish true
`LaserTypeNParameters` at `+0x6F8`, real `Animation` subobjects,
concrete vtables, and two 0x800-byte Curve arrays (not guesswork padding).
Private typed MSVC probe for the 522B base constructor emitted 538B and
**did not match**: it is not accepted or made artificially exact. Complete
PE byte hashes, call sites and unresolved type layout are in
[concrete Laser allocation native frontier](LASER_CONCRETE_ALLOCATION_NATIVE_AUDIT.md)
and `.analysis/core197-laser-factory-constructor-frontier.json`.
No production inputs changed: **zero further cold replay units**; previous
CORE196 whole-root **42,087/42,087** dual-sanitizer scenarios and
CORE195 **223/223** native strict provider replays remain intact.


CORE196 continues the **one complete 41,967-byte Enemy root** using the
*actual* already accepted native-exact 474-byte `LaserController::create_laser`
from `src/LaserFactory.cpp` and complete 75-byte registration from
`src/LaserRegistration.cpp`. The previous CORE192 host still exists as
protected evidence, but the active private `core196` source/host/recipe
actually executes both production methods, with its four **92-byte concrete
native allocation factories still explicitly captured**. Test-only 34-slot
Laser classes provide correct signed virtual init ABI, without fabricating
native concrete subclasses or accepting their source. **1,146 new semantic
cases**, including **96 actual Enemy opcode-702/703 to production-creator
calls**, cover count limits, handle wrap and floor, all four types, allocation
failure, signed init rejection, real intrusive-list registration, and
exception short-circuiting. The full 84-TU GCC13 host now passes
**42,087 / 42,087** O2/UBSan and O2/ASan+UBSan tests (vptr excluded only
because unrelated `WeaponStoneInfo` RTTI is not linked, leaks enabled).
The five active source/recipe hashes, both binaries and full test logs are
protected in `.analysis/core196-enemy-whole-root-proof.json` with
`.analysis/core196-dispatch-host.log` and
`.analysis/core196-dispatch-host-asan.log`. Full evidence:
[actual byte-exact Laser factory in the entire Enemy root](ENEMY_WHOLE_ROOT_REAL_LASER_CREATOR_INTEGRATION.md).
**No production compiler graph input changed in CORE196**: zero further
native cold-build/replay units. The current total remains **222 authored
exact functions, 57,991 bytes**. The 41,967-byte main Enemy switch,
concrete allocators and derived Laser initialization remain nonexact.


CORE/EXACT-195 reconstructs the **entire 474-byte** original
`LaserController::create_laser` at `0x004D47F0`. Its real 4-entry native
switch table at `0x004D49CC`, original 2-byte `66 90` alignment, four
separate 92-byte allocator call targets, signed count/handle gates, true
vtable `+0x14` integer-returning initializer and previously exact 75-byte
LaserController registration now compile from natural maintained C++20
(`src/LaserFactory.cpp`, corrected `LaserParameters.hpp` and four unresolved
concrete allocator interfaces in `DiagnosticAllocator.hpp`). Canonical unit
`laser_controller_create_laser` strictly matches **474/474 native function
bytes** and **492/492 full compiler-contribution bytes** with **all 21
original native relocations**, *including all four table entries*, under
locked MSVC19.44 x86. The actual header closure selects **33 provider
sources / 223 canonical units**. Only these 33 objects were cold-compiled,
and every one of **223/223 complete prior/new units** strictly replayed
against the real PE with fresh source/object receipts. Independent complete
COFF audit found no other code-byte mismatch; 42 internal compiler `$SG`
source symbol renumbers were reconciled against the **unchanged original
relocation offsets, target addresses, types and literal bytes**, not invented
or waived. Complete evidence:
[474-byte factory and whole switch exact proof](LASER_CONTROLLER_CREATE_WHOLE_EXACT_RECONSTRUCTION.md),
`.analysis/core195-native-laser-creator-audit.json`,
`.analysis/core195-223-strict-attested.json` and
`.analysis/core195-all-42-sg-renames.json`.
**No full cold replay** was run. This adds **474 authored exact bytes** but
*does not accept* the four allocator factory bodies or the **41,967-byte**
Enemy boss root; the last CORE192 40,941-case entire-root private host still
captures this 474B method and must explicitly integrate the real source.


CORE/EXACT-194 reconstructs the **entire genuine native 75-byte**
`LaserController::register_laser(Laser*)` at `0x004C9300` from real
`Laser.link+0x8`, `LaserController.active+0x10` and `count+0x28` fields.
Both native direct calls (`IntrusiveLink::initialize` at `0x0044A670`
and `IntrusiveList::prepend` at `0x0044A6B0`) were independently
established; **75/75 original bytes with two relocations** replay exact
under locked MSVC 19.44 x86. The now independently byte-exact in CORE195 **474-byte**
LaserController creator at `0x004D47F0` calls this method at four verified
sites after allocation/virtual init. The only affected compiler-receipt
closure is **3 production TUs**, **22/22** complete strict units all passed
fresh cold build; other providers were not cold-built. Current source:
`src/LaserRegistration.cpp`, updated real member declaration in
`src/LaserParameters.hpp`, canonical
`build/core194-canonical/LaserRegistration.obj`. Private native bytes,
2 original targets, 4 caller sites, source/object hashes and replay log:
`.analysis/core194-native-laser-registration-audit.json` and
`.analysis/core194-affected-replay.log`; complete evidence at
[real laser registration exact reconstruction](LASER_REGISTRATION_NATIVE_EXACT_RECONSTRUCTION.md).
CORE194 added **one authored exact / 75 bytes**; CORE195 subsequently
accepted the entire separate 474-byte factory. Neither adds native byte
credit for the 41,967-byte Enemy boss. CORE192's 40,941 whole-root
scenarios remain protected; they were compiled before the new nonvirtual
member declaration and do not yet execute the real registration method.


CORE192 added **both complete original large Laser spawn opcode branches**
to the *same existing entire Enemy source-draft root*: native **702** has
682 bytes/153 instructions/15 calls at `0x004944C7..0x00494771`, and
**703** has 787 bytes/176 instructions/16 calls at
`0x00494771..0x00494A84`. Native independent instruction audit confirms
the original **0.9f strict/unordered XY relative-position threshold**,
record+metadata pair via writable queued COW, *actual* PMR
`BulletCommand` copies, type0/type1 distinct layouts, optional
`integer_argument(1)` on 703, angle normalization and late actual
`Context::laser_controller`. The original **474-byte** LaserController
creator at `0x004D47F0` was an explicit nonexact host boundary in CORE192;
CORE195 now accepts its **whole native body** separately, but the old host
still uses the capture until explicitly reintegrated. New **303** complete-root cases
include 96 COW copies, 96 missing-owner creations, 288 real PMR deep
copies, 48 operand-retargeted Contexts and 15 exceptions. Both full 82-TU
O2/UBSan and ASan+UBSan hosts pass **40,941/40,941** scenarios (only vptr
instrumentation excluded for unrelated unlinked RTTI, leaks checked).
Protected current native audits, four input SHA hashes, two host hashes and
full logs: `.analysis/core192-enemy-whole-root-proof.json` and
`.analysis/core192-native-702-703-audit.json`. Full evidence:
[CORE192 Laser 702/703 integration](ENEMY_WHOLE_ROOT_702_703_LASER_CREATION.md).
No maintained native compiler input changed, so **zero canonical cold
replay units** were required; native whole root remains **nonexact**.


CORE191 integrates the **actual accepted 151-byte**
`EnemyController::animation_file` from `src/EnemyResourceSelection.cpp`
into the *single complete-root* Enemy dispatcher host. The prior historical
selector-failure hook remains **private**, but the new 146 real-route cases
(36 direct / 110 full original opcode 555) execute the exact production
selector with native array bounds, separate inner/outer Contexts, live Stage
global, sound-before-VM order and Stage exceptions. The Stage getter remains
a test-only captured unimplemented boundary, not a guessed production body.
All **40,638 / 40,638** scenarios pass in **both GCC13 O2/UBSan and
O2/ASan+UBSan**, with `vptr` excluded solely due unlinked unrelated fixture
RTTI; leak detection enabled. New current proof and logs:
`.analysis/core191-enemy-whole-root-proof.json`,
`.analysis/core191-dispatch-host.log` and
`.analysis/core191-dispatch-host-asan.log`. Details:
[CORE191 exact selector in whole root](ENEMY_WHOLE_ROOT_REAL_FILE_SELECTOR_INTEGRATION.md).
CORE191 changes **no production compiler graph input**, so it requires
**zero additional native cold-build/strict replay units**; CORE190's
68/68 strict native units remain the validated baseline. The original
41,967-byte boss root **is still not machine-code exact**.


CORE/EXACT-190 independently recovered the **entire 151-byte**
`EnemyController::animation_file(int)` at `0x004AAE10`, a genuine complete
callee of the 41,967-byte Enemy Boss dispatcher (including opcode 555).
Index 7 calls the live Stage/Background global `0x005C069C` getter at
`0x004AADF0`, index 0 calls Context/BulletController (with the CORE185 20B
byte-exact getter), index 1 calls Context/EffectInfo, and other indices use
the genuine checked `std::array<AnimationFile*,8>::at` helper `0x004AA130`.
The original Stage owner tag/name is still **inferred** and its 20B getter
remains undefined. Three private natural MSVC probes produced 124, 145 and
finally **151** bytes; the accepted nested source emits **151/151 native
bytes**, with **seven independently established relocation anchors** and
zero differences under the locked compiler. Maintained source:
`src/EnemyResourceSelection.cpp`, `src/StageResource.hpp`, and true eight-slot
`EnemyController.hpp` array storage; canonical object is
`build/core190-canonical/EnemyResourceSelection.obj`. The `EnemyController.hpp`
header change expanded the receipt-derived affected closure to **12 provider
TUs / 68 strict native units** (including new selector); **68/68** complete
old/new units passed fresh cold build and canonical relocation-aware replay.
Six changed internal MSVC `$SG` string labels were reconciled to their same
independently verified target literals, with no shortened comparison or skipped
old unit. Further evidence: [full 151-byte resource selector](ENEMY_RESOURCE_SELECTOR_EXACT_RECONSTRUCTION.md).
**No full cold replay was run.** The 41,967-byte Enemy root remains
**machine-code nonexact**, with the CORE188 **40,492-case** private semantic
host and original proofs protected. Its old host captures the 151B routing
boundary; a later integration should switch to real new selector without
mistaking that host for native x86 codegen exactness.


CORE188 independently checked the original queued-selector return ABI.
The genuine **396-byte** `0x00498B80` writable selector and **305-byte**
`0x00498D10` ensure-only selector both call the separately decoded
**55-byte** `0x00467CC0` result constructor, which writes two raw pointer
words. The complete Enemy 609–612 caller consumes them as
`std::pair<EnemyQueuedRecord*, ShotMetadata*>`, **not** a by-value
`shared_ptr`. New private whole-root candidate and tests correct this prior
simplification and implement actual native COW/ensure-only ownership using
`std::pmr::forward_list`, `std::shared_ptr` and `DebugAllocator`.
**631** additional real-owner scenarios cover 144 deep COW copies, 288
initial allocations, 144 unique-owner reuses, 144 list expansions, 192
command-vector expansions, 19 ensure-only selections and 36 post-selection
operand exceptions. All **40,492 / 40,492** complete-host cases pass in
GCC13 O2/UBSan **and** ASan+UBSan (only vptr disabled because of unrelated
unlinked native RTTI; leak detection enabled). The original native functions
remain **compiler-byte nonexact**, as does the entire 41,967-byte Enemy root.
Proof-bound inputs, native call audit, limitations and next steps:
[CORE188 selector pair/COW](ENEMY_QUEUED_SELECTOR_PAIR_COW_RECONSTRUCTION.md).
CORE188 changes **zero canonical production replay units**, so no full or
partial native cold replay was run for this private semantic refinement.


CORE187 next attacked one **genuine large native case** rather than only
leaf setters: original Enemy opcodes **609/610/611/612 all share the single
1,457-byte, 314-instruction, 29-call primary branch** at
`0x004931DD..0x0049378D` (original SHA-256
`f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b`).
The entire shared branch now runs inside the **same** native-root candidate,
using actual `ShotMetadata`/`BulletCommand` fields and PMR vector growth,
split on the native cursor/index and extended arguments, with cursor written
last. The original **396-byte queued owner selector** at `0x00498B80`
remains explicitly captured: its provisional COW interpretation is not
accepted source. The **888 new host cases** include **864 real selected
metadata accesses, 216 real PMR vector expansions and 22 expected exceptions**
(12 preserving partial writes). All **38,973** prior tests passed in both
GCC13 O2/UBSan and O2/ASan+UBSan (with the vptr/leak caveat above):
**39,861 / 39,861**. New production/compiler graph inputs = **zero**;
no new native cold replay or whole-root codegen exact credit. The active audit,
hashes, full member/write-order evidence and limitations are recorded at
[CORE187 609–612](ENEMY_WHOLE_ROOT_609_612_SHOT_COMMAND_INTEGRATION.md).


CORE/EXACT-185 added native `BulletController::animation_file() const` at
`0x004859B0`: **20/20** byte-exact native code, zero relocations. The actual
Bullet owner at +0x286D8C and distinct `EnemyController::animation_file`
selector at `0x004AAE10` independently establish the getter. The only five
canonical providers including `Bullet.hpp` were cold-built, and **33/33**
affected units strictly replayed. The Bullet TU now uses
`build/core185-canonical/BulletController.obj`, not its superseded
core180-canonical path. Canonical object count increased to 165 only in CORE190.

CORE186 then integrated the **whole original 555 branch** into the **same**
41,967-byte Enemy root host. Native code at `0x0048C3F4..0x0048C577`
comprises **388 bytes / 81 instructions and ten direct calls**; an independent
Capstone/locked-PE audit discovered that its File-spawn **layer is 3**, *not*
the `-1` of the otherwise superficially similar Enemy defeat path. The full
candidate calls the real existing SoundInf pan adapter, Motion/Enemy position,
XY distance/direction and four-argument File wrapper; the real Bullet file
getter is executed in the index-0 selection test. The then-unaccepted 151B file dispatcher, Stage owner and seven-argument
VM producer were captured as explicit boundaries in CORE186; CORE190 now
accepts the **complete 151B selector** separately, while Stage/VM remain open. **540 new host scenarios** cover both independent gates,
strict 0.2 squared threshold, alternate Contexts, five routed indices, zero
VM operand reads, full owner images and **18 exception** cases. All prior
38,433 scenarios also pass, for **38,973/38,973** with GCC13 O2/UBSan.
Source/proof and limits: [opcode 555 native and whole-root evidence](ENEMY_OPCODE_555_EFFECT_RECONSTRUCTION.md).
No additional source graph changed in CORE186: **zero further native cold
replay units**, no full cold replay and no fresh root machine-byte credit.


The previously verified exact target is **Enemy opcode 539's real callee**,
`LaserController::reset_all_lasers` at `0x004D2430`. Full native body
**263/263 bytes**, **14/14** independent relocation anchors including EH and
cookie support, locked **MSVC 19.44.35211 x86**. It walks the native intrusive
list at `LaserController+0x10`, resets each `Laser+0x6AC` Timer, clears
`Laser+0x6CC` and makes the true vtable `+0x44` `erase(1,0)` call; it does
**not** skip state==1. Current source is `src/LaserParameters.cpp/.hpp`,
tracked unit is `laser_reset_all_lasers` in `config/match-units.toml`.
**Two affected** production TUs (`LaserParameters.cpp` `/fp:precise`,
`DialogueText.cpp` `/fp:strict`) were cold built and all **21/21** full
old/new units (**4,148 bytes**) replayed; the other **162** object receipts
were reused with verified hashes. The real typed Laser owner tests pass
**601/601** each under GCC/Clang ASan+UBSan. Related Dialogue ownership tests
also pass. Detailed evidence:
[opcode 539 complete callee](ENEMY_OPCODE_539_LASER_RESET_EXACT_RECONSTRUCTION.md).

The complete Enemy *caller* at `0x0049579E..0x004957BB` is 30 native bytes /
7 instructions: read the live state `Context` (`EnemyState+0x2EC`), call
`Context::laser_controller` at `0x0041CA90`, then invoke the exact callee.
**No VM operand reads**. CORE183 added this case to the **same entire root**,
not an isolated faux function. The additional **192** host cases include
**32** caught virtual exceptions, **208** actual erase calls, **64** context
retargets, current/next unlink handling and observer lifetime checks, while
preserving all **38,241** predecessor tests. See
[whole-root 539 integration](ENEMY_WHOLE_ROOT_539_LASER_RESET_INTEGRATION.md).

The most recent **active private** root work is:

- `.analysis/core197-enemy-dispatch-candidate.cpp` — the current entire
  41,967-byte Enemy source draft with new 700/701 plus all previous
  539/555/609–612/702/703 branches, real 474B Laser creator and 75B register.
- `.analysis/core197-dispatch-host.cpp`,
  `.analysis/core197-queued-parameters-host-cases.inc`,
  `.analysis/core197-dispatch-host-recipe.json` — complete 84-TU GCC host
  retaining all CORE196 original-owner and exception scenarios.
- `.analysis/core197-dispatch-host.log`,
  `.analysis/core197-dispatch-host-asan.log`,
  `.analysis/core197-native-700-701-audit.json`,
  `.analysis/core197-enemy-whole-root-proof.json` — 42,424/42,424 two-mode
  host cases, native instruction/call audits and four SHA-bound inputs.
  Protect both `build/core197-dispatch-host*` binaries and older proof hashes.
- CORE197's **separate concrete-Laser allocation audit** remains at
  `.analysis/core197-laser-factory-constructor-frontier.json` and the
  associated private nonmatching constructor probe, not part of this host.
  All prior CORE196/192/191/188/187/185/183 proof-bound originals and
  binary artifacts are protected and must not be discarded.

For recent neighboring work see
[548 exact FrontInf](ENEMY_OPCODE_548_STAGE_TITLE_EXACT_RECONSTRUCTION.md),
[548 complete-root integration](ENEMY_WHOLE_ROOT_548_STAGE_TITLE_INTEGRATION.md),
[549 exact membership/551 color ABI](ENEMY_COLOR_CONTAINS_NATIVE_RECONSTRUCTION.md),
[549 whole-root integration](ENEMY_WHOLE_ROOT_549_AND_COLOR_CORRECTION.md),
[551 FogValue route](ENEMY_WHOLE_ROOT_551_FOG_INTEGRATION.md),
[554 BulletController caller](ENEMY_WHOLE_ROOT_554_BULLET_INTEGRATION.md),
[517/518 Screen/message](ENEMY_SCREEN_MESSAGE_517_518_RECONSTRUCTION.md),
[502/503 visibility](ENEMY_VISIBILITY_OPCODE_502_503_RECONSTRUCTION.md)
and the [whole switch layout](CORE_ENEMY_DISPATCH_LAYOUT.md).
Original 539, 555, 609–612, **700, 701, 702 and 703** are integrated in the one active
whole-root candidate (none implies whole-root native exactness). Original 548 was integrated as of CORE181.

## Next high-value research, including large functions

1. **Continue the same 41,967-byte Enemy Boss function**, preserving CORE183,
   CORE185, CORE187, CORE188, CORE191, CORE192 and CORE196 proof-bound
   inputs, real Context owners and all **42,424** current dual-sanitizer tests. The original opcode **555** and larger
   shared **609–612** caller are now integrated. Next independently resolve
   native compiler/EH closure for the **396-byte** `0x00498B80` COW and
   **305-byte** `0x00498D10` ensure-only selectors (semantic pair ABI now
   tested). The **474-byte native LaserController creator `0x004D47F0`**
   and its 75-byte registration callee are now **both exactly reconstructed**.
   The complete production creator is now **linked into the whole-root
   host**; next independently attack its **four unresolved 92-byte concrete
   Laser allocators / virtual initializer bodies**, with four
   concrete beam factory cases, virtual init and lifetime. The **151-byte**
   `EnemyController::animation_file` remains exact and already integrated;
   also attack the still undefined Stage getter `0x004AADF0` and
   Stage/Background owner `0x005C069C`, other missing primary heads and
   compiler/EH exactness. Nearby additional blockers: Renderer handle lookups for **502/503**, the actual ScreenInf
   factory and message cancellation for **517/518**, and the real Stage/Fog
   owner behind `0x005C069C` for **551**. Do not infer identities from old
   reference files or collapsed helper aliases. The full root's switch
   tables, EH and compiler partition remain unsolved.
2. **Attack other large Boss bodies and their real leaf dependencies**, not
   just short setters. Notable open work includes the ~40,752-byte Animation
   VM, 1,707-byte damage query, full Dialogue frame/message resources,
   Renderer ownership, and whole-game startup/lifetime. Follow
   [source map](SOURCE_MAP.md), [architecture](ARCHITECTURE.md),
   [roadmap](ROADMAP.md) and [evidence index](EVIDENCE_INDEX.md).
3. The **nine presently mapped nonexact whole roots** also deserve closure:
   `FunctionChainController::remove_unlocked` (`0x412400`),
   `create_bomb_controller` (`0x478300`),
   `EnemyState::update_mesh` (`0x4A4190`),
   `EnemyPattern::emit_items` (`0x4A5350`),
   `PlayerFeedback::record_hit` (`0x4FB3A0`),
   `create_hit_controller` (`0x4C20D0`),
   ProgressSaveManager construction (`0x50E5D0`),
   ProgressSaveManager::commit (`0x50F660`) and
   `archive_compress` (`0x539550`). Their unique native findings live in the
   corresponding documents from [EVIDENCE_INDEX](EVIDENCE_INDEX.md).

## Protected data and fast scoped verification

`config/match-units.toml` is the **only** current canonical object inventory,
not a static build-directory list copied from old handoffs. As of CORE195 it
selects **167** actual `build/**/*.obj` files with **167 sibling
`.receipt.json` files**. Their distribution is core141 66, core142 6,
core145 3, core149 1, core151 1, core154 5, core154-v2 1, core156 1,
core158 10, core163 19, core164 8, core166 2, core167 1, core174 2,
core178 9, core180 26, **core182 2, core185 1, core190 1, core194 1
and core195 1**. Old probe objects/receipts may be
retained as historical evidence but are not current acceptance units. Also
preserve the twenty historical unfinished QueryProtocol/sound/Alignment
products documented in
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound protocol](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Animation pool](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

**For CORE195**, the changed `LaserParameters.hpp` virtual signature
and new `DiagnosticAllocator.hpp` concrete factory interfaces affect exactly
**33 receipt-derived canonical providers / 223 units**. Every one of those
33 sources was rebuilt under its own pinned flags and all **223/223** full
native strict unit comparisons passed. No unfiltered cold replay was run.
**For CORE194**, new real `LaserController::register_laser` and
`LaserParameters.hpp` affect **3 provider objects / 22 native units**;
**22/22** strict cold replays pass, other source providers not rebuilt.
**For CORE190**, changes to real `EnemyController.hpp` and new full selector
source affect exactly **12** receipt-derived canonical providers, all **68/68**
complete native strict units passed after **12** serial reduced-priority cold
compiles. **For CORE185**, changed `Bullet.hpp` inputs affected five canonical
providers: **33/33** prior units / **5** cold objects passed. **For CORE186/CORE187/CORE188/CORE191/CORE192/CORE196 private entire-root host integrations**, changed
production compiler inputs = **zero**; they rebuilt only separate GCC13
semantic hosts (and CORE187's additional AddressSanitizer variant), not any
native cold replay unit. Do **not** invoke whole-graph cold replay, Ghidra, MSVC or
full CI just for an evidence handoff. Verify `git status`, `git diff --check`,
protected product hashes and links; reuse the CORE185 native canonical
replay and the current CORE196 full-root semantic host receipts. The older CORE192
boundary remains historical; the new CORE196 unhooked caller executes the
actual exact Laser creator, though the concrete native allocation factories
remain explicit fixture boundaries. The CORE190
native-exact selector is linked into this host, but its Stage getter and
actual renderer/VM producer remain separate private boundaries. To resume actual RE, inspect all dirty work (the user owns
all modifications), review the specific native instructions with the attested
Ghidra/PE workflows, select the true affected include closure from compiler
receipts, then cold-build/replay **only those affected units**. Original
compiler/SDK/resource/target files are all ignored and must be preserved.

Useful commands from the repository root:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
# Only when a source unit actually changed:
scripts/build.py --unit laser_reset_all_lasers
scripts/repo-python scripts/compare-coff-function.py --unit laser_reset_all_lasers
```

Before changing build products, read [workflow](RE_WORKFLOW.md) and
[oracle definitions](ORACLES.md). Use `scripts/repo-python` for all Python
invocations, serial `nice -n 15` for heavy jobs, never patch the target PE
or Ghidra database bytes, and distinguish **real x86 canonical exactness**
from isolated O2/UBSan scenario counts. Keep source/docs/commit messages in
English (preserving official Japanese target metadata). Commit substantive
progress promptly with **`gpt-web: <description>`**.

## Cleanup and history lookup

CORE184 retires **eight** unreferenced, regenerable temporary files totaling
**15,391,114 bytes**, including a synthetic 12.5 MB compiler-output stress
log, an intermediate host-only object, the superseded CORE182 probe pair and
two disposable factory test output directories. The exact SHA-256/path/size
inventory and protected-before/after file hashes are stored in the ignored
`.analysis/core184-handoff-cleanup-audit.json`. This cleanup does not alter
maintained source, canonical manifest, original target, exact-credit ledger,
current root inputs, evidence archives or active compiler products.

For historical checkpoint narrative and old retirement inventories, use
`git show f709625:docs/RE_HANDOFF.md` and the focused evidence documents;
those dated paragraphs are intentionally **not** duplicated in this current
handoff. Private legacy original-input archives remain available under
`.analysis/`, and all CORE183/CORE185/CORE187/CORE188/CORE191/CORE192 root candidates/proofs listed above remain intact.

# TH20 reconstruction: current handoff

**Updated 2026-10-28; CORE/RECON-343 entire Player option control-flow refinement.** This file is the concise
entrypoint, **not** a running transcript. Previous 1,689-line historical
handoff is available with `git show e7fa30d:docs/RE_HANDOFF.md`.
Use the [focused evidence index](EVIDENCE_INDEX.md) for individual native
observations, receipts and exact proofs, and [AGENTS.md](../AGENTS.md)
for compulsory reconstruction, commit and tool rules. Historical counts in
old reports and probe filenames are **not** current status.

## Immutable target, current exact status and protected objects

| Property | Current value |
| --- | --- |
| Comparison target | Japanese TH20 v1.00a Steamless, `resources/th20.exe` (ignored) |
| Target size | 1,858,560 bytes |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Provisional target boundaries | 6,928 |
| Source-present mappings, all origins | **1,122** |
| Canonical strict native units | **1,111** |
| Unique canonical object providers | **222**, each with an exact `.obj` and `.receipt.json` |
| Exact game-authored whole functions | **324**, covering **81,529 native bytes** |

The **live ledgers, not this dated table**, are authoritative. Before
reconstruction work run:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

`config/match-units.toml` selects the protected canonical objects and
per-source locked MSVC x86 profiles. The target is the agreed Steamless
variant; embedded 1.00c title strings do not change its verified v1.00a
package identity. Never swap the target with the Steam-original backup.
The 222 current canonical object/receipt pairs, native proof documents,
private Ghidra data and toolchains must be protected. **A native exact
function is not proof of whole-game linkage or runtime completeness.**

## Recently closed complete gameplay bosses (do not reopen as nonexact)

| Entire original function | Address | Native bytes | Focused proof |
| --- | --- | ---: | --- |
| `clear_animation_handle_value` | `0x0049DA50` | **20** | [whole native value clear](ANIMATION_HANDLE_VALUE_CLEAR_EXACT_RECONSTRUCTION.md) |
| `AnimationFile::spawn_flag2` / `Player::animation_file_ref` | `0x0049CBF0` / `0x00421810` | **57 / 17** | [whole native resource access](PLAYER_OPTION_RESOURCE_ABI_EXACT_RECONSTRUCTION.md) |
| `WeaponStoneInfo::option_script_variant` / `initialize_option_pair` | `0x00534130` / `0x00533180` | **77 / 90** | [complete virtual dispatches](WEAPON_STONE_OPTION_DISPATCH_EXACT_RECONSTRUCTION.md) |
| `PlayerRecord::available_option_count` | `0x004B81A0` | **38** | [native option count and WeaponStone offsets](PLAYER_OPTION_COUNT_AND_WEAPON_EXACT_RECONSTRUCTION.md) |
| `Player::set_option_field_fc` | `0x004FB290` | **165** | [option management protocol](PLAYER_OPTION_MANAGEMENT_EXACT_RECONSTRUCTION.md) |
| `PlayerFeedback::record_hit` | `0x004FB3A0` | **115** | [capped hit recorder](PLAYER_FEEDBACK_RECORD_HIT_EXACT_RECONSTRUCTION.md) |
| `Player::reset_initial_state` | `0x004FB450` | **966** | [whole reset state machine](PLAYER_INITIAL_RESET_966_EXACT_RECONSTRUCTION.md) |
| `PlayerTable::clamped_field_1e4` | `0x004C5DB0` | **73** | [mode clamp and state flags](PLAYER_RESET_MODE_EXACT_RECONSTRUCTION.md) |
| `Player::clear_option_animations` | `0x004FF8F0` | **237** | [full sweep and accessor chain](PLAYER_OPTION_RESET_EXACT_RECONSTRUCTION.md) |
| `Player::draw` | `0x004F8AF0` | **145** | [draw and flush](PLAYER_DRAW_EXACT_RECONSTRUCTION.md) |
| `player_draw_callback` | `0x004FEFB0` | **13** | [whole forwarded callback](PLAYER_DRAW_EXACT_RECONSTRUCTION.md) |
| `Player::collision_rectangle_circle` | `0x004F91D0` | **661** | [rotated hit/graze](PLAYER_ROTATED_COLLISION_661_EXACT_RECONSTRUCTION.md) |
| `BulletController::rebuild_active_bullets` | `0x0047D600` | **863** | [active frame, six draw groups](BULLET_ACTIVE_UPDATE_863_EXACT_RECONSTRUCTION.md) |
| Bullet aim direction-mode selector | `0x00485740` | **434** | [aim modes](BULLET_AIM_SELECTOR_EXACT_RECONSTRUCTION.md) |
| `Bullet::process_collision` | `0x00484A20` | **2,018** | [entire hit/graze lifecycle](BULLET_COLLISION_2018_EXACT_RECONSTRUCTION.md) |
| `Bullet::update_physics` | `0x00485B60` | **1,846** | [complete state machine and native table](BULLET_PHYSICS_1846_EXACT_RECONSTRUCTION.md) |
| `Bullet::cancel` | `0x0047C8F0` | **662** | [cancel and AnimationHandle lifecycle](BULLET_CANCEL_662_EXACT_RECONSTRUCTION.md) |
| Bullet four-way wrap | `0x00483270` | **781** | [whole screen-wrap](BULLET_WRAP_BOSS_EXACT_RECONSTRUCTION.md) |
| Bullet four-edge boundary handler | `0x00482A60` | **832** | [whole collision dispatcher](BULLET_BOUNDARY_BOSS_EXACT_RECONSTRUCTION.md) |
| `BulletController::fire` | `0x00481780` | **339** | [whole firing caller](BULLET_FIRE_EXACT_RECONSTRUCTION.md) |
| `Player::collision_rectangle` / `collision_circle` | `0x004F8CE0` / `0x004F8FF0` | **777 / 466** | [rectangle](PLAYER_COLLISION_RECTANGLE_EXACT_RECONSTRUCTION.md), [circle](PLAYER_COLLISION_CIRCLE_EXACT_RECONSTRUCTION.md) |

See the ledgers for all earlier accepted small/medium functions, including
Timer, Bullet command 0/1/2/3/7/8/9/10, reflection, drawing orchestration,
AnimationHandle and Player direction. Original compiler padding, data
jump tables and shared/folded helper aliases **must not be double counted**.

The new `Player::draw()` preserves all eight native Renderer references and
was revalidated with **57/57** scoped exact units across **22** cold objects,
including all 21 previously exact header consumers. Its separate 13-byte
`player_draw_callback` forwards the native EAX result and passes 1/1
additional scoped strict unit. See the focused proof.

The freshly closed Player option state sweep and four typed accessors add
**327 strict bytes**; all **49/49** units affected by new Player.hpp
declarations replayed across **18** source objects, with no full replay.
The complete **966-byte** Player initialization/reset root `0x004FB450`
is now **966/966 strict exact**, with **208 original instructions and 40
independently verified native relocation sites**. It closes the caller of
the 237B option-sweep, typed position-history and 73/20/26B mode/flag chain.
CORE/EXACT-314 recomputed the real affected closure and passed **61/61
strict units across 21 cold objects**, with no full-graph replay. Earlier
CORE/EXACT-308 independently corrected Ghidra's tentative 0x00471170
library-function label to a genuine `std::clamp<int>` call. The next
substantial Player frontier is the separate **1,518-byte**
`Player::rebuild_option_animations` at `0x004FACA0` (still nonexact).

CORE/EXACT-316 subsequently closed the separate complete **115B**
`PlayerFeedback::record_hit` with three originally attested native calls;
**9/9** affected units in one PlayerStorage object remain exact. This is
not the still-open **332B Player graze effect** at `0x004F8B90`.

CORE/EXACT-320 now closes **six** independently original option-related
functions (328 bytes), including the complete 165-byte two-array broadcast,
42-byte typed ShotController bit-zero setter, and 63-byte float-to-fixed
conversion. The `Player.hpp`/`PlayerStorage.hpp`/`Rectangle.hpp` receipt
closure was **87/87 affected strict units across 26 cold objects**.
The 1,518-byte `Player::rebuild_option_animations` is **still open** and
should be reconstructed as a complete parent, not a prefix or a mere
collection of these leaf methods.

CORE/EXACT-322 adds five previously unmapped complete native functions
and promotes the independently validated original 64-byte
`PlayerRecord::starting_power` method from the existing canonical unit
(**334 nonoverlapping original bytes**). The PlayerRecord clamps, signed
option division and two actual Weapon virtual offset forwarders are exact.
Only the `PlayerRecord.hpp`/`WeaponStoneInfo.hpp` receipt closure was cold
replayed, **267/267 strict units in 33 objects**. The 1,518-byte
`Player::rebuild_option_animations` still needs whole-parent reconstruction.

CORE/EXACT-326 closes both complete WeaponStone option script and option
initialization dispatchers, adding **167 exact native bytes** to the same
canonical provider; its actual include closure passed **39/39** strict units
across **8 cold rebuilt objects**. The large **1,518-byte** Player option
rebuild remains an independent open full root.

CORE/EXACT-330 also closes the 57-byte native AnimationFile flag-2
spawn wrapper and 17-byte real Player AnimationFile getter. The actual
`AnimationFile.hpp`/`Player.hpp` receipt include closure passed **232/232
strict units across 49 cold source objects**, retaining the previous
compiler profiles. The 1,518-byte parent remains **nonexact**: these new
ABIs distinguish its native 5-arg resource creation from a speculative
direct 7-arg call.

CORE/RECON-333 now maintains the **whole 1,518-byte**
`Player::rebuild_option_animations` at `src/PlayerOptionRebuild.cpp`
as a **NONEXACT** complete-function C++20 source frontier. The locked
MSVC `/GS-` plus live 8-byte-aligned `IntPoint` result matches the native
stack prologue and full return, and emits **1,518B / 411 instructions**
with **410/418 original instruction kinds in order**. Independent original
reference audit: **57 E8 calls + 3 PE HIGHLOW fields**. It still lacks
full original relocation/instruction/lifetime equivalence, so **zero
canonical exact bytes** were claimed. The resource script fields at
PlayerShotData+0x88/+0xA8 and stack-slot ownership need further review.
Read [the full boss source frontier](PLAYER_OPTION_REBUILD_FULL_SOURCE_FRONTIER.md).

CORE/EXACT-335 closes the complete **20-byte** `AnimationHandle`
value-clear operation at `0x0049DA50`, then restores its original call in
the maintained full Player option rebuild parent. Only the owning existing
`BulletCollisionAnimationHelpers.cpp` canonical object was cold rebuilt:
**8/8** exact units remain accepted; the parent was separately compiled
and is **still nonexact**.

CORE/RECON-343: a fresh whole-parent audit corrected an original-absent
late AnimationFile null guard, restored native script-table base-plus-byte-
displacement indexing, and used original `-999.0f` float literals.
The complete natural source now emits **1,518B / 411 i386 instructions**,
with **410/418 native instruction kinds aligned**, and the same 57 direct
call / three absolute relocation counts. **It remains NONEXACT**: eight
native instructions are still absent, COFF second literal offset
`+0x49F` differs from native `+0x4AB`, and full byte/relo replay fails.
Only this nonexact source/evidence changed, so zero accepted exact units
needed cold replay. See the focused whole-source frontier.

## Open complete-function roots — next agent's priorities

1. **Bullet command 11 `0x00481200`: 1,404 bytes / 357 native
   instructions.** The entire boss now has maintained nonexact
   `src/BulletCommand11.cpp`; read the [whole source frontier](BULLET_COMMAND11_FULL_SOURCE_FRONTIER.md). Its entire real 50B cross, 50B dot and 155B
   normalization helpers are exact. Full private candidates live at
   `.analysis/core255-BulletCommand11-splitarrays.cpp` and
   `.analysis/core263-command11-polar-one-literal.cpp` (older experiments). Real original
   `1.0f` for polar radius produces **353/357 original instruction kinds**
   in one full-body candidate; the remaining four original stores of
   384.0/448.0 may reflect real locals, but do **not** insert inert locals
   merely for bytes. Read
   [complete command11 geometry frontier](BULLET_COMMAND11_GEOMETRY_EXACT_RECONSTRUCTION.md).
2. **BulletController single-group draw `0x0047DB70`: 273 bytes.**
   Maintained entire function source now lives at `src/BulletDrawGroup.cpp`;
   read [the whole typed source frontier](BULLET_DRAW_GROUP_FULL_SOURCE_FRONTIER.md).
   Original parent `draw_groups` at `0x0047DC90` is separately exact (81B).
   Full private candidate `.analysis/core285-draw-result-after-offset.cpp`
   aligns all **82 original instruction kinds** but emits **283B**:
   original x87-to-SSE rotation argument temporary ownership differs.
   Check actual `Angle` return and `Animation::set_rotation` ABI; do not
   pad/de-pad manually. See [draw proof](BULLET_DRAW_GROUPS_EXACT_RECONSTRUCTION.md).
3. **Whole Bullet single-shot emitter `0x004818E0`: 3,735 native
   code bytes plus one NOP and two native switch tables (13+11 entries),
   **3,832B whole compiler contribution** and eight linker `CC` bytes.
   Complete C++20 private source candidates:
   `.analysis/core288-BulletEmitterFull.cpp`,
   `.analysis/core290-BulletEmitterFull-RealMetadataLifetime.cpp` and
   `.analysis/core292-emit-*.cpp`. The best ordered mnemonic alignment
   is **789/935**, still *not exact*. Real
   `std::shared_ptr<EtamaArgInf>` move ownership at `0x0047C530`
   differs from the installed STL (native 63B versus probe 54B);
   Renderer Animation allocation (298B), file script binding (338B),
   and 66B Bullet intrusive prepend need exact ABI closure. See
   [full emitter C++ frontier](BULLET_EMITTER_FULL_CXX_FRONTIER.md).
4. **Entire Bullet command/update dispatcher `0x0047DCF0` (12,140B)**
   and **Enemy ECL opcode dispatcher `0x0048C010` (41,967B)** remain
   separate nonexact large roots. The Enemy whole-root source and
   historical host investigations are documented by
   [dispatch layout](CORE_ENEMY_DISPATCH_LAYOUT.md) and
   [source map](SOURCE_MAP.md). Old dual-sanitizer host scenario counts
   are *historical only*, not a current CI or exactness gate. Animation
   VM, Renderer resource owners and Player damage lifecycle also remain
   substantial open work.
5. **Player graze feedback `0x004F8B90` (332B)** remains private and
   nonexact. Its whole tentative source is
   `.analysis/core298-PlayerGrazeFeedback-Live.cpp`. Three provisional
   member interfaces from the incomplete experiment were carefully
   preserved in `.analysis/core298-pending-graze-interfaces-original.patch`
   and `.analysis/core298-PENDING_GRAZE_FEEDBACK.md`, **not** left in
   maintained headers without strict regression. Native callees
   `0x004FE8D0`, `0x0049DC60`, `0x0049BE20` need independent review.

## New large Player frontier after exact reset

The full `Player::rebuild_option_animations` at `0x004FACA0` is
**1,518 native bytes, still nonexact**. Its maintained C++20 whole-function
source is now [here](PLAYER_OPTION_REBUILD_FULL_SOURCE_FRONTIER.md). It is called directly by the
now complete 966B reset root and contains resource/AnimationHandle
replacement, Player option assignment and animation-file selection.
Work on its own whole-function evidence and genuine callees, not a
shortened prefix or speculative owner interface. See
[the complete reset proof](PLAYER_INITIAL_RESET_966_EXACT_RECONSTRUCTION.md).

## Resume workflow and bounded verification

The locked compiler profile for most accepted x86 objects is
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc`. Some canonical sources use other separately verified
profiles: **always read each unit's `profile`**. Use `nice -n 15` for
MSVC/Ghidra/replay. The actual source include closures are captured in
canonical `.receipt.json` files; never estimate the impact of a shared
header from a static old handoff. Example:

```bash
# Only when the source or an included header was actually modified:
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/ChangedSource.cpp
# Always run for any admitted exact code/tracking changes:
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
git diff --check
```

For a shared header edit, inspect prior receipts for every canonical
provider that includes that header and replay **only those** sources.
If MSVC renumbers a private `$SG` string symbol, adjust *only* the
compiler-local symbol after confirming the original relocation offset,
type and target remain independently unchanged, then rerun its complete
unit. All accepted claims require **complete function native equality**
plus independently grounded original relocation targets; a provisional
`structural-exact` diagnostic alone does not earn credit. Never run
unfiltered whole-repository cold replay for a routine checkpoint.

For documentation-only or ignored artifact cleanup, do **not** invoke
MSVC, Ghidra, full CI or native replay on an unchanged reconstruction
graph. Run the target hash, Git diff/link checks and tracking/progress
checks instead. Commit substantive work promptly with subjects starting
**`gpt-web:`**. Maintain all comments/docs/commit messages in English;
answer the user in Chinese.

## Protected storage, artifact retirement and history

CORE/CLEANUP-300 retired **2,496 unused ignored files / 203.65 MiB**:
2,113 obsolete noncanonical build outputs and 383 unreferenced historical
compressed snapshots. The exact retired paths, sizes and SHA-256 values
are in ignored `.analysis/core300-retired-artifact-inventory.json`.
**All 212 canonical `.obj`/receipt pairs remain intact**; the target,
Ghidra database, 4.2GB Wine/MSVC toolchain, active unresolved-boss probes
and referenced private native evidence were not changed. The safe dry-run
and protected-retirement criteria are in
`.analysis/core300-safe-artifact-prune.py` and
[reconstruction workflow](RE_WORKFLOW.md). Retired build-only products
can be regenerated from retained private `.analysis` source scripts or
maintained sources. Historical proof documents and old dated handoffs
remain recoverable from Git, e.g.
`git show e7fa30d:docs/RE_HANDOFF.md`.

**Do not `git clean -fdx`, remove entire `build/` or `.analysis/`, or
reclaim `.tools/`, `ghidra-project/`, `_reference/` or executable files.**
Treat every dirty source edit as owned work: investigate it and preserve
nonexact hypotheses privately before cleaning maintained declarations.

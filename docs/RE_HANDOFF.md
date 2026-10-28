# TH20 reconstruction: current handoff

**Updated 2026-10-28; CORE/RECON-302 Bullet command-11 frontier.** This file is the concise
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
| Source-present mappings, all origins | **1,094** |
| Canonical strict native units | **1,084** |
| Unique canonical object providers | **213**, each with an exact `.obj` and `.receipt.json` |
| Exact game-authored whole functions | **296**, covering **79,066 native bytes** |

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
The 213 current canonical object/receipt pairs, native proof documents,
private Ghidra data and toolchains must be protected. **A native exact
function is not proof of whole-game linkage or runtime completeness.**

## Recently closed complete gameplay bosses (do not reopen as nonexact)

| Entire original function | Address | Native bytes | Focused proof |
| --- | --- | ---: | --- |
| `Player::draw` | `0x004F8AF0` | **145** | [draw and flush](PLAYER_DRAW_EXACT_RECONSTRUCTION.md) |
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
including all 21 previously exact header consumers. See the focused proof.

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

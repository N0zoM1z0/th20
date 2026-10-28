# Current TH20 reconstruction handoff

**Checkpoint:** CORE186 whole-Enemy opcode 555 integration, following CORE/EXACT-185 native Bullet file getter.
This is the **current** entrypoint for the next agent, not a cumulative session
log. Read [AGENTS.md](../AGENTS.md) first for exactness policy, source rules,
`gpt-web: ` commit subjects and **affected-only** replay requirements. This
handoff describes the live state on 2026-10-28; older batch counts in focused
evidence documents are historical, not competing current status.

## Repository, target and canonical status

- Worktree: `main`, with CORE/EXACT-185 saved as commit `2713b35`
  (`gpt-web: reconstruct exact Bullet file getter for Enemy opcode 555`).
  CORE186 preserves the complete-root investigation and its private inputs;
  check `git log -2 --oneline` and `git status` for the newest local commit.
  Factory has no network/push. **Do not discard dirty or ignored work:** the
  user explicitly said the single worker owns all modifications.
- Target: Japanese TH20 **v1.00a Steamless**, `resources/th20.exe` (ignored),
  SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
  Do not switch to the Steam-original backup or any other release. See
  [target provenance](TARGET_PROVENANCE.md) and `config/target.toml`.
- Live ledgers: **6,928** target function candidates, **1,014** source-present
  mappings, **1,005** physical canonical strict units, **219** confirmed
  authored exact functions / **57,291** authored exact bytes. The 164 current
  canonical objects cover **181,664** comparison bytes. **Nine**
  source-present whole-function mappings remain nonexact. These are not a
  whole-game completion percentage; see generated [progress](PROGRESS.md).
- The **41,967-byte** native `EnemyState::execute_opcode()` at `0x0048C010`
  is still **not machine-code exact**. Its *single complete-root source draft*
  covers **124 effective opcode values / 95 primary heads** and passes
  **38,973 / 38,973** `-O2`/UBSan whole-root host scenarios. Do not claim
  partial native root bytes as exact functions.

## Latest work to resume

CORE/EXACT-185 added native `BulletController::animation_file() const` at
`0x004859B0`: **20/20** byte-exact native code, zero relocations. The actual
Bullet owner at +0x286D8C and distinct `EnemyController::animation_file`
selector at `0x004AAE10` independently establish the getter. The only five
canonical providers including `Bullet.hpp` were cold-built, and **33/33**
affected units strictly replayed. The Bullet TU now uses
`build/core185-canonical/BulletController.obj`, not its superseded
core180-canonical path. Canonical object count remains 164.

CORE186 then integrated the **whole original 555 branch** into the **same**
41,967-byte Enemy root host. Native code at `0x0048C3F4..0x0048C577`
comprises **388 bytes / 81 instructions and ten direct calls**; an independent
Capstone/locked-PE audit discovered that its File-spawn **layer is 3**, *not*
the `-1` of the otherwise superficially similar Enemy defeat path. The full
candidate calls the real existing SoundInf pan adapter, Motion/Enemy position,
XY distance/direction and four-argument File wrapper; the real Bullet file
getter is executed in the index-0 selection test. The still-unaccepted 151B
file dispatcher, Stage owner and seven-argument VM producer are captured as
explicit boundaries. **540 new host scenarios** cover both independent gates,
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

- `.analysis/core185-enemy-dispatch-candidate.cpp` — entire natural-source
  Enemy root draft, now including opcode 539 **and** 555; it supersedes CORE183
  only as the *current candidate*, never as whole-root exactness.
- `.analysis/core185-dispatch-host.cpp`,
  `.analysis/core185-enemy-effect-host-cases.inc`,
  `.analysis/core185-dispatch-host-recipe.json` — one host with **81 TUs**,
  previous 80 plus actual `src/GeometryMetrics.cpp`.
- `.analysis/core185-dispatch-host.log`,
  `.analysis/core185-native-555-audit.json`,
  `.analysis/core185-enemy-whole-root-proof.json` — passed scenarios, original
  independent opcode instructions and SHA-bound four private source inputs.
  Protect the active executable `build/core185-dispatch-host` as evidence.
- All CORE183 inputs/logs and original 539 proof remain protected and
  unchanged, as do CORE181/179 and archived original-input records. **Do not
  confuse older count summaries with the current active host**.

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
Original 539 **and 555** are now integrated in the one active whole-root
candidate (neither native-exact). Original 548 was integrated as of CORE181.

## Next high-value research, including large functions

1. **Continue the same 41,967-byte Enemy Boss function**, preserving CORE183
   and CORE185 input hashes, real Context owners and the 38,973 current host
   tests. The original opcode **555** caller is now integrated; continue with
   the **151-byte** native `EnemyController::animation_file` selector, real
   Stage/Background resource owner at `0x005C069C`, other missing primary heads
   and compiler/EH exactness. Nearby additional blockers: Renderer handle lookups for **502/503**, the actual ScreenInf
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
not a static build-directory list copied from old handoffs. As of CORE186 it
selects **164** actual `build/**/*.obj` files with **164 sibling
`.receipt.json` files**. Their distribution is core141 66, core142 6,
core145 3, core149 1, core151 1, core154 5, core154-v2 1, core156 1,
core158 10, core163 19, core164 8, core166 2, core167 1, core174 2,
core178 9, core180 26, **core182 2 and core185 1**. Old probe objects/receipts may be
retained as historical evidence but are not current acceptance units. Also
preserve the twenty historical unfinished QueryProtocol/sound/Alignment
products documented in
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound protocol](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Animation pool](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

**For CORE185**, changed production/header inputs affected five canonical
providers: **33/33** scoped units / **5** cold objects passed. **For CORE186's
private entire-root host integration**, changed production compiler inputs =
**zero**; it rebuilt only the separate GCC13 semantic host, not any native
cold replay unit. Do **not** invoke whole-graph cold replay, Ghidra, MSVC or
full CI just for an evidence handoff. Verify `git status`, `git diff --check`,
protected product hashes and links; reuse the CORE185 attested results. To resume actual RE, inspect all dirty work (the user owns
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
`.analysis/`, and all CORE183/CORE185 root candidates/proofs listed above remain intact.

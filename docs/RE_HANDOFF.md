# Current TH20 reconstruction handoff

**Checkpoint:** CORE184 documentation/artifact retirement after CORE183.
This is the **current** entrypoint for the next agent, not a cumulative session
log. Read [AGENTS.md](../AGENTS.md) first for exactness policy, source rules,
`gpt-web: ` commit subjects and **affected-only** replay requirements. This
handoff describes the live state on 2026-10-28; older batch counts in focused
evidence documents are historical, not competing current status.

## Repository, target and canonical status

- Worktree: `main`, last reconstruction commits `f709625` (whole Enemy opcode
  539 integration) and `9d8c5bc` (byte-exact full Laser reset). Both use the
  required `gpt-web: ` subject prefix. At cleanup start the worktree was clean,
  and `main` was **21 commits ahead** of `origin/main`. Local commits have
  **not** been pushed; the factory shell has no network. Always recheck Git
  status at the next session. **Do not ignore or discard dirty work**: the user
  explicitly stated that all modifications belong to this single session.
- Target: Japanese TH20 **v1.00a Steamless**, `resources/th20.exe` (ignored),
  SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
  Do not switch to the Steam-original backup or any other release. See
  [target provenance](TARGET_PROVENANCE.md) and `config/target.toml`.
- Live ledgers: **6,928** target function candidates, **1,013** source-present
  mappings, **1,004** physical canonical strict units, **218** confirmed
  authored exact functions / **57,271** authored exact bytes. The 164 current
  canonical objects cover **181,644** comparison bytes. **Nine**
  source-present whole-function mappings remain nonexact. These are not a
  whole-game completion percentage; see generated [progress](PROGRESS.md).
- The **41,967-byte** native `EnemyState::execute_opcode()` at `0x0048C010`
  is still **not machine-code exact**. Its *single complete-root source draft*
  covers **123 effective opcode values / 94 primary heads** and passes
  **38,433 / 38,433** `-O2`/UBSan whole-root host scenarios. Do not claim
  partial native root bytes as exact functions.

## Latest work to resume

The first exact target is **Enemy opcode 539's real callee**,
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

- `.analysis/core183-enemy-dispatch-candidate.cpp` — **whole** natural-source
  root draft, including opcode 539; source of truth for further work.
- `.analysis/core183-dispatch-host.cpp`,
  `.analysis/core183-laser-reset-host-cases.inc`,
  `.analysis/core183-dispatch-host-recipe.json` — exact existing semantic host,
  including the entire suite of earlier case includes; use the recipe's
  **80-TU** list, rather than inventing a new independent dispatcher.
- `.analysis/core183-dispatch-host.log`,
  `.analysis/core183-native-539-audit.json`,
  `.analysis/core183-enemy-whole-root-proof.json` — passed host log,
  independently decoded original seven-instruction case and SHA-bound inputs.
  The active host executable is `build/core183-dispatch-host`, which is
  **protected by the proof**. Do not delete it as an unused binary.
- Previous `.analysis/core181-*`, `.analysis/core179-*` and prior host inputs,
  native audits and proof files are historical protected evidence. The
  CORE181 draft and host remain unchanged. Large `.analysis/*original-inputs*`
  and `*pre-registration-ledgers*` archives preserve original SHA-bound
  inputs and must **not** be confused with temporary logs.

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
Original 539 is now **integrated**; do not use pre-CORE183 notes that say it
is still pending. Original 548 is integrated as of CORE181.

## Next high-value research, including large functions

1. **Continue the same 41,967-byte Enemy Boss function**, preserving CORE183
   input hashes, real Context owners and current host tests. Investigate
   original opcode **555** and other missing primary heads, and independently
   decode the complete original branch and callee before adding code. Nearby
   blockers: Renderer handle lookups for **502/503**, the actual ScreenInf
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
not a static build-directory list copied from old handoffs. As of CORE184 it
selects **164** actual `build/**/*.obj` files with **164 sibling
`.receipt.json` files**. Their distribution is core141 66, core142 6,
core145 3, core149 1, core151 1, core154 5, core154-v2 1, core156 1,
core158 10, core163 19, core164 8, core166 2, core167 1, core174 2,
core178 9, core180 27 and **core182 2**. Old probe objects/receipts may be
retained as historical evidence but are not current acceptance units. Also
preserve the twenty historical unfinished QueryProtocol/sound/Alignment
products documented in
[damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md),
[sound protocol](SOUND_PROTOCOL_RECONSTRUCTION.md) and
[Animation pool](ANIMATION_POOL_LIFETIME_RECONSTRUCTION.md).

**For documentation/cleanup only**, changed reconstruction inputs = **zero**,
affected cold-build/replay units = **zero**. Do **not** invoke whole-graph
cold replay, Ghidra, MSVC or full CI just for a handoff. Verify `git status`,
`git diff --check`, protected product hashes and links; reuse the CORE183
attested result. To resume actual RE, inspect all dirty work (the user owns
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
`.analysis/`, and the exact root candidate/proofs listed above remain intact.

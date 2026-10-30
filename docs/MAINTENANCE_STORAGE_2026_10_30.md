# CORE/MAINT-830 — current agent handoff correction and protected probe storage retirement

**Date: 2026-10-30.** This is a **documentation and ignored-product cleanup**
after [the separately committed original-PE-backed 3,159B quad parent source
refinement](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md)
(`708a40d`, `gpt-web: recover all quad submission boss call and data roles`).
That earlier checkpoint **changed C++** and compiled and verified its one
NONEXACT method; the present cleanup **does not** change any native C++ input,
compiler profile, match manifest, exact unit, relocation oracle, game-origin
ledger or source ownership declaration. **Affected exact replay scope: zero**.
There was **no unfiltered cold replay**, MSVC rebuild, Ghidra query, full
public CI, game binary patch or playable-game claim in this cleanup.

## Live state verified before cleanup

| Actual current source/acceptance fact | 2026-10-30 verified value |
| --- | ---: |
| Locked Japanese v1.00a Steamless PE SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Original PE size | 1,858,560 bytes |
| Provisional Ghidra functions | 6,928, not universally reconciled boundaries |
| Complete source-present mappings and strict units | **1,238 each** |
| Canonical pinned-MSVC object/receipt pairs | **259** |
| Distinct fully original authored-game exact functions | **589** |
| Strict disjoint authored-game original `.text` coverage | **193,512 bytes** |
| Whole-game link/playability | **Not yet available** |

These are **dated live tool results**, not completion percentages or historical
checkpoint sums. Read [current handoff](RE_HANDOFF.md),
`config/match-units.toml` and `scripts/report-reconstruction-status.py`
for live status after this checkpoint.

## Source and documentation corrections for the next agent

- The entire **3,159B /763-x86** quad submission Boss at `0x0043F6A0`
  remains **SOURCE-PRESENT, NONEXACT**. Old documents' **3,796B /973-x86
  +20B table** candidate is superseded by **3,212B /810-x86 +20B table**;
  source-verified 41/41 E8 and 96/96 native HIGHLOW **target roles** are
  *not* whole-native byte equality. The [current dedicated proof](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md),
  [new original/source verifier](../scripts/verify-animation-quad-submit-source-roles.py)
  and prominent historical-report caveats prevent future reintroduction of
  the old branch, packed-color or viewport-cache hypotheses.
- The distinct renderer **2,725B texture/sampler-state** and **1,163B
  four-mode blend-state** D3D9 Boss children are each **whole strict exact**,
  including genuine original after-RET PE pointer tables. The larger
  **3,159B renderer submission** and **5,993B 49-mode Animation draw**
  parents are still NONEXACT; their exact child functions must not be counted
  again as parent code. The README, compact handoff, architecture and source
  ownership index now distinguish all four functions correctly.
- The old **203/210** and **204/210** Bullet command call closure snapshots
  described *earlier experiments*, not the current **208/210** original E8
  occurrences leading to complete game-callee source. The remaining **two
  original E8 occurrences are compiler-runtime helpers**; the original
  **12,140B /2,490-x86** 34+8+11-switch parent is still SOURCE-ABSENT and
  NONEXACT. [Immutable PE call verifier](../scripts/verify-bullet-command-call-coverage.py).
- Historical **245/243/236/212 canonical-object** counts were previous
  inventory states. The live count is **259**; the [workflow](RE_WORKFLOW.md)
  and [handoff](RE_HANDOFF.md) no longer call older retirement summaries
  current. [Roadmap](ROADMAP.md) puts complete big parents, not only
  already-sourced leaf functions, at the top of future work.
- [Evidence index](EVIDENCE_INDEX.md) now uses live coverage in its entry
  paragraph, labels historical compiler output accurately, and collapses
  duplicate links for the same 1,163B strict blend Boss and for the
  60B+34B+16B strict texture lookup/STL chain without deleting the
  independent older dated evidence files.

All changed documents preserve English developer-facing documentation,
source comments and claim boundaries. Original historical proof bodies
remain intact except for clearly marked supersession notices.

## Guarded storage deletion, hash audit and exact bytes saved

The existing `scripts/prune-generated-artifacts.py` was run in its
**dry-run-first** mode and each candidate was inspected by directory and
size. It identifies only ignored, untracked **reproducible `build/**/*.obj`
or `.receipt.json` noncanonical products** not protected by the live manifest,
tracked documentation's specific proof object/receipt references, or active
Player/Bullet/mesh compiler-probe directory allowlist. It does **not** sweep
`build/` or `.analysis/` indiscriminately, delete original executable/
reference evidence, remove pinned MSVC/Wine/D3DX tools, or alter the
Ghidra project.

| Audited filesystem property | Before / after or protected result |
| --- | ---: |
| Reproducible disposable products removed | **693 files** |
| Exact logical bytes freed | **28,586,424 bytes (27.26 MiB)** |
| `build/` logical bytes before cleanup | 101,430,617 bytes |
| `build/` logical bytes after cleanup | 72,844,193 bytes |
| `build/` displayed disk usage | approximately **105M → 76M** |
| Protected canonical `.obj` / matching `.receipt.json` | **259 + 259, all original hashes unchanged** |
| Source/proof-specific object or receipt refs protected | **83** (may overlap canonical or active) |
| **Distinct SHA-256-protected `build/` files** | **546**, all verified unchanged |
| Other active probe files retained by dir allowlist | **1,694** |
| Original PE | Required SHA-256 unchanged |
| Pinned toolchain manifest | SHA-256 unchanged: `c7d83a3ea87b64c2d11faaeb0373f6369050ece41e413ea2e816059a97355464` |
| Ghidra project, installed MSVC/Wine/D3DX | **Preserved; no deletion outside `build/`** |
| Fresh post-cleanup dry run | **0 eligible files /0 bytes** |

The guard wrote **an entirely new, non-overwritten private deletion and
protection inventory** before deleting a file:

    .analysis/core830-guarded-build-prune-inventory.json

That file has SHA-256
`8f60d7066e5e9c7cb99b1ae6c8da59e907908cdbe3cbe09869681d23ebae0ed7`
and records all 693 deleted paths with byte sizes/hashes, all **546**
protected file hashes, tracked proof references and active protection
directories. The script and an independent later SHA check verified every
protected hash after cleanup and every deleted path's absence. Before and
after `resources/th20.exe` SHA and `.tools/vs2022-pinned.manifest` SHA were
identical. The complete compiler-probe source and retained `core829` proof
`build/core829-probe/AnimationQuadSubmitRoles.obj` **and** its matching
`build/core829-probe/AnimationQuadSubmitRoles.receipt.json` were protected.

`.analysis/` (~293M) primarily contains retained private native evidence,
historical source experiments and losslessly compressed replay/source
snapshots. `.tools/` (~4.2G) contains the **installed** MSVC/Wine/D3DX
candidate and its locked manifests; neither is an unneeded download cache.
They were left intact to avoid destroying canonical reproducibility in
exchange for apparent storage savings.

## Reproduce safe validation without whole-graph replay

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/build.py --check
    scripts/repo-python scripts/progress.py --check
    scripts/repo-python scripts/prune-generated-artifacts.py
    git diff --check

The earlier source-only checkpoint also ran an independent locked-original
PE audit and one **noncanonical** source compile via
`scripts/verify-animation-quad-submit-source-roles.py`, with exact replay
scope zero because no existing canonical match unit includes the changed
`src/AnimationQuadSubmit.cpp` or its verifier. This cleanup itself touched
no native compiler inputs and therefore **ran no cold replay at all**.

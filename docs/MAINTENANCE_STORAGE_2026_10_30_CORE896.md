# CORE/MAINT-896 — live handoff reconciliation and guarded retired-probe cleanup

**Date: 2026-10-30.** This is a **documentation/navigation, guarded
`build/` product and cleanup-script allowlist** checkpoint. It changes
**no maintained game C++ source/header**, no native compiler flags,
accepted exact-function graph, real PE target, original-origins ledger,
canonical byte comparator or fresh match admission. The latest native
source reconstruction checkpoint before this cleanup is **`116d242`**
(`gpt-web: match 140-byte polygon tick and seven native range leaves,
recover dynamics source`). **Native recompilation/cold replay scope:
zero source providers and zero strict units.** The graph already had
accepted receipts and is unchanged here. Do not run Ghidra/MSVC or a
whole-graph replay merely to correct dated prose or discard ignored
regenerable diagnostics.

## Baseline evidence and corrections for the next agent

At the start of this maintenance work the **locked Japanese TH20 v1.00a
Steamless PE** was the same 1,858,560B file, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The actual live reconstructed graph had **6,928 provisional original
function candidates, 1,297 source-present mappings, 1,295 whole-native
strict units, 299 canonical object/receipt pairs, and 637 distinct
original authored-game strict-exact functions /233,802 original
`.text` bytes**. These values are a dated verified snapshot, **not
an assertion of whole-game buildability**; consult the
[current handoff](RE_HANDOFF.md) and source/acceptance ledgers for
future changes.

Before maintenance, the current 209-line handoff listed more than
50 very long completed rows, sometimes duplicated the same 2,169B
LINESTRIP, and buried unfinished parents among already completed
whole-Boss entries. It still said that the **1,204B polygon Boss was
SOURCE-ABSENT**, that the **120B palette callee remained open**, and
that a now exact 1,378B Mode6 preparation caller was unfinished.
The [current handoff](RE_HANDOFF.md) is now a focused snapshot of
**open original whole parent functions, exact acceptance boundaries,
next steps and protected data/validation policy**; the
[evidence index](EVIDENCE_INDEX.md) retains the longer dated native
experiments, reorganized by active-Boss reading order and grouped
strict acceptance. The README's repeated 40+ row exact catalog is
consolidated into subsystem-specific summaries, without deleting the
individual original-native proof files.

In particular, the [roadmap](ROADMAP.md), [architecture](ARCHITECTURE.md)
and [source ownership](SOURCE_MAP.md) now agree: the original
**3,159B quad-submit Boss is entire whole strict exact** (3,180B
with genuine NOP/case-table compiler contribution), while the
**separate 5,993B 49-mode Animation Draw dispatcher remains
SOURCE-PRESENT/NONEXACT** despite native-length candidate code and
complete callee names. The current **827B polygon dynamic update**
and **104B outline wrapper** are both SOURCE-PRESENT/NONEXACT;
the original **140B timer tick, 233B group, 296B configuration,
120B palette and 1,204B outline** are already whole strict exact.
Their seven native counted-range helper bodies are exact, but their
original hand-authored vs template-instantiated origin is unresolved,
so they add **no credited authored-game code bytes**.

Selected high-traffic **historical source reports** now carry an
explicit supersession banner pointing to their newer whole original
acceptances, without rewriting the dated compiler diagnostics:
[old quad candidate](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md),
[early 5,993B Draw typed candidate](ANIMATION_DRAW_BOSS_5993_TYPED_49_MODE_PARENT_FRONTIER.md),
[73B/86B math helpers and now-exact 1,378B Mode6 parent](ANIMATION_PROJECTION_MATH_73_86_STRICT_EXACT.md),
[72B/77B Vector2 leaves and now-exact 1,204B parent](ANIMATION_VECTOR2_COMPOUND_VALUE_72_77_STRICT_EXACT.md),
[78B shape XY helper and now-exact shape parents](ANIMATION_SHAPE_XY78_STRICT_EXACT.md),
and the [previous October 30 storage audit](MAINTENANCE_STORAGE_2026_10_30.md).
The main 5,993B Draw [current original-byte frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md)
remains NONEXACT and now explicitly warns that its experiment totals
are dated rather than live canonical coverage.

## Retired *only* regenerated, unprotected compiler probes

The existing [`scripts/prune-generated-artifacts.py`](../scripts/prune-generated-artifacts.py)
was run in **dry-run-first** mode; eligible ignored files and their
directory breakdown were inspected. The original cleanup allowlist
was updated to also protect the currently unfinished `core835-probe`,
`core872-probe`, `core873-probe`, `core877-probe`, `core881-probe`,
`core894-probe`, `core897-probe`, and `core898-probe` directories
covering current Animation Draw, Player, rotated-quad, 827B dynamic
and 104B wrapper investigations. Other older selected original CFG
benchmark directories remain protected as before. Older
source-compiled probes of *already accepted* Game/Animation bosses
may be recreated and are not protected as canonical inputs.

The script selects only ignored, untracked **noncanonical
`build/**/*.obj` and `*.receipt.json`** files, excluding every live
`config/match-units.toml` canonical object/receipt, every individual
build artifact referenced by tracked proof documentation, and every
protected active-probe directory. The actual original PE SHA-256 is
checked *before and after* deletion, and SHA-256 of **all 634 distinct
protected build files** was checked unchanged after applying.

| Item | Observed result |
| --- | ---: |
| Pre-cleanup `build/` logical bytes | **115,627,515** |
| Files actually retired | **683** |
| Exact logical bytes freed | **30,885,900** (**29.46 MiB**) |
| Post-cleanup `build/` logical bytes | **84,741,615** |
| `du -sh build` | approximately **119M → 88M** |
| Canonical `.obj` / matching receipts protected | **299 + 299**, all SHA-256 unchanged |
| Individual referenced proof artifacts protected | **111** references (may overlap canonical/active) |
| Distinct SHA-256-protected build files | **634**, all hashes unchanged |
| Active-probe files excluded by directory allowlist | **1,881** |
| Fresh subsequent guarded dry run | **0 disposable files, 0 bytes** |

Before any file was unlinked, the tool wrote a new **private,
untracked audit inventory** at:

```text
.analysis/core896-guarded-prune-inventory.json
```

Its SHA-256 is
`3f2592659f98690a04ed587321f43223692c62bb37169758c4187312a8947e8a`.
It preserves the original target SHA, all 683 removed paths and
per-file SHA-256/byte sizes, all 634 protected path hashes, the
actual referenced proof artifacts, allowlist and observed totals.
The inventory **was not overwritten, tracked, or sent outside the
private repository**. Its presence is useful evidence when deciding
whether an old ignored build probe must be regenerated.

## Intentionally not deleted

The original `resources/th20.exe` SHA remained unchanged. The pinned
Visual Studio manifest `.tools/vs2022-pinned.manifest` also remained
identical (SHA-256
`c7d83a3ea87b64c2d11faaeb0373f6369050ece41e413ea2e816059a97355464`).
The `.tools/` toolchain and Wine/D3DX payload (~4.2G),
`_reference/` (~157M), attested `ghidra-project/` (~44M),
Git history (~181M), `.venv/` and source are all protected.
`.analysis/` (~295M), including **84 unique frozen input snapshots
(~94.49 MiB)**, original native analyses, evidence and the new audit
was deliberately kept. Do **not** `rm -rf build/` or `.analysis/`,
prune Git history, or delete pinned proprietary toolchains to claim
extra savings. Storage savings stated above are *actual* logical
removed bytes, not a projected dry-run total.

## Verification scope after deletion

The original-target verification and live status reporter still
returned the pinned PE and unchanged **637 game exact /233,802B**.
The guarded cleaner independently reported unchanged protected
hashes and a fresh **0-candidate dry run**. The last checks in this
maintenance scope are Markdown relative-link validity, required
config/status/progress consistency, native target hash, Git
`diff --check`, updated cleanup-tool syntax and the protected audit
inventory. There are **no native code or match-manifest changes**, so
**no cold exact replay, Ghidra run or MSVC build** is required.

For another future cleanup:

```bash
scripts/repo-python scripts/prune-generated-artifacts.py
# Inspect candidates and preserve any newly active original Boss probes.
scripts/repo-python scripts/prune-generated-artifacts.py --apply \
  --inventory .analysis/NEW-UNIQUE-RETIREMENT-AUDIT.json
```

Never reuse the existing audit filename or assume historical canonical
object counts are current. Preserve every dirty worktree change; use
`gpt-web:` commits for verified progress.

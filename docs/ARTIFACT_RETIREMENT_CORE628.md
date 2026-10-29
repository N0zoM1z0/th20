# CORE/DOC-CLEANUP-628 — current-state documentation and guarded probe-cache retirement


**Later current-state correction (CORE/MAINT-751, 2026-10-29):** This
report is an *archived checkpoint*, not the live exact inventory.
The 3,735B Bullet emitter and 73B Animation factory were subsequently
admitted whole-native exact, and the graph subsequently reached
1,203 strict units /245 canonical object/receipt pairs. See
[current RE_HANDOFF](RE_HANDOFF.md) and the later
[guarded cleanup](MAINTENANCE_STORAGE_2026_10_29.md). The historical
498/175,709 and 243-provider counts below are dated, not current;
do not discard private original ABI snapshots to increase reclaimed space.

**Date:** 2026-10-29. This is a **documentation/control-plane and ignored
artifact** cleanup, not a new native reconstruction checkpoint. The target,
real C++/public headers, function ledger classification, pinned canonical
unit definitions, MSVC profiles and game-authored exact byte count are
unchanged. No native cold build or unfiltered canonical replay was run.

## Verified original reconstruction state, now expressed once

The live [agent handoff](RE_HANDOFF.md) was reduced from **813 lines to
147**. The former long handoff was mixing a large series of superseded,
chronologically ordered progress totals into what appeared to be current
instructions. Those historical details remain in individual
[evidence reports](EVIDENCE_INDEX.md), and the exact former handoff
remains in Git at `git show 3e0f343:docs/RE_HANDOFF.md`. The current
handoff contains one live, ledger-grounded status table, a closed-native
function summary, a single table of large unfinished bosses, exactness
boundaries and affected-only verification procedure.

| Live measure | Verified accepted count |
| --- | ---: |
| Provisional native function candidates | 6,928 |
| Source-present mappings | **1,183** |
| Configured complete native strict units | **1,184** |
| Distinct locked MSVC object/receipt providers | **243** |
| Distinct **game-authored** exact complete functions | **498** |
| Accepted original disjoint **game-authored** code bytes | **175,709** |

Important corrections for subsequent agents:

- The complete original **1,404B Bullet command-11**, **1,036B LZSS
  compressor**, **3,490B InputDevice poll**, **11,110B ECL Runtime
  tick** and **298B Animation pool allocation** are **already strict
  exact**. Old source-frontier NONEXACT narratives for those individual
  *closed* bodies must not be mistaken for live status.
- The original **3,735B/935-instruction Bullet emitter** is **NOT**
  native exact, even though current maintained C++ emits **3,736B/936**,
  **934/935 native mnemonic kinds in original order**, all **60
  original E8 physical callees in the same order**, and matching
  3,832B compiler span / 69 absolute reference **counts**. Native
  mode-12 x87 operand order, an extra compiler NOP and E8 physical
  field displacement remain unresolved; no original parent bytes are
  credited. See [latest complete native x87 evidence](BULLET_EMITTER_3735_X87_RETURNS_934_FRONTIER.md).
- The **3,111B Player main frame**, **555B Player movement**, **273B
  Bullet draw-group**, **1,649B Enemy mesh**, **12,140B Bullet
  dispatcher**, **41,967B Enemy ECL dispatcher** and **39,470B
  Animation VM** are still independently NONEXACT. An exact child
  does not close its parent. The independently exact 63B legacy STL
  shared_ptr move assignment is **library-origin excluded**, not an
  extra 63 game-authored bytes.
- Dated [CORE/CLEANUP-497](ARTIFACT_RETIREMENT_2026_10_29.md) and
  [CORE/CLEANUP-300](ARTIFACT_RETIREMENT_2026_10_28.md) counts were
  valid **only at their checkpoint dates**. Their earlier 236/212
  canonical-provider counts are no longer current. Preserve historical
  evidence rather than rewriting its originally measured results.

This edit reorganizes documentation without altering existing native
code or exact claims; it does not assert whole-program linkage or a
playable game.

## Explicit guarded deletion: reproducible probe objects only

The tool `scripts/prune-generated-artifacts.py` was run with a
**separate dry run**, then explicit `--apply` with a **new immutable
private audit name**. Its live manifest-derived protected set includes
all 243 canonical objects and all 243 adjacent native compiler
receipts. An additional allowlist retains current nonexact
Bullet/Player/mesh/game-control probes and source-specific old active
experiments; the allowlist was expanded to protect current
`core601`, `core614`, `core616`, `core620`, `core621`, `core622`,
`core626`, `core541` and `core558` probe objects/receipts.

| Category | Actual cleanup result |
| --- | ---: |
| Regenerable noncanonical `.obj` / `.receipt.json` deleted | **1,148 files** |
| Reclaimed exact original filesystem bytes | **45,337,123 bytes** |
| Space reclaimed | **43.24 MiB** |
| Physical `build/` before | approximately **120 MB** |
| Physical `build/` after | approximately **74 MB** |
| Protected whole-native canonical MSVC objects | **243**, all SHA-256 unchanged |
| Protected canonical sibling receipts | **243**, all SHA-256 unchanged |
| Active noncanonical probe files kept | **1,696** |
| Original PE target | SHA-256 unchanged |
| Native-source/manifest changes | **None** |
| Whole repository cold replay | **Not run** |

Every removed filename, original length and original SHA-256 is
preserved in **ignored private audit**
`.analysis/core628-build-retirement-inventory.json`. It also preserves
all **486 protected canonical object/receipt SHA-256 hashes**, the
precise active-directory allowlist, and immutable target identity.
The dry-run/actual command transcripts are respectively
`.analysis/core628-retirement-dry-run.log` and
`.analysis/core628-retirement-apply.log`. The `--apply` run itself
rechecked **all 486 protected hashes** and the game PE hash after
removing the files, refusing symlinks, non-build trees and tracked
objects. All passed. A probe can be rebuilt from its retained source,
flags and original PE/C++ evidence rather than trusting old
intermediate `.obj` bytes.

### Corrected cleanup-tool audit semantics

The older script **always overwrote** the historical
`.analysis/core497-build-retirement-inventory.json` when applied,
which risked destroying a prior unique SHA/path retirement inventory.
That is now fixed. Dry run remains the default; application to a
nonempty deletion set **requires a new** `--inventory .analysis/NAME.json`
path; the script rejects existing or outside-tree audit paths before
deleting a file. For example:

```sh
scripts/repo-python scripts/prune-generated-artifacts.py
# Only after reviewing its selection and safe protected counts:
scripts/repo-python scripts/prune-generated-artifacts.py \
    --apply --inventory .analysis/next-unique-audit.json
```

No historical core497 or core300 inventory was overwritten. A focused
negative CLI test also inserted one disposable synthetic test object,
then proved **four invalid/unsafe apply invocations** (missing inventory,
existing inventory, outside-directory path and nested path) each fail
**before** deleting it or modifying the current audit. The test object
was removed after the check; results are in ignored private
`.analysis/core628-script-audit-guard-tests.log`. The new manifest
protection is recomputed from live `config/match-units.toml` each time,
not a stale hardcoded number. After this application,
subsequent dry runs should identify **zero** currently eligible
objects unless fresh ephemeral probes are generated.

## Explicitly protected substantial local storage

- **Installed toolchain** in `.tools/` (approximately **4.2 GB**):
  real MSVC (approximately 2.9 GB), Wine environment (approximately
  1.3 GB) and installed D3DX SDK. These are **required to reproduce
  native MSVC output**; they are not disposable build products.
- **Original/game evidence:** original `resources/th20.exe` SHA-256
  `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
  private original provenance backups and `_reference/`, attested
  `ghidra-project/`, Git history and all real native source.
- **Independent study archives** in ignored `.analysis/` (about
  **278 MB** total, with approximately **126 MiB** historical
  `.json.gz` / `.log.gz`): many are **unique frozen original ABI/source
  input or prior successful native-replay snapshots referenced by
  retained research scripts/documents**. Their age is not sufficient
  evidence to delete them. Whole-body native audits and `.analysis`
  scripts are also retained. They were **not** purged to inflate
  the reclaimed storage figure.

Do **not** use `git clean -fdx`, delete the complete `build/` or
`.analysis/`, remove the installed MSVC/Wine environment, rewrite
canonical receipts, delete immutable PE data or discard unresolved
large-boss probe evidence. The current [storage workflow](RE_WORKFLOW.md)
and [agent rules](../AGENTS.md) require protected hashes and
*affected-only* rebuilds on later source changes.

## Verification and Git scope

There are **zero changed native build inputs and zero affected strict
units requiring replay**. Documentation, a dry-run-first cleanup
control script and ignored cache products are the only changes.
Appropriate gates: original target hash, manifest/ledger validation,
current generated progress, Markdown links, Git staged/diff checks,
the cleanup script's private SHA inventory, and targeted
Python/control-plane tests for the changed cleanup script.
No reason exists to recompile a 1,184-unit source graph for this
maintenance batch. Commit checkpoint subject uses the required
**`gpt-web:`** prefix.

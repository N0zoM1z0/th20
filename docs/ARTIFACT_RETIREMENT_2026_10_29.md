# CORE/CLEANUP-497 — live handoff correction and guarded object-cache retirement

**Historical checkpoint; superseded for live counts by
[CORE/DOC-CLEANUP-628](ARTIFACT_RETIREMENT_CORE628.md).** The 1,670 files,
55.82 MiB, 236 canonical providers and 151-line handoff below accurately
describe **this earlier batch only**. Subsequent reconstruction raised
canonical providers to 243, and repeated session updates expanded the handoff
to 813 lines; the newer cleanup returned it to 147 current-state lines and
removed another 1,148 reproducible probes / 43.24 MiB. The guarded cleanup
command now requires a unique `--inventory` filename so it cannot overwrite
this checkpoint's private SHA/path audit. Historical findings below are
retained unchanged.


**Date:** 2026-10-29. Reconstruction semantics and original physical
matching claims are **unchanged** by this maintenance checkpoint. The
preceding CORE/EXACT-496 native 215-byte diagnostic result was
independently verified and committed separately before cleanup, so
this batch began from a clean Git worktree.

## Measured ignored-object retirement

| Category | Result |
| --- | ---: |
| Ignored MSVC probe/cache files deleted | **1,670** |
| Exact bytes reclaimed | **58,533,248** |
| MiB reclaimed | **55.82 MiB** |
| Physical `build/` disk use before | ~125 MB |
| Physical `build/` disk use after | ~65 MB |
| Current protected canonical objects | **236** |
| Current protected sibling receipt JSON files | **236** |
| Active unresolved-boss probe files retained | **1,520** |
| Original PE target | **SHA-256 unchanged** |
| Whole-repository cold replay | **Not run** |

The explicit opt-in script `scripts/prune-generated-artifacts.py`
selects only ignored, noncanonical MSVC `.obj` and
`.receipt.json` products under `build/`.
It derives the live protected set from **every source object in
`config/match-units.toml`**, computes their SHA-256 values
before deletion, and checks every one again afterward. The
user-selected executable SHA-256 is verified both before and
after the operation. It rejects unexpected tracked `build/` files
and does not follow symlinks.

The script is a **dry run by default**:

```sh
scripts/repo-python scripts/prune-generated-artifacts.py
# Review protected counts and selected paths before requesting:
scripts/repo-python scripts/prune-generated-artifacts.py --apply
```

Before deleting, it writes every selected path, original file
length and SHA-256 to the private ignored audit
`.analysis/core497-build-retirement-inventory.json`,
along with the SHA-256 of all 472 protected objects/receipts.
The completed operation removed the chosen paths and verified
there were **zero remaining eligible disposable build files**.
No canonical or active protected path was removed. If a
historical discarded compiler probe is needed, regenerate it
from retained private source/commands rather than using an old
object as a native-match oracle.

The allowlist deliberately retains live unresolved Bullet
group-drawing and emitter/command-11 probes, Player
555B movement and 3,111B frame studies, Enemy mesh probes,
and Archive LZSS probes. The allowlist is recorded in the
script and in the audit; **reassess it against the current
unclosed bosses before another cleanup**. This is not
permission to remove all noncanonical inputs or to delete
an unresolved game root's only source.

## Preserved private analysis and source-of-truth products

The separate ignored `.analysis/` tree remains intact
(approximately **269 MB**). It contains original PE
disassembly, independent native reference attestations,
C++ source hypotheses, reverse-engineering scripts, and
**387 compressed snapshot files** (about **126 MiB**).
The historical archives are explicitly referenced by
private study scripts; their age alone does not establish
that they are safely disposable. They were **not**
bulk-deleted. The existing
[CORE/CLEANUP-300 historical retirement](ARTIFACT_RETIREMENT_2026_10_28.md)
is a dated earlier audit with only **212** canonical
objects at that time, not an authoritative live count.

The installed `.tools/` MSVC/SDK toolchain,
`ghidra-project/` database, supplied original game
provenance, `resources/th20.exe`, tracked C++ and
documentation, Git history and all 472 protected
canonical binary/receipt artifacts were untouched.
**Do not run `git clean -fdx`, remove the whole
`build/` or `.analysis/` tree, or delete the original
executables or private toolchain to reclaim space.**

## Corrected navigation and historical status

The accumulated 1,253-line `docs/RE_HANDOFF.md`
contained many sequential checkpoint paragraphs
claiming individual input functions were still
NONEXACT even after later whole exact acceptance.
It was replaced by a **151-line current handoff**
that lists verified totals, truly closed functions,
remaining large bosses and exact source-replay
rules. The previous exact long handoff remains
recoverable from `git show 9eed65c:docs/RE_HANDOFF.md`.
The separate 1,689-line earlier historical
handoff also remains in Git history.

Corrections include: the **465B InputInf initialization**,
**726B DirectInput discovery**, **170B XInput discovery**,
**466B shutdown**, **1,081B Player option frame** and
**1,518B Player option rebuild** are now already exact.
The **3,490B InputDevice polling**, **555B Player movement**,
**3,111B Player main frame**, Enemy mesh, Bullet drawing,
Bullet command-11/emitter and Archive LZSS roots are
**still NONEXACT**. The independent 215B normal
diagnostic and 221B error-flagging diagnostic are
different physical original routines, both exact,
with correct original DirectInput caller targets.

The navigation [evidence index](EVIDENCE_INDEX.md)
and current [README](../README.md) were corrected
accordingly. Comment-only edits in the two public headers
`src/InputInf.hpp` and `src/InputState.hpp`
removed claims that already exact input functions were unfinished.
These edits have **no semantic C++ change**, but the
header receipt hashes changed. Actual *pre-edit*
include-graph receipts bounded the necessary replay
to **8 native source providers / 30 strict units**.
The complete cold replay passed **12/12 and 18/18
units across those eight objects** at reduced priority:
`.analysis/core497-comment-preedit-header-closure.json`,
`.analysis/core497-comment-only-scoped-batch0.log`
and `batch1.log`. No other unit was cold-replayed
for these comments or storage cleanup.

## Post-cleanup gates

- Original locked game SHA-256 verified, unchanged.
- All **236 canonical objects and 236 receipts** preserved
  byte-for-byte with private SHA-256 audit.
- Source-status ledgers validate **400 complete original
  game-authored functions, 121,429 game body bytes and
  1,176 canonical strict units** in 236 providers.
- `scripts/progress.py --check`, Markdown link checks,
  `git diff --check` and staged change validation
  are required before the maintenance commit.

A code/source matching checkpoint and a documentation/
artifact-retirement checkpoint have separate commits,
so later agents can investigate native progress without
confusing ignored cache deletion with new exact byte credit.

# TH20 reconstruction workflow

This control plane follows the local TH095 reconstruction repository. Its
accepted source, function addresses, VC7.1 flags, CRT library assumptions, and
special assembly exceptions are not TH20 evidence.

## Session preflight

The user requires affected-only validation and quick handoffs. Documentation
and cleanup batches with an unchanged reconstruction graph need Git/diff/link
checks and protected-product hash checks, with zero replay units. Skip Ghidra,
MSVC, full CI and canonical replay for these batches. The preflight below is for
changes to reconstruction code, native analysis evidence or acceptance state.
Use the active session's requested commit prefix. State the affected replay scope
in the handoff; an unchanged documentation/cleanup batch reports zero units.
Reuse completed passing checks when their inputs are unchanged. Resuming a
handoff or retiring artifacts does not require restarting those checks.

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

Read `RE_HANDOFF.md` and the relevant source/evidence; consult the other guides
as needed for the selected unit. Use one native reconstruction writer at a time.
Own all live dirty and untracked work in this single-worker repository;
there is no other session whose changes should be skipped. Ghidra and compiler
wrappers serialize their operations.

## Bounded reconstruction loop

1. Select one address from `config/functions.csv`. Reconcile its entry, exits,
   tail calls, shared code, jump tables, padding, and disconnected ranges with
   target control flow. The initial Ghidra span is only a candidate boundary.
2. Use attested disassembly, callers, callees, xrefs, strings and decompilation.
   Keep raw decompiler text and temporary hypotheses under `.analysis/`.
3. Form a semantic and ABI hypothesis. Preserve uncertain names, types,
   ownership and object boundaries as unknowns.
4. Compile a natural C/C++ probe for the complete selected function with the
   pinned x86 compiler and explicit flags. Runtime/library origins need
   independent evidence; auto-analysis does not classify authorship.
5. Compare instructions, stack/register behavior, complete extents and
   relocations. Diagnostic structural-exact excludes relocation fields and
   therefore does not establish exactness.
6. Maintain shared production source under `src/`. Add a canonical unit only
   with explicit source/object/profile/symbol/target/size/relocations. Use
   `compare_size` for complete compiler contributions including associated
   tables/padding; keep authored credit in `size` separate.
7. Cold-build and strictly replay the unit. Resolve relocation destinations
   from independently reviewed symbols/data/control-flow evidence. Never
   fill canonical destinations by solving the field being compared.
8. Record an exact result only after the canonical replay has zero differences
   over its complete extent. Update mapping, origins, source presence and
   match ledgers separately; do not infer one from another.
9. Record the evidence and affected replay scope, regenerate progress when its
   inputs change, inspect the public diff and commit a stable checkpoint.

Replay every affected unit after a shared header, profile, translation-unit,
layout or relocation-anchor change. Profiles are per source/unit, not a global
assumption. Record semantic interpretation, link coherence and runtime behavior
separately from exactness.

Determine affected providers from the changed input closures and manifest
dependencies. Use individual unit commands or repeated `--source` filters;
do not default to an unfiltered replay. Reuse passing evidence for unchanged
providers. Public CI covers the exact oracle and metadata when those tools
change. The historical portable semantic suite is retired; its paths and scenario
counts in evidence documents describe dated experiments, available in Git history
(see [retained tests](../tests/README.md)). Investigate a specific unresolved native
behavior or ABI question with a temporary probe under `.analysis/`. Preserve
target error paths in source and compare their complete native contributions.

## Large dispatcher evidence

Function-based Ghidra exports can omit valid switch cases even without output
truncation. Use `query OUTPUT disassemble_range COUNT START INCLUSIVE_END` to
read the existing listing throughout an independently reconciled interval.
This operation neither defines missing instructions nor changes function bodies.
Then use `scripts/audit-dispatcher.py` with the complete PE interval, explicit
pointer table, optional compressed index table and that export. Review omissions
and external branches; no source, boundary ownership or exact claim follows
automatically. See CORE_ECL_DISPATCH_RECONSTRUCTION.md for both current roots
and reproducible commands. Keep whole compiler contributions, associated tables
and all unreferenced failure/exit paths in subsequent comparisons.

## Decoded operand navigation

Use `query OUTPUT operand_scalars LIMIT START INCLUSIVE_END VALUE...` through the
attested wrapper to locate numeric operands in one bounded existing memory block.
The query is read-only, reports original scalar widths and explicit truncation,
and checks cancellation. Numeric matches are navigation leads; inspect the full
receiver/producer/consumer flow before assigning field ownership or meaning.
No matching instruction does not establish padding or absence of dynamic access.
See TOOLS.md and ANIMATION_BINDING_RECONSTRUCTION.md for the verified CORE119 use.

## Retiring generated artifacts

Keep current handoff, architecture, oracle and source-map documents concise and
separate. Record unique evidence in its focused document and update the evidence
index. Historical session logs stay in Git; dated batch counts do not override
live ledgers. Correct misleading source names/comments with the usual affected
replay rather than carrying unsupported semantics into future work.

During longer batches, retire replaced trials periodically once their
replacement evidence is verified. Preserve active inputs and native evidence;
archive original SHA-bound inputs and receipts before removing copied headers
or old snapshots. Keep heavy verification/build jobs serial at reduced priority.
Do not wait until the end of a long batch to address accumulating temporary data.

Retire superseded build artifacts after every stable reconstruction batch, as
explicitly requested by the user. Protect every current
`config/match-units.toml` object and its sibling
`.receipt.json` before removing obsolete experiment builds. Keep toolchain smoke
proof reports and probe sources, active probes, native exports and evidence
supporting reviewed ledgers. Completed regenerable smoke binaries and copied SDK
DLLs can be retired while retaining their saved proof and master SDK files.
Completed generated checkouts, CMake build trees and temporary setup environments
can be removed after confirming they contain no tracked or active input. Preserve
locked tools, reference source, Ghidra and supplied game files.

Downloaded MSVC installer payloads under `.tools/downloads/msvc/` are a
regenerable cache, separate from the installed compiler and SDK under
`.tools/msvc/`. After checking the installed tools, this cache can be retired
with a path/size/hash inventory. Preserve `.tools/vs2022-pinned.manifest`, the
tool lock and installed files; never follow tool symlinks during deletion.
The bootstrap skips MSVC downloads when the installed compiler is present.

The pinned D3DX NuGet archive under `.tools/downloads/` is also a regenerable
download cache. Check its locked package hash and verify the extracted SDK files
against the archive before retiring it; preserve the installed SDK and record
both the cache inventory and installed-file hashes. Bootstrap reuses an installed
D3DX SDK without downloading this cache again.

Record removed paths/bytes and protected hashes privately. Verify those hashes
after cleanup; an unchanged graph requires no replay. If the batch also changes
reconstruction inputs, strictly replay only the affected units, using explicit
source filters or individual unit commands at reduced priority. Never run a
whole-graph replay or cold build solely for cleanup or documentation.
Source/header/profile changes require fresh affected builds. EXACT-058 records
the historical first retirement pass; its broader verification is not the
current required scope.

Inactive successful replay snapshots may be archived losslessly as `.json.gz`.
Completed historical replay logs may likewise use `.log.gz` after checking an
explicit successful terminal summary and rejecting failure or mismatch records.
Verify that every saved unit passed, check the decompressed content against the
original SHA-256 before retiring the uncompressed file, and record both hashes
and bytes saved. Keep current snapshots, native exports, failed experiments and
active inputs intact. Read archived evidence with `gzip.open` through
`scripts/repo-python`; an archived path is preserved evidence, not a missing
verification. Store cleanup-only replay reports compressed from the outset.

Superseded generated handoff inventories may also be archived losslessly after
checking that the current handoff uses a newer inventory. Preserve their exact
decompressed bytes, record both hashes and update the current handoff's archive
lookup. Do not retire the current product inventory or active investigation inputs.

Superseded source-freeze hash reports may use the same lossless archival process.
Keep the current freeze and every report protected by the active investigation;
record the original and archive hashes in the current handoff's private lookup.

Completed historical public-CI logs may likewise be archived as `.log.gz` after
checking their terminal success marker and successful test summary. Record the
original path, original SHA-256, archive path and archive SHA-256 in the private
retirement inventory; verify decompressed bytes before removing the original.
Keep current CI evidence, failed logs, native exports and active inputs intact.

## Live guarded artifact-retirement procedure (CORE/DOC-CLEANUP-628)

The newer [CORE/DOC-CLEANUP-628 storage audit](ARTIFACT_RETIREMENT_CORE628.md)
supersedes earlier **live artifact/provider counts**, not their recorded
historical facts. The current original native graph uses **243 canonical
object/receipt providers (486 protected files)** and **1,184 configured
strict units**. All 243 objects and sibling receipts are protected from
retirement by the *live* `config/match-units.toml`; no hardcoded prior
236/212-provider numbers should be treated as live.

The audited follow-on retired **1,148 noncanonical `.obj`/receipt files,
45,337,123 bytes (43.24 MiB)** from ignored `build/`, while retaining
1,696 active probe files and **all 486 live protected SHA-256 hashes**,
including the immutable original target. The proof includes a unique private
`.analysis/core628-build-retirement-inventory.json`, a dry-run transcript
and an apply transcript. Actual active Bullet 3,735B and Player
555B/3,111B source inputs and selected compiler probe objects were retained.

**Do not overwrite previous retirement audits.** The guarded script now
requires an explicit **new, unique** audit inventory for applying a nonempty
deletion set:

```sh
scripts/repo-python scripts/prune-generated-artifacts.py
# Review the target/protected/dry-run scope before explicitly applying:
scripts/repo-python scripts/prune-generated-artifacts.py \
    --apply --inventory .analysis/unique-new-retirement-inventory.json
```

Deleting historical `.analysis/*.json.gz` archives for their age is unsafe:
retained source freeze/replay records and native evidence cite many of these
exact snapshots. Preserve the Ghidra project, original executable, installed
MSVC/Wine/D3DX, private references, native source, canonical receipts,
independent PE proofs and current active hypotheses. An unchanged native
source/manifest graph has **zero affected exact units** and does not require
cold replay. The current [short handoff](RE_HANDOFF.md) is authoritative;
check dated old proof documents via [the evidence index](EVIDENCE_INDEX.md).

## Historical guarded build-object cleanup (CORE/CLEANUP-497)

The [2026-10-29 artifact retirement report](ARTIFACT_RETIREMENT_2026_10_29.md)
supersedes *live* artifact counts in the dated CORE/CLEANUP-300
report. Use the tracked dry-run-first
`scripts/prune-generated-artifacts.py` for follow-on cleanup.
It reads the **live manifest** for exact protected objects and
receipts and explicitly retains the active, unfinished complete-boss
probe sets. A previous safety-audited application retired
**1,670 ignored noncanonical compiler objects/receipts, reclaiming
55.82 MiB**; **all 236 current canonical object/receipt pairs**
and the immutable game executable SHA-256 remained unchanged.
Each deleted file's path, original byte count and SHA-256 are in
the private `.analysis/core497-build-retirement-inventory.json`.

Do not treat the 126 MiB of private historical `.analysis/*.gz`
archives as disposable merely because they are old: retained
historical research scripts explicitly reference these snapshots.
The 1,253-line old handoff is available at
`git show 9eed65c:docs/RE_HANDOFF.md`; the current
[compact handoff](RE_HANDOFF.md) is the authoritative source
for current exact/nonexact status. Old native exact counts and
old NONEXACT descriptions in focused proof documents must be
read with their checkpoint date and later supersession notes.

## Protected storage and ignored artifact retirement (CORE/CLEANUP-300)

Treat `build/` as a regenerable object cache, **not** as a stable evidence
archive. The live `config/match-units.toml` is the source of truth for
protected canonical objects; each currently selected object also has a
corresponding `.receipt.json` describing its actual included headers.
Never retire either file, or any original executable, source/toolchain,
private Ghidra database, original native disassembly or cited research
snapshot. Do not run whole-graph replay for documentation and storage
cleanup if native compiler inputs are unchanged.

The completed [CORE/CLEANUP-300 audit](ARTIFACT_RETIREMENT_2026_10_28.md)
retired 2,496 obsolete ignored products and reclaimed 203.65 MiB,
without touching 212 canonical object/receipt pairs. The private
`.analysis/core300-safe-artifact-prune.py` is dry-run by default,
rechecks manifest/target protection and records deleted file names,
sizes and SHA-256 values. Regenerate any retired private host or probe
from retained source rather than treating legacy build outputs as
exactness evidence. Preserve any ongoing nonexact source hypothesis
privately before removing its speculative public declarations.

# TH20 reconstruction workflow

This control plane follows the local TH095 reconstruction repository. Its
accepted source, function addresses, VC7.1 flags, CRT library assumptions, and
special assembly exceptions are not TH20 evidence.

## Session preflight

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
```

Read `RE_HANDOFF.md`, `ARCHITECTURE.md`, `ORACLES.md`, and the relevant source.
Read `SEMANTIC_RECONSTRUCTION.md` before assigning semantic meaning. Work in
one writable session. Ghidra and compiler wrappers serialize their operations.

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
9. Update knowledge/handoff, run affected replays, regenerate progress, run CI,
   inspect the public diff and commit a stable checkpoint.

Replay every affected unit after a shared header, profile, translation-unit,
layout or relocation-anchor change. Profiles are per source/unit, not a global
assumption. Exact source, semantic acceptance, link coherence and runtime
behavior remain independent acceptance gates.

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

## Retiring generated artifacts

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

Record removed paths/bytes and protected hashes privately. Strictly compare all
current units after cleanup; do not cold-rebuild an unchanged source graph just
for cleanup or documentation. Source/header/profile changes require the usual
affected cold replay. EXACT-058 records the first retirement pass.

Inactive successful replay snapshots may be archived losslessly as `.json.gz`.
Verify that every saved unit passed, check the decompressed content against the
original SHA-256 before retiring the uncompressed file, and record both hashes
and bytes saved. Keep current snapshots, native exports, failed experiments and
active inputs intact. Read archived evidence with `gzip.open` through
`scripts/repo-python`; an archived path is preserved evidence, not a missing
verification. Store cleanup-only replay reports compressed from the outset.

## CORE/EXACT-104 checkpoint

The complete Item owner batch preserves one genuine semantic declaration/body
with actual Animation/Timer/list storage, native whole-array byte initialization
under its resource-free/no-observer precondition and actual lifetime/scheduler
publication. The uniform /fp:strict profile reproduces observed runtime float
operations and while/decrement without inert locals. Native full extents,
constants, ABI/EH/vtable support and actual O2/ASan/UBSan precede admission.
Shared list constructor/reset disagreements remain recorded supporting boundaries.
The frozen747-unit/143-object graph builds each changed object once; literal
renames follow complete native payload identities. Cleanup replays existing
objects and protects current receipts, source, native evidence and historical
SHA-bound input closures. See [Item ownership](ITEM_OWNER_RECONSTRUCTION.md).

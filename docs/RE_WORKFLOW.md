# TH20 reconstruction workflow

> Current workflow: follow the **Highest priority** section in `AGENTS.md`.
> Prefer affected exact comparisons and useful Markdown knowledge. Ordinary
> notes do not require full CI, native replay or document-hash/pin refreshes.
> Older broad validation instructions apply only when their impact is relevant.


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

## Comment-only C++/header edits and canonical literal-name receipts

Documentation-only edits under `docs/` do not modify compiler inputs and
need **zero native replay**. However, even a **comment-only** change under
`src/*.cpp` or a shared `src/*.hpp` changes the pinned compiler input
fingerprint. A header change also affects all transitive C++ consumers,
regardless of whether any generated machine-code instruction changes.
Determine the actual *quoted-include closure* and replay only the
currently accepted exact units from those sources. Noncanonical and
source-present/NONEXACT consumers have no strict receipt to refresh.

MSVC may renumber the compiler-generated `$SG...` **symbol names** of
string literals when a header's source line numbering changes. This
was observed during the 2026-10-31 `InputState.hpp` status-comment
correction: original `InputInf::start` had a genuine PE HIGHLOW at
`0x00420990+0x0A -> 0x0056D674`, and `InputInf::initialize_devices`
had one at `0x00420D80+0xA3 -> 0x0056D6D4`. The canonical COFF
symbols shifted from `$SG171238` to `$SG171248` and `$SG171420` to
`$SG171430`, *without changing any original native code bytes or
physical relocation destinations*. These two and **only** these two
actual symbol-name fields were adjusted in `config/match-units.toml`
after independently verifying the original PE HIGHLOW and all
nonrelocated original x86 bytes. The 17 genuinely affected pinned
source objects then replayed **42/42 exact native units** with no
full-graph cold compilation. This is a narrow compiler-evidence
receipt update, not an ABI change or license to rename unknown
relocations without original-PE proof.

## Repository size and basic checks

Keep required inputs (original game, pinned tools and Ghidra project), current
source and exact ledgers, reproducible build/comparison scripts, and useful
knowledge. Record current blockers, verified findings and worthwhile failed
approaches in short English notes. A document citation alone does not justify
keeping a file. Git preserves historical tracked text.

Delete obsolete input snapshots, completed comparison/CI logs, historical
archives, duplicate exports and cleanup reports when they no longer help an
open question. Remove their evidence references too. Command examples may still
name disposable output paths: running the recipe recreates those products.
Retain an old compiler context only when an unresolved question depends on
inputs that are difficult to reproduce; identify that reason in the relevant
working note. No new archive, per-file audit or cleanup report is required.

The build cleanup script protects current manifest objects and receipts, skips
tracked files and symlinks, and checks retained product/target hashes. It lists
candidates by default. Use an explicit keep path for a needed compiler context:

```sh
scripts/repo-python scripts/prune-generated-artifacts.py
scripts/repo-python scripts/prune-generated-artifacts.py --keep build/open-question
scripts/repo-python scripts/prune-generated-artifacts.py --keep build/open-question --apply
```

Review the selection before applying. Keep source drafts and native evidence;
noncanonical objects can normally be rebuilt. Do not remove the entire build
or analysis tree. Preserve supplied game files, projects and game-specific Wine
state. Reuse Factory's pinned tools as described in [shared tools](SHARED_TOOLS.md).

Documentation and cleanup with unchanged native inputs have zero affected exact
units. Inspect diffs/links and check protected hashes; no MSVC, Ghidra or replay.
Native changes still require fresh affected builds and complete strict comparison,
including owned extents and relocations. Exactness comes from that comparison.

Default public CI runs syntax, ledger, build-configuration, source-profile and
private-artifact checks in a clean checkout without proprietary inputs. Run
`scripts/repo-python scripts/ci.py` when changing these inputs. `--full` adds
synthetic exact-oracle tests for relevant comparator changes. Other tool tests
are selected explicitly for the changed tool. Reports, progress generation,
native replay and reference-review suites are separate task-specific commands,
not routine commit gates.

# TH20 reconstruction workflow

This control plane follows the local TH095 reconstruction repository. Its
accepted source, function addresses, VC7.1 flags, CRT library assumptions, and
special assembly exceptions are not TH20 evidence.

## Session preflight

```bash
git status --short --branch
python3 scripts/verify-target.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
python3 scripts/ghidra.py check
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
4. Compile a small natural C/C++ probe with the pinned x86 compiler and explicit
   flags. Runtime/library origins need independent evidence; auto-analysis
   does not classify authorship.
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

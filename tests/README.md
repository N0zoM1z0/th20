# Exact-oracle and control-plane tests

The maintained tests cover strict COFF comparison and receipt freshness,
dispatcher auditing, canonical ECL relocation owners, reference indexing and
repository Python selection. Run only the relevant checks when these tools
change. `scripts/repo-python scripts/ci.py` remains the public CI entrypoint.
Exact reconstruction checkpoints use affected locked-compiler builds and
complete canonical replay, as described in [the workflow](../docs/RE_WORKFLOW.md).

The historical portable C++ semantic suite and its Python runners were retired
on 2026-10-28. Allocation-failure/null robustness cases, exception matrices,
sanitizer hosts and scenario counts are not ongoing acceptance requirements.
Native source still preserves the target's original branches and EH.

Older evidence documents retain dated test paths and results. Their source is
available at commit `9bca5ea`, for example:

```bash
git show 9bca5ea:tests/ecl_arguments_semantics.cpp
```

A specific unresolved target behavior or ABI question can use a temporary probe
under ignored `.analysis/`; no historical suite needs to be restored or rerun.

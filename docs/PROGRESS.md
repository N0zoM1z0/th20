# TH20 reconstruction progress

Read the current checkout's ledgers with:

```bash
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The report distinguishes provisional candidates, source mappings, source
presence, configured comparison units and credited game-authored exact
functions. Exact byte totals use the accepted extents in
[`config/matches.csv`](../config/matches.csv).

For a Markdown snapshot and SVG generated from those same totals, run
`scripts/repo-python scripts/progress.py`. Both files are written to
`.analysis/progress/`. This keeps the published instructions independent of
any one checkpoint's totals.

Inspect which local builds need refreshing with
`scripts/repo-python scripts/replay-exact-units.py --list-stale-sources`.
See [the handoff](RE_HANDOFF.md) for the current work queue.

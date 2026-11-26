# TH20 reconstruction progress

The status report reads the current checkout's ledgers.

```bash
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The report distinguishes provisional candidates, source mappings, source
presence, configured comparison units and credited game-authored exact
functions. Exact byte totals use the accepted extents in
[`config/matches.csv`](../config/matches.csv).

For a Markdown snapshot and SVG generated from those same totals, run
`scripts/repo-python scripts/progress.py`. The Markdown snapshot is written to
`.analysis/progress/PROGRESS.md`; the SVG is written to
[`resources/progress.svg`](../resources/progress.svg) and displayed in the README.
Regenerate the SVG when publishing updated ledger totals.

Inspect which local builds need refreshing with
`scripts/repo-python scripts/replay-exact-units.py --list-stale-sources`.
See [the handoff](RE_HANDOFF.md) for the current work queue.

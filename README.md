# 東方錦上京 ～ Fossilized Wonders.

<p align="center">
  <img
    src="resources/title-screen.png"
    width="640"
    alt="Original Japanese TH20 title screen">
</p>

<p align="center">
  <img src="resources/progress.svg" alt="TH20 exact source reconstruction progress">
</p>

Source reconstruction of the original Japanese TH20 v1.00a **Steamless**
executable. Function-level exactness requires reproducible comparison against
one hash-attested target. The workflow follows [TH095](https://github.com/N0zoM1z0/th095),
with Ghidra and a separate modern MSVC environment for TH20.

> [!IMPORTANT]
> Reconstruction is in progress. Verified source components and exact function
> comparisons are available; the repository does not yet build a playable game.
> Origin review, source presence, exactness, linkage and runtime behavior are
> separate statuses.

## Exact target

Supply your own executable as `resources/th20.exe`:

| Property | Required value |
| --- | --- |
| Version | Japanese 1.00a, user-selected Steamless variant |
| Embedded title/replay label | 1.00c; recorded separately from registry/package identification |
| Size | `1,858,560` bytes |
| SHA-256 | `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| MD5 | `e7ccdbd2f319ba868ce386e484fff1d3` |
| Image base | `0x00400000` |
| Entry point | `0x005435E0` |

```bash
scripts/import-target.sh /path/to/th20.exe
scripts/repo-python scripts/verify-target.py
```

The Steam-original backup is retained locally as provenance evidence. Its
code differs from the comparison target. See [target provenance](docs/TARGET_PROVENANCE.md)
for official Japanese release and independent executable identification.
Game executables, assets, private databases, toolchains and reference checkouts
are excluded from Git.

## Repository status

| Area | Current position |
| --- | --- |
| Target and analysis | Locked executable; independent, fully attested Ghidra 12.1.3 project |
| Inventory | 6,928 provisional candidates; origin and boundary review in progress |
| Source | Seventy-five mapped component functions across twenty comparison objects |
| Authored exactness | Fifty-two functions, 3,830 bytes |
| Library comparisons | Four MSVC minstd_rand component equivalents pass exact replay; excluded from authored totals |
| Shared float view | Three exact comparisons; enclosing owner and origin review remain open |
| Empty/defaulted lifetime contributions | Three exact comparisons; authored versus compiler-synthesized origin remains open |
| Configuration initializers | Two exact comparisons; authored versus compiler-synthesized origin remains open |
| Window contributions | Flags initialization and foreground wrapper pass exact replay; origin remains open |
| Audio state construction | Three complete exact record constructors; authored versus compiler origin remains open |
| Animation handle construction | Complete 23-byte exact value constructor; authored versus compiler origin remains open |
| Vector arithmetic | Five complete exact members; original class spelling and authored/library origin remain open |
| Whole-program build and runtime | Not available |

[Generated progress](docs/PROGRESS.md) and `scripts/report-reconstruction-status.py`
are the canonical live totals. The authored-byte denominator covers only the
currently reviewed set; it is not whole-game completion.

The pinned compiler candidate is MSVC `19.44.35211` x86, with Windows SDK
`10.0.26100.0` and D3DX `9.29.952.8`. Clean `/Od` C++20 profiles reproduce the
accepted components. These results do not establish executable-wide compiler
flags, SDK or CRT identity. Profiles and relocation anchors are recorded per
source in `config/match-units.toml`.

## Build and verify

Public checks need Python 3.11+ and a C++20 compiler, with no original game or
proprietary toolchain:

```bash
scripts/repo-python scripts/ci.py
```

Private reconstruction checks:

```bash
scripts/bootstrap-tools.sh
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/replay-exact-units.py
```

On a fresh private workspace, provision tools as described in
[Tools](docs/TOOLS.md), then run `scripts/repo-python scripts/ghidra.py import` once.
Every query re-attests the executable and complete mapped code section;
inventory refreshes never overwrite reviewed ledgers.

## Reference review

[Oracatt/Touhou20](https://github.com/Oracatt/Touhou20) is pinned locally under
ignored `_reference/Touhou20`. Its target hash matches ours. Its v1.00c label
comes from embedded strings; our v1.00a identification follows the independent
hash registry and supplied package. Both observations are preserved in provenance.

The [review](docs/REFERENCE_REVIEW.md) records the repository-wide evidence audit,
module dispositions, stale reports and independently verified absorption.
Validated source diagnostics route further analysis; reference source, build
layout and completion claims are not imported wholesale.

The [function-by-function review](docs/REFERENCE_FUNCTION_REVIEW.md) is now
active across all existing implementations. Its explicit decisions and pending
counts are separate from the earlier file audit; scanning or compiling a file
does not complete its function reviews.

## Documentation

- [Current handoff](docs/RE_HANDOFF.md)
- [Architecture and target inventory](docs/ARCHITECTURE.md)
- [Reconstruction workflow](docs/RE_WORKFLOW.md)
- [Independent oracles](docs/ORACLES.md)
- [Build and strict matching](docs/BUILD_MATCHING.md)
- [Ghidra setup and attestation](docs/GHIDRA.md)
- [Tool routing](docs/TOOLS.md)
- [Source ownership](docs/SOURCE_MAP.md)
- [Semantic reconstruction policy](docs/SEMANTIC_RECONSTRUCTION.md)
- [Reference review](docs/REFERENCE_REVIEW.md)
- [Function-by-function reference review](docs/REFERENCE_FUNCTION_REVIEW.md)
- [Runtime invincibility launcher](docs/RUNTIME_PATCH.md)
- [Verified knowledge base](docs/KNOWLEDGE_BASE.md)
- [Roadmap](docs/ROADMAP.md)
- [Generated progress](docs/PROGRESS.md)
- [Agent rules](AGENTS.md)

## Credits

- [Oracatt/Touhou20](https://github.com/Oracatt/Touhou20): reference
  reconstruction, source diagnostics and behavioral investigations that guide
  our independent, function-by-function review.
- [N0zoM1z0/th095](https://github.com/N0zoM1z0/th095): reconstruction workflow,
  exact-oracle control plane, tracking conventions and README/progress layout.

## License

[MIT](LICENSE) for this repository's original code and TH095-derived control
plane. It grants no rights to the original game, downloaded tools or external
reference material. Maintained prose and commit messages are in English;
official names and original target evidence retain their original language.

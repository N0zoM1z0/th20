# 東方錦上京 ～ Fossilized Wonders. reconstruction

TH20 Japanese v1.00a reconstruction, bootstrapped using the local TH095
workflow. The exact oracle is the **user-selected Steamless** variant, not
unmodified non-Steam retail. See [target provenance](docs/TARGET_PROVENANCE.md).

| State | Bootstrap checkpoint |
| --- | --- |
| Target identity | verified, SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` |
| Analysis | separate, attested Ghidra 12.1.3 project |
| Candidate inventory | 6,928 provisional functions, all awaiting review |
| Compiler | pinned MSVC 19.44.35211 x86 candidate; flags remain unknown |
| Build environment | Win32/DirectX/MSVC compile + PE32 link + Wine smoke verified |
| Reconstructed source / exact units | 0 / 0 |

The original files stay in `../game_exe/`. `resources/th20.exe` is an ignored
symlink to the supplied target. Game data, executables, private databases,
toolchains and generated outputs are excluded from Git.

```bash
cd /home/pentester/coding/codex_ida/th20-reconstruction/th20
scripts/bootstrap-tools.sh
python3 scripts/verify-provenance.py --fetch
python3 scripts/verify-target.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/ghidra.py check
python3 scripts/toolchain-smoke.py
python3 scripts/ci.py
```

On a fresh private workspace, supply that exact executable at
`resources/th20.exe` and run `python3 scripts/ghidra.py import` once. Existing
projects use `check`; inventory refreshes never overwrite reviewed ledgers.
The [workflow](docs/RE_WORKFLOW.md), [oracles](docs/ORACLES.md),
[build guide](docs/BUILD_MATCHING.md), [Ghidra guide](docs/GHIDRA.md),
[tool routing](docs/TOOLS.md), [source map](docs/SOURCE_MAP.md),
[knowledge base](docs/KNOWLEDGE_BASE.md), [roadmap](docs/ROADMAP.md),
[progress](docs/PROGRESS.md) and [handoff](docs/RE_HANDOFF.md) define the process.

The control-plane scripts adapt MIT-licensed TH095 code; its compiler flags,
source mappings, game layouts and assembly exceptions do not transfer. This
repository's license grants no rights to the original game or downloaded tools.

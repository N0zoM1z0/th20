# Tool routing

Use `scripts/repo-python` for all Python commands, following TH10's interpreter
selection convention. It resolves paths from the script location, so it also
works from another directory. An explicit `TH20_PYTHON` path or command takes
precedence; otherwise the repository's `.venv/bin/python` is preferred. A
present but broken or mismatched repository environment fails without silently
switching interpreters. Python subprocesses inherit the selected interpreter
through `sys.executable`.

Python 3.11+ is required. The local environment must provide pefile 2024.8.26
and Capstone 5.0.6, pinned in `config/python-requirements.txt` and checked against
`config/tools.lock.toml`. A fresh public checkout without `.venv` can use a
compatible system Python for standard-library checks. Optional packages may be
absent there; any installed package must match its pin. Decoder-dependent
commands require the provisioned environment. The wrapper does not install
packages or change the working directory.

| Need | Command | Evidence boundary |
| --- | --- | --- |
| Reproduce installed tools | `scripts/bootstrap-tools.sh` | pinned downloads/commits; ignored local tools |
| Check installed binaries/versions | `scripts/repo-python scripts/doctor.py` | locked critical tool fingerprints and banners |
| Check Japanese variant provenance | `scripts/repo-python scripts/verify-provenance.py --fetch` | immutable independent registry + supplied files |
| Attest exact target | `scripts/repo-python scripts/verify-target.py` | SHA-256/MD5/size/PE/section hashes |
| Attest Ghidra database | `scripts/repo-python scripts/ghidra.py check` | original file bytes, loaded metadata and complete mapped code |
| Inspect target semantics | `scripts/repo-python scripts/ghidra.py query/decompile` | attested read-only view; provisional meanings |
| Rank target-wide leads | `scripts/repo-python scripts/ghidra.py architecture` | private metrics, no automatic source/origin promotion |
| Compile explicit probe | `scripts/compile-probe.sh SOURCE build/OUTPUT.obj FLAGS...` | x86 COFF + freshness receipt |
| Compile configured unit | `scripts/repo-python scripts/build.py --unit NAME` | pinned compiler, explicit unit profile |
| Strict canonical comparison | `scripts/repo-python scripts/compare-coff-function.py --unit NAME --json` | all bytes + explicit relocations |
| Cold replay accepted units | `scripts/repo-python scripts/replay-exact-units.py` | serial unique object builds; never refresh anchors automatically |
| Validate tracking | `scripts/repo-python scripts/validate-tracking.py --require-target` | ledger consistency; does not prove exactness |
| Report/generate state | `scripts/repo-python scripts/report-reconstruction-status.py`, `scripts/repo-python scripts/progress.py` | ledger-derived, not prose-derived |
| Compile/link/runtime smoke | `scripts/repo-python scripts/toolchain-smoke.py` | infrastructure only, zero reconstruction credit |
| Public CI | `scripts/repo-python scripts/ci.py` | no private target or installed proprietary tools required |

`.venv` pins pefile/capstone for optional raw-PE/disassembly experiments. The
control plane and public tests use Python's standard library. reccmp 0.1.6 and
objdiff 3.8.0 are supporting navigation/diff tools; the canonical exact gate is
the relocation-aware comparator. `objdiff.json` starts empty until reference
objects are independently prepared; its build routing is configured.

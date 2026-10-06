# Tool routing

| Need | Command | Evidence boundary |
| --- | --- | --- |
| Reproduce installed tools | `scripts/bootstrap-tools.sh` | pinned downloads/commits; ignored local tools |
| Check installed binaries/versions | `python3 scripts/doctor.py` | locked critical tool fingerprints and banners |
| Check Japanese variant provenance | `python3 scripts/verify-provenance.py --fetch` | immutable independent registry + supplied files |
| Attest exact target | `python3 scripts/verify-target.py` | SHA-256/MD5/size/PE/section hashes |
| Attest Ghidra database | `python3 scripts/ghidra.py check` | original file bytes, loaded metadata and complete mapped code |
| Inspect target semantics | `scripts/ghidra.py query/decompile` | attested read-only view; provisional meanings |
| Rank target-wide leads | `python3 scripts/ghidra.py architecture` | private metrics, no automatic source/origin promotion |
| Compile explicit probe | `scripts/compile-probe.sh SOURCE build/OUTPUT.obj FLAGS...` | x86 COFF + freshness receipt |
| Compile configured unit | `python3 scripts/build.py --unit NAME` | pinned compiler, explicit unit profile |
| Strict canonical comparison | `python3 scripts/compare-coff-function.py --unit NAME --json` | all bytes + explicit relocations |
| Cold replay accepted units | `python3 scripts/replay-exact-units.py` | serial unique object builds; never refresh anchors automatically |
| Validate tracking | `python3 scripts/validate-tracking.py --require-target` | ledger consistency; does not prove exactness |
| Report/generate state | `scripts/report-reconstruction-status.py`, `scripts/progress.py` | ledger-derived, not prose-derived |
| Compile/link/runtime smoke | `python3 scripts/toolchain-smoke.py` | infrastructure only, zero reconstruction credit |
| Public CI | `python3 scripts/ci.py` | no private target or installed proprietary tools required |

`.venv` pins pefile/capstone for optional raw-PE/disassembly experiments. The
control plane and public tests use Python's standard library. reccmp 0.1.6 and
objdiff 3.8.0 are supporting navigation/diff tools; the canonical exact gate is
the relocation-aware comparator. `objdiff.json` starts empty until reference
objects are independently prepared; its build routing is configured.

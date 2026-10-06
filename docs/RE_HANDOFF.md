# Current reconstruction handoff

## REF-005 — 2026-10-06 — tools and test review checkpoint

The exhaustive goal remains active. Added 91 individual support reviews: all
39 tooling definitions, 37 root test bodies and 15 scheduler CPU-oracle bodies.
Current inventory: 6,707 definitions; 281 terminal decisions; 6,426 pending.
Of 103 parser-gap files, three are manually reconciled and 100 remain pending.

- Removed one unreviewed phantom scheduler callback body caused by `__cdecl`
  forward declarations consuming the next class. Narrow parse-view annotation
  normalization preserves original source bytes, offsets and hashes. All 190
  earlier review IDs/body hashes remain valid. Synthetic regression passes.
- Manually reconciled conditional CLI entry declarations and inline x87 test
  instructions. Reviewed tool rejection policies and CPU-oracle limitations;
  source tests and normalized state comparisons add no native exact credit.
- Portable binary-parser CTest passes. No production source/profile/layout/
  anchor changed: existing 32 units, nine objects, 1,848 full compared bytes;
  authored exact 25 functions, 1,549 bytes. No redundant cold replay required.

Next: input's 84 definitions, then every remaining implementation and parser
gap. Native core's indexed production bodies were already reviewed; the older
REF-004 suggestion of remaining native-core owners was inaccurate. Deferred
native owner/protocol work is still individually recorded. Private evidence:
`.analysis/ref005-*`. Earlier checkpoint totals below are historical.

## REF-004 — 2026-10-06 — archive review checkpoint

The exhaustive goal is still active. All eight archive source/header files and
64 explicit definitions now have individual reviews: eighteen native cases
deferred with specific contracts and forty-six integration/test/report helpers.
No archive parser gap remains. Total terminal decisions: 190; 6,518 indexed
bodies and 103 parser-gap files elsewhere are pending.

- Recovered counted filename sum 0x456270, complete 71-byte canonical unit.
  Its caller, not the sum, selects eight independently read crypt records.
- Cold full replay: 32/32 units, nine objects, 1,848 compared bytes.
  Authored exact: 25 functions, 1,549 bytes; source-present mappings: 32.
- Independent target distinguishes signed native crypt/allocator ABI, pointer
  LZSS with persistent global dictionary, sixteen-byte ArcMngr/record storage,
  virtual stream lifetime, CRT name comparison and full locked file selection.
- Recorded extra source rejection policies, ASCII-view versus CRT comparison,
  raw-pointer versus optional/vector returns, omitted native size-out parameter
  and reference storage/global ownership changes. Do not bulk-import archive.
- All four selected unmodified production/verifier TUs compile serially after
  adding its declared CMake source-SHA macros to the diagnostic recipe. Cached
  receipts remain conservative; any source change triggers revalidation/retry.
- Added portable filename-sum cases for explicit count, embedded zeros, high
  bytes, wrap and zero-length input. Public CI and private tracking pass.

Next coherent families: native_core's remaining value/string/container/file
owners, then every remaining indexed implementation and manual parser gap.
Scheduler/runtime/archive deferred native protocols remain individually logged
follow-ups. No new approval is needed to continue the user-authorized goal.

Private evidence: .analysis/ref004-*, reference-functions/exact-replay-008.log
and compiler receipts under build/. REF-003 and earlier totals below are history.

## REF-003 — 2026-10-06 — runtime review checkpoint

The exhaustive user goal remains active. Every existing implementation needs
an individual decision; record difficult cases and continue without a module
default rejection. Next: archive source/ownership and its tests, followed by
every remaining indexed implementation and parser gap.

- Added explicit README credits to Oracatt/Touhou20 and N0zoM1z0/th095.
- All nine runtime_core source/header/include files and 67 explicit bodies
  reviewed: nine absorbed reference bodies, twenty-four native deferred cases,
  thirty-four integration/test helpers. Each decision binds its own body hash.
- Total explicit decisions: 126; 6,582 indexed bodies still pending.
- cpu_compare.cpp's single WINAPI annotation parse gap manually reconciled
  against the full file and five indexed definitions. Public hash/count-bound
  reconciliation ledger leaves 103 of 104 gap files pending.
- Eleven new full canonical units: LockRegistry flag members, custom PMR
  constructor/destructor/equality, TaskInfo destructor/virtual wrappers/helpers,
  and Worker construction. Independent file-backed RTTI/vtable and separately
  queried library/node callees establish all anchors before canonical replay.
- Cold complete replay: 31/31 units, eight objects, 1,777 compared bytes.
  Authored exact: 24 functions, 1,478 bytes; source-present mappings: 31.
- Three exact empty/defaulted PMR/TaskInfo lifetime contributions have pending
  authored/compiler origins and no authored credit, in addition to two pending
  float-view functions and two excluded STL equivalents.
- Worker destructor and custom PMR allocation/deallocation remain declared
  without definitions. These are partial owners, not complete linked services.
- Deferred concrete contracts include checked versus unchecked indexing,
  fixed native globals, allocator receiver/deleting flags, CRT new-handler
  paths, native variadic logging and conversion-failure behavior, and graphics
  0x4D9E30 owning its Worker at +0xD90. Read the individual review rows.
- Portable UBSan tests cover registry representation-preserving toggles and
  nullable TaskInfo callback masking, plus all previously accepted components.
- The installed D: runtime play aid matches the maintained no-hit scripts;
  hits return before effects/death. Actual hit playthrough remains unverified.

Private evidence: .analysis/ref003-*, reference-functions/exact-replay-007.log
and build object receipts. Public CI and private tracking gates pass. No
reference implementation text or executable bytes were imported publicly.
Read REFERENCE_FUNCTION_REVIEW.md and SOURCE_MAP.md; do not equate this bounded
runtime checkpoint with completing the exhaustive reference goal.

## REF-002 — 2026-10-06 — exhaustive review remains active

The user clarified that every existing reference implementation must receive
an individual review. Easy exact recoveries should be absorbed immediately;
difficult cases should record evidence and remaining work, then continue.
Do not treat REF-001's file/module scan as satisfying this requirement.

- Index: 916 nongenerated C/C++ files; 6,708 definitions, including 4,193
  reconstruction candidates. Role/address hints are provisional, not mappings.
- Parser gaps in 104 files require manual reconciliation. Deleted declarations
  and generated Ghidra exports are excluded; defaulted bodies and lambdas remain.
- Explicit decisions cover 59 native-core/export/scheduler bodies. The other
  6,649 indexed bodies are pending, as are parse-gap reconciliations.
- Timer mode now matches through its natural two-bit field representation.
- Timer add/tick restore original receiver/global-clock/helper-call ABI and
  match all 295/324 bytes, including eight/ten independent relocations.
- Two float receiver helpers match 16/35 bytes. Their enclosing owner/origin
  remains pending, so they receive no authored progress credit.
- Scheduler: all 35 indexed implementation bodies have individual decisions:
  eleven absorbed exact, eighteen deferred nonexact, six integration helpers.
  Link construction/insertion and eight node operations restore receiver ABI.
- Cold replay: twenty units, four objects, 1,450 bytes. Authored exact: sixteen
  Timer/FunctionChain functions, 1,231 bytes; source-present mappings: twenty.
- User-requested runtime invincibility launcher is installed beside the
  D: game. Hit entry now returns before any effects; the earlier stock-only
  mode is superseded. Revised Windows launch/readback passes; file unchanged.
  See RUNTIME_PATCH.md; no hit/respawn playthrough or reconstruction credit.
- README now follows TH095: supplied title image centered at width 640,
  followed by the separate 560x176 progress SVG.
- Private original-reference TU probes cover scheduler/archive/runtime; build
  include dependencies and verifier hash macros need distinct recipe handling.

Read `REFERENCE_FUNCTION_REVIEW.md`. Use `index-reference-functions.py --check`
and `report-reference-functions.py` through `scripts/repo-python`; explicit
review outcomes bind to body hashes. Reference compiler probes stay serial and
never confer semantic or exact credit. Continue runtime/archive and every
remaining implementation; scheduler constructor/EH, iterator/allocator aliases
and dispatch are specifically recorded follow-ups rather than accepted source.
No approval or new task is needed to keep progressing.

Private evidence: `.analysis/ref002-*`, `.analysis/reference-functions/`.
The following records are historical checkpoints.

## REF-001 — 2026-10-06

The reference-wide review and first independently verified absorption are
recorded in `REFERENCE_REVIEW.md`. The pinned local checkout is
`_reference/Touhou20`, explicitly ignored and blocked from public CI's tracked
tree. The public repository is https://github.com/N0zoM1z0/th20, with TH095-style
README/progress, About and topics. Maintained prose is English; official names
and original evidence retain their language. Commit subjects use
`gpt-6.1-sol: <description>`.

All Python invocations now go through `scripts/repo-python`, modeled on TH10.
Shell launchers and public CI use the same entry point; it prefers the pinned
local environment and supports standard-library-only fresh public checkouts.

- All 10,822 reference files audited; 55 group dispositions account for them.
- Same target hash: registry/package identification is 1.00a, embedded
  title/replay labels are 1.00c. Both are verified in target provenance.
- 153 diagnostic sites in 124 functions independently accepted as routing
  evidence, with no mapping/source/exact credit inherited.
- Maintained source: `src/Random.*` and `src/Timer.*`; five source-present mappings.
- Four canonical units replay complete contributions from two cold objects.
- Authored exact credit: two Timer functions, 131 bytes. RNG's two exact
  equivalents are excluded as MSVC STL; __aullshr is excluded as CRT.
- Timer mode: natural source, behavior checked, three differing bytes; no credit.
- Current origin review: three authored, three exclusions, 6,922 pending.
- Public semantic/synthetic CI, private target/tracking/Ghidra checks, reference
  byte/freshness audit and independent source-diagnostic checks pass.
- Portable reference binary-parser and archive CTests pass. Linux cannot link
  its Windows-wmain archive verifier; no game/runtime credit follows.
- No whole-game build/runtime or reference implementation bulk import.

Next coherent family: Timer delta/tick and global clock/rounding, or enclosing
RNG seed/distribution/storage ownership. Other candidate families are indexed
in the reference review; avoid inheriting its service-suffixed layouts or
historical behavior counts. Replay existing units after any shared-source change.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/review-reference.py
scripts/repo-python scripts/ghidra.py architecture
scripts/repo-python scripts/import-reference-leads.py --check
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
```

Private evidence: `.analysis/reference-review/`, `.analysis/reference-core*`,
`.analysis/reference-rng-anchor*`; receipts are beside `build/Random.obj` and
`build/Timer.obj`. The bootstrap record below is historical.

## BOOT-001 — 2026-10-06

The TH20 control plane and local build/analysis environment are initialized.
The user selected existing **Japanese v1.00a Steamless** as the sole exact
oracle. The Steam-original backup remains provenance evidence. This decision
is persistent; do not ask again or silently substitute the non-Steam variant.

- Target SHA-256: `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
- Repository: `/home/pentester/coding/codex_ida/th20-reconstruction/th20`.
- Supplied files: `../game_exe/`; ignored target symlink `resources/th20.exe`.
- Analysis: independent Ghidra 12.1.3 `TH20` project, fully target-attested.
- Inventory: 6,928 provisional functions, all origins/boundaries awaiting review.
  Architecture export has 22,731 direct call edges, 11,307 global-reference rows
  and 711 string-reference rows; these are routing evidence only.
- Mapping/source/exact: **0 / 0 / 0**; canonical manifest and claims are empty.
- Candidate compiler: MSVC 19.44.35211 x86, linker 14.44.35211.0,
  toolset directory 14.44.35207, SDK 10.0.26100.0, D3DX 9.29.952.8.
  Game compiler build and flags remain unproved; see `ORACLES.md`.
- Shared analysis-tool symlinks point at TH095's `.tools/`. Compiler/SDK/Wine
  and private Ghidra state are local to TH20. TH095 source, ledgers, database,
  environment and protected untracked files were not changed.
- Optional project-agnostic web bridge is prepared with a TH20 env template
  and launcher. No listener, user service or external endpoint was published.

## Validation evidence

Passed target/provenance verification, locked tool fingerprints/version banners,
Ghidra check plus bounded entry disassembly/decompilation and architecture
export, tracking/build-graph/progress gates, synthetic exact-oracle tests and
public CI. The target verifier rejects the Steam-original backup as a substitute;
the Ghidra attestation rejects a deliberately wrong expected target hash without
mutating the database or executing a query. Exact replay reports zero configured
units and does not manufacture matching credit.

The cold compiler probe passed x86 COFF, Win32/DirectX C++ headers, PE32 linker
and Wine/D3DX runtime checks. Infrastructure probe hashes at this checkpoint:

- Source: `f043a7f400b12088efe5cab8ca30e67c8a7803070fa6e0be022f340a2f5cce0a`.
- Object: `3053df6b6a59a90c3514c2445542530581691acec2058e550851e6227e87d27d`.
- PE32 executable: `9e8c92f9d647ac954ebf1fe3234087a7de81bd3004b6454029cc200277b53c02`.

Objects, debug records, raw decompilation, downloaded registry/manifests and
full command receipts stay in ignored `build/` and `.analysis/bootstrap/`.
The smoke executable is a console infrastructure probe, not a game build.

## Resume

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/ci.py
```

Read `AGENTS.md`, `RE_WORKFLOW.md`, `ARCHITECTURE.md`, `ORACLES.md`,
`SEMANTIC_RECONSTRUCTION.md` and `SOURCE_MAP.md` first. Next lane: one bounded
owner/ABI family from the provisional inventory, using independent target-local
evidence and clean compiler probes. Do not project TH095 roles/layouts/flags
onto TH20. Maintain one writable session and serial compiler/Ghidra access.

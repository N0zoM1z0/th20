# REF-044: tooling, historical bridges and exhaustive review closure

The pinned reference at `011aa029d1dac51578107bc98a0006bd750e453c` now has an
explicit terminal decision for all **6,945 indexed implementation bodies**.
All **113 files with parser gaps** have individual manual reconciliations.
This completes the requested review of the existing reference implementations;
whole-game reconstruction, ownership and native behavior remain open.

The last coherent batch reads **184 bodies across 46 files**, including Python
module execution, nested functions and lambdas, PowerShell modules and all
historical C++ bridge/test bodies. All 184 are support-reviewed. These scripts
and instrumented adapters supply no additional complete native exact unit.
Original reference scripts, report writers, PE builders and Windows drivers
were read without executing or importing them. No reference source or generated
machine-byte arrays were copied into maintained production.

## Coverage and correction

| Final batch | Bodies |
| --- | ---: |
| Root PowerShell build recipes | 5 |
| Historical C++ bridge and ABI/link tests | 36 |
| Incremental Python verification | 27 |
| Source audit and registry scripts | 39 |
| Platform evidence exporter | 1 |
| Root test scripts | 10 |
| Asset, binary, packaging and oracle tools | 66 |
| Total | 184 |

Manual reading found that the original parser omitted the naked MSVC
`invoke_probe` definition at `incremental/native_bridge/abi_check.cpp:29-63`.
Offset-preserving normalization of the three historical files' calling
conventions and block/line assembly recovers it. The original 6,944 IDs and all
their fields, including original CRLF body/file hashes, are unchanged. Exactly
one body is added, bringing the authoritative denominator to 6,945.

Original grammar diagnostics remain visible for these three files, even when
definitions are recovered through the normalized parse view. The final 16 gap
files contain 119 sites: nine PowerShell inventory sites, 55 historical MSVC
sites, four program-entry declaration/annotation sites and 51 sites in the
50-entry callback initializer fragment. Each whole file and site was manually
reconciled. The PowerShell source-game recipe's two named helpers,
`Get-SourceGuard` and `Read-SourceProject`, were fully read inside its module
review. The callback fragment defines no functions; its actual template owners
were reviewed in the earlier Sprite batch.

A synthetic CRLF parser regression checks recovery of a naked invoker and line
assembly, exact original body hashes, file hashes and retained grammar errors.
Discovery is still separate from a manual review decision.

## Findings and evidence boundaries

The seven bridge exports increment counters and adapt recovered RNG/Timer
operations to DLL calling conventions. Their underlying natural core source
already has canonical units. Instrumentation, host-relative clock access,
`DllMain` and export adapters differ from original function bodies and receive
no second exact credit.

The ABI harness checks selected prepared objects, returns, stack/nonvolatile
registers and FP controls. The separate relocated link harness maps PE copies,
rewrites seven bridge imports and tests two bases; its preferred-base lane can
skip, and its invoker checks fewer preserved registers than the ABI harness.
Neither executes the original entry point as a complete loader/startup oracle.
FP status flags, exceptions and integrated gameplay remain outside acceptance.

The historical playable builder copies the retained original engine and adds
seven DLL tail-jump replacements. Its approved-change, relocation, import and
checksum checks verify that hybrid artifact's construction. They do not produce
an independent source game. Source/ASan build recipes and snapshot tools cover
selected source-file hashes and MSBuild compile/resource project edges; they
do not close all include, toolchain, linker and original lifetime dependencies.

Runtime capture compares sparse shared replay/stage/frame keys and selected
scalars. Missing frames are omitted, duplicate keys can overwrite, reads are
asynchronous and comparison-time filesystem hashes do not attest recording-time
executables. Some summary fields are literal claims rather than derived checks.
These observations do not prove all-frame, controls, audio or rendered output
equivalence.

The opcode auditor checks concrete source cases, adapter routes, stock resource
histograms and original selector tables. This is static dispatch coverage. The
ETEX13 auditor uses literal operands and local CFG dominators to exclude a
specific command at two stock creation bodies under explicit valid-state and
sequential-entry assumptions. Global aliases, external reentrancy, threads and
the original invalid-copy case remain separate native questions.

Registry writers rebind preselected archive, scheduler and program-entry
associations. They retain scoped algorithm/component/compilation evidence and
unresolved dependencies. A passing or current registry entry is not a whole
native function byte comparison. Binary exporters likewise use provisional
linear windows, decompiler range metadata or the next known entry; none supplies
an automatically accepted complete extent or original semantic ownership.

Asset recovery compares archive entries, duplicate payloads, script roundtrips
and WAV-decoded PCM. Exact resource bytes do not establish exact C++ functions
or native playback/resource lifetimes. Generated callback/style data was
reviewed as evidence, without importing target literals. The range downloader
resumes by size and has an optional final digest; the toolkit recipe has an
unhashed auxiliary archive. These tools were not adopted as our attested build
or Ghidra wrappers.

## Final ledger and validation

| Reference disposition | Bodies |
| --- | ---: |
| Absorbed into canonical exact source | 114 |
| Library exact association | 3 |
| Reviewed, nonexact and recorded | 1,877 |
| Reviewed support/test/tool implementations | 4,951 |
| Pending | 0 |
| Total | 6,945 |

These are reference-body decisions. A reference helper can map to several
canonical members, several bodies can share one component, and scaffolding has
no original native entry. They must not be summed as reconstructed native
function counts or interpreted as a game-completion percentage.

The maintained source and probes are unchanged from REF-043. All **241 complete
canonical units** replay with zero differences using current hash-verified
cold-build receipts: **57 objects / 18,320 disjoint comparison bytes**. Source
presence is 241; authored exact credit remains **57 functions / 4,074 bytes**,
with **180 origins pending** and four separate library comparisons. Earlier
reference diagnostic objects remain stale unless independently rebuilt.

The authoritative public records are `reference-function-index.csv`,
`reference-source-files.csv`, `reference-function-reviews.csv` and
`reference-parse-gap-reviews.csv` under `config/`. Private full-reading notes,
hash-bound inventories, canonical results and one-shot registration receipts
remain under `.analysis/ref044-*`. Registration writers must never be rerun.

Validation checks the clean pinned reference, unchanged old identities, exactly
one recovered implementation, all body/file bindings, all grammar decisions,
target/Ghidra attestation, current canonical replay, public tests and tracking/
progress gates. Review closure does not change compiler-wide assumptions or
claim a linked, playable independent game.

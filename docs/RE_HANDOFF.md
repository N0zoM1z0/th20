# Current reconstruction handoff

This is the current state, not a cumulative session log. Historical checkpoints
are preserved in Git and the [evidence index](EVIDENCE_INDEX.md). Use generated
[progress](PROGRESS.md) and the ledgers for live counts.

## Verified state

The sole target is Japanese v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its embedded title/replay label is 1.00c; this is the same executable, not a
second target. The Steam-original backup is provenance evidence. See
[target provenance](TARGET_PROVENANCE.md).

The maintained graph contains 889 physical strict units, 163 comparison objects,
167,588 disjoint comparison bytes and 897 source-present mappings. Eight
mapped whole functions remain nonexact. Authored coverage is separately 175 exact
functions / 46,728 bytes, with 184 confirmed authored origins. File::clear and
the two Renderer texture creators and EnemyMeshOwner allocation are reviewed
authored but source-absent.
The pinned reference
has 6,945 terminal implementation reviews and all 113 parser-gap files reconciled.
These figures do not imply whole-game linkage or playable behavior. Percentages
over currently reviewed authored functions do not measure the whole-game 95%
byte-exact objective.

CORE/EXACT-137 accepts the complete 213-byte parameterized RenderMesh factory.
Natural by-value SDK forwarding and the public-class declaration reproduce
compiler initialization under the provider's C++17 profile. All 93 EH support
bytes and 39 folded SDK/compiler helper bytes independently replay without extra
coverage. Actual Enemy publication establishes authored origin. All 228 prior
affected units remain exact after 36 fresh serial builds; 127 objects are reused.
See [allocation evidence](MESH_ALLOCATION_EXACT_RECONSTRUCTION.md).
Public CI passes all 81 tests in 415.228 seconds; three focused UBSan fixtures
and two ASan/UBSan lifecycle fixtures also pass. Private validation receipts are
in `.analysis/core137-gates.json`.
Eighty superseded object/receipt files are retired after original-input
preservation. All 889 units strictly replay afterward from existing objects;
all 326 protected hashes remain unchanged, with zero cleanup compiler calls.
The final audit is `.analysis/core137-final-audit.json`.

## Current local products

The manifest owns all current object paths. Its 163 canonical objects are under
`build/core127-canonical/` (1), `build/core128-canonical/` (1), `build/core129-canonical/` (5),
`build/core130-canonical/` (9), `build/core131-canonical/` (2), `build/core132-canonical/` (2),
`build/core133-canonical/` (11), `build/core134-canonical/` (5), `build/core137-canonical/` (36),
`build/maintenance124-canonical/` (91). Protect their 163 sibling receipts as well.
The source freeze is `.analysis/core137-final-frozen-source.json`; fresh affected
results are `.analysis/core137-affected-results.json.gz`. The new factory and
complete support are recorded in `.analysis/core137-new-exact-results.json` and
`.analysis/core137-support.json`.

All prior object/receipt pairs and authentic source versions were verified before
editing and archived in `.analysis/core137-pre-header-inputs.json.gz`. Preserve
the historical maintenance125 and CORE127 through CORE136 original-input archives.
The current retirement archive references shared original inputs by SHA and
retains additional private probe inputs inline; preserve both original and
retirement archives. Current protected products, retirement inventory and replay
are `.analysis/core137-protected.json`, `.analysis/core137-cleanup.json` and
`.analysis/core137-post-cleanup-results.json.gz`; retired inputs and receipts are
in `.analysis/core137-retired-inputs.json.gz`. Cleanup never rewrites receipts
or cold-builds an unchanged source graph.

Retain original compiler input archives, failed experiment evidence, native
exports and the locked target/tools/Ghidra/reference. Old receipts describe
their original input closures; never rewrite them to imply fresh verification.
Retire superseded builds only after replacement verification and protected hash
checks, as specified in [the workflow](RE_WORKFLOW.md).

## Next reconstruction work

File::clear at 0x0044AB00 is a reviewed 284-byte authored body with no maintained
implementation or source mapping. It requires actual Renderer detachment/texture
retirement and the +6C buffer producer. File destruction now invokes that real
interface and then destroys stem/filename through the complete accepted SDK chain.
Keep resource-absent fixture clears distinct from loaded-resource retirement.
Scalar File allocation retains its
existing profile without /EHsc; adding /EHsc emits 129/native67. File construction
exception declarations are unchanged. Do not change them merely to shorten code.

Renderer texture creators at 0x0044C0B0 / 0x0044C150 are now reviewed authored,
with complete 155-/139-byte native bodies but no maintained source or exact unit.
Actual Graphics device/format accessors are available; resolve the complete
Renderer receiver before implementing its members. Preserve nonzero HRESULT
handling, mode bits and full byte-size arithmetic. The format selector's predicate
is an observed native constant zero, not a configuration binding or an added
input-domain exception. Its accessor aliases do not change existing physical
unit ownership or establish a unique original source origin.

ProgressSaveManager constructor and commit at 0x0050E5D0 and 0x0050F660 remain
whole nonexact (198/native199 and 68/native70), totaling 269 native bytes. Native
post-call NOP differences are unresolved. C++17 is inapplicable to this owner
because Worker contains actual std::jthread. The /sdl, /Z7, /fp:strict and /Ob1
lifetime trials do not close these roots; do not repeat unchanged trials or
insert padding/change actual void contracts. Load and destruction are now exact.
Use the ECL C++17 and load /sdl results as bounded profile leads, not global flags.
Other open mapped roots include Enemy mesh deformation, compression
and allocation/removal factories. Do not repeat unchanged old trials.

Node and Region scalar allocation are now exact with unchanged shared new T
and actual constructor bodies. Preserve the class/public declarations and
complete typed caller replay. Struct C++17, brace/value, defaulted/in-class
initializer and constructor-visibility Node probes do not explain the target.
Unlocked scheduler removal remains whole 156/native162; global HitCtrlInf creation
remains whole 82/native92. Both retain unobserved native resets; do not introduce
dead resets for emission. The whole 1,707-byte damage query remains unimplemented;
its unconsumed counter and heap release before later reads remain open.

Animation+4A0 bits 4..5 now have an independently consumed two-bit view; their
renderer state meaning remains open. Existing byte/RHS/8-bit literal and /Os
OR probes do not explain grid emission; the actual field assignment does.
The generic CORE095 Angle subtraction and XY norm origins remain pending.
Whole Enemy deformation is now reviewed authored but remains 1548/native1649;
its 101-byte local conversion has no observed direct byte read or address
formation. Do not add that unused calculation or the compressor's unobserved sum
merely for emission. EnemyMeshOwner destruction and nested release are exact;
its scalar allocation at 0x0048B010 remains source-absent, with seven native
preclear stores unexplained by natural57/119/129-byte probes. The four-argument
RenderMesh factory at 0x004712D0 is now exact; its original whole Enemy caller
and outer EnemyMeshOwner creation remain open.

The descriptor arrays and sprite binding are now available for the real loading
protocol; they do not establish mutable ANM packet/buffer ownership or loaded-File
clearing. The +6C word remains opaque: bounded operand navigation finds only its
three clear accesses and does not identify an allocation producer.

Continue coherent core protocols around the whole Animation VM at `0x0042B5D0`.
Its full extent is 40,752 bytes: 39,470 code, two alignment bytes, 644 pointer-table
bytes and 636 index bytes. Retain all 161 case heads / 636 selections and the
24 internal jumps omitted by Ghidra function membership. No partial VM credit
has been admitted. The signed opcode domain is -1 through 634.

The five indirect calls have established signatures: one virtual update on the
eight-byte callback base, one unary cdecl entry callback at +5DC, and three cdecl
script-selection calls at +5E0. The remaining concrete owners and lambda adapters
are unresolved. Native `EffectMenuWindowInf` is directly derived, 72 bytes; its
constructor exception contract and drawing dependencies remain open.

Resolve the actual Renderer owner before introducing its maintained declaration.
The native allocation is `0x7D40E94` bytes. The interval +6000DFC..+6000DFF between
an inline Animation and the next scalar is unresolved. No observed direct access
does not prove padding; allocation alignment does not explain it by itself.
Other open boundaries include mutable ANM packet/buffer lifetime, File VM creation,
global startup and full rendering/resource ownership. The whole Enemy dispatcher
at `0x0048C010` also remains open; the whole ECL Runtime tick is already exact.

## Resume discipline

Follow [AGENTS.md](../AGENTS.md) and run the documented preflight. Use
`scripts/repo-python` for every Python invocation and `scripts/ghidra.py` for
attested Ghidra work. Keep one writable session, heavy work serial at nice 15 /
CPU 3, and bounded Ghidra memory. No REA or delegated reconstruction. Preserve
English maintained prose, the official Japanese title and the commit prefix
`gpt-6-astra-medium:`. Keep `config/claims.csv` header-only.

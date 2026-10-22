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

The maintained graph contains 891 physical strict units, 164 comparison objects,
167,737 disjoint comparison bytes and 899 source-present mappings. Eight
mapped whole functions remain nonexact. Authored coverage is separately 181 exact
functions / 47,071 bytes, with 190 confirmed authored origins. File::clear, the two
Renderer texture creators and the full AnimationFile
spawn protocol are reviewed authored but source-absent.
The pinned reference
has 6,945 terminal implementation reviews and all 113 parser-gap files reconciled.
These figures do not imply whole-game linkage or playable behavior. Percentages
over currently reviewed authored functions do not measure the whole-game 95%
byte-exact objective.

CORE/EXACT-141 accepts the complete 67-byte Pbg::File scalar allocation
factory. PbgFileAllocation.cpp owns its sole instantiation under the verified
C++20 profile without /EHsc; PbgFile.cpp retains its original method/destructor
profile. The shared allocation body, File constructor and exception declarations
are unchanged. All 890 prior units strictly replay after the new-source snapshot
migration, and all 232 bytes of Pbg EH/deleting/wide/initialization support pass.
The folded initialization helper adds no duplicate coverage. Authored/library
provenance for this factory remains pending. See
[allocation evidence](PBG_FILE_ALLOCATION_PROFILE.md).

Public CI passes all 81 tests (335.274 seconds). Cleanup retires 330 replaced
object/receipt files (9,633,608 bytes), preserving authentic input closures.
All 891 units strictly replay afterward using existing objects; all 328 current
product hashes and 279 source hashes remain unchanged. No cleanup compilation
was performed. Nineteen empty build directories were also removed.

## Current local products

All 164 canonical objects and their sibling receipts are under
`build/core141-canonical/`; the manifest is authoritative. The final source
freeze is `.analysis/core141-final-frozen-source.json` (279 paths). The original
163-object migration is recorded in `core141-affected-results.json.gz`, with the
final PbgFile-only refresh in `core141-pbg-refresh-results.json`. New-factory
acceptance is `core141-new-exact-results.json`; support and contract audits are
`core141-support.json`, `core141-graph-audit.json` and `core141-section-audit.json`.
These private names are relative to `.analysis/`.

Retain the nine private investigation object/receipt pairs still at the build
root: core103-QueryProtocol-v5 and the core109..core113 sound probes. They support
unresolved query/sound ownership and dispatcher work, not canonical exact credit.
See [damage query](DAMAGE_QUERY_PROTOCOL_RECONSTRUCTION.md) and
[sound evidence](SOUND_PROTOCOL_RECONSTRUCTION.md). Their protected hashes are
`.analysis/core141-retained-private-products.json`.

Authentic old inputs and receipts were archived before editing in
`.analysis/core141-pre-header-inputs.json.gz`. The interim PbgFile input closure
is `core141-intermediate-inputs.json.gz`; the first source snapshot remains
`core141-first-frozen-source.json`. Retain these and the earlier original-input
archives, native exports, rejected probes and locked tools/reference/target.
Never rewrite immutable receipts or cold-build an unchanged graph for cleanup.
Final validation, protected retirement and full existing-object replay are
recorded in `.analysis/core141-gates.json`, `core141-retirement-plan.json`,
`core141-cleanup.json` and `core141-post-cleanup-results.json.gz`. Retired original
closures are preserved in `core141-retired-inputs.json.gz`.

## Next reconstruction work

AnimationFile::spawn(full protocol) at 0x00450CB0 is a reviewed 922-byte authored
body with no maintained source or canonical unit. Preserve optional output
publication before the requested-stem check, hidden handle return, actual flags
and full VM/Renderer registration dependencies. Its exact convenience wrappers
do not close the producer. Resolve the real Renderer owner before implementing
this method; current fixtures explicitly capture this boundary.

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
merely for emission. EnemyMeshOwner allocation at
0x0048B010, defaulted construction, destruction and nested release are now exact.
The four-argument RenderMesh factory at 0x004712D0 is also exact. Preserve the
shared empty-pack value-initialization model and the actual Angle exception
contract. The enclosing whole Enemy caller remains open.

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

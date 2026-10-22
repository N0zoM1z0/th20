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

The maintained graph contains 861 physical strict units, 163 comparison objects,
165,103 disjoint comparison bytes and 869 source-present mappings. Eight
mapped whole functions remain nonexact. Authored coverage is separately 158 exact
functions / 44,627 bytes, with 163 confirmed authored origins. File::clear is
reviewed authored but remains source-absent. The pinned reference
has 6,945 terminal implementation reviews and all 113 parser-gap files reconciled.
These figures do not imply whole-game linkage or playable behavior. Percentages
over currently reviewed authored functions do not measure the whole-game 95%
byte-exact objective.

CORE/EXACT-132 accepts nine complete File/Animation lifetime roots, adding 866
physical comparison bytes. Ordinary File destruction and real template-array
allocation/release retain the two string members, actual Animation lifetime,
array cookies, reverse destruction and distinct lock ordering. Fifteen origin
decisions identify eleven authored, two STL and two compiler functions; File
clear remains unimplemented and receives no source or exact credit.
All 128 previous affected units pass after 31 objects build once, with 132
unaffected objects reused. Complete EH support and the extended actual-owner
lifetime fixture pass. All 80 public tests pass in 342.394 seconds; the private
ASan/UBSan lifetime fixture passes in 8.546 seconds. After retirement, all 861
units strictly replay with all 326 current object/receipt hashes unchanged and
no compiler invocations. See
[File/template lifetime evidence](ANIMATION_FILE_LIFETIME_RECONSTRUCTION.md).

## Current local products

Canonical paths in `config/match-units.toml` use
`build/maintenance124-canonical/`, `build/core127-canonical/EclLoaderBuffer.obj`,
the two objects under `build/core128-canonical/`, retained objects under
`build/core129-canonical/`, `build/core130-canonical/`, `build/core131-canonical/`
and 31 objects under `build/core132-canonical/`.
Protect all 163 objects and
sibling receipts. The current source freeze is
`.analysis/core132-final-frozen-source.json`; affected strict results are
`.analysis/core132-affected-results.json.gz`, with new roots separately in
`.analysis/core132-new-exact-results.json` and complete support in
`.analysis/core132-eh-support.json`. Post-retirement results are
`.analysis/core132-post-cleanup-results.json.gz`.

Original inputs for the reused maintenance124 objects remain preserved in
`.analysis/maintenance125-original-inputs.json.gz`; core127/core128/core129 proofs
protect their newer objects. All 163 old pairs were verified before editing;
the 31 replaced objects' authentic input versions and original receipts are in
`.analysis/core132-pre-header-inputs.json.gz`. Original CORE130/131 archives remain
preserved for their historical products.
Retired inputs and immutable receipts are in
`.analysis/core132-retired-inputs.json.gz`; current protected hashes and the
66-product / 2,468,065-byte removal record are in
`.analysis/core132-protected.json` and `.analysis/core132-cleanup.json`.
No current canonical products are removed or rebuilt for cleanup.

Retain original compiler input archives, failed experiment evidence, native
exports and the locked target/tools/Ghidra/reference. Old receipts describe
their original input closures; never rewrite them to imply fresh verification.
Retire superseded builds only after replacement verification and protected hash
checks, as specified in [the workflow](RE_WORKFLOW.md).

## Next reconstruction work

File::clear at 0x0044AB00 is a reviewed 284-byte authored body with no maintained
implementation or source mapping. It requires actual Renderer detachment/texture
retirement and the +6C buffer producer. File destruction now invokes that real
interface and then destroys stem/filename. Keep resource-absent fixture clears
distinct from loaded-resource retirement. Scalar File allocation retains its
existing profile without /EHsc; adding /EHsc emits129/native67. File construction
exception declarations are unchanged. Do not change them merely to shorten code.

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
Five CORE095 exact support origins remain pending alongside whole Enemy
deformation. Do not add its unused radius conversion or the compressor's
unobserved sum merely for emission.

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
`gpt-6.1-sol:`. Keep `config/claims.csv` header-only.

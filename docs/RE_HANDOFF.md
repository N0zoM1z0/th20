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

The maintained graph contains 844 physical strict units, 161 comparison objects,
162,849 disjoint comparison bytes and 857 source-present mappings. Thirteen
mapped whole functions remain nonexact. Authored coverage is separately 97 exact
functions / 31,370 bytes, with 101 confirmed authored origins. The pinned reference
has 6,945 terminal implementation reviews and all 113 parser-gap files reconciled.
These figures do not imply whole-game linkage or playable behavior. Percentages
over currently reviewed authored functions do not measure the whole-game 95%
byte-exact objective.

CORE/EXACT-127 accepts complete ECL registration and fifteen supporting physical
functions, adding 1,874 comparison bytes. Unsigned file-relative address rebasing
and a per-source C++17 profile explain the complete registration/insertion path.
Thirteen origin decisions separately identify the custom name predicate, eleven
SDK functions and an existing compiler initializer. Eleven folded aliases pass
without duplicate credit. All 844 strict units and all 80 public tests pass
(322.805 seconds). Only the affected EclLoaderBuffer object is rebuilt; the
other 160 objects retain immutable receipts. See
[registration evidence](ECL_BUFFER_REGISTRATION_EXACT_RECONSTRUCTION.md).

## Current local products

Canonical paths in `config/match-units.toml` use
`build/maintenance124-canonical/` plus the new
`build/core127-canonical/EclLoaderBuffer.obj`. Protect all 161 objects and sibling
receipts. The current source freeze is `.analysis/core127-final-frozen-source.json`;
strict results are `.analysis/core127-exact-results.json.gz` and post-retirement
results are `.analysis/core127-post-cleanup-results.json.gz`.

Original inputs for the reused 160 objects remain preserved in
`.analysis/maintenance125-original-inputs.json.gz`. The replaced EclLoaderBuffer
object's original inputs were verified before editing and preserved in
`.analysis/core127-original-inputs.json.gz`. Retired object/probe inputs and
immutable receipts are in `.analysis/core127-retired-inputs.json.gz`; protected
hashes and removal records are `.analysis/core127-protected.json` and
`.analysis/core127-cleanup.json`. The superseded core126 object was retired after
replacement verification. No current canonical products were removed or rebuilt
for cleanup.

Retain original compiler input archives, failed experiment evidence, native
exports and the locked target/tools/Ghidra/reference. Old receipts describe
their original input closures; never rewrite them to imply fresh verification.
Retire superseded builds only after replacement verification and protected hash
checks, as specified in [the workflow](RE_WORKFLOW.md).

## Next reconstruction work

Use the C++17 emission result as a bounded profile lead for another coherent
nonexact protocol, rather than assuming global flags. The four ProgressSaveManager
constructor/destructor/load/commit roots at 0x0050E5D0, 0x0050E990, 0x0050F3B0 and
0x0050F660 remain nonexact and total 1,130 native bytes. Review their existing
evidence before fresh probes; preserve one natural source body and actual owners.
Other open mapped roots include Enemy mesh deformation, grid strips, compression
and allocation/removal factories. Do not repeat unchanged old trials.

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

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

The maintained graph contains 827 physical strict units, 160 comparison objects,
160,921 disjoint comparison bytes and 842 source-present mappings. Fifteen
mapped whole functions remain nonexact. Authored coverage is separately 94 exact
functions / 30,383 bytes, with 98 confirmed authored origins. The pinned reference
has 6,945 terminal implementation reviews and all 113 parser-gap files reconciled.
These figures do not imply whole-game linkage or playable behavior.

CORE/EXACT-123 admitted nine whole callback roots (414 bytes) and independently
verified five folded aliases without duplicate physical credit. The actual
eight-byte callback base has five virtual slots. Real virtual destruction runs
outside allocator lock 1. Signed Bullet getters and the script callback preserve
negative-sentinel bypass and full-width results. The 149,903-case callback
fixture and all 79 public tests pass at that checkpoint. See
[callback evidence](ANIMATION_CALLBACK_RECONSTRUCTION.md).

The maintenance batch renames the unsupported `Hit` callback label to
`AnimationEntryCallback`, removes an unused forward declaration and corrects
stale source comments. It adds no exact units or authored credit. All 827 strict
units pass after 160 fresh object builds, including independent checks of the
five folded callback aliases and full slot table. All 79 public tests pass
(339.559 seconds). Protected cleanup replays the complete graph without another
compiler invocation. The local receipt is `.analysis/maintenance124-resume.json`.

## Current local products

Canonical object paths are authoritative in `config/match-units.toml` and now
use `build/maintenance124-canonical/`. Protect each object and sibling receipt.
The maintenance source freeze is
`.analysis/maintenance124-final-frozen-source.json`; complete results are
`.analysis/maintenance124-exact-results.json.gz`. The original CORE123 compiler
inputs were verified and archived in
`.analysis/maintenance124-original-inputs.json.gz` before source changes.

Retain original compiler input archives, failed experiment evidence, native
exports and the locked target/tools/Ghidra/reference. Old receipts describe
their original input closures; never rewrite them to imply fresh verification.
Retire superseded builds only after replacement verification and protected hash
checks, as specified in [the workflow](RE_WORKFLOW.md).

## Next reconstruction work

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

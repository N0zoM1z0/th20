# Independent oracles and acceptance

## Target identity

The user-selected Japanese v1.00a Steamless executable is the sole comparison
target. `config/target.toml` locks its whole-file identity, PE mapping and section
hashes. The Steam-original backup is provenance evidence, not a substitute for
comparison bytes. See [target provenance](TARGET_PROVENANCE.md).

Every Ghidra wrapper call verifies the local target and the database's source
bytes, identity, PE mapping, six samples and complete mapped .text hash. This
attestation establishes identity, not the correctness of inferred names,
signatures or function extents. Complete PE control flow must reconcile those.

## Compiler and ABI

The installed candidate is MSVC 19.44.35211 x86 / linker 14.44.35211.0, with
Windows SDK 10.0.26100.0 and D3DX 9.29.952.8. Critical binaries are hash-locked.
The game's linker generation and companion custom.exe corroborate this choice;
the game's complete compiler, SDK, CRT and flags are not globally proven.
Use the profile recorded for each source/unit in `config/match-units.toml`.

Compiler receipts record commands, profile, source/header hashes, target identity,
compiler identity and object hash. Canonical replay rejects absent or stale
receipts. The recorded compiler command must name the unit's source. The
source and every file in the compiler's include trace must match their recorded
hashes, regardless of file extension. Unrelated paths can change while receipts
remain valid. A new or removed path with the same case-insensitive basename as
a captured input invalidates the receipt because it can change include
resolution. Immutable receipts retain their original snapshots. Use
`replay-exact-units.py --list-stale-sources` to find affected providers locally.
The comparator supports ordinary x86 COFF.

## Strict comparison

Validation scope follows the user's affected-only requirement. An unchanged
reconstruction graph needs no replay for documentation, handoff or cleanup;
protected hashes and appropriate diff/link checks suffice. For reconstruction
changes, determine affected providers from captured include closures and
manifest dependencies, then verify only those units. Use individual unit commands
or explicit `--source` filters; do not run an unfiltered whole-graph replay as a
default. Reuse valid evidence for unchanged providers.

`compare-coff-function.py --unit NAME` compares the complete compiler
contribution. It checks COFF relocation offsets and types against the manifest
and verifies that DIR32 fields coincide with the locked PE's HIGHLOW fields.
For a same-section symbol, the COFF symbol's position must resolve to its
independently established anchor. This permits MSVC to renumber a local `$LN`
label. A `$SG` literal must have a COFF definition with matching bytes at its
anchored PE address. For adjacent COFF literals, the check includes their
payload and terminator. Other symbols require the recorded name. After
resolving the relocations with their COFF addends,
the comparison checks every code and owned data byte. Aux-less boundaries
use the next function or section end. Reconcile associated alignment and tables
with the function that owns them.

Positional diagnostics may exclude relocation fields or solve potential
destinations. Such results route investigation; they cannot supply canonical
anchors from the target field being compared. Folded aliases may be independently
verified, but the same physical bytes receive only one canonical unit/mapping.

## Acceptance boundaries

| Claim | Target-local evidence | Compiler/ABI evidence | Complete strict replay |
| --- | --- | --- | --- |
| Provisional role/name | Required | Optional | No |
| ABI-visible field/type | Required | Required | No |
| Source-present behavior | Required | Required | No |
| Canonical exact function | Required | Required | Required |
| Playable whole program | Runtime paths and ownership | Complete compile/link | Independent |

Authored origin, source presence, semantic acceptance, exactness, linkage and
runtime behavior remain separate. Historical portable fixtures corroborated
behavior only inside their documented domains; they did not prove native
resource or startup integration. That suite is retired (see
[retained tests](../tests/README.md)). Exact acceptance uses complete native
comparison, including original error paths and EH. Current results live in
[the handoff](RE_HANDOFF.md) and
[live progress report](PROGRESS.md).

No target byte arrays, assembly, arbitrary padding, inert locals, fake returns,
ABI lies, patched compilers or source-profile branches are permitted. TH095's
historical assembly exceptions do not transfer. Infrastructure tests use
synthetic fixtures. See [build/matching](BUILD_MATCHING.md),
[workflow](RE_WORKFLOW.md) and [semantic policy](SEMANTIC_RECONSTRUCTION.md).

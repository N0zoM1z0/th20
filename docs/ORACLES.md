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
receipts. Conservative freshness includes every maintained source/header and
probe: a shared-header edit currently requires the complete graph to be rebuilt.
Ordinary x86 COFF is supported; /GL and bigobj/LTCG are not.

## Strict comparison

`compare-coff-function.py --unit NAME` verifies the complete compiler contribution
and all relocation identities, offsets, types and addends. Independently
established DIR32/REL32 anchors are replayed, then every byte is compared.
Unknown, missing, extra or overlapping relocations fail. Aux-less boundaries use
the next actual function or section end, never a target-sized prefix. Retain
associated alignment/tables and reconcile their ownership explicitly.

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
runtime behavior remain separate. Portable O2/sanitizer fixtures corroborate
behavior inside their documented domains; they do not prove native resource or
startup integration. Current results live in [the handoff](RE_HANDOFF.md) and
[generated progress](PROGRESS.md), not historical batch counts.

No target byte arrays, assembly, arbitrary padding, inert locals, fake returns,
ABI lies, patched compilers or source-profile branches are permitted. TH095's
historical assembly exceptions do not transfer. Infrastructure tests use
synthetic fixtures. See [build/matching](BUILD_MATCHING.md),
[workflow](RE_WORKFLOW.md) and [semantic policy](SEMANTIC_RECONSTRUCTION.md).

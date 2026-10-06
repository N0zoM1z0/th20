# Independent oracles and acceptance

## Oracle A: exact target

The user-selected Japanese TH20 v1.00a **Steamless** executable is the sole
comparison target. `config/target.toml` pins its whole-file identity, PE
mapping and section hashes. The Steam-original backup is provenance evidence;
it is not interchangeable with decrypted comparison bytes. Neither may be
silently replaced by non-Steam retail, a trial, a localization or a later build.

Ghidra is a view of the target. Every wrapper call first verifies the local
file, then checks the database's SHA-256/MD5/module, actual database source-file
bytes and file size, image base, mapped PE image size and entry point, six
mapped samples and the SHA-256 of the complete mapped `.text` virtual extent.
Ghidra names, signatures and function extents remain provisional even after
identity attestation.

## Oracle B: compiler and ABI

The installed candidate compiler reports `19.44.35211 for x86` and linker
`14.44.35211.0`. Their binaries and compiler backends are locked by hash.
The game directly observes linker generation 14.44; its Rich header is absent.
The companion `custom.exe` corroborates compiler/linker build 35211. This
corroboration does not prove the game's exact compiler, SDK, CRT or flags.
Windows SDK 10.0.26100.0 and D3DX 9.29.952.8 are provisioned candidates.

Compiler probes record full commands, input hashes, included-header hashes,
profile, compiler identity and object hash. Canonical replay rejects missing or
stale receipts. Ordinary x86 COFF is supported; `/GL` and bigobj/LTCG are not.
Recover toolchain/profile differences with evidence rather than weakening gates.

## Exact comparison

The TH095 COFF comparator has been adapted for modern MSVC. `--unit` verifies
manifest target identity, fresh compilation, full contribution size and exact
relocation identities/offsets/types. It replays explicit DIR32 and REL32
anchors with real COFF addends, then compares **all** bytes. Unknown, missing,
extra or overlapping relocations fail closed. Modern aux-less functions use
the next real function boundary or section end; target-sized prefix slicing
is forbidden. Reconcile compiler padding/tables explicitly.

The positional diagnostic mode reports structural bytes separately from
relocation fields and may solve potential destinations as **diagnostics**.
Those solved fields are not independent evidence and must not be mechanically
promoted into the canonical relocation manifest.

## Acceptance matrix

| Claim | Target-local evidence | Compiler/ABI evidence | Complete exact replay |
| --- | --- | --- | --- |
| Provisional role/name | required | optional | no |
| ABI-visible field/type | required | required | no |
| Source-present behavior | required | required | no |
| Canonical exact function | required | required | required |
| Playable whole program | runtime paths + ownership | complete compile/link | independent |

Supporting oracles include runtime behavior, a portable compiler, official
API documentation, and adjacent games. None substitutes for target comparison.
Do not copy target bytes into source, use arbitrary padding/inert locals/fake
returns, invent ABI declarations, patch a compiler, or import TH095 assembly
exceptions. Infrastructure tests use synthetic fixtures, never game bytes.

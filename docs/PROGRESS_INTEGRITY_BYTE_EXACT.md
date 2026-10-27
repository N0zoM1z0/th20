# Complete ProgressMetadata integrity calculation (CORE/EXACT-165)

This investigation uses only the locked Japanese TH20 1.00a Steamless PE32,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native `ProgressMetadata::calculate_integrity` entry at **0x00463F20**
occupies an entire **134-byte** function. Earlier CORE089 experiments emitted
125 bytes and correctly withheld exactness; the earlier source declarations
and assumptions have now been independently tested rather than adopted.

## Native byte and ABI evidence

The complete native body acquires the actual process lock at slot 20 through a
`std::lock_guard<std::recursive_mutex>`, starts at Metadata+0x58, and sums
individual unsigned bytes up to, but not including, Metadata+0x1D0.
The running accumulator and both return temporaries are one byte wide, wrapping
modulo 256. The native exit returns its byte zero-extended in EAX. The independent
checksum-validation caller at 0x00464035 calls this entry and explicitly uses
`movzx ecx, al` at 0x0046403A before comparing against the stored checksum.
This establishes the genuine **uint8_t return contract**, correcting the old
uint32_t declaration; the original C++ source spelling remains inferred.

The target's starting address expression compiles through the actual
`&field_58[0]` array element, including its otherwise surprising compiler
`mov eax, 1; imul ecx, eax, 0` sequence. The loop compares the full addresses
with signed `jge` (0x7D), not the `jae` (0x73) emitted by the earlier raw
pointer comparison. An explicit signed-int32 address comparison retains this
native x86 behavior without inserting inert operations or artificial padding.
The loop body, byte accumulation, lock lifetime, security-cookie epilogue and
all generated code agree. This is native signed 32-bit address behavior, not an
unconditional claim about arbitrary host pointers or portable address ordering.

Six complete relocations bind to separately established targets:

| COFF role | Native address |
| --- | --- |
| Process security cookie | 0x005B25C0 |
| Process LockRegistry object | 0x005C0240 |
| LockRegistry::slot | 0x0040C310 |
| Recursive mutex lock_guard constructor | 0x0040B730 |
| Recursive mutex lock_guard destructor | 0x0040B900 |
| Security cookie check | 0x005429EE |

These exact names and destinations already occur in independently accepted
Worker, random and other canonical units. No destination was derived by solving
the compared relocation field. After replaying these roles, **all 134 bytes are
identical**. The genuine zero-argument x86 member and eight-bit return are
reconstructed in one maintained C++ function, not a copied decompiler body.

## Propagation and validation

The public header and ProgressIntegrity source change naturally propagates into
**eight** affected translation-unit objects and **22 previously accepted units**,
as derived from real compiler `/showIncludes` receipt closures. All eight objects
are cold-built serially from locked MSVC 19.44.35211 x86 into
`build/core164-canonical/`, without overwriting the previous products. The 22
existing full units and the new complete 134-byte unit strictly replay, including
the 161-byte `ProgressMetadata::update_integrity`. That caller changes only its
COFF relocation's decorated symbol from the old 32-bit return signature to the
now-correct byte-return signature at the already established 0x00463F20.
No extra compared extent is trimmed. The other 156 graph objects reuse verified
receipts and unchanged input closures.

The focused five progress test suites pass: real Metadata/Snapshot storage,
complete save/load/short-write protocol, parsing, Profile storage, and
SaveManager worker/lifetime behavior. This is O2/UBSan portable behavioral
corroboration, **not** a playable game or proof of original OS startup.
Private `.analysis/core164-progress-scope.json` retains protected old product
hashes and the exact affected closure. The diagnostic profiles and literal
native instructions stay ignored. CORE/EXACT-165 preserves all original
products and compares only the changed units.

## Open boundaries

Whole Enemy opcode dispatch at 0x48C010, the 1,649-byte Enemy deformation,
the 630-byte drop scatter producer, 1,036-byte archive compressor, unresolved
SaveManager construction/commit and complete native game linkage remain separate
work. Their semantic reconstructions are not credited by this new unit.

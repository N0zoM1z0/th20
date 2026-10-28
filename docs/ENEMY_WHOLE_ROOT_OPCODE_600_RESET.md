# CORE202: complete native opcode 600 queued-parameter reset in the whole Enemy root

The original 41,967-byte `EnemyState::execute_opcode` at `0x0048C010`
remains **machine-code nonexact**. CORE202 continues the same complete
source-draft root with the original opcode **600**, independently decoded
from the locked Japanese v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire opcode is a **403-byte / 90-instruction / 10-direct-call** primary
head at `0x00492434..0x004925C6`; its native SHA-256 is
`bc2525ef83d9d18087fdde23327b7492d1721851dd245e20f74dd05dd04a0223`.
The complete native opcode interval, all original call destinations, decoded
instruction heads and original case-path catalog were checked independently;
original instructions are saved at `.analysis/core202-native-op600.asm`, and
a machine-readable audit at `.analysis/core202-native-600-audit.json`.
The case is part of the 41,967-byte boss function, **not** an isolated
faux source function or new authored exact credit.

## Original native caller and real struct owners

The original calls are, in order: the genuine `EnemyState::integer_argument(0)`;
**CORE/EXACT-200's native-byte-exact 396-byte** `EnemyState::writable_shot`
(`0x00498B80`); standard two-pointer-pair helpers; the complete actual
`ShotParameters::ShotParameters` (`0x0047BD20`); the complete actual
`EtamaArgInf::EtamaArgInf` (`0x0047BB90`); the actual PMR-aware
`EtamaArgInf::operator=(EtamaArgInf&&)` (`0x0048BB00`); and the actual
`EtamaArgInf` destructor (`0x0047C450`).

The selected `EnemyQueuedRecord` is **not blanket-zeroed**. Instead, the
original 40-byte default `ShotParameters` temporary replaces only the
record's `parameters` at offset `+0x8`. A genuinely default-constructed
`EtamaArgInf` temporary then uses the actual move assignment to reset the
shared metadata value, with PMR vector lifetime and its **two default
BulletCommand elements**. The metadata's native default `sound` and
`alternate_sound` are **21 and 38**, not zero. The original record fields
reset afterward are exactly:

| Record offset | Native write |
| --- | --- |
| `+0x34` and `+0x38` | `vector_34.x` and `.y` to +0.0f |
| `+0x40`, `+0x44`, `+0x48` | All three `vector_40` components to +0.0f |
| `+0x30` | `field_30` to integer zero, last |

Critically, `record+0x3C`, **`vector_34.z`**, is **not touched** by the native
branch, including when its bits encode negative zero or NaN. The selected
shared pointer is preserved as a real typed owner while its metadata is
updated; any other shared alias remains isolated when the exact COW selector
must first clone. No other ECL operands are read after the queue index.

## Same entire-root implementation and validation

The current private natural-source whole-root candidate
`.analysis/core202-enemy-dispatch-candidate.cpp` adds original case 600
to all previously integrated branches, using real typed value construction,
move assignment and actual `EnemyState::writable_shot` through the already
accepted CORE201 adapter. The host `.analysis/core202-dispatch-host.cpp`
links **all 85 previous translation units**, including maintained
`src/EnemyQueuedSelection.cpp`, the exact 474-byte Laser creator and the
exact 75-byte registration function, unchanged.

The new `.analysis/core202-op600-host-cases.inc` passes **152 additional
whole-root cases**: **114 regular reset paths**, involving actual PMR
metadata destruction/reinitialization, 30 shared-owner deep COW clones,
24 forward-list extensions, real default metadata values and exact
record/parameter fields; **14 injected early/late exceptions**, confirming
owner/allocation mutation is appropriately visible before the first record
reset; and **24 cross-opcode sequences** that execute 700, 701, 600, and
701 again against the same actual owner. Tests check raw `vector_34.z` bits,
remaining record identity, unchanged nonqueue EnemyState bytes, complete
unchanged other queue records, default PMR vector element contents and
original ECL operand order. The only injected failure boundaries are
clearly private tests, not fabricated native behavior.

Both entire-root **85-TU** GCC13 `-O2 -Wall -Wextra -Werror` host variants
passed **43,125/43,125** scenarios: previous 42,973 plus 152. The first
uses UBSan, the second ASan+UBSan with leak detection and only unrelated
unlinked `WeaponStoneInfo` vptr instrumentation disabled. Build/run logs
are `.analysis/core202-dispatch-host.log` and
`.analysis/core202-dispatch-host-asan.log`. Original instruction audits,
four source/recipe hashes, both full host executables and their logs are
protected in `.analysis/core202-enemy-whole-root-proof.json`.
All historical CORE201/200/199/198 and earlier proof-bound original inputs,
compiler products and executable outputs remain intact and protected.

## Exactness scope and next priorities

The single complete-root candidate covers **135 effective opcode values /
103 original primary heads** (of 174). This remains *semantic* evidence,
**not** original 41,967-byte native machine-code exactness. No production
source/header/manifest changed, so CORE202 required **zero additional
native cold-build/replay units** and did **not** run a whole cold replay.
Conservative native exact totals stay **224 authored whole exact functions /
58,692 bytes / 1,010 canonical units**.

Next substantial work includes the complete original **593-byte native
opcode 601** at `0x00492803`: it calls the separately exact 305-byte
ensure-only `EnemyState::shared_shot` before handling record position and
original downstream player/launch functions at `0x0049C740` and
`0x00481780`, with nontrivial call ordering and actual owned parameters.
Those downstream callees must be independently verified; do not fabricate
their contracts from partial decompilation. Other large Enemy case heads,
original full-root switch/EH compiler partition and derived Laser factory
lifetime remain open.

# Enemy ECL opcode 619 — writable queued metadata radial offset

## Status and boundary

Opcode 619 is represented by natural C++ in src/EnemyStateQueuedParametersOpcode.cpp,
linked through the maintained EnemyState::execute_opcode root host, and covered
by native PE, locked-profile i386 COFF and ASan/UBSan checks. It is an inline
case fragment in the original 41,967-byte EnemyState::execute_opcode body at
0x0048C010, not a standalone native function or independently replayable unit.
The parent remains **NONEXACT** and receives no whole-parent byte credit.

Checkpoint subject: gpt-web: restore Enemy opcode 619 metadata radial offset.

## Locked native case

Target: resources/th20.exe, Japanese TH20 1.00a Steamless image,
SHA-256 a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897.

| Property | Native value |
| --- | --- |
| Selector index | 137 |
| Start | 0x00492CB9 |
| End (exclusive) | 0x00492D4D |
| Extent | 148 bytes |
| Decoded instructions | 35 |
| Direct E8 calls | 7 |
| Case SHA-256 | 0c19fd5ccbe0b7e7192ae19791933b960fc758a0eb39d10b62af1ed5fa84f5ca |

The ordered native call targets are:

1. 0x004AB080 — EnemyState::integer_argument(0)
2. 0x00498B80 — EnemyState::writable_shot
3. 0x0040B280 — pair move
4. 0x0048B180 — std::get<0>
5. 0x0040B280 — pair move
6. 0x0048B160 — std::get<1>
7. 0x004AAFB0 — EnemyState::float_argument(1)

## Recovered behavior and ordering

The source preserves the native sequence:

1. Read integer selector operand 0.
2. Call the real writable_shot selector. Shared metadata is cloned here.
3. Extract pair member 0, then pair member 1. The record pointer is deliberately
   retained as an unused local because the native get<0> call is observable
   in the original call map.
4. Read float operand 1 only after the COW operation and both pair extractions.
5. Store the float at ShotMetadata::field_00.

field_00 is consumed as a radial offset by the BulletEmitter and Laser
creation paths. The case therefore updates the queued metadata radial offset,
not the queued record's vector_34/vector_40 lanes.

The right-hand side of the assignment is evaluated after selector/COW and
pair extraction. If float operand 1 throws, the metadata COW clone remains
visible, but no field write occurs. The root test checks both the old shared
owner and the new queue owner, as well as preserved neighboring metadata and
record vectors.

## Production integration and verification

execute_enemy_queued_parameters_opcode now handles 619 alongside the
existing 700/701 branches. Its former false-returning root-test stub was
removed; the production helper is part of HOST_SOURCES and the locked
MSVC-compatible i386 COFF source list.

The maintained verifier checks the original selector/pointer-table entry,
148-byte case hash, all 35 instruction boundaries, seven ordered native call
targets, and the compiled COFF relocation order. The ASan/UBSan root test
exercises queue index 1, shared-owner COW before the float read, field_00
writeback, neighboring-field preservation, and the float-read exception
between COW and store.

This is source recovery for one inline case only. It does not establish an
independent function unit, strict exact-byte receipt, or whole-parent
completion. The 41,967-byte dispatcher remains **NONEXACT**; no full cold
replay was run.

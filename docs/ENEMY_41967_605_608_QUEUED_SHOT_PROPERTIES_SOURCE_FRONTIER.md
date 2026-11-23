# Enemy opcodes 605–608 — queued-shot property writes

**CORE/RECON-1264.** Four adjacent inline cases in the original 41,967-byte
`EnemyState::execute_opcode()` root now have natural C++ source in
`src/EnemyStateQueuedShotPropertyOpcode.cpp`, are routed by the production
root, and execute under the maintained ASan/UBSan root host. The original
root remains **NONEXACT**; these inline cases receive no standalone function
or whole-parent byte credit.

## Native PE evidence

The locked Japanese 1.00a PE selector table at `0x004966B8` maps opcodes
605/606/607/608 to compressed selector indexes 126/127/128/129. Their
original case bodies are contiguous at the following boundaries:

| Opcode | Selector | Native case range | Bytes | x86 instructions | Direct E8 calls | Native operation |
| ---: | ---: | --- | ---: | ---: | ---: | --- |
| 605 | 126 | `0x00492F1C..0x00492FD9` | 189 | 43 | 8 | shared record speed + speed step |
| 606 | 127 | `0x00492FD9..0x00493094` | 187 | 43 | 8 | shared record 16-bit count + rows |
| 607 | 128 | `0x00493094..0x00493128` | 148 | 35 | 7 | COW metadata 16-bit `field_38` |
| 608 | 129 | `0x00493128..0x004931DD` | 181 | 43 | 8 | COW metadata sound + alternate sound |

The four bodies total **705 bytes / 164 x86 instructions / 31 direct E8 calls**.
The maintained verifier checks each complete native case boundary, SHA-256,
selector, ordered direct-call destination list, and the actual 16-/32-bit
store offsets. The individual case-body SHA-256 values are:

- 605: `0a7faf5abeed95e7c015a8ad088b360f28e797938a69b3beaa0a136e74882c4d`
- 606: `d66c6891ed34af6ea7729ecd413c63103996da500054c60aac29daa2dd7eab76`
- 607: `bcff45aa2412959c2c134ee30b8447fee1c3a1d3a8053b1943bc4b9914f75224`
- 608: `9320ba2c32239e2058bd4a154de447a92c848c34bde1b13ed1911b9889ab7260`

## Reconstructed receiver and mutation rules

- **605:** read integer selector 0, resolve `EnemyState::shared_shot`, extract
  pair-first `EnemyQueuedRecord*`, then read float operands 1 and 2 and write
  `ShotParameters::speed` and `speed_step` (record offsets `+0x24/+0x28`).
- **606:** same ensure-only shared selector and pair-first record; read integer
  operands 1 and 2 in order, narrow each to signed 16-bit, then write
  `ShotParameters::count` and `rows` (record offsets `+0x2C/+0x2E`).
- **607:** read integer selector 0, call `writable_shot` before reading operand
  1, extract pair-second `ShotMetadata*`, narrow operand 1 to 16-bit, and write
  `ShotMetadata::field_38` at metadata offset `+0x38`.
- **608:** same writable selector and pair-second metadata receiver; read
  integer operands 1 and 2 in order and write `ShotMetadata::sound` and
  `alternate_sound` at offsets `+0x3C/+0x40`.

The pair-second distinction for 607/608 is important: these writes do **not**
target the adjacent `EnemyQueuedRecord` Vector3 lanes. The natural C++ helper
retains both pair extractions and the real shared/COW selectors.

## Root-host regression coverage

The maintained root host executes all four cases through
`EnemyState::execute_opcode()` and the production helper. It verifies:

- 605 float argument order, speed/speed-step writes, stable shared owner, and
  second-float exception after the first speed write;
- 606 integer argument order, 16-bit narrowing into count/rows, stable shared
  owner, and second-integer exception after the count write but before rows;
- 607 COW before the integer read, pair-second `field_38` update, 16-bit
  narrowing, preservation of `field_3A` and the original owner, and
  first-integer exception after COW but before the field write;
- 608 COW before both integer reads, sound/alternate-sound writes, and a
  second-integer exception that preserves the first sound write in the clone
  while leaving the original shared owner unchanged.

Only the actual metadata/record owners and allocator paths are used; no
false-returning test stub or synthetic byte sequence is involved. The
maintained verifier now executes **129 focused host source units** under
ASan/UBSan and compiles **62 locked-profile i386 COFF units**. No full cold
replay was run.

# CORE199: two large native Laser parameter branches in the whole Enemy boss

This checkpoint extends the *same complete 41,967-byte*
`EnemyState::execute_opcode` source-draft root at `0x0048C010`, against the
locked Japanese Steamless TH20 target (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
It adds two genuinely distinct **large native primary heads**, not stubbed
stand-alone leaf functions or arbitrarily shortened opcode fragments:

| Opcode | Original native interval (exclusive end) | Bytes | x86 instructions | Direct calls |
| --- | --- | ---: | ---: | ---: |
| **711** | `0x00494CE7..0x00494F52` | **619** | 141 | 15 |
| **713** | `0x00494A84..0x00494CE7` | **611** | 137 | 16 |

Both intervals were decoded independently from the locked PE. Their original
instruction heads, native branch bytes, 15/16 call targets, exit jumps and
bounds agree with the independently generated complete native case-path
catalog. The local disassembly and native SHA-256 evidence reside in
`.analysis/core199-native-op711.asm`,
`.analysis/core199-native-op713.asm`, and
`.analysis/core199-native-711-713-audit.json`.
No native bytes, compiler database or target PE have been patched.

## Real owners and original data flow

Original opcode 711 constructs `LaserType2Parameters` through the native
constructor at `0x0048B650`; opcode 713 constructs
`LaserType3Parameters` through `0x0048B5B0`. Both read the original ECL
`integer_argument(0)` and call the **396-byte writable queued metadata
selector** `0x00498B80`, which returns a concrete record/metadata
pointer pair. They then copy the genuine `std::pmr::vector<BulletCommand>`
into each parameter object's independently owned PMR vector using native
`0x0047C570`—not a shallow borrowed pointer. The selector's original
compiler/EH identity remains **nonexact**, although its existing natural
COW candidate and ownership behavior are tested independently.

Both cases use a **strictly greater than 0.9f** comparison of the actual
`EnemyQueuedRecord::vector_40.z` against native 0x3F666666. The greater
path adds `record.vector_40 + record.vector_34` and forces output Z to
zero. Zero, negative, threshold-equal, NaN/unordered and other non-greater
values instead use `EnemyState::position_ref() + record.vector_34`, keeping
its full Z component. Position addition invokes the real `Vector3` owner.

The two parameter layouts differ. Native 711 copies shot type, color and
normalized angle, speed and metadata width; it also copies the metadata's
`field_24` count, `sound`, `alternate_sound` and radial offset, ORs **bit 0**
into the real `LaserType2Flags` word, and stores the current view index. It
then calls the genuine `Context::laser_controller` getter and the already
machine-code-exact **474-byte** `LaserController::create_laser` with type 2.
Only **integer operand 0** is read.

Native 713 instead fills the *actual* `LaserType3Parameters` color/field
word, angle, metadata command flag, width, selected shot position's Z and
radial offset. Only **after** those writes does it read
`integer_argument(1)` as the Laser handle. That argument may retarget the
live Enemy `Context` before the subsequent owner getter, and the returned
handle may affect the final parameter. It then calls the exact 474-byte
creator with type **3**. The original native local for an optional result
pointer is initialized to null; no output publication was inferred.
The complete original datatype and field-offset audit is recorded in the
private CORE199 proof; the surrounding real typed constructors are already
maintained in `src/LaserParameters.cpp`.

## Single whole-root host integration and validation

The active source-draft root is
`.analysis/core199-enemy-dispatch-candidate.cpp`, with complete host
`.analysis/core199-dispatch-host.cpp` and new test fixture
`.analysis/core199-laser-type2-type3-host-cases.inc`.
The new **319** scenarios include:

- 144 original type-2 and 144 original type-3 parameter/factory caller
  observations, checking every relevant genuine field, the native 0.9f
  threshold and raw position bits, real deep-copy command storage, and
  original pointer/receiver identity.
- 288 genuine PMR command-vector deep copies, 96 shared-owner COW events,
  48 late Context retargets, and **15 staged VM/creator exceptions** with
  full earlier state and shared-owner isolation checks.
- **16** original 711/713 calls that execute the *actual separately accepted*
  474-byte production `LaserController::create_laser` rather than a fake
  creator callback. **Eight** of those complete the actual separately exact
  75-byte `LaserController::register_laser` intrusive-list insertion. Their
  downstream concrete 92-byte native allocation and derived virtual init
  bodies remain honest test-fixture boundaries and are **not** credited as
  native-exact production implementations.

All previous **42,424** scenarios remain passing, giving
**42,743/42,743** complete-host cases in *both* full 84-TU GCC13 `-O2
-Wall -Wextra -Werror` UBSan and ASan+UBSan configurations. Only `vptr`
instrumentation is disabled in the latter due to unlinked unrelated
`WeaponStoneInfo` RTTI; leak detection is enabled. Full logs are
`.analysis/core199-dispatch-host.log` and
`.analysis/core199-dispatch-host-asan.log`, and the protected SHA-bound
current inputs/binaries/original byte audit are recorded in
`.analysis/core199-enemy-whole-root-proof.json`. Historical CORE198,
CORE197 (concrete Laser constructors), CORE196 and prior evidence remains
preserved, with no cold replay or cleanup of earlier private outputs.

## Exactness and next actions

The one entire Enemy source draft now covers **134 effective opcode values
and 102 original primary heads** of 174. That is semantic coverage, **not
x86 machine-code equivalence** for the original 41,967-byte boss. CORE199
changed **no production source/header/manifest or compiler inputs**, so
its canonical affected native cold replay scope is **zero**. No full or
unrelated native cold replay was run. The conservative accepted exact
ledger remains **222 authored whole functions / 57,991 bytes / 1,008
canonical units**, including the earlier accepted 474-byte Laser creator
and its 75-byte registration callee.

Next priorities include the original 396-byte shared metadata COW selector,
complete derived Laser classes/four concrete 92-byte allocators, remaining
large Enemy opcode heads, and whole-root MSVC EH/jump partition. Do not
claim exactness merely because this GCC sanitizer host passes, and do not
turn a partial opcode into a separate fake root function.

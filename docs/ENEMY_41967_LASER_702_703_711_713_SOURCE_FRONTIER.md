# CORE/RECON-1143/1144 — natural-C++ source fragments for Enemy ECL Laser opcodes 702, 703, 711 and 713

The maintained source now contains `execute_enemy_laser_opcode(EnemyState&, opcode)` in `src/EnemyStateLaserOpcode.cpp` for four original large Enemy ECL Laser branches. This helper is a source-organization fragment for eventual integration into `EnemyState::execute_opcode()`; it is **not** claimed to be a separate original native function, and it does not define or replace the 41,967-byte parent.

## Original native branch proof

The immutable Japanese TH20 1.00a Steamless PE (SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`) has the following original case entries:

| Opcode | Original case head | Reachable x86 heads | Direct E8 count | Constructor E8 | Destructor E8 |
| ---: | --- | ---: | ---: | --- | --- |
| 702 | `0x004944C7` | 153 | 15 | `0x004944CD -> 0x0047C130` LaserType0 | `0x00494766 -> 0x0047C4B0` LaserType0 |
| 703 | `0x00494771` | 176 | 16 | `0x00494777 -> 0x0047C030` LaserType1 | `0x00494A79 -> 0x0047C490` LaserType1 |
| 711 | `0x00494CE7` | 141 | 15 | `0x00494CED -> 0x0048B650` LaserType2 | `0x00494F47 -> 0x0048B8B0` LaserType2 |
| 713 | `0x00494A84` | 137 | 16 | `0x00494A8A -> 0x0048B5B0` LaserType3 | `0x00494CDC -> 0x0048B890` LaserType3 |

The original native verifier independently confirms the whole 41,967B/8,896-instruction Enemy parent, its 704-byte compact opcode selector, all 174 relocatable case pointers, and all four bounded case CFGs. The cases reach the common parent epilogue without unresolved branch edges. The parent now has a partial C++ root entry (CORE/RECON-1196), but remains incomplete and NONEXACT.

## Maintained C++ behavior

All four branches use the real `EnemyState::writable_shot()` 396B copy-on-write selector, returning the actual `EnemyQueuedRecord*` and `ShotMetadata*` pair. They copy the record's PMR `BulletCommand` vector into a real Laser parameter object, use the record/metadata fields to construct the original position, angle, speed/length/width, duration, sound, flags and view index, then call the actual Context-owned `LaserController::create_laser()`.

- Opcode 702 creates `LaserType0Parameters`, preserves the 0.9 position/Z gate, normalizes the queued shot angle, copies the type-0 sound fields and ORs the native low flag bit `1`, then invokes Laser type `0`.
- Opcode 703 creates `LaserType1Parameters`, preserves the same position/Z gate, copies all four duration values, sound/alternate-sound, type/color and the native low flag bit `2`, then reads VM integer operand `1` late into the real `handle` field before invoking Laser type `1`.
- Opcode 711 creates `LaserType2Parameters`, copies the queued shot type/color/angle/speed, maps `EtamaArgInf::field_24` to the Laser count, copies metadata width/radial offset/sound fields, initializes the flags to the native constructor-zeroed value then ORs bit `1`, and invokes Laser type `2`.
- Opcode 713 creates `LaserType3Parameters`, copies the queued shot position-Z/color/angle and metadata field values, reads the second VM integer into the actual handle, and invokes Laser type `3`.

The helper uses the already whole-exact LaserType0/1/2/3 constructors/destructors, writable queued-record selector, PMR vector copy assignment, Context LaserController accessor and 474B Laser factory. No private `select_queued_metadata_boundary` or `create_native_laser_boundary` remains in the maintained source. No assembly, manual padding, or invented original function body is used.

## Scoped verification and exactness limits

`src/EnemyStateLaserOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. Its relocations reference all four real typed parameter constructors/destructors, `EnemyState::writable_shot`, the PMR BulletCommand copy, `Context::laser_controller`, and `LaserController::create_laser`. The original native case audit was rerun with `.analysis/core716-enemy-41967-Laser-opcode-native-case-CFG.py`; it independently confirms 702's 153/15, 703's 176/16, 711's 141/15 and 713's 137/16 original instruction/E8 counts and each constructor/destructor site.

This helper does not receive a `config/functions.csv` original-function mapping because the original 702/703/711/713 bodies are inline regions inside `EnemyState::execute_opcode()`, not independent native functions. The 41,967B parent still has no maintained complete body, no canonical whole-parent unit and zero parent byte credit. Run `scripts/verify-enemy-laser-opcode-source.py` for the maintained-source/original-CFG cross-check. No full cold replay was performed.

Next work: continue through other large native opcode clusters (especially the remaining Laser and queued Bullet-command branches), then integrate the supported opcode fragments into a natural-C++ parent dispatcher without treating this helper as the complete 41,967B function.

## Maintained root-host execution closure — CORE/RECON-1247

The maintained root host previously replaced execute_enemy_laser_opcode with
a false-returning stub. CORE/RECON-1247 removes that stub and links the real
EnemyStateLaserOpcode.cpp helper together with LaserParameters.cpp. The four
large production branches now execute under the maintained ASan/UBSan
EnemyState::execute_opcode host.

The host uses the real LaserType0/1/2/3 parameter constructors and destructors,
the real LaserController constructor/reset and Context lookup, the real
EnemyState::writable_shot() selector, PMR BulletCommand vector copies and
normalization. The create_laser method is an explicit capture-only test
boundary: it snapshots the typed temporary before its real destructor runs.
The separate production LaserFactory.cpp remains independently strict exact
at 474/474 body bytes (492/492 compared bytes).

The four branch tests cover both sides of the native 0.9 Z-position gate:
702 and 711 use vector_40 + vector_34 with Z cleared, while 703 and 713 use
the EnemyState position fallback. They verify all four parameter layouts,
flags, type/color, lengths, widths, speeds, duration fields, sounds, view
index and copied PMR command vectors. Opcode 703 additionally triggers real
writable-shot COW; opcodes 703 and 713 read handle operand 1 late, retarget
Context during that read, and prove the final factory receives the newly
selected LaserController.

The maintained root verifier now runs verify-enemy-laser-opcode-source.py
itself and checks the original bounded CFG counts: 702 **153/15**, 703
**176/16**, 711 **141/15**, 713 **137/16** (instruction heads / direct E8).
Together these inline branches cover **2,699 native bytes, 607 instruction
heads and 62 original E8 calls**. It also checks the natural-C++ helper's
**47 ordered COFF relocations**, including all four real parameter
constructor/destructor pairs, writable-shot selection, PMR vector copy,
position reads, angle normalization, late integer reads, Context lookup and
factory handoff.

Affected-only strict dependency replays passed LaserParameters.cpp **12/12**
(all four parameter ctor/dtor pairs, LaserController ctor, selector and
reset) and LaserFactory.cpp **1/1** (474/474). The maintained root verifier
compiles **31** locked i386 COFF source units and its ASan/UBSan host executes
the four production case helpers. The factory method is deliberately captured
at the host boundary; this is not a claim that the native game Laser allocation
graph is fully executed by the test.

These are inline case restorations only. The 41,967-byte Enemy dispatcher
remains NONEXACT and receives no whole-parent byte credit. No full cold replay,
assembly, NOP or padding was used.
